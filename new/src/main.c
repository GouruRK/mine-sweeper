/**
 * @file main.c
 * @author Laborde Quentin & Kies Remy
 * @brief
 * @date 01-08-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../include/game.h"
#include "../include/graph.h"
#include "../include/init.h"
#include "../include/interaction.h"
#include "../include/struct.h"
#include "../include/tool.h"

int main(void) {
    Game g;
    g.height = 2;
    g.width = 2;
    g.terrain = init_board(g.width, g.height);
    print_ms(g);
    free_board(g.terrain, g.height);
    return 0;
}
