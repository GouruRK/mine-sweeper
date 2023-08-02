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

void parser(int argc, char** argv) {
    int option_index = 0, opt;
    Game g = init_game();
    static struct option long_options[] = {
        {"help", no_argument, 0, 'h'},
        {"custom", required_argument, 0, 'c'},
        {"random", required_argument, 0, 'r'},
        {0, 0, 0, 0}};

    while ((opt = getopt_long(argc, argv, "hc:r:", long_options, &option_index)) != -1) {
        switch (opt) {
            case 'c':
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

            case 'r':
                int r;
                ok = sscanf(optarg, "%d", &r);
                if (ok == 1) {
                    g.seed = r;
                } else {
                    fprintf(stderr, "/!\\ Unexpected character in -r option /!\\ \n");
                    fprintf(stderr, "Modification will not be considered.\n");
                }
                break;

            default:
                break;
        }
    }
}
