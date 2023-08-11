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

int main(int argc, char *argv[]) {
    int stop = 0, valid_file = 0;

    Game g = parser(argc, argv);
    srand((g.seed_flag) ? (g.seed) : (time(NULL)));

    valid_file = read_file(&g);
    if (!valid_file) {
        g.terrain = init_board_empty(g.width, g.height);
        if (!g.terrain) {
            fprintf(stderr, "Terrain not loaded\n End of execution\n");
            return EXIT_FAILURE;
        }
    }
    resize_game(&g);

    print_game(g);
    fprintf(stderr, "c oui\n");

    MLV_execute_at_exit(exit_function, &stop);
    MLV_create_window("Minesweeper", "Minesweeper", g.cell_size * g.width, g.cell_size * g.height);
    MLV_change_default_font("../extern_file/mine_sweeper.ttf", g.cell_size / 2);
    draw_game(g);
    draw_flag(0, 0, g.cell_size);
    MLV_update_window();
    MLV_wait_seconds(5);
    MLV_free_window();
    return 0;
}
