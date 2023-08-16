/**
 * @file tool.c
 * @author Laborde Quentin & Kies Remy
 * @brief
 * @date 02-08-2023
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "../include/tool.h"

#include <MLV/MLV_all.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/struct.h"

void print_board(Game g) {
    printf("Board:\n");
    for (int y = 0; y < g.height; y++) {
        for (int x = 0; x < g.width; x++) {
            printf("%3d", g.terrain[y][x]);
        }
        printf("\n");
    }
}

void print_game(Game g) {
    printf("Size: x:%d y:%d\n", g.width, g.height);
    printf("Mines: %d\n", g.mines);
    printf("File: %s\n", g.map);
    if (g.terrain) {
        print_board(g);
    }
}

int random_coord(int max) {
    return rand() % (max + 1);
}

void resize_game(Game* g) {
    int win_w = MLV_get_desktop_width(), win_h = MLV_get_desktop_height();

    if ((g->cell_size * g->width > win_w) ||
        (g->cell_size * g->height + GRAPHIC_SAFETY_MARGIN > win_h)) {
        if (win_w < win_h) {
            g->cell_size = win_w / g->width;
        } else {
            g->cell_size = (win_h - GRAPHIC_SAFETY_MARGIN) / g->height;
        }
    }
}

void coord_to_cell(int* x, int* y, int cell_size) {
    *x = *x / cell_size;
    *y = (*y - GRAPHIC_HEADER) / cell_size;
}