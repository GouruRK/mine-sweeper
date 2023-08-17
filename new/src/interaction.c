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

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/init.h"
#include "../include/struct.h"

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
                printf("One day maybe...\n");
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