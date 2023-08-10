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

void exit_function(void* data);
void draw_undiscorvered(int x, int y, int cell_size);
void draw_flag(int x, int y, int cell_size);
void draw_discovered(int x, int y, int cell_size, int val);

#endif