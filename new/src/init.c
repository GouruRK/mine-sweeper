/**
 * @file init.c
 * @author Laborde Quentin & Kies Remy
 * @brief
 * @date 01-08-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../include/init.h"

#include <stdlib.h>

#include "../include/struct.h"
#include "../include/tool.h"

Game init_game(void) {
    Game g = {
        .cell_size = 100,
        .width = 10,
        .height = 10,
        .seed_flag = 0,
        .seed = 0,
        .finished = 0,
        .mines = 10,
        .terrain = NULL,
        .map = NULL};
    return g;
}

Cell** init_board_empty(int width, int height) {
    Cell** tab = calloc(height, sizeof(Cell*));
    if (!tab) {
        return NULL;
    }
    for (int i = 0; i < height; i++) {
        Cell* tmp = calloc(width, sizeof(Cell));
        if (!tmp) {
            free_board(tab, i);
            return NULL;
        }
        tab[i] = tmp;
    }
    return tab;
}

Cell** init_board_full(int width, int height) {
    Cell** tab = calloc(height, sizeof(Cell*));
    if (!tab) {
        return NULL;
    }
    for (int i = 0; i < height; i++) {
        Cell* tmp = malloc(width * sizeof(Cell));
        if (!tmp) {
            free_board(tab, i);
            return NULL;
        }
        tab[i] = tmp;
        for (int j = 0; j < width; j++) {
            tab[i][j] = MINE;
        }
    }
    return tab;
}

int create_game_param(Game* g, int user_x, int user_y) {
    if (g->mines > (g->height * g->width) / 2) {
        g->terrain = init_board_full(g->width, g->height);
    } else {
        g->terrain = init_board_empty(g->width, g->height);
    }

    if (!g->terrain) {
        return 0;
    }

    if (g->mines > (g->height * g->width) / 2) {
        g->terrain[user_y][user_y] = UNDISCOVERED;

        for (int i = 0; i < g->height * g->width - g->mines - 1; i++) {
            int x = random_coord(g->width - 1);
            int y = random_coord(g->height - 1);
            while (g->terrain[y][x] == UNDISCOVERED) {
                x = random_coord(g->width - 1);
                y = random_coord(g->height - 1);
            }
            g->terrain[y][x] = UNDISCOVERED;
        }
    } else {
        for (int i = 0; i < g->mines; i++) {
            int x = random_coord(g->width - 1);
            int y = random_coord(g->height - 1);
            while (g->terrain[y][x] == MINE && x != user_x && y != user_y) {
                x = random_coord(g->width - 1);
                y = random_coord(g->height - 1);
            }
            g->terrain[y][x] = MINE;
        }
    }
    return 1;
}

void free_board(Cell** tab, int line) {
    for (int i = 0; i < line; i++) {
        free(tab[i]);
    }
    free(tab);
}