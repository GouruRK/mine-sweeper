#include <stdio.h>
#include <MLV/MLV_all.h>

/* * * * * * * */
/*    Define   */
/* * * * * * * */

#define SQUARE_SIZE 100

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
int convert_screen_coords_to_grid_coords(Game g, int window_width, int window_height, int x_souris, int y_souris, int* x, int* y);

/**
 * Gère les interractions avec l'utilisateur et le programme
*/
int play(Game g, int window_width, int window_height);
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

int convert_screen_coords_to_grid_coords(Game g, int window_width, int window_height, int x_souris, int y_souris, int* x, int* y) {
    if ((0 <= x_souris && x_souris < window_width) || (0 <= y_souris && y_souris < window_height)) {
        *x = x_souris / SQUARE_SIZE;
        *y = y_souris / SQUARE_SIZE;
        return 0;
    }
    return 1;
}

void play(Game g, int window_width, int window_height) {
    // On regarde si l'utilisateur a cliqué :
    int x_souris, y_souris;
    int x, y;
    MLV_get_mouse_position(&x_souris, &y_souris);
    if(!convert_screen_coords_to_grid_coords(g, window_width, window_height, x_souris, y_souris, &x, &y)) { // si l'utilisateur a cliqué dans la fenêtre
        if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED) { // clique gauche
            MLV_draw_filled_rectangle(x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE, MLV_COLOR_WHITE);
        } else if (MLV_get_mouse_button_state(MLV_BUTTON_RIGHT) == MLV_PRESSED) { // clique droit
            /*Nothing*/
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
    do {
        play(g, window_width, window_height);
        affiche_lignes(g, window_width, window_height);
        MLV_update_window();   
    } while (!arret);

    // on ferme la fenêtre
    MLV_free_window();
}


// Initialisation

void init_t(Game* g) {
    g -> width = 10;
    g -> height = 6;
    g -> mines = 8;
    g -> termine = 0; // on suppose que `termine` est un "bool"
    int l1[10] = {0, 0, 9, 9, 0, 9, 0, 0, 0, 0}; 
    int l2[10] = {0, 2, 0, 3, 0, 0, 0, 0, 0, 0}; 
    int l3[10] = {0, 1, 9, 0, 0, 0, 0, 0, 0, 0}; 
    int l4[10] = {0, 0, 0, 0, 0, 0, 0, 0, 9, 9}; 
    int l5[10] = {0, 0, 0, 0, 0, 0, 0, 0, 9, 0}; 
    int l6[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};    
    int *vect[6];
    vect[0] = l1;
    vect[1] = l2;
    vect[2] = l3;
    vect[3] = l4;
    vect[4] = l5;
    vect[5] = l6;
    g -> terrain = vect;
}

/* * * * * * * */
/*    main     */
/* * * * * * * */

int main(int argc, char *argv[]) {
    Game g;
    init_t(&g);
    affiche_t_main(g);
    return 0;
}