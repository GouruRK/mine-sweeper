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

Game init_game(void) {
    Game g = {
        .cell_h = 0,
        .cell_w = 0,
        .width = 10,
        .height = 10,
        .seed = 0,
        .finished = 0,
        .mines = 10,
        .terrain = NULL,
        .map = NULL};
    return g;
}

Cell** init_board(int width, int height) {
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

void free_board(Cell** tab, int line) {
    for (int i = 0; i < line; i++) {
        free(tab[i]);
    }
    free(tab);
}