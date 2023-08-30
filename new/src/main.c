/**
 * @file main.c
 * @author Laborde Quentin & Kies Remy
 * @brief
 * @date 01-08-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <MLV/MLV_all.h>
#include <stdlib.h>
#include <time.h>

#include "../include/game.h"
#include "../include/graph.h"
#include "../include/init.h"
#include "../include/interaction.h"
#include "../include/struct.h"
#include "../include/tool.h"

int main(int argc, char* argv[]) {
    Game g = parser(argc, argv);
    srand((g.seed_flag) ? (g.seed) : (time(NULL)));
    int stop = 0, valid_file = 0;

    valid_file = read_file(&g);
    if (!valid_file) {
        g.terrain = init_board_empty(g.width, g.height);
        if (!g.terrain) {
            fprintf(stderr, "Terrain not loaded\n End of execution\n");
            return EXIT_FAILURE;
        }
    }
    resize_game(&g);

    init_window_mlv(&stop, g);

    if (play(&g, valid_file, &stop)) {
        return EXIT_FAILURE;
    }

    if (defeat(&g) || victory(&g)) {
        MLV_wait_seconds(5);
    }
    free_board(g.terrain, g.height);
    MLV_free_window();
    return EXIT_SUCCESS;
}
