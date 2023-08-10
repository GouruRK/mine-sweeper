/**
 * @file main.c
 * @author Laborde Quentin & Kies Remy
 * @brief
 * @date 01-08-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#include <MLV/MLV_all.h>
#include <stdlib.h>
#include <time.h>

#include "../include/game.h"
#include "../include/graph.h"
#include "../include/init.h"
#include "../include/interaction.h"
#include "../include/struct.h"
#include "../include/tool.h"

int main(int argc, char *argv[]) {
    int stop = 0;
    srand(time(NULL));
    MLV_execute_at_exit(exit_function, &stop);
    MLV_create_window("Minesweeper", "Minesweeper", 400, 400);
    MLV_change_default_font("../extern_file/mine_sweeper.ttf", 400 / 2);
    // draw_undiscorvered(0, 0, 400);
    // draw_flag(0, 0, 100);
    draw_discovered(0, 0, 400, 1);
    MLV_update_window();
    MLV_wait_seconds(10);
    MLV_free_window();
    return 0;
}
