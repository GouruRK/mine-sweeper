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
 * @param data set to '1' whenever the user close the window
 */
void exit_function(void* data);

/**
 * @brief Initialises all functions needed before the game.
 *        (prompt, window, 1st board)
 *
 * @param stop varaible used to exit libMLV's window
 * @param g actual game status
 */
void init_window_mlv(int* stop, Game g);

/**
 * @brief Draws one undiscorved cell.
 *
 * @param x cell abscissa
 * @param y cell ordinate
 * @param cell_size cell dimension
 */
void draw_undiscovered(int x, int y, int cell_size);

/**
 * @brief Draws one discorved cell with a number on it.
 *
 * @param x cell abscissa
 * @param y cell ordinate
 * @param cell_size cell dimension
 * @param val number to draw (1 <= val 8)
 */
void draw_discovered(int x, int y, int cell_size, int val);

/**
 * @brief Draws a flag on a cell.
 *
 * @param x cell abscissa
 * @param y cell ordinate
 * @param cell_size cell dimension
 */
void draw_flag(int x, int y, int cell_size);

/**
 * @brief Draws the number of mines on which there is no flag.
 *
 * @param nbmine number of mine left.
 */
void draw_nbmine(int nbmine);

/**
 * @brief Draws the save button.
 *
 */
void draw_save(void);

/**
 * @brief Draws all the header's componentes :
 *        save button, number of mine left.
 *
 * @param nbmine
 */
void draw_header(int nbmine);

/**
 * @brief Draws a mine at the end of the game.
 *
 * @param x cell abscissa
 * @param y cell ordinate
 * @param cell_size cell dimension
 * @param explosed 0 = safe / 1 explosion
 */
void draw_mine(int x, int y, int cell_size, int explosed);

/**
 * @brief Draws the end phase of the game.
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
