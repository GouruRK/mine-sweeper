#include <stdio.h>
#include <MLV/MLV_all.h>

/* * * * * * * */
/*    Define   */
/* * * * * * * */

#define SQUARE_SIZE 75

/* * * * * * * */
/*  Structures */
/* * * * * * * */

typedef struct _game {
    int width;
    int height;
    int mines;
    int **terrain;
    int termine;
} Game;

/* * * * * * * */
/*  Prototypes */
/* * * * * * * */

/**
 * @brief Enregistrement de la fonction de call back pour la lib MLV
 *        lors de la fermeture de la fenêtre
 * 
 * @param data 
*/
void stop_affichage(void* data);


/**
 * @brief Permet d'afficher les lignes sur la fenêtre représentant la grille
 *        de jeu
 * 
 * @param g Structure représentant la grille et les données qui lui sont 
 *          propres
 * @param game_panel_width La largeur de la grille de jeu
 * @param game_panel_height La hauteur de la grille de jeu
*/
void affiche_lignes(Game g, int game_panel_width, int game_panel_height);

/**
 * @brief Affiche les boutons permettant d'interagir avec le programme
 *        pour quitter ou recommencer une partie
 * 
 * @param g Structure représentant la grille et les données qui lui sont 
 *          propres
 * @param control_panel_width La largeur du panel avec les boutons
 * @param game_panel_height La hauteur du panel de jeu avec la grille 
 *        représentée. Cette donnée est important car le panel avec les
 *        boutons se trouvant en dessous de la grille de jeu, il se trouve
 *        alors a y = game_panel_height
 * @param control_panel_height La hauteur du panel avec les boutons
*/
void affiche_boutons(Game g, int control_panel_width, int game_panel_height,
        int control_panel_height);

/**
 * @brief Permet de convertir la position de la souris par sa position dans
 *        la grille
 * 
 * @param x La position en x de la souris, qui est modifié pour prendre la 
 *          valeur en x dans le tableau
 * @param y La position en y de la souris, qui est modifié pour prendre la 
 *          valeur en y dans le tableau
*/
void convert_screen_coords_to_grid_coords(int* x, int* y);

/**
 * @brief Fonction qui permet d'afficher la fenêtre et d'interagir avec
 *        l'utilisateur. Elle est également responsable de gérer la 
 *        fermeture de la fenêtre
 * 
 * @param g Structure représentant la grille et les données qui lui sont 
 *          propres
*/
void play(Game g);

/**
 * @brief Fonction permettant de déterminer les actions de l'utilisateur et
 *        d'agir en conséquence. Les interactions possibles de l'utilisateurs
 *        sont des clics gauche ou droit.
 *        Les actions possibles sont :
 *         - Fermeture du jeu (par la "x" de la fenêtre ou en cliquant sur
 *           le bouton "Quitter") ;
 *         - Recommencer la partie (en cliquant sur le bouton "Recommencer");
 *         - Découvrir une case (en faisant un clique gauche sur la grille);
 *         - Déposer un drapeau (en faisant un clique droit sur la grille)
 *
 * @param g Structure représentant la grille et les données qui lui sont 
 *          propres
 * @param game_panel_width La largeur du panel de jeu
 * @param game_panel_height La hauteur du panel de jeu
 * @param control_panel_height La hauteur du panel des boutons
 * @param x La position en x de la souris
 * @param y La position en y de la souris
 * @param arret Argument modifié à `1` si l'utilisateur souhaite quitter 
 *        la partie
*/
void action(Game g, int game_panel_width, int game_panel_height,
        int control_panel_height, int x, int y, int* arret);

/**
 * @brief Fonction permettant de découvrir une case. Si la case n'est pas une
 *        mine ou n'est pas adjacente à une mine, elle révèle les cases 
 *        adjacentes etc. Modifie l'aspect graphique de la grille
 *
 * @param g Structure représentant la grille et les données qui lui sont 
 *          propres
 * @param x La position en x de la case a révéler
 * @param y La position en y de la case a révéler
*/
void revele_propagation(Game* g, int x, int y);

/** @brief Permet de poser un drapeau. Si un drapeau est déjà présent,
 *        le drapeau est retiré. Modifie l'aspect graphique de la grille
 * 
 * @param g Structure représentant la grille et les données qui lui sont 
 *          propres
 * @param x La position en x de la case où poser le drapeau
 * @param y La position en y de la case où poser le drapeau
*/
void poser_drapeau(Game* g, int x, int y);

/**
 * @brief Permet de savoir si le jeu est perdu. Le jeu est perdu si une 
 *        mine est découverte
 * 
 * @param g Structure représentant la grille et les données qui lui sont 
 *          propres
 * @return `1` si c'est perdu, `0` sinon
*/
int perdu(Game g);

/**
 * @brief Permet de réinitialiser la grille, et l'affchage de celle ci
 * 
 * @param g Structure représentant la grille et les données qui lui sont 
 *          propres
 * @param game_panel_width La largeur du panel de jeu
 * @param game_panel_height La hauteur du panel de jeu
 * @param control_panel_height La hauteur du panel des boutons
*/
void re_init(Game* g, int game_panel_width, int game_panel_height, 
        int control_panel_height);


/**
 * @brief Permet de savoir si une case possède une mine
 * 
 * @param g Structure représentant la grille et les données qui lui sont 
 *          propres
 * @param x La coordonnée en x de la case à vérifier
 * @param y La coordonnée en y de la case à vérifier
 * @return `1` si la case possède une mine `0` sinon où si les coordonnées
 *         de la case sont en dehors de la grille
*/
int hasmine_g(Game* g, int x, int y);

/**
 * @brief Permet de savoir combien de mines sont adjacentes a une case
 * 
 * @param g Structure représentant la grille et les données qui lui sont 
 *          propres
 * @param x La coordonnée en x de la case à vérifier
 * @param y La coordonnée en y de la case à vérifier
 * @return int : le nombre de mines adjacentes (entre 0 et 8 inclus)
*/
int nbmines_g(Game* g, int x, int y);

/**
 * @brief Permet de découvrir une case. Si la case découverte n'est pas une
 *        mines mais est adjacentes à d'autres mines, alors son contenu est 
 *        remplacé par le nombre de mines adjacentes. 
 *        Ne modifie pas l'aspect graphique
 * 
 * @param g Structure représentant la grille et les données qui lui sont 
 *          propres
 * @param x La coordonnée en x de la case à découvrir
 * @param y La coordonnée en y de la case à découvrir
 * @return `1` si la case découverte est une mine, `0` sinon
*/
int Pied_g(Game* g, int x, int y);

/**
 * @brief Permet de poser un drapeau sur une case, ou de retirer un drapeau
 *        sur une case qui en possède déjà un. Ne modifie pas l'aspect
 *        graphique
 * 
 * @param g Structure représentant la grille et les données qui lui sont 
 *          propres
 * @param x La coordonnée en x de la case où poser le drapeau
 * @param y La coordonnée en y de la case où poser le drapeau
*/
void Drapeau_g(Game* g, int x, int y);

/* * * * * * * */
/*  Fonctions */
/* * * * * * * */

void stop_affichage(void* data) {
	int* arret = (int*) data;
	*arret = 1;
}

void affiche_lignes(Game g, int game_panel_width, int game_panel_height) {
    MLV_draw_filled_rectangle(0, 0, game_panel_width, game_panel_height, 
                             MLV_COLOR_GRAY);
    // les lignes horizontales
    for (int y = 0; y < g.height + 1; y++) {
        MLV_draw_line(0, y * SQUARE_SIZE, game_panel_width, y * SQUARE_SIZE,
                     MLV_COLOR_BLACK);
    }

    // les lignes verticales
    for (int x = 0; x < g.width + 1; x++) {
        MLV_draw_line(x * SQUARE_SIZE, 0, x * SQUARE_SIZE, game_panel_height,
                     MLV_COLOR_BLACK);
    }
}

void affiche_boutons(Game g, int control_panel_width, int game_panel_height,
                    int control_panel_height) {
    MLV_draw_filled_rectangle(0, game_panel_height + 1, control_panel_width,
                             game_panel_height + control_panel_height,
                             MLV_COLOR_WHITE);
    int y = game_panel_height + (control_panel_height / 2);
    int w, h;
    MLV_get_size_of_text("Quitter", &w, &h);
    MLV_draw_text(100 - w/2,
                 y - h/2,
                 "Quitter",
                 MLV_COLOR_BLACK
                 );
    MLV_get_size_of_text("Nombre de mines : 1", &w, &h);
    MLV_draw_text(control_panel_width / 2 - w/2,
                 y - h/2,
                 "Nombre de mines : %d",
                 MLV_COLOR_BLACK,
                 g.mines
                 );
    MLV_get_size_of_text("Recommencer", &w, &h);
    MLV_draw_text(control_panel_width - 100 - w/2,
                 y - h/2,
                 "Recommencer",
                 MLV_COLOR_BLACK,
                 g.mines
                 );
}

void convert_screen_coords_to_grid_coords(int* x, int* y) {
    *x = *x / SQUARE_SIZE;
    *y = *y / SQUARE_SIZE;
}

void play(Game g) {
    int arret = 0; 
    // On enregistre la fonction de call back
    MLV_execute_at_exit(stop_affichage, &arret);

    // Création de la fenêtre
    int game_panel_width = (g.width) * SQUARE_SIZE;
    int game_panel_height = (g.height) * SQUARE_SIZE;
    int control_panel_height = 100;
    MLV_create_window("Minesweeper", "minesweeper", game_panel_width,
                     game_panel_height + control_panel_height);
    
    // Affichage des différents "panels" (la grille et les boutons)
    affiche_lignes(g, game_panel_width, game_panel_height);
    affiche_boutons(g, game_panel_width, game_panel_height, 
                   control_panel_height);
    MLV_update_window();
    
    // Tant que l'utilisateur ne ferme pas la fenêtre
    int x, y;
    do {
        MLV_get_mouse_position(&x, &y);
        action(g, game_panel_width, game_panel_height, control_panel_height, 
              x, y, &arret);
    } while (!arret);

    // on ferme la fenêtre
    MLV_free_window();
}

void action(Game g, int game_panel_width, int game_panel_height, 
           int control_panel_height, int x, int y, int* arret) {
    // Si l'utilisateur a cliqué dans la fenêtre
    int window_width = game_panel_width;
    int window_height = game_panel_height + control_panel_height;
    if ((0 <= x && x < window_width) && (0 <= y && y < window_height)) {
        // Si on a cliqué dans le panel de jeu
        if (0 <= y && y < game_panel_height) {
            convert_screen_coords_to_grid_coords(&x, &y);
            // Si le joueur a perdu, il ne peut plus poser de mine ou 
            // découvrir des cases
            if (perdu(g)) return; 
            // clique gauche
            if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED) { 
                revele_propagation(&g, x, y);
                MLV_update_window();
            } else if (MLV_get_mouse_button_state(MLV_BUTTON_RIGHT) == MLV_PRESSED) { // clique droit
                poser_drapeau(&g, x, y);
                MLV_wait_milliseconds(200);
            }
        } else { // Si on a cliqué dans le panel des boutons
            if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED) {
                int w, h;
                int panel_middle = game_panel_height + (control_panel_height / 2);
                // Si l'utilisateur veut quitter
                MLV_get_size_of_text("Quitter", &w, &h);
                if ((100 - w/2 <= x && x <= 100 + w/2) && (panel_middle - h/2 <= y && y <= panel_middle + h/2)) {
                    *arret = 1;
                }
                // Si l'utilisateur veut recommencer
                MLV_get_size_of_text("Recommencer", &w, &h);
                if ((game_panel_width - 100 - w/2 <= x && x <= game_panel_width - 100 + w/2) && (panel_middle - h/2 <= y && y <= panel_middle + h/2)) {
                    re_init(&g, game_panel_width, game_panel_height, control_panel_height);
                    MLV_update_window();
                    MLV_wait_milliseconds(200);
                }
            }
        }
    }
}

void revele_propagation(Game* g, int x, int y) {
    if ((0 <= x && x < g->width) && (0 <= y && y < g->height)) {
        int prev = g->terrain[y][x];
        int explose = Pied_g(g, x, y);
        if (prev != g->terrain[y][x]) { // Si on a pas encore découvert la case
            MLV_draw_filled_rectangle(
                                    x * SQUARE_SIZE + 1,
                                    y * SQUARE_SIZE + 1,
                                    SQUARE_SIZE-1,
                                    SQUARE_SIZE-1,
                                    MLV_COLOR_WHITE
                                    );
            if (!explose) { // si on explose pas
                if (g->terrain[y][x] != -11) {
                    MLV_draw_text(
                                 x * SQUARE_SIZE + SQUARE_SIZE/2,
                                 y * SQUARE_SIZE + SQUARE_SIZE/2,
                                 "%d",
                                 MLV_COLOR_BLACK,
                                 g->terrain[y][x]
                                 );
                } else if (g->terrain[y][x] == -11) {
                    int adjacentes[8][2] = {
                        {x+1, y},
                        {x+1, y+1},
                        {x+1, y-1},
                        {x, y+1},
                        {x, y-1},
                        {x-1, y},
                        {x-1, y+1},
                        {x-1, y-1}
                    };
                    for (int i = 0; i < 8; i++) {
                        if ((0 <= adjacentes[i][0] && adjacentes[i][0] < g->width) && (0 <= adjacentes[i][1] && adjacentes[i][1] < g->height)) {    
                            if (g->terrain[adjacentes[i][1]][adjacentes[i][0]] == 0) {
                                revele_propagation(g, adjacentes[i][0], adjacentes[i][1]);
                            }
                        }
                    }
                }
            } else {
                MLV_draw_text(
                             x * SQUARE_SIZE + SQUARE_SIZE/2 - 20,
                             y * SQUARE_SIZE + SQUARE_SIZE/2,
                             "Boom !",
                             MLV_COLOR_BLACK
                             );
            }
        }
    }
}

void poser_drapeau(Game* g, int x, int y) {
    int previous = g->terrain[y][x];
    Drapeau_g(g, x, y);
    if (previous != g->terrain[y][x]) {
        if (g->terrain[y][x] == -9 || g->terrain[y][x] == -10) { // On dessine le drapeau
            MLV_draw_text(
                            x * SQUARE_SIZE + SQUARE_SIZE/2 - 30,
                            y * SQUARE_SIZE + SQUARE_SIZE/2,
                            "Drapeau !",
                            MLV_COLOR_BLACK
                            );
        } else { // on enlève le drapeau
            MLV_draw_filled_rectangle(
                                        x * SQUARE_SIZE + 1,
                                        y * SQUARE_SIZE + 1,
                                        SQUARE_SIZE-1,
                                        SQUARE_SIZE-1,
                                        MLV_COLOR_GRAY
                                        );
        }
        MLV_update_window();
    }
}

int perdu(Game g) {
    for (int y = 0; y < g.height; y++) {
        for (int x = 0; x < g.width; x++) {
            if (g.terrain[y][x] == 10) {
                return 1;
            }
        }
    }
    return 0;
}

void re_init(Game* g, int game_panel_width, int game_panel_height, int control_panel_height) {
    // On réinitialise le plateau
    for (int y = 0; y < g->height; y++) {
        for (int x = 0; x < g->width; x++) {
            if (g->terrain[y][x] == -9 || g->terrain[y][x] == 10) {
                g->terrain[y][x] = 9;
            } else if (g->terrain[y][x] != 9) {
                g->terrain[y][x] = 0;
            }
        }
    }
    MLV_clear_window(MLV_COLOR_WHITE);
    affiche_lignes(*g, game_panel_width, game_panel_height);
    affiche_boutons(*g, game_panel_width, game_panel_height, control_panel_height);
    MLV_update_window();
}

int hasmine_g(Game* g, int x, int y) {
    if ((0 <= x && x < g->width) && (0 <= y && y < g->height)) {
        if (g->terrain[y][x] == 9 || g->terrain[y][x] == -9) {
            return 1;
        }
    }
    return 0;
}

int nbmines_g(Game* g, int x, int y) {
    int coords[8][2] = {
        {x+1, y},
        {x+1, y+1},
        {x+1, y-1},
        {x, y+1},
        {x, y-1},
        {x-1, y},
        {x-1, y+1},
        {x-1, y-1}
    };
    int cpt = 0;
    for (int k = 0; k < 8; k++) {
        cpt += hasmine_g(g, coords[k][0], coords[k][1]);
    }
    return cpt;
}

int Pied_g(Game* g, int x, int y) {
    if (g->terrain[y][x] == 9) {
        g->terrain[y][x] = 10;
        return 1;
    }
    if (g->terrain[y][x] == 0) {
        int nb = nbmines_g(g, x, y);
        if (nb) { // nb != 0
            g->terrain[y][x] = nb;
        } else { 
            g->terrain[y][x] = -11;
        }
    }
    return 0;
}

void Drapeau_g(Game* g, int x, int y) {
    if (0 <= x && x < g->width) {
        if (0 <= y && y < g->height) {
            if (g->terrain[y][x] == 9) {
                g->terrain[y][x] = -9;
            } else if (g->terrain[y][x] == -9) {
                g->terrain[y][x] = 9;
            } else if (g->terrain[y][x] == -10) {
                g->terrain[y][x] = 0;
            } else if (g->terrain[y][x] == 0) {
                g->terrain[y][x] = -10;
            }
        }
    }
}

// Initialisation

void init_t(Game* g) {
    g->width = 10;
    g->height = 6;
    g->mines = 7;
    g->termine = 0; // on suppose que `termine` est un "bool"
    int template[6][10] = {
        {0, 0, 9, 9, 0, 9, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 9, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 9, 9},
        {0, 0, 0, 0, 0, 0, 0, 0, 9, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    int** terrain = malloc(g->height * sizeof(int*));
    if (terrain == NULL) exit(1);
    
    for (int i = 0; i < g->height; i++) {
        int* ligne = calloc(g->width, sizeof(int));
        if (ligne == NULL) exit(1);
        for (int j = 0; j < g->width; j++) {
            ligne[j] = template[i][j];
        }
        terrain[i] = ligne;
    }
    g->terrain = terrain;
}

/* * * * * * * */
/*    main     */
/* * * * * * * */

int main(int argc, char *argv[]) {
    Game g;
    init_t(&g);
    play(g);
    free(g.terrain);
    return 0;
}