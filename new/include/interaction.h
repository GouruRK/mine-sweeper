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

Game parser(int argc, char** argv);
int read_file(Game* g);
void save(Game* g);

#endif