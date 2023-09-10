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

/**
 * @brief Initialises game with default values.
 *
 * @return Initialised game
 */
Game init_game(void);

/**
 * @brief Initialises the board empty and fills it with mines.
 *
 * @param width board width
 * @param height board height
 * @return Cell** board initialised
 */
Cell** init_board_empty(int width, int height);

/**
 * @brief Initialises the board full of mines and fills it with mines.
 *
 * @param width board width
 * @param height board height
 * @return Cell** board initialised
 */
Cell** init_board_full(int width, int height);

/**
 * @brief Creates a game with parameters.
 *
 * @param g Actual game status
 * @param user_x user x input
 * @param user_y user y input
 * @return '0' error
 *         else '1'
 */
int create_game_param(Game* g, int user_x, int user_y);

/**
 * @brief Free the memory allocated for the board.
 *
 * @param tab board to free
 * @param line mumber of line you want to free.
 */
void free_board(Cell** tab, int line);

#endif
