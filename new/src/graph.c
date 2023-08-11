/**
 * @file graph.c
 * @author Laborde Quentin & Kies Remy
 * @brief
 * @date 01-08-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../include/graph.h"

#include <MLV/MLV_all.h>

#include "../include/struct.h"

void exit_function(void* data) {
    int* arret = (int*)data;
    *arret = 1;
}

void draw_undiscorvered(int x, int y, int cell_size) {
    int s_x = x * cell_size, s_y = y * cell_size;
    int border = cell_size / 10;
    MLV_draw_filled_triangle(s_x, s_y,
                             s_x + cell_size, s_y,
                             s_x, s_y + cell_size,
                             MLV_COLOR_LIGHT_GREY);
    MLV_draw_filled_triangle(s_x + cell_size, s_y,
                             s_x, s_y + cell_size,
                             s_x + cell_size, s_y + cell_size,
                             MLV_COLOR_DARK_GRAY);
    MLV_draw_filled_rectangle(s_x + border, s_y + border,
                              cell_size - 2 * border,
                              cell_size - 2 * border,
                              MLV_COLOR_GREY);
}

void draw_flag(int x, int y, int cell_size) {
    int s_x = x * cell_size, s_y = y * cell_size;
    int border = cell_size / 10;

    MLV_draw_filled_rectangle(s_x + 2 * border,
                              s_y + cell_size - 2.5 * border,
                              cell_size - 4 * border,
                              border / 2,
                              MLV_COLOR_BLACK);

    MLV_draw_filled_rectangle(s_x + 3 * border,
                              s_y + cell_size - 3 * border,
                              cell_size - 6 * border,
                              border / 2,
                              MLV_COLOR_BLACK);

    MLV_draw_filled_rectangle(s_x + cell_size / 2 - border / 4,
                              s_y + cell_size / 2 - border,
                              border / 2,
                              // 2nd rect y - 3rd rect y
                              (s_y + cell_size - 3 * border) - (s_y + cell_size / 2 - border),
                              MLV_COLOR_BLACK);

    MLV_draw_filled_triangle(s_x + cell_size / 2 + border / 4,
                             s_y + 2 * border,

                             s_x + cell_size / 2 + border / 4,
                             s_y + cell_size - 4.5 * border,

                             // same as 2st rectangle start x
                             s_x + 2.5 * border,
                             s_y + 4.5 * border,
                             MLV_COLOR_RED);
}

void draw_discovered(int x, int y, int cell_size, int val) {
    MLV_Color tab_col[8] = {
        MLV_COLOR_BLUE,
        MLV_COLOR_GREEN,
        MLV_COLOR_RED,
        MLV_COLOR_DARK_BLUE,
        MLV_COLOR_DARK_RED,
        MLV_COLOR_CYAN,
        MLV_COLOR_PURPLE,
        MLV_COLOR_DARK_GREY};

    int s_x = x * cell_size,
        s_y = y * cell_size,
        text_w, text_h;

    MLV_draw_filled_rectangle(s_x, s_y,
                              cell_size, cell_size,
                              MLV_COLOR_GREY);
    MLV_get_size_of_text("1", &text_w, &text_h);
    MLV_draw_text(s_x + cell_size / 2 - text_w / 2,
                  s_y + cell_size / 2 - text_h / 2,
                  "1", tab_col[val - 1]);
}

void draw_game(Game g) {
    Cell c;
    for (int y = 0; y < g.height; y++) {
        for (int x = 0; x < g.width; x++) {
            c = g.terrain[y][x];
            if (c == UNDISCOVERED || c == MINE) {
                draw_undiscorvered(x, y, g.cell_size);
            } else if (c == FLAG || c == FLAG_MINE) {
                draw_undiscorvered(x, y, g.cell_size);
                draw_flag(x, y, g.cell_size);
            }
        }
    }
}