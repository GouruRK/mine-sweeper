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

/**
 * @brief Registers the callback function for libMLV
 *        when the window is closed.
 *
 * @param data
 */
void exit_function(void* data);

/**
 * @brief Initialises all functions needed before the game.
 *        (prompt, window, 1st board)
 *
 * @param stop varaible used to exit windows libMLV
 * @param g actual game status
 */
void init_window_mlv(int* stop, Game g);

/**
 * @brief Draws one undiscorved cell.
 *
 * @param x cell width
 * @param y cell height
 * @param cell_size
 */
void draw_undiscovered(int x, int y, int cell_size);

/**
 * @brief Draws one discorved cell with a number on it.
 *
 * @param x cell width
 * @param y cell height
 * @param cell_size
 * @param val number to draw (1 <= val 8)
 */
void draw_discovered(int x, int y, int cell_size, int val);

/**
 * @brief
 *
 * @param x cell width
 * @param y cell height
 * @param cell_size
 */
void draw_flag(int x, int y, int cell_size);

/**
 * @brief Draw the number of mines on which there is no flag.
 *
 * @param nbmine number of mine left.
 */
void draw_nbmine(int nbmine);

/**
 * @brief Draws save button.
 *
 */
void draw_save(void);

/**
 * @brief Draw the all header.
 *        (save button, number of mine left)
 *
 * @param nbmine
 */
void draw_header(int nbmine);

/**
 * @brief Draw a mine at the end of the game.
 *
 * @param x cell width
 * @param y cell height
 * @param cell_size
 * @param explosed 0 = safe / 1 explosion
 */
void draw_mine(int x, int y, int cell_size, int explosed);

/**
 * @brief Draws the end pahse of the game.
 *        (draw all mines)
 *
 * @param g Final game status
 */
void draw_end_game(Game g);

/**
 * @brief Draws all the game.
 *        (header, board)
 *
 * @param g
 */
void draw_game(Game g);

#endif