import subprocess
import multiprocessing
import time
import os
import sys


def get_test_count():
    while True:
        try:
            test_count = int(input("Enter the test count: "))
            if test_count <= 0:
                print("Test count must be a positive integer.")
            else:
                return test_count
        except ValueError:
            print("Invalid input. Please enter a valid integer.")


def process_result(result, total_count):
    lines = result.split("\n")
    for line in lines:
        if line.startswith("%"):
            continue
        elif line.startswith("同花顺"):
            count = line.split(":")[1].replace("次", "").strip()
            total_count[0] += int(count)
        elif line.startswith("顺子"):
            count = line.split(":")[1].replace("次", "").strip()
            total_count[1] += int(count)
        elif line.startswith("四炸"):
            count = line.split(":")[1].replace("次", "").strip()
            total_count[2] += int(count)
        elif line.startswith("三拖二"):
            count = line.split(":")[1].replace("次", "").strip()
            total_count[3] += int(count)
        elif line.startswith("三炸"):
            count = line.split(":")[1].replace("次", "").strip()
            total_count[4] += int(count)
        elif line.startswith("两对"):
            count = line.split(":")[1].replace("次", "").strip()
            total_count[5] += int(count)
        elif line.startswith("一对"):
            count = line.split(":")[1].replace("次", "").strip()
            total_count[6] += int(count)
    return total_count


def print_progress(progress_values):
    lowest_progress = min(progress_values)
    print("Progress: {}%".format(lowest_progress))


poker_exe_path = "../build/Poker.exe"
if not os.path.exists(poker_exe_path):
    print("Error: {} does not exist.".format(poker_exe_path))
    input('Press Enter to exit...')
    sys.exit(1)

test_count = get_test_count()

# Number of processes to use
num_processes = min(multiprocessing.cpu_count(), test_count)

print("Using {} processes".format(num_processes))

# Calculate the number of processes and the remainder
num_processes = min(multiprocessing.cpu_count(), test_count)
remainder = test_count % num_processes

# Create a list to store the subprocesses
processes = []

# Launch the subprocesses
for i in range(num_processes):
    # Calculate the number of tests for each process
    tests_per_process = test_count // num_processes
    if i == num_processes - 1:
        # Add the remainder to the last process
        tests_per_process += remainder

    # Create the command to run the subprocess
    command = [poker_exe_path, str(tests_per_process)]

    # Launch the subprocess using subprocess.Popen
    process = subprocess.Popen(
        command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    processes.append(process)

# Process the results
total_count = [0] * 7
progress_values = []
while any(processes):
    for i, process in enumerate(processes):
        if process is not None and process.poll() is not None:
            result = process.communicate()[0].decode()
            total_count = process_result(result, total_count)
            processes[i] = None
        elif process is not None:
            progress = process.stdout.readline().decode().strip()
            if progress.startswith("%"):
                progress_values.append(float(progress[1:]))
        else:
            continue
    if progress_values:
        print_progress(progress_values)
        progress_values = []
    time.sleep(0.1)
print("Progress: 100.0%")

# Print the total count
print("情况  \t                次数\t          概率")
print("同花顺\t{:20}\t{:13.10f}%".format(
    total_count[0], total_count[0] / test_count * 100))
print("顺子  \t{:20}\t{:13.10f}%".format(
    total_count[1], total_count[1] / test_count * 100))
print("四炸  \t{:20}\t{:13.10f}%".format(
    total_count[2], total_count[2] / test_count * 100))
print("三拖二\t{:20}\t{:13.10f}%".format(
    total_count[3], total_count[3] / test_count * 100))
print("三炸  \t{:20}\t{:13.10f}%".format(
    total_count[4], total_count[4] / test_count * 100))
print("两对  \t{:20}\t{:13.10f}%".format(
    total_count[5], total_count[5] / test_count * 100))
print("一对  \t{:20}\t{:13.10f}%".format(
    total_count[6], total_count[6] / test_count * 100))

input('Press Enter to exit...')
sys.exit(0)
