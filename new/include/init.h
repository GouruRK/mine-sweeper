/**
 * @file init.h
 * @author Laborde Quentin & Kies Remy
 * @brief
 * @date 01-08-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __INIT_INIT__
#define __INIT_INIT__

#include "struct.h"

Game init_game(void);
Cell** init_board_empty(int width, int height);
Cell** init_board_full(int width, int height);
void free_board(Cell** tab, int line);

#endif