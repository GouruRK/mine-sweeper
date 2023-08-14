/**
 * @file game.h
 * @author Laborde Quentin & Kies Remy
 * @brief
 * @date 01-08-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __INIT_GAME__
#define __INIT_GAME__

#include "struct.h"

int is_in_board(int width, int height, int x, int y);
int nb_mines(Game* g, int x, int y);
int break_cell(Game* g, int x, int y);
void flag_cell(Game* g, int x, int y);
int victory(Game* g);
int defeat(Game* g);
void extend_undiscovered(Game* g, int x, int y);

#endif