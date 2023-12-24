#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <stdbool.h>

#ifndef __linux__
#include "windows.h"
#else
#include "unistd.h"
#endif

typedef struct
{
    uint8_t suit;
    uint8_t rank;
} Poker;

#endif