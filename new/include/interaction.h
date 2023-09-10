/**
 * @file interaction.h
 * @author Laborde Quentin & Kies Remy
 * @brief
 * @date 01-08-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __INIT_INTER__
#define __INIT_INTER__

#include "struct.h"

/**
 * @brief Parses the given arguments to the programm.
 *
 * @param argc number of arguments
 * @param argv array of arguments
 * @return Initialised game
 */
Game parser(int argc, char** argv);

/**
 * @brief Read a file in order to load a game.
 *
 * @param g Game where information will be write
 * @return 0 error / 1 ok
 */
int read_file(Game* g);

/**
 * @brief Save current game status.
 *
 * @param g Current game status
 */
void save(Game* g);

/**
 * @brief Overall function to handle user's interactions.
 *
 * @param g Game to be modificated
 * @param valid_file if the function have to load a file
 * @param stop variable used to exit libMLV's window
 * @return '0' ok / '1' error
 */
int play(Game* g, int valid_file, int* stop);

#endif
