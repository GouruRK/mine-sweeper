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
 * @brief Check if the cell at coordinates (`x`, `y`) are in the board of given dimensions.
 *
 * @param width width of the board
 * @param height height of the board
 * @param x cell abscissa
 * @param y cell ordinate
 * @return '0' if the cell is out of the board
 *         '1' if the cell is in the board
 */
int is_in_board(int width, int height, int x, int y);

/**
 * @brief Return the number of mines in the neighborhood
 *        of the given cell at coordinates (`x`, `y`).
 *
 * @param g Current game status
 * @param x cell abscissa
 * @param y cell ordinate
 * @return number the mines
 */
int nb_mines(Game* g, int x, int y);

/**
 * @brief Break the given cell at coordinates (`x`, `y`) and retrun if the user discovered a mine.
 *
 * @param g Current game status
 * @param x cell abscissa
 * @param y cell ordinate
 * @return '0' the user break a normal cell.
 *         '1' the user break a mine.
 */
int break_cell(Game* g, int x, int y);

/**
 * @brief Place or remove a flag on the given cell at coordinates (`x`, `y`).
 *
 * @param g Current game status
 * @param x cell abscissa 
 * @param y cell ordinate
 */
void flag_cell(Game* g, int x, int y);

/**
 * @brief Check if the user win the game.
 *        The winning conditions are :
 *          - all cells are discovered or mine,
 *          - all mines have a flag on them and flag counter is the total number of mines.
 *
 * @param g Current game status
 * @return '1' user win
 *         '0' game not finnished
 */
int victory(Game* g);

/**
 * @brief Check of the usuer loose the game.
 *        The loosing condition is : a mine has beed discovered.
 *
 * @param g Current game status
 * @return '0' the user can continue to play
 *         '1' the user has explosed, end of the game
 */
int defeat(Game* g);

/**
 * @brief If the case has no mine in is neighborhood extend to other
 *        cell until they got a mine is her neighborhood.
 *
 * @param g Current game status
 * @param x current cell abscissa
 * @param y current cell ordinate
 * @param func_graph function who draw the cell when discovered
 */
void extend_undiscovered(Game* g, int x, int y, void (*func_graph)(int, int, int, int));

/**
 * @brief Return the number of mines without flag on them.
 *
 * @param g Current game status
 * @return Number of mines without flag on them
 */
int mine_left(Game* g);

#endif
