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

/**
 * @brief Tells is the coords are in the grids.
 *
 * @param width width of the board
 * @param height height of the board
 * @param x width of the cell
 * @param y height of the cell
 * @return 0 if the cell is out of the grid
 *         1 if the cell is in the grid
 */
int is_in_board(int width, int height, int x, int y);

/**
 * @brief Return the number of mines in the nieghborhood
 *        of the given cell.
 *
 * @param g Actual game status
 * @param x width of the cell
 * @param y height of the cell
 * @return number the mines
 */
int nb_mines(Game* g, int x, int y);

/**
 * @brief Break the given cell and retrun if the user explose.
 *
 * @param g Actual game status
 * @param x width of the cell
 * @param y height of the cell
 * @return 0 the user break a normal cell.
 *         1 the user break a mine.
 */
int break_cell(Game* g, int x, int y);

/**
 * @brief Place or remove a flag on the given cell.
 *
 * @param g Actual game status
 * @param x width of the cell
 * @param y height of the cell
 */
void flag_cell(Game* g, int x, int y);

/**
 * @brief Tells if the user win the game.
 * (all cells discovered or mine) or (all mine have a flag on it)
 *
 * @param g Actual game status
 * @return 1 user win
 *         0 game not finnished
 */
int victory(Game* g);

/**
 * @brief Tells if the user has explosed.
 *
 * @param g Actual game status
 * @return 0 the user can play
 *         1 the user has explosed, end of the game
 */
int defeat(Game* g);

/**
 * @brief If the case has no mine in is neighborhood extend to other
 *        cell until they got a mine is her neighborhood.
 *
 * @param g Actual game status
 * @param x width of the cell
 * @param y height of the cell
 * @param func_graph function who draw the cell when discovered
 */
void extend_undiscovered(Game* g, int x, int y, void (*func_graph)(int, int, int, int));

/**
 * @brief Return the number of mine without flag on it.
 *
 * @param g Actual game status
 * @return Number of mine without flag on it
 */
int mine_left(Game* g);
#endif