/**
 * @file graph.h
 * @author Laborde Quentin & Kies Remy
 * @brief
 * @date 01-08-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __INIT_GRAPH__
#define __INIT_GRAPH__

#include "struct.h"

void exit_function(void* data);
void init_window_mlv(int* stop, Game g);
void draw_undiscovered(int x, int y, int cell_size);
void draw_flag(int x, int y, int cell_size);
void draw_discovered(int x, int y, int cell_size, int val);
void draw_nbmine(int nbmine);
void draw_save(void);
void draw_header(int nbmine);
void draw_mine(int x, int y, int cell_size, int explosed);
void draw_end_game(Game g);

void draw_game(Game g);

#endif