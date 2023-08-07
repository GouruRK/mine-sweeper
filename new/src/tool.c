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

#include <stdio.h>
#include <stdlib.h>

#include "../include/struct.h"

void print_board(Game g) {
    printf("Board:\n");
    for (int y = 0; y < g.height; y++) {
        for (int x = 0; x < g.width; x++) {
            printf("%d", g.terrain[y][x]);
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