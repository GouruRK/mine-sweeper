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
    MLV_Event ev = MLV_NONE;
    MLV_Keyboard_button touche;
    MLV_Mouse_button mouse;
    MLV_Button_state state;
    int stop = 0, valid_file = 0, x, y;
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

    MLV_execute_at_exit(exit_function, &stop);
    MLV_create_window("Minesweeper", "Minesweeper", g.cell_size * g.width, g.cell_size * g.height);
    MLV_change_default_font("../extern_file/mine_sweeper.ttf", g.cell_size / 2);
    draw_game(g);
    MLV_update_window();
    if (!valid_file) {
        do {
            ev = MLV_wait_event_or_milliseconds(&touche, NULL, NULL, NULL, NULL, &x, &y, &mouse, &state, 100);
            if (ev == MLV_MOUSE_BUTTON && state == MLV_PRESSED) {
                coord_to_cell(&x, &y, g.cell_size);
                if (mouse == MLV_BUTTON_LEFT) {
                    break;
                } else if (mouse == MLV_BUTTON_RIGHT) {
                    g.terrain[y][x] = (g.terrain[y][x] == FLAG) ? (UNDISCOVERED) : (FLAG);
                }
            }

        } while (!stop);
        free_board(g.terrain, g.height);
        if (!create_game_param(&g, x, y)) {
            fprintf(stderr, "Terrain not loaded\n End of execution\n");
            return EXIT_FAILURE;
        }
    }

    while (!stop) {
        ev = MLV_wait_event_or_milliseconds(&touche, NULL, NULL, NULL, NULL, &x, &y, &mouse, &state, 100);
        if (ev == MLV_MOUSE_BUTTON && state == MLV_PRESSED) {
            coord_to_cell(&x, &y, g.cell_size);
            if (mouse == MLV_BUTTON_LEFT) {
                break_cell(&g, x, y);
                // print_board(g);
                draw_discovered(x, y, g.cell_size, g.terrain[y][x]);
                MLV_update_window();

            } else if (mouse == MLV_BUTTON_RIGHT) {
                flag_cell(&g, x, y);
                if (g.terrain[y][x] == FLAG) {
                    draw_flag(x, y, g.cell_size);
                } else {
                    draw_undiscorvered(x, y, g.cell_size);
                }
                MLV_update_window();
            }
        }
    }
    MLV_free_window();
    return EXIT_SUCCESS;
}
