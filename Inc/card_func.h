#ifndef CARD_FUNC_H
#define CARD_FUNC_H

#include "main.h"

/**
 * @brief 为玩家发放新的扑克牌
 *
 * @param pokers 存储玩家扑克牌的数组
 */
void new_card(Poker **pokers);

/**
 * @brief 判断扑克牌是否存在重复
 *
 * @param pokers 扑克牌数组
 * @param pokers_all 扑克牌使用情况数组
 * @return true 如果存在重复牌
 * @return false 如果不存在重复牌
 */
bool is_duplicate(Poker pokers, bool **pokers_all);

/**
 * @brief 分析扑克牌
 *
 * @param poker 扑克牌数组
 * @param statistic 统计结果数组
 */
void card_analyze(Poker *poker, uint64_t **statistic);

#endif
