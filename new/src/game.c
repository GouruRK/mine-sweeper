/**
 * @file game.c
 * @author Laborde Quentin & Kies Remy
 * @brief
 * @date 01-08-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../include/game.h"

#include <stdio.h>

#include "../include/struct.h"

int is_in_board(int width, int height, int x, int y) {
    return ((x >= 0 && x < width) &&
            (y >= 0 && y < width));
}

int nb_mines(Game* g, int x, int y) {
    if (!is_in_board(g->width, g->height, x, y)) {
        return 0;
    }
    int coords[8][2] = NEIGHBOR(x, y);
    int acc = 0;

    for (int i = 0; i < 8; i++) {
        int n_x = coords[i][0], n_y = coords[i][1];
        acc += (is_in_board(g->width, g->height, n_x, n_y) &&
                (g->terrain[n_y][n_x] == MINE || g->terrain[n_y][n_x] == FLAG_MINE));
    }
    return acc;
}

int break_cell(Game* g, int x, int y) {
    if (!is_in_board(g->width, g->height, x, y)) {
        return 0;
    }
    if (g->terrain[y][x] == MINE) {
        g->terrain[y][x] = EXPLOSION;
        return 1;
    }
    if (g->terrain[y][x] == UNDISCOVERED) {
        int val = nb_mines(g, x, y);
        fprintf(stderr, "voisin %d", val);
        g->terrain[y][x] = (!val) ? EMPTY : val;
    }
    return 0;
}

void flag_cell(Game* g, int x, int y) {
    if (!is_in_board(g->width, g->height, x, y)) {
        return;
    }

    Cell c = g->terrain[y][x];
    if (c == MINE) {
        c = FLAG_MINE;
    } else if (c == FLAG_MINE) {
        c = MINE;
    } else if (c == FLAG) {
        c = UNDISCOVERED;
    } else if (c == UNDISCOVERED) {
        c = FLAG;
    }
}

int victory(Game* g) {
    int win_all_discovered = 1;
    int acc_flag_mine = 0;

    for (int y = 0; y < g->height; y++) {
        for (int x = 0; x < g->width; x++) {
            Cell c = g->terrain[y][x];

            if (c == FLAG) {
                return 0;
            } else if (c == FLAG_MINE) {
                acc_flag_mine++;
            } else if (c == UNDISCOVERED) {
                win_all_discovered = 0;
            }
        }
    }
    return win_all_discovered || acc_flag_mine == g->mines;
}

int defeat(Game* g) {
    for (int y = 0; y < g->height; y++) {
        for (int x = 0; x < g->width; x++) {
            if (g->terrain[y][x] == EXPLOSION) {
                return 1;
            }
        }
    }
    return 0;
}

void extend_undiscovered(Game* g, int x, int y) {
}