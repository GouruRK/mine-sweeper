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
 * @brief Parse the argument given to the project.
 *
 * @param argc number of argument
 * @param argv array of argument
 * @return Initialised game
 */
Game parser(int argc, char** argv);

/**
 * @brief Read the file in order to load a game.
 *
 * @param g Game where information will be write
 * @return 0 error / 1 ok
 */
int read_file(Game* g);

/**
 * @brief Save actual game status.
 *
 * @param g Actual game status
 */
void save(Game* g);

/**
 * @brief Overall function where who handle user interactions.
 *
 * @param g Game who will be modificated
 * @param valid_file if the function have to load a file
 * @param stop varaible used to exit windows libMLV
 * @return 0 ok / 1 error
 */
int play(Game* g, int valid_file, int* stop);

#endif