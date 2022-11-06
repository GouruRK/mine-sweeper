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
void affiche_lignes(Game g, int window_width, int window_height);

/**
 * Fonction principale de l'affichage du terrain
*/
void affiche_t_main(Game g);

/**
 * Permet de convertir les coordonnées de la souris dans les coordonnées du tableau
 * Modifie les variables x et y en les coordonnées
 * Retourne 0 si la souris est dans la fenêtre, 1 sinon
*/
int convert_screen_coords_to_grid_coords(int window_width, int window_height, int x_souris, int y_souris, int* x, int* y);

/**
 * Gère les interractions avec l'utilisateur et le programme
*/
void play(Game* g, int window_width, int window_height, int* clique_droit);

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

/* * * * * * * */
/*  Fonctions */
/* * * * * * * */

// Graphique

void stop_affichage(void* data){
	int* arret = (int*) data;
	*arret = 1;
}

void affiche_lignes(Game g, int window_width, int window_height) {
    // les lignes horizontales
    for (int y = 0; y < g.height + 2; y++) {
        MLV_draw_line(0, y * SQUARE_SIZE, window_width, y * SQUARE_SIZE, MLV_COLOR_BLACK);
    }

    // les lignes verticales
    for (int x = 0; x < g.width + 2; x++) {
        MLV_draw_line(x * SQUARE_SIZE, 0, x * SQUARE_SIZE, window_height, MLV_COLOR_BLACK);
    }
}

int convert_screen_coords_to_grid_coords(int window_width, int window_height, int x_souris, int y_souris, int* x, int* y) {
    if ((0 <= x_souris && x_souris < window_width) || (0 <= y_souris && y_souris < window_height)) {
        *x = x_souris / SQUARE_SIZE;
        *y = y_souris / SQUARE_SIZE;
        return 0;
    }
    return 1;
}

void play(Game* g, int window_width, int window_height, int* clique_droit) {
    // On regarde si l'utilisateur a cliqué :
    int x_souris, y_souris;
    int x, y;
    MLV_get_mouse_position(&x_souris, &y_souris);
    if(!convert_screen_coords_to_grid_coords(window_width, window_height, x_souris, y_souris, &x, &y)) { // si l'utilisateur a cliqué dans la fenêtre
        if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED) { // clique gauche
            int prev = g -> terrain[y][x];
            int explose = Pied_g(g, x, y);
            if (prev != g -> terrain[y][x]) { // Si on a pas encore découvert la case
                MLV_draw_filled_rectangle(
                                         x * SQUARE_SIZE + 1,
                                         y * SQUARE_SIZE + 1,
                                         SQUARE_SIZE-1,
                                         SQUARE_SIZE-1,
                                         MLV_COLOR_WHITE
                                         );
                if (!explose) { // si on a pas explosé
                    if (g -> terrain[y][x] != -11) {
                        MLV_draw_text(
                                     x * SQUARE_SIZE + SQUARE_SIZE/2,
                                     y * SQUARE_SIZE + SQUARE_SIZE/2,
                                     "%d",
                                     MLV_COLOR_BLACK,
                                     g -> terrain[y][x]
                                     );
                                    
                    }
                } else {
                    MLV_draw_text(
                                 x * SQUARE_SIZE + SQUARE_SIZE/2 - 20,
                                 y * SQUARE_SIZE + SQUARE_SIZE/2,
                                 "Boom !",
                                 MLV_COLOR_BLACK
                                 );
                }
            MLV_update_window();
            *clique_droit = 0;
            }
        } else if (MLV_get_mouse_button_state(MLV_BUTTON_RIGHT) == MLV_PRESSED) { // clique droit
            if (*clique_droit) {
                return;
            }
            *clique_droit = 1; 
            int previous = g -> terrain[y][x];
            Drapeau_g(g, x, y);
            if (previous != g -> terrain[y][x]) {
                if (g -> terrain[y][x] == -9 || g -> terrain[y][x] == -10) { // On dessine le drapeau
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
        } else {
            *clique_droit = 0; 
        }
    }   
}

void affiche_t_main(Game g) {
    int arret = 0; 
    // On enregistre la fonction de call back
    MLV_execute_at_exit(stop_affichage, &arret);

    // Création de la fenêtre
    int window_width = (g.width) * SQUARE_SIZE;
    int window_height = (g.height) * SQUARE_SIZE;
    MLV_create_window("Minesweeper", "minesweeper", window_width, window_height);
    MLV_draw_filled_rectangle(0, 0, window_width, window_height, MLV_COLOR_GRAY);
    
    // Tant que l'utilisateur ne ferme pas la fenêtre
    affiche_lignes(g, window_width, window_height);
    MLV_update_window();
    int clic_gauche = 0;
    do {
        play(&g, window_width, window_height, &clic_gauche);
        // affiche_lignes(g, window_width, window_height);
        // MLV_update_window();
    } while (!arret);

    // on ferme la fenêtre
    MLV_free_window();
}


// Non graphique

int hasmine_g(Game* g, int x, int y){
    if ((0 <= x && x < g -> width) && (0 <= y && y < g -> height)) {
        if (g -> terrain[y][x] == 9 || g -> terrain[y][x] == -9) {
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
    if (g -> terrain[y][x] == 9) {
        g -> terrain[y][x] = 10;
        return 1;
    }
    if (g -> terrain[y][x] == 0) {
        int nb = nbmines_g(g, x, y);
        if (nb) { // nb != 0
            g -> terrain[y][x] = nb;
        } else { 
            g -> terrain[y][x] = -11;
        }
    }
    return 0;
}

void Drapeau_g(Game* g, int x, int y){
    if (0 <= x && x < g -> width) {
        if (0 <= y && y < g -> height) {
            if (g -> terrain[y][x] == 9) {
                g -> terrain[y][x] = -9;
            } else if (g -> terrain[y][x] == -9) {
                g -> terrain[y][x] = 9;
            } else if (g -> terrain[y][x] == -10) {
                g -> terrain[y][x] = 0;
            } else if (g -> terrain[y][x] == 0) {
                g -> terrain[y][x] = -10;
            }
        }
    }
}

// Initialisation

void init_t(Game* g) {
    g -> width = 10;
    g -> height = 6;
    g -> mines = 7;
    g -> termine = 0; // on suppose que `termine` est un "bool"
    int template[6][10] = {
        {0, 0, 9, 9, 0, 9, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 9, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 9, 9},
        {0, 0, 0, 0, 0, 0, 0, 0, 9, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };
    int** terrain = malloc(g -> height * sizeof(int*));
    if (terrain == NULL) exit(1);
    
    for (int i = 0; i < g -> height; i++) {
        int* ligne = calloc(g -> width, sizeof(int));
        if (ligne == NULL) exit(1);
        for (int j = 0; j < g -> width; j++) {
            ligne[j] = template[i][j];
        }
        terrain[i] = ligne;
    }
    g -> terrain = terrain;
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