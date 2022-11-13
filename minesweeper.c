#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <MLV/MLV_all.h>

/* * * * * * * */
/*  Structures */
/* * * * * * * */

typedef struct _game {
    int width;
    int height;
    int mines;
    int** terrain;
    int termine;
} Game;

/* * * * * * * */
/*  Prototypes */
/* * * * * * * */

/**
 * @brief Permet d'initialiser le plateau de jeu dans tous les cas posssible.
 *
 * @param argc Le nombre d'arguements.
 * @param argv Le tableau contenant les arguments.
 * @param g Structure représentant la grille et les données qui lui sont
 *         propres.
 */
void init_jeu(int argc, char* argv[], Game* g);

/**
 * @brief Permet d'initialiser le plateau de jeu si le fichier est invalides.
 *
 * @param argc Le nombre d'arguements.
 * @param argv Le tableau contenant les arguments.
 * @param g Structure représentant la grille et les données qui lui sont
 *         propres.
 */
void init_jeu_avec_param(int argc, char* argv[], Game* g);

/**
 * @brief Permet de lire le fichier si il est bien formé.
 *
 * @param fichier Fichier contenant le jeu.
 * @param g Structure représentant la grille et les données qui lui sont
 *         propres.
 */
void lecture_fichier(FILE* fichier, Game* g);

/**
 * @brief Permet de lire 1 nombre du fichier voulu.
 *
 * @param fichier Fichier contenant le jeu.
 */
int lecture_param(FILE* fichier);

/**
 * @brief Crée un tableau composé de 0 dans chaque case à partir de
 *          g->height et g->width et l'initialise dans g->tableau.
 *
 * @param g Structure représentant la grille et les données qui lui sont
 *         propres.
 */
void init_tableau(Game* g);

/**
 * @brief Permet de mettre les valeurs du fichier dans le tableau.
 *
 * @param fichier Fichier contenant le jeu.
 * @param g Structure représentant la grille et les données qui lui sont
 *         propres.
 */
void ecrire_tableau(FILE* fichier, Game* g);

/**
 * @brief Permet de mettre des mines aléatoirement dans un tableau composé.
 *
 * @param g Structure représentant la grille et les données qui lui sont
 *         propres.
 */
void ecrire_tableau_random(Game* g);

/**
 * @brief Permet de mettre des mines aléatoirement dans un tableau composé.
 *
 * @param i Indice de la position de l'arguement -j dans argv.
 * @param argv Le tableau contenant les arguments.
 * @param g Structure représentant la grille et les données qui lui sont
 *         propres.
 */
void lecture_arg_j(int i, char* argv[], Game* g);

/**
 * @brief Permet liberer la mémoire utliser par tableau sur tas.
 *
 * @param tab tableau contenant des adresses de tableaux.
 * @param lignes nombre de ligne du tableau.
 */
void free_2d_tab(int** tab, int lignes);

/**
 * @brief Permet de générer un nombre aléatoire entre min et max (inclu).
 *
 * @param min nombre minimum pouvant etre generé.
 * @param max nombre maximum pouvant etre generé.
 */
int random_n(int min, int max);

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
 * @param taille_case La taille des cases du jeu
*/
void affiche_lignes(Game g, int game_panel_width, int game_panel_height,
        int taille_case);

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
 * @brief Affiche l'actuel status d'une grille
 * 
 * @param g Structure représentant la grille et les données qui lui sont 
 *          propres
 * @param taille_case La taille des cases
*/
void affiche_grille(Game g, int taille_case);

/**
 * @brief Affiche le message "Victoire !" en cas de victoire
 * 
 * @param game_panel_width La largeur du panel de jeu
 * @param game_panel_height La hauteur du panel de jeu
*/
void affiche_victoire(int game_panel_width, int game_panel_height);

/**
 * @brief Affiche le message "Défaite !" en cas de défaite
 * 
 * @param game_panel_width La largeur du panel de jeu
 * @param game_panel_height La hauteur du panel de jeu
*/
void affiche_defaite(int game_panel_width, int game_panel_height);

/**
 * @brief Permet de convertir la position de la souris par sa position dans
 *        la grille
 * 
 * @param x La position en x de la souris, qui est modifié pour prendre la 
 *          valeur en x dans le tableau
 * @param y La position en y de la souris, qui est modifié pour prendre la 
 *          valeur en y dans le tableau
 * @param taille_case La taille des cases du jeu
*/
void convert_screen_coords_to_grid_coords(int* x, int* y, int taille_case);

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
 * @param taille_case La taille des cases du jeu
 * @param arret Argument modifié à `1` si l'utilisateur souhaite quitter 
 *        la partie
*/
void action(Game g, int game_panel_width, int game_panel_height,
        int control_panel_height, int x, int y, int taille_case, int* arret);

/**
 * @brief Fonction permettant de découvrir une case. Si la case n'est pas une
 *        mine ou n'est pas adjacente à une mine, elle révèle les cases 
 *        adjacentes etc. Modifie l'aspect graphique de la grille
 *
 * @param g Structure représentant la grille et les données qui lui sont 
 *          propres
 * @param x La position en x de la case a révéler
 * @param y La position en y de la case a révéler
 * @param taille_case La taille des cases du jeu
*/
void revele_propagation(Game* g, int x, int y, int taille_case);

/** @brief Permet de poser un drapeau. Si un drapeau est déjà présent,
 *        le drapeau est retiré. Modifie l'aspect graphique de la grille
 * 
 * @param g Structure représentant la grille et les données qui lui sont 
 *          propres
 * @param x La position en x de la case où poser le drapeau
 * @param y La position en y de la case où poser le drapeau
 * @param taille_case La taille des cases du jeu
*/
void poser_drapeau(Game* g, int x, int y, int taille_case);

/**
 * @brief Dessine un drapeau
 * 
 * @param x La position en x de la case où dessiner le drapeau
 * @param x La position en y de la case où dessiner le drapeau
 * @param taille_case La taille des cases
*/
void dessine_drapeau(int x, int y, int taille_case);

/**
 * @brief Change la couleur d'une case pour signifier qu'elle est découverte
 * 
 * @param x La position en x de la case à révéler
 * @param y La position en y de la case à révéler
 * @param taille_case La taille des cases
*/
void dessine_case_revelee(int x, int y, int taille_case);

/**
 * @brief Permet de d'afficher un nombre sur une case
 * 
 * @param x La position en x de la case à révéler
 * @param y La position en y de la case à révéler
 * @param taille_case La taille des cases
 * @param nb Le nombre a afficher
*/
void dessine_nombre(int x, int y, int taille_case, int nb);

/**
 * @brief Permet de sauvegarder la grille courrante dans le fichier `save.ga`
 * 
 * @param g Structure représentant la grille et les données qui lui sont
 *          propres
*/
void save(Game* g);

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
 * @brief Permet de savoir si la partie est gagnée. Les conditions de 
 *        victoires sont :
 *          - tous les drapeaux sont bien placés (sur des mines donc)
 *          - toutes les cases sont découvertes sauf celles des mines
 * 
 * @param g Structure représentant la grille et les données qui lui sont
 *          propres
 * 
 * @return `1` si c'est gagné, `0` sinon
*/
int victoire_g(Game* g);

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
        int control_panel_height, int taille_case);


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

void init_jeu(int argc, char* argv[], Game* g) {
    int fichierOK = 0;
    if (argv[argc - 1][0] != '-') {  // pas un parametre
        FILE* f;
        f = fopen(argv[argc - 1], "r");
        if (f != 0 && (argc - 1 != 0)) {  // le fichier existe
            fichierOK = 1;
            lecture_fichier(f, g);
            fclose(f);
        }
    }
    if (fichierOK == 0) {
        init_jeu_avec_param(argc, argv, g);
    }
}

void init_jeu_avec_param(int argc, char* argv[], Game* g) {
    int seed = time(NULL);
    g->height = 10, g->width = 10, g->mines = 10;
    for (int i = 1; i < argc - 1; i++) {
        if (argv[i][0] != '-') {  // pas un parametre
            FILE* f;
            f = fopen(argv[i], "r");
            if (f != 0) {  // le fichier existe
                fprintf(stderr, "\x1B[31m /!\\ \x1B[0m 2 paramètres renseignés au mauvais endroit \x1B[31m /!\\ \x1B[0m \n");
                exit(1);
            }
        } else {
            if (argv[i][1] == 'j') {
                lecture_arg_j(i, argv, g);
                i += 3;
            }
            if (argv[i][1] == 'a') {
                seed = atoi(argv[i + 1]);
                i++;
            }
        }
    }
    init_tableau(g);
    srand(seed);
    ecrire_tableau_random(g);
}

void lecture_arg_j(int i, char* argv[], Game* g) {
    int h = atoi(argv[i + 1]), l = atoi(argv[i + 2]), m = atoi(argv[i + 3]);
    if (m >= l * h) {
        fprintf(stderr, "\x1B[31m/!\\ \x1B[0m Plus de mine que de case \x1B[31m /!\\ \x1B[0m \n");
        exit(2);
    }
    g->height = atoi(argv[i + 1]);
    g->width = atoi(argv[i + 2]);
    g->mines = atoi(argv[i + 3]);
}

void ecrire_tableau_random(Game* g) {
    int acc = 0, i = 0, j = 0;
    while (acc != g->mines) {
        i = random_n(0, (g->height) - 1);
        j = random_n(0, (g->width) - 1);
        if (g->terrain[i][j] == 0) {
            g->terrain[i][j] = 9;
            acc++;
        }
    }
}

int random_n(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

void lecture_fichier(FILE* fichier, Game* g) {
    g->height = lecture_param(fichier);
    g->width = lecture_param(fichier);
    g->mines = lecture_param(fichier);
    init_tableau(g);
    ecrire_tableau(fichier, g);
}

int lecture_param(FILE* fichier) {
    char* endPtr;  // pour strtol
    int val = 0;
    char c;
    do {
        c = fgetc(fichier);
        if (c != ' ' && c != '\n') {
            // converti char en entier(evite etape par ascii)
            val = val * 10 + strtol(&c, &endPtr, 10);
        }
    } while (c != EOF && c != ' ' && c != '\n');
    return val;
}

void init_tableau(Game* g) {
    int** tab = calloc(g->height, sizeof(int*));
    if (!tab) {
        exit(1);
    }
    for (int i = 0; i < g->height; i++) {
        int* l = calloc(g->width, sizeof(int));
        if (!l) {
            free_2d_tab(tab, i - 1);
            free(tab);
            exit(1);
        }
        tab[i] = l;
    }
    g->terrain = tab;
}

void ecrire_tableau(FILE* fichier, Game* g) {
    for (int i = 0; i < g->height; i++) {
        for (int j = 0; j < g->width; j++) {
            fscanf(fichier, "%d", &(g->terrain[i][j]));
        }
    }
}

void free_2d_tab(int** tab, int lignes) {
    for (int i = 0; i < lignes; i++) {
        free(tab[i]);
    }
    free(tab);
}

void stop_affichage(void* data) {
	int* arret = (int*) data;
	*arret = 1;
}

void affiche_lignes(Game g, int game_panel_width, int game_panel_height,
                    int taille_case) {
    MLV_draw_filled_rectangle(0, 0, game_panel_width, game_panel_height, 
                             MLV_COLOR_GRAY);
    // les lignes horizontales
    for (int y = 0; y < g.height + 1; y++) {
        MLV_draw_line(0, y * taille_case, game_panel_width, y * taille_case,
                     MLV_COLOR_BLACK);
    }

    // les lignes verticales
    for (int x = 0; x < g.width + 1; x++) {
        MLV_draw_line(x * taille_case, 0, x * taille_case, game_panel_height,
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
    MLV_get_size_of_text("Quit", &w, &h);
    MLV_draw_text(control_panel_width * 1/5 - w/2,
                 y - h/2,
                 "Quit",
                 MLV_COLOR_BLACK
                 );
    MLV_get_size_of_text("Mines : 1", &w, &h);
    MLV_draw_text(control_panel_width * 2/5 - w/2,
                 y - h/2,
                 "Mines : %d",
                 MLV_COLOR_BLACK,
                 g.mines
                 );
    MLV_get_size_of_text("Save", &w, &h);
    MLV_draw_text(control_panel_width * 3/5 - w/2,
                 y - h/2,
                 "Save",
                 MLV_COLOR_BLACK,
                 g.mines
                 );
    MLV_get_size_of_text("Restart", &w, &h);
    MLV_draw_text(control_panel_width * 4/5 - w/2,
                 y - h/2,
                 "Restart",
                 MLV_COLOR_BLACK,
                 g.mines
                 );
}

void affiche_grille(Game g, int taille_case) {
    for (int y = 0; y < g.height; y++) {
        for (int x = 0; x < g.width; x++) {
            if (g.terrain[y][x] == -11) {
                dessine_case_revelee(x, y, taille_case);
            } else if (g.terrain[y][x] == -9 || g.terrain[y][x] == -10) {
                dessine_drapeau(x, y, taille_case);
            } else if (1 <= g.terrain[y][x] && g.terrain[y][x] <= 8) {
                dessine_case_revelee(x, y, taille_case);
                dessine_nombre(x, y, taille_case, g.terrain[y][x]);
            }
        }
    }
}

void affiche_victoire(int game_panel_width, int game_panel_height) {
    MLV_draw_filled_rectangle(0, 0, game_panel_width, game_panel_height,
                             MLV_COLOR_WHITE);
    int w, h;
    MLV_get_size_of_text("Victoire !", &w, &h);
    MLV_draw_text(game_panel_width/2 - w/2,
                 game_panel_height/2 - h/2,
                 "Victoire !",
                 MLV_COLOR_GREEN
                 );
    MLV_update_window();
}

void affiche_defaite(int game_panel_width, int game_panel_height) {
    MLV_draw_filled_rectangle(0, 0, game_panel_width, game_panel_height,
                             MLV_COLOR_WHITE);
    int w, h;
    MLV_get_size_of_text("Défaite !", &w, &h);
    MLV_draw_text(game_panel_width/2 - w/2,
                 game_panel_height/2 - h/2,
                 "Défaite !",
                 MLV_COLOR_RED
                 );
    MLV_update_window();
}

void convert_screen_coords_to_grid_coords(int* x, int* y, int taille_case) {
    *x = *x / taille_case;
    *y = *y / taille_case;
}

void play(Game g) {
    int arret = 0;
    // On enregistre la fonction de call back
    MLV_execute_at_exit(stop_affichage, &arret);

    // On détermine les dimensions des cases
    int taille_case = 100;
    unsigned int w, h;
    int game_panel_width = (g.width) * taille_case;
    int game_panel_height = (g.height) * taille_case;
    int control_panel_height = 50;

    MLV_get_desktop_size(&w, &h);
    
    int window_w = (g.width) * taille_case;
    int window_h = (g.height) * taille_case + control_panel_height;
    while (window_w + 100 > w || window_h + 100 > h) {
        taille_case--;
        window_w = (g.width) * taille_case;
        window_h = (g.height) * taille_case + control_panel_height;
    }
    game_panel_width = (g.width) * taille_case;
    game_panel_height = (g.height) * taille_case;

    // Création de la fenêtre
    MLV_create_window("Minesweeper", "minesweeper", window_w,
                     window_h);
    
    // Affichage des différents "panels" (la grille et les boutons)
    affiche_lignes(g, game_panel_width, game_panel_height, taille_case);
    affiche_boutons(g, game_panel_width, game_panel_height, 
                   control_panel_height);
    affiche_grille(g, taille_case);
    MLV_update_window();
    
    // Tant que l'utilisateur ne ferme pas la fenêtre
    int x, y;
    do {
        MLV_get_mouse_position(&x, &y);
        action(g, game_panel_width, game_panel_height, control_panel_height,
              x, y, taille_case, &arret);
    } while (!arret);

    // on ferme la fenêtre
    MLV_free_window();
}

void action(Game g, int game_panel_width, int game_panel_height, 
           int control_panel_height, int x, int y, int taille_case, 
           int* arret) {
    // Si l'utilisateur a cliqué dans la fenêtre
    int window_width = game_panel_width;
    int window_height = game_panel_height + control_panel_height;
    if ((0 <= x && x < window_width) && (0 <= y && y < window_height)) {
        // Si on a cliqué dans le panel de jeu
        if (0 <= y && y < game_panel_height) {
            convert_screen_coords_to_grid_coords(&x, &y, taille_case);
            // Si le joueur a perdu, il ne peut plus poser de mine ou 
            // découvrir des cases
            if (perdu(g)) return; 
            // clique gauche
            if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == 
                MLV_PRESSED) { 
                revele_propagation(&g, x, y, taille_case);
                MLV_update_window();
            } else if (MLV_get_mouse_button_state(MLV_BUTTON_RIGHT) == 
                       MLV_PRESSED) { // clique droit
                poser_drapeau(&g, x, y, taille_case);
                MLV_wait_milliseconds(400);
            }
            if (victoire_g(&g)) {
                affiche_victoire(game_panel_width, game_panel_height);
            } else if (perdu(g)) {
                affiche_defaite(game_panel_width, game_panel_height);
            }
        } else { // Si on a cliqué dans le panel des boutons
            if (MLV_get_mouse_button_state(MLV_BUTTON_LEFT) == MLV_PRESSED) {
                int w, h;
                int panel_middle = game_panel_height + (control_panel_height / 2);
                // Si l'utilisateur veut quitter
                MLV_get_size_of_text("Quitter", &w, &h);
                if ((game_panel_width * 1/5 - w/2 <= x 
                     && x <= game_panel_width * 1/5 + w/2) 
                    && (panel_middle - h/2 <= y 
                     && y <= panel_middle + h/2)) {
                    *arret = 1;
                }
                // Si l'utilisateur veut sauvegarder
                if ((game_panel_width * 3/5 - w/2 <= x
                     && x <= game_panel_width * 3/5 + w/2) 
                    && (panel_middle - h/2 <= y 
                     && y <= panel_middle + h/2)) {
                    save(&g);
                }
                // Si l'utilisateur veut recommencer
                MLV_get_size_of_text("Recommencer", &w, &h);
                if ((game_panel_width * 4/5 - w/2 <= x 
                     && x <= game_panel_width * 4/5 + w/2) 
                    && (panel_middle - h/2 <= y 
                     && y <= panel_middle + h/2)) {
                    re_init(&g, game_panel_width, game_panel_height,
                            control_panel_height, taille_case);
                    MLV_update_window();
                    MLV_wait_milliseconds(400);
                }
            }
        }
    }
}

void revele_propagation(Game* g, int x, int y, int taille_case) {
    if ((0 <= x && x < g->width) && (0 <= y && y < g->height)) {
        int prev = g->terrain[y][x];
        int explose = Pied_g(g, x, y);
        // Si on a pas encore découvert la case
        if (prev != g->terrain[y][x]) {
            dessine_case_revelee(x, y, taille_case);
            if (!explose) { // si on explose pas
                if (g->terrain[y][x] != -11) {
                    dessine_nombre(x, y, taille_case, g->terrain[y][x]);
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
                        if ((0 <= adjacentes[i][0] 
                             && adjacentes[i][0] < g->width) 
                            && (0 <= adjacentes[i][1] 
                             && adjacentes[i][1] < g->height)) {    
                            if (g->terrain[adjacentes[i][1]][adjacentes[i][0]] == 0) {
                                revele_propagation(g, adjacentes[i][0], 
                                                  adjacentes[i][1],
                                                  taille_case);
                            }
                        }
                    }
                }
            }
        }
    }
}

void poser_drapeau(Game* g, int x, int y, int taille_case) {
    int previous = g->terrain[y][x];
    Drapeau_g(g, x, y);
    if (previous != g->terrain[y][x]) {
        // On dessine le drapeau
        if (g->terrain[y][x] == -9 || g->terrain[y][x] == -10) {
            dessine_drapeau(x, y, taille_case);
        } else { // on enlève le drapeau
            MLV_draw_filled_rectangle(
                                        x * taille_case + 1,
                                        y * taille_case + 1,
                                        taille_case-1,
                                        taille_case-1,
                                        MLV_COLOR_GRAY
                                        );
        }
        MLV_update_window();
    }
}

void dessine_drapeau(int x, int y, int taille_case) {
    int xx[3] = {
        x * taille_case + taille_case/4,
        x * taille_case + taille_case*3/4,
        x * taille_case + taille_case/4,
    };
    int yy[3] = {
        y * taille_case + taille_case*1/4,
        y * taille_case + taille_case/2,
        y * taille_case + taille_case*3/4,
    };
    MLV_draw_filled_polygon(xx, yy, 3, MLV_COLOR_RED);
}

void dessine_case_revelee(int x, int y, int taille_case) {
    MLV_draw_filled_rectangle(
                            x * taille_case + 1,
                            y * taille_case + 1,
                            taille_case-1,
                            taille_case-1,
                            MLV_COLOR_WHITE
                            );
}

void dessine_nombre(int x, int y, int taille_case, int nb) {
    MLV_draw_text(
                 x * taille_case + taille_case/2,
                 y * taille_case + taille_case/2,
                 "%d",
                 MLV_COLOR_BLACK,
                 nb
                 );
}

void save(Game* g) {
    // On ouvre un fichier
    FILE* f = fopen("save.ga", "w");
    // Ici, la vérification de l'existence de f est optionnelle : si f
    // n'existe pas, il est créé
    fprintf(f, "%d %d %d\n", g->height, g->width, g->mines);
    for (int y = 0; y < g->height; y++) {
        for (int x = 0; x < g->width; x++) {
            if (x == g->width - 1) {
                fprintf(f, "%d", g->terrain[y][x]);
            } else {
                fprintf(f, "%d ", g->terrain[y][x]);
            }
        }
        if (y != g->height - 1) {
            fprintf(f, "\n");
        }
    }
    fclose(f);
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

int victoire_g(Game* g) {
    int nb_drapeau_bien_place = 0;
    int nb_mines = 0;
    int cases_decouvertes = 0;
    for (int y = 0; y < g->height; y++) {
        for (int x = 0; x < g->width; x++) {
            int case_t = g->terrain[y][x];
            if (case_t == 9) { // mine
                nb_mines++;
            } else if (case_t == -9) { // mine + drapeau bien placé
                nb_mines++;
                nb_drapeau_bien_place++;
            } else if (case_t == -10) { // drapeau mal placé
                nb_drapeau_bien_place--;
            } else if (case_t == -11 || (1 <= case_t && case_t <= 8)) {
                // case découverte sans mine
                cases_decouvertes++;
            }
        }
    }
    return nb_drapeau_bien_place == nb_mines 
           || ((g->width * g->height - cases_decouvertes) == nb_mines);
}

void re_init(Game* g, int game_panel_width, int game_panel_height, 
             int control_panel_height, int taille_case) {
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
    affiche_lignes(*g, game_panel_width, game_panel_height, taille_case);
    affiche_boutons(*g, game_panel_width, game_panel_height, 
                    control_panel_height);
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

/* * * * * * * */
/*    main     */
/* * * * * * * */

int main(int argc, char* argv[]) {
    Game g;
    init_jeu(argc, argv, &g);
    play(g);
    free_2d_tab(g.terrain, g.height);
    return 0;
}