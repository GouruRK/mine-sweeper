/**
 * @file tool.h
 * @author Laborde Quentin & Kies Remy
 * @brief
 * @date 02-08-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __INIT_TOOL__
#define __INIT_TOOL__

#include "struct.h"

void print_board(Game g);
void print_game(Game g);
int random_coord(int max);
void resize_game(Game* g);

#endif