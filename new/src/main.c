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

    init_window_mlv(&stop, g);
    if (!valid_file) {
        do {
            ev = MLV_wait_event_or_milliseconds(&touche, NULL, NULL, NULL, NULL, &x, &y, &mouse, &state, TIME_INTERVAL);
            if (ev == MLV_MOUSE_BUTTON && state == MLV_PRESSED) {
                coord_to_cell(&x, &y, g.cell_size);
                if (mouse == MLV_BUTTON_LEFT) {
                    break;
                } else if (mouse == MLV_BUTTON_RIGHT) {
                    g.terrain[y][x] = (g.terrain[y][x] == FLAG) ? (UNDISCOVERED) : (FLAG);
                    if (g.terrain[y][x] == FLAG) {
                        draw_flag(x, y, g.cell_size);
                    } else {
                        draw_undiscovered(x, y, g.cell_size);
                    }
                    draw_header(mine_left(&g));
                }
            }
        } while (!stop);
        free_board(g.terrain, g.height);
        if (!create_game_param(&g, x, y)) {
            fprintf(stderr, "Terrain not loaded\n End of execution\n");
            return EXIT_FAILURE;
        }
    }

    draw_game(g);
    extend_undiscovered(&g, x, y, draw_discovered);

    while (!stop) {
        ev = MLV_wait_event_or_milliseconds(&touche, NULL, NULL, NULL, NULL, &x, &y, &mouse, &state, 100);
        if (ev == MLV_MOUSE_BUTTON && state == MLV_PRESSED) {
            coord_to_cell(&x, &y, g.cell_size);
            if (mouse == MLV_BUTTON_LEFT) {
                extend_undiscovered(&g, x, y, draw_discovered);

            } else if (mouse == MLV_BUTTON_RIGHT) {
                flag_cell(&g, x, y);

                if (g.terrain[y][x] == FLAG || g.terrain[y][x] == FLAG_MINE) {
                    draw_flag(x, y, g.cell_size);
                } else if (g.terrain[y][x] == UNDISCOVERED) {
                    draw_undiscovered(x, y, g.cell_size);
                }
                draw_header(mine_left(&g));
            }
        }
    }
    MLV_free_window();
    return EXIT_SUCCESS;
}
