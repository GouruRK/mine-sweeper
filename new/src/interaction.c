/**
 * @file interaction.c
 * @author Laborde Quentin & Kies Remy
 * @brief
 * @date 01-08-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../include/interaction.h"

#include <MLV/MLV_all.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/game.h"
#include "../include/graph.h"
#include "../include/init.h"
#include "../include/tool.h"

Game parser(int argc, char** argv) {
    int option_index = 0, opt;
    Game g = init_game();
    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"custom", required_argument, 0, 'c'},
        {"random", required_argument, 0, 'r'},
        {0, 0, 0, 0}};

    while ((opt = getopt_long(argc, argv, "hc:r:", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'c':;
                /* :; to avoid (pedantic):
                'a label can only be part of a statement and a declaration is not a statement'. */
                int h, w, m, ok;
                ok = sscanf(optarg, "%d %d %d", &h, &w, &m);
                if (ok == 3) {
                    if (h * w <= m) {
                        fprintf(stderr, "/!\\ Too much mines for this size /!\\ \n");
                        fprintf(stderr, "Modification will not be considered.\n");
                        break;
                    }
                    g.height = h;
                    g.width = w;
                    g.mines = m;
                } else {
                    fprintf(stderr, "/!\\ Unexpected character in -c option /!\\ \n");
                    fprintf(stderr, "Modification will not be considered.\n");
                }
                break;

            case 'r':;
                int r;
                ok = sscanf(optarg, "%d", &r);
                if (ok == 1) {
                    g.seed = r;
                    g.seed_flag = 1;
                } else {
                    fprintf(stderr, "/!\\ Unexpected character in -r option /!\\ \n");
                    fprintf(stderr, "Modification will not be considered.\n");
                }
                break;

            case 'h':
                printf(
                    "\nMinesweeper helper :\n\n"
                    "./build/minesweeper [map] [-r seed] [-c \"height width mines\"]\n\n"
                    "map :\n"
                    "\t path to the file where the map is written\n\n"
                    "-r / --random :\n"
                    "\t seed for the random genrator (int)\n\n"
                    "-c / --custom :\n"
                    "\t Generate a random map using the given paramaters\n"
                    "\t\t height of the map (int)\n"
                    "\t\t width of the map (int)\n"
                    "\t\t number of mines (int)\n\n");
                break;

            default:
                break;
        }
    }
    if (optind < argc) {
        if (optind == argc - 1) {
            g.map = argv[optind];
        } else {
            printf("Too much arguments (1 for map)\n");
        }
    }
    return g;
}

int read_file(Game* g) {
    if (!g->map) {
        return 0;
    }
    int acc = 0, val;
    FILE* f = fopen(g->map, "r");
    if (!f) {
        return 0;
    }
    int h, w, m, ok;
    ok = fscanf(f, "%d %d %d\n", &h, &w, &m);

    if (ok != 3) {
        fclose(f);
        return 0;
    }
    g->terrain = init_board_empty(w, h);
    if (!g->terrain) {
        fclose(f);
        return 0;
    }
    while (fscanf(f, "%d", &val) != EOF) {
        if (val != 0) {
            int line = acc / w;
            int col = acc - line * w;
            g->terrain[line][col] = val;
        }
        acc++;
    }
    if (acc != w * h) {
        printf("Oh no\n");
    }
    g->height = h;
    g->width = w;
    g->mines = m;
    fclose(f);
    return 1;
}

void save(Game* g) {
    if (!g->terrain) {
        return;
    }
    FILE* f = fopen("../grids/save.ga", "w");
    if (!f) {
        return;
    }
    fprintf(f, "%d %d %d\n", g->height, g->width, g->mines);

    for (int y = 0; y < g->height; y++) {
        for (int x = 0; x < g->width; x++) {
            fprintf(f, "%d", g->terrain[y][x]);
            if (x != g->width - 1) {
                fprintf(f, " ");
            }
        }
        if (y != g->height - 1) {
            fprintf(f, "\n");
        }
    }
    fclose(f);
    return;
}

int play(Game* g, int valid_file, int* stop) {
    MLV_Event ev = MLV_NONE;
    MLV_Keyboard_button touche;
    MLV_Mouse_button mouse;
    MLV_Button_state state;
    int x, y;

    if (!valid_file) {
        do {
            ev = MLV_wait_event_or_milliseconds(&touche, NULL, NULL, NULL, NULL, &x, &y, &mouse, &state, TIME_INTERVAL);
            if (ev == MLV_MOUSE_BUTTON && state == MLV_PRESSED) {
                if (y > GRAPHIC_HEADER) {
                    coord_to_cell(&x, &y, g->cell_size);
                    if (mouse == MLV_BUTTON_LEFT) {
                        break;
                    } else if (mouse == MLV_BUTTON_RIGHT) {
                        g->terrain[y][x] = (g->terrain[y][x] == FLAG) ? (UNDISCOVERED) : (FLAG);
                        if (g->terrain[y][x] == FLAG) {
                            draw_flag(x, y, g->cell_size);
                        } else {
                            draw_undiscovered(x, y, g->cell_size);
                        }
                        draw_header(mine_left(g));
                    }
                } else if (y < 63 && y > 12 &&
                           x < MLV_get_window_width() - 12 &&
                           x > MLV_get_window_width() - 62) {
                    save(g);
                }
            }
        } while (!(*stop));
        free_board(g->terrain, g->height);
        if (!create_game_param(g, x, y)) {
            fprintf(stderr, "Terrain not loaded\n End of execution\n");
            return EXIT_FAILURE;
        }
    }

    draw_game(*g);
    extend_undiscovered(g, x, y, draw_discovered);

    while (!(*stop)) {
        ev = MLV_wait_event_or_milliseconds(&touche, NULL, NULL, NULL, NULL, &x, &y, &mouse, &state, 100);
        if (y > GRAPHIC_HEADER) {
            if (ev == MLV_MOUSE_BUTTON && state == MLV_PRESSED) {
                coord_to_cell(&x, &y, g->cell_size);
                if (mouse == MLV_BUTTON_LEFT && !(g->terrain[y][x] == FLAG) && !(g->terrain[y][x] == FLAG_MINE)) {
                    extend_undiscovered(g, x, y, draw_discovered);

                } else if (mouse == MLV_BUTTON_RIGHT) {
                    flag_cell(g, x, y);

                    if (g->terrain[y][x] == FLAG || g->terrain[y][x] == FLAG_MINE) {
                        draw_flag(x, y, g->cell_size);
                    } else if (g->terrain[y][x] == UNDISCOVERED || g->terrain[y][x] == MINE) {
                        draw_undiscovered(x, y, g->cell_size);
                    }
                    draw_header(mine_left(g));
                }
            }
        } else if (y < 63 && y > 12 &&
                   x < MLV_get_window_width() - 12 &&
                   x > MLV_get_window_width() - 62) {
            save(g);
        }

        if (defeat(g) || victory(g)) {
            draw_end_game(*g);
            break;
        }
    }
    return EXIT_SUCCESS;
}