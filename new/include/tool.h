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

/**
 * @brief Prints the board on the terminal.
 *
 * @param g game that contains the board
 */
void print_board(Game g);

/**
 * @brief Prints the game on the terminal.
 *
 * @param g game to print
 */
void print_game(Game g);

/**
 * @brief Generates a random number between 0 and max (both include).
 *
 * @param max number max
 * @return random number
 */
int random_coord(int max);

/**
 * @brief Decreases the size of the game if necessary.
 *
 * @param g game height and width
 */
void resize_game(Game* g);

/**
 * @brief Translates graphic coordinates into array coordinates.
 *
 * @param x graphic abscissa
 * @param y graphic ordinate
 * @param cell_size
 */
void coord_to_cell(int* x, int* y, int cell_size);

#endif
