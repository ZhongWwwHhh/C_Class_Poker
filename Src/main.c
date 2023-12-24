#include "main.h"
#include "card_func.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "zh_CN.UTF-8");

    // get loop times from arg
    uint64_t loop_times = -1;
    if (argc < 2)
    {
        printf("Please provide the loop times as an argument.\n");
        return 0;
    }
    loop_times = strtoull(argv[1], NULL, 10);

    // init rand
#ifndef __linux__
    uint16_t PID = GetCurrentProcessId(); // 获取当前进程的ID（仅适用于Windows平台）
#else
    uint16_t PID = getpid(); // 获取当前进程的ID（仅适用于Linux平台）
#endif

    /**
     * 使用时间和进程ID作为随机数种子
     *
     * 在使用随机数时，为了增加随机性，通常会使用一个种子来初始化随机数生成器。
     * 使用时间和进程ID作为种子可以确保每次程序运行时都会得到不同的随机数序列。
     * 如果只使用时间作为种子，当程序在同一秒内多次运行时，可能会得到相同的随机数序列。
     * 通过添加进程ID作为种子的一部分，可以进一步增加随机性，确保每次运行都有不同的种子。
     * 这样可以提高随机数的质量和随机性，使得生成的随机数更加均匀和随机。
     */
    srand((unsigned)time(NULL) + PID);

    // init statistic
    /**
     * 同花顺 flush（5 张点数连续、花色相同的牌）
     * 顺子 straight（5 张点数连续、花色不同的牌）
     * 四炸 four（有 4 张点数相同、花色不同的牌）
     * 三拖二 full_house（5 张牌中有 3 张点数相同和 1 个对子）
     * 三炸 three（3 张点数相同、花色不同的牌）
     * 两对 two_pairs（有 2 个对子）
     * 一对 pair（有 1 个对子）
     */
    uint64_t *statistic;
    statistic = (uint64_t *)malloc(sizeof(uint64_t) * 7);
    for (uint8_t i = 0; i < 7; i++)
    {
        statistic[i] = 0;
    }

    // init pokers
    Poker *pokers;
    pokers = (Poker *)malloc(sizeof(Poker) * 5);

    for (uint64_t i = 0; i < loop_times; i++)
    {
        new_card(&pokers);
        card_analyze(pokers, &statistic);

        if (0 == i % 1000000)
        {
            printf("%%%6.3f\n", ((float)i / (float)loop_times) * 100);
            fflush(stdout);
        }
    }

    const char *patterns[] = {"同花顺", "顺子", "四炸", "三拖二", "三炸", "两对", "一对"};

    for (uint8_t i = 0; i < 7; i++)
    {
        printf("%s: %lld次\n", patterns[i], statistic[i]);
    }

    free(pokers);

    return 0;
}