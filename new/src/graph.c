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

void init_window_mlv(int* stop, Game g) {
    MLV_execute_at_exit(exit_function, stop);
    MLV_create_window("Minesweeper", "Minesweeper", g.cell_size * g.width, g.cell_size * g.height + GRAPHIC_HEADER);
    MLV_change_default_font("../extern_file/mine_sweeper.ttf", g.cell_size / 2);
    draw_game(g);
}

void draw_undiscovered(int x, int y, int cell_size) {
    int s_x = x * cell_size, s_y = y * cell_size + GRAPHIC_HEADER;
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
    MLV_update_window();
}

void draw_flag(int x, int y, int cell_size) {
    int s_x = x * cell_size, s_y = y * cell_size + GRAPHIC_HEADER;
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
                             s_y + cell_size / 2,

                             // same as 2st rectangle start x
                             s_x + 2.5 * border,
                             s_y + 3.5 * border,
                             MLV_COLOR_RED);
    MLV_update_window();
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
        s_y = y * cell_size + GRAPHIC_HEADER,
        text_w, text_h;

    MLV_draw_filled_rectangle(s_x, s_y,
                              cell_size, cell_size,
                              MLV_COLOR_GREY);
    MLV_draw_rectangle(s_x, s_y,
                       cell_size, cell_size,
                       MLV_COLOR_DARK_GREY);
    if (val >= ONE && val <= EIGHT) {
        MLV_get_size_of_text("%d", &text_w, &text_h, val);
        MLV_draw_text(s_x + cell_size / 2 - text_w / 2,
                      s_y + cell_size / 2 - text_h / 2,
                      "%d", tab_col[val - 1], val);
    }
    MLV_update_window();
}

void draw_nbmine(int nbmine) {
    int x, y;
    MLV_get_size_of_adapted_text_box("%d", 0, &x, &y, nbmine);
    MLV_draw_text_box(MLV_get_window_width() / 2 - x / 2,
                      GRAPHIC_HEADER / 2 - y / 2,
                      x, y, "%d", 0,
                      MLV_COLOR_DARK_GREY,
                      MLV_COLOR_RED,
                      MLV_COLOR_DARK_GREY,
                      MLV_TEXT_CENTER,
                      MLV_HORIZONTAL_CENTER,
                      MLV_VERTICAL_CENTER,
                      nbmine);
    MLV_update_window();
}

void draw_save(void) {
    // 62 because 50 width box and 12 margin top left right.
    int x = MLV_get_window_width() - 62, y = 12;
    int cell_size = 50, border = cell_size / 10;
    MLV_draw_filled_triangle(x, 12,
                             x + cell_size, y,
                             x, y + cell_size,
                             MLV_COLOR_LIGHT_GREY);
    MLV_draw_filled_triangle(x + cell_size, y,
                             x, y + cell_size,
                             x + cell_size, y + cell_size,
                             MLV_COLOR_DARK_GRAY);
    MLV_draw_filled_rectangle(x + border, y + border,
                              cell_size - 2 * border,
                              cell_size - 2 * border,
                              MLV_COLOR_GREY);

    MLV_draw_filled_rectangle(x + 2 * border,
                              y + 2 * border,
                              cell_size - 4 * border,
                              3 * border,
                              MLV_COLOR_YELLOW);

    MLV_draw_filled_triangle(x + 2 * border, y + 2 * border,
                             x + 2 * border, y + cell_size - 2 * border,
                             x + cell_size / 2, y + cell_size / 2,
                             MLV_COLOR_YELLOW);

    MLV_draw_filled_triangle(x + cell_size - 2 * border, y + 2 * border,
                             x + cell_size - 2 * border, y + cell_size - 2 * border,
                             x + cell_size / 2, y + cell_size / 2,
                             MLV_COLOR_YELLOW);

    MLV_update_window();
}

void draw_header(int nbmine) {
    MLV_draw_filled_rectangle(0, 0,
                              MLV_get_window_width(),
                              GRAPHIC_HEADER,
                              MLV_COLOR_DARK_GREY);
    draw_nbmine(nbmine);
    draw_save();
}

void draw_mine(int x, int y, int cell_size, int explosed) {
    MLV_Color col = (explosed) ? (MLV_COLOR_RED) : (MLV_COLOR_BLACK);
    int s_x = x * cell_size, s_y = y * cell_size + GRAPHIC_HEADER;
    int text_w, text_h;

    MLV_get_size_of_text("*", &text_w, &text_h);
    MLV_draw_text(s_x + cell_size / 2 - text_w / 2,
                  s_y + cell_size / 2 - text_h / 2,
                  "*", col);
    MLV_update_window();
}

void draw_end_game(Game g) {
    for (int y = 0; y < g.height; y++) {
        for (int x = 0; x < g.width; x++) {
            Cell c = g.terrain[y][x];
            if (c == MINE || c == FLAG_MINE) {
                draw_mine(x, y, g.cell_size, 0);
            } else if (c == EXPLOSION) {
                draw_mine(x, y, g.cell_size, 1);
            }
        }
    }
}

void draw_game(Game g) {
    Cell c;
    for (int y = 0; y < g.height; y++) {
        for (int x = 0; x < g.width; x++) {
            c = g.terrain[y][x];
            if (c == UNDISCOVERED || c == MINE) {
                draw_undiscovered(x, y, g.cell_size);
            } else if (c == FLAG || c == FLAG_MINE) {
                draw_undiscovered(x, y, g.cell_size);
                draw_flag(x, y, g.cell_size);
            } else if ((c >= ONE && c <= EIGHT) || c == EMPTY) {
                draw_discovered(x, y, g.cell_size, c);
            }
        }
    }
    draw_header(g.mines);
}