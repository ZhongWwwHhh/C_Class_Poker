#include "card_func.h"

void new_card(Poker **pokers)
{
    bool *pokers_all;
    pokers_all = (bool *)malloc(sizeof(bool) * 52);
    for (uint8_t i = 0; i < 52; i++)
    {
        pokers_all[i] = false;
    }

    for (uint8_t i = 0; i < 5; i++)
    {
        do
        {
            (*pokers)[i].suit = rand() % 4;
            (*pokers)[i].rank = rand() % 13;
        } while (is_duplicate((*pokers)[i], &pokers_all));
    }
    free(pokers_all);

    // Sort the cards by rank and then by suit
    for (uint8_t i = 0; i < 4; i++)
    {
        for (uint8_t j = 0; j < 4 - i; j++)
        {
            if ((*pokers)[j].rank > (*pokers)[j + 1].rank)
            {
                Poker temp = (*pokers)[j];
                (*pokers)[j] = (*pokers)[j + 1];
                (*pokers)[j + 1] = temp;
            }
            else if ((*pokers)[j].rank == (*pokers)[j + 1].rank && (*pokers)[j].suit > (*pokers)[j + 1].suit)
            {
                Poker temp = (*pokers)[j];
                (*pokers)[j] = (*pokers)[j + 1];
                (*pokers)[j + 1] = temp;
            }
        }
    }
}

bool is_duplicate(Poker pokers, bool **pokers_all)
{

    uint8_t hash = pokers.suit * 13 + pokers.rank;
    if ((*pokers_all)[hash])
    {
        return true;
    }
    (*pokers_all)[hash] = true;
    return false;
}

void card_analyze(Poker *pokers, uint64_t **statistic)
{
    /**
     * 同花顺 flush（5 张点数连续、花色相同的牌）
     * 顺子 straight（5 张点数连续、花色不同的牌）
     * 四炸 four（有 4 张点数相同、花色不同的牌）
     * 三拖二 full_house（5 张牌中有 3 张点数相同和 1 个对子）
     * 三炸 three（3 张点数相同、花色不同的牌）
     * 两对 two_pairs（有 2 个对子）
     * 一对 pair（有 1 个对子）
     */

    // printf("%u %u %u %u %u\n", (unsigned int)pokers[0].rank, (unsigned int)pokers[1].rank, (unsigned int)pokers[2].rank, (unsigned int)pokers[3].rank, (unsigned int)pokers[4].rank);

    if (pokers[0].rank + 1 == pokers[1].rank && pokers[1].rank + 1 == pokers[2].rank && pokers[2].rank + 1 == pokers[3].rank && pokers[3].rank + 1 == pokers[4].rank)
    {
        // 顺
        if (pokers[0].suit == pokers[1].suit && pokers[0].suit == pokers[2].suit && pokers[0].suit == pokers[3].suit && pokers[0].suit == pokers[4].suit)
        {
            // 同花顺
            (*statistic)[0]++;
        }
        else
        {
            // 顺子
            (*statistic)[1]++;
        }
    }
    else if (pokers[0].rank == pokers[3].rank || pokers[1].rank == pokers[4].rank)
    {
        // 四炸
        (*statistic)[2]++;
    }
    else if (pokers[0].rank == pokers[1].rank && pokers[2].rank == pokers[4].rank || pokers[3].rank == pokers[4].rank && pokers[0].rank == pokers[2].rank)
    {
        // 三拖二
        (*statistic)[3]++;
    }
    else if (pokers[0].rank == pokers[2].rank || pokers[1].rank == pokers[3].rank || pokers[2].rank == pokers[4].rank)
    {
        // 三炸
        (*statistic)[4]++;
    }
    else if (pokers[0].rank == pokers[1].rank && pokers[2].rank == pokers[3].rank || pokers[0].rank == pokers[1].rank && pokers[3].rank == pokers[4].rank || pokers[1].rank == pokers[2].rank && pokers[3].rank == pokers[4].rank)
    {
        // 两对
        (*statistic)[5]++;
    }
    else if (pokers[0].rank == pokers[1].rank || pokers[1].rank == pokers[2].rank || pokers[2].rank == pokers[3].rank || pokers[3].rank == pokers[4].rank)
    {
        // 一对
        (*statistic)[6]++;
    }
}
