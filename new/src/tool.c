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

#include "../include/struct.h"

void print_ms(Game g) {
    for (int y = 0; y < g.height; y++) {
        for (int x = 0; x < g.width; x++) {
            printf("%d", g.terrain[y][x]);
        }
        printf("\n");
    }
}