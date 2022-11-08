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
 * Initialise un terrain
*/
void init_t(Game* g);

/**
 * Permet de savoir si l'utilisateur ferme la fenêtre
*/
void stop_affichage(void* data);

/**
 * Permet d'afficher les lignes
*/
void affiche_lignes(Game g, int game_panel_width, int game_panel_height);

/**
 * Fonction principale de l'affichage du terrain
*/
void affiche_t_main(Game g);

/**
 * Permet de convertir les coordonnées de la souris dans les coordonnées du tableau
 * Modifie les variables x et y en les coordonnées
 * Retourne 0 si la souris est dans la fenêtre, 1 sinon
*/
void convert_screen_coords_to_grid_coords(int* x, int* y);

/**
 * Gère les interractions avec l'utilisateur et le programme
*/
void play(Game* g, int x, int y);

/**
 * Permet de savoir s'il y a une mine au coordonnée (x, y)
*/
int hasmine_g(Game* g, int x, int y);

/**
 * Renvoie le nombre de mines il y a autour de la case (x, y) 
 * (la case est exclue)
*/
int nbmines_g(Game* g, int x, int y);

/**
 * Pose le pied sur la case (x, y), modifie la case en conséquence et 
 * renvoie si on a explosé
*/
int Pied_g(Game* g, int x, int y);

/**
 * Pose un drapeau sur la case (x, y) si c'est possible
*/
void Drapeau_g(Game* g, int x, int y);

/**
 * Révèle une case et les cases adjacentes si pas de mines dessus
 * Propage la fonction aux cases adjacentes
*/
void revele_propagation(Game* g, int x, int y);

/**
 * Renvoie 1 si la partie est perdue
 * O sinon
*/
int perdu(Game* g);

/* * * * * * * */
/*  Fonctions */
/* * * * * * * */

// Graphique

void stop_affichage(void* data){
	int* arret = (int*) data;
	*arret = 1;
}

void affiche_lignes(Game g, int game_panel_width, int game_panel_height) {
    MLV_draw_filled_rectangle(0, 0, game_panel_width, game_panel_height, MLV_COLOR_GRAY);
    // les lignes horizontales
    for (int y = 0; y < g.height + 1; y++) {
        MLV_draw_line(0, y * SQUARE_SIZE, game_panel_width, y * SQUARE_SIZE, MLV_COLOR_BLACK);
    }

    // les lignes verticales
    for (int x = 0; x < g.width + 1; x++) {
        MLV_draw_line(x * SQUARE_SIZE, 0, x * SQUARE_SIZE, game_panel_height, MLV_COLOR_BLACK);
    }
}

void convert_screen_coords_to_grid_coords(int* x, int* y) {
    *x = *x / SQUARE_SIZE;
    *y = *y / SQUARE_SIZE;
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
                    int adjacentes[4][2] = {
                        {x+1, y},
                        {x-1, y},
                        {x, y+1},
                        {x, y-1}
                    };
                    for (int i = 0; i < 4; i++) {
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

void poser_drapeau(void);

int perdu(Game* g) {
    for (int y = 0; y < g->height; y++) {
        for (int x = 0; x < g->width; x++) {
            if (g->terrain[y][x] == 10) {
                return 1;
            }
        }
    }
    return 0;
}

void play(Game* g, int x, int y) {
    if (perdu(g)) return;
    // on regarde sur quelles cases l'utilisateur a cliqué
    convert_screen_coords_to_grid_coords(&x, &y);
    if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED) { // clique gauche
        revele_propagation(g, x, y);
        MLV_update_window();
    } else if (MLV_get_mouse_button_state(MLV_BUTTON_RIGHT) == MLV_PRESSED) { // clique droit
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
}   


void affiche_control_panel(Game g, int game_panel_width, int game_panel_height, int control_panel_height) {
    MLV_draw_filled_rectangle(0, game_panel_height + 1, game_panel_width, game_panel_height + control_panel_height, MLV_COLOR_WHITE);
    int y = game_panel_height + (control_panel_height / 2);
    int w, h;
    MLV_get_size_of_text("Quitter", &w, &h);
    MLV_draw_text(100 - w/2,
                 y - h/2,
                 "Quitter",
                 MLV_COLOR_BLACK
                 );
    MLV_get_size_of_text("Nombre de mines : 1", &w, &h);
    MLV_draw_text(game_panel_width / 2 - w/2,
                 y - h/2,
                 "Nombre de mines : %d",
                 MLV_COLOR_BLACK,
                 g.mines
                 );
    MLV_get_size_of_text("Recommencer", &w, &h);
    MLV_draw_text(game_panel_width - 100 - w/2,
                 y - h/2,
                 "Recommencer",
                 MLV_COLOR_BLACK,
                 g.mines
                 );
}

void action(Game g, int game_panel_width, int game_panel_height, int control_panel_height, int x, int y, int* arret) {
    // Si l'utilisateur a cliqué dans la fenêtre
    int window_width = game_panel_width;
    int window_height = game_panel_height + control_panel_height;
    if ((0 <= x && x < window_width) && (0 <= y && y < window_height)) {
        // Si on a cliqué dans le panel de jeu
        if (0 <= y && y < game_panel_height) {
            if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED) { // clique gauche
                convert_screen_coords_to_grid_coords(&x, &y);
                revele_propagation(&g, x, y);
                MLV_update_window();
            } else if (MLV_get_mouse_button_state(MLV_BUTTON_RIGHT) == MLV_PRESSED) { // clique droit
                /*poser_drapeau*/
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
                    MLV_wait_milliseconds(500);
                }
            }
        }
    }
}

void affiche_t_main(Game g) {
    int arret = 0; 
    // On enregistre la fonction de call back
    MLV_execute_at_exit(stop_affichage, &arret);

    // Création de la fenêtre
    int game_panel_width = (g.width) * SQUARE_SIZE;
    int game_panel_height = (g.height) * SQUARE_SIZE;
    int control_panel_height = 100;
    MLV_create_window("Minesweeper", "minesweeper", game_panel_width, game_panel_height + control_panel_height);
    
    // Affichage des différents "panels" (la grille et les boutons)
    affiche_lignes(g, game_panel_width, game_panel_height);
    affiche_control_panel(g, game_panel_width, game_panel_height, control_panel_height);
    MLV_update_window();
    
    // Tant que l'utilisateur ne ferme pas la fenêtre
    int x, y;
    do {
        MLV_get_mouse_position(&x, &y);
        action(g, game_panel_width, game_panel_height, control_panel_height, x, y, &arret);
    } while (!arret);

    // on ferme la fenêtre
    MLV_free_window();
}


// Non graphique

int hasmine_g(Game* g, int x, int y){
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

int Pied_g(Game* g, int x, int y){
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

void Drapeau_g(Game* g, int x, int y){
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
    affiche_t_main(g);
    free(g.terrain);
    return 0;
}