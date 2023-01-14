#ifndef MAIN_INIT
#define MAIN_INIT

#include "struct.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <MLV/MLV_all.h>

// Files from minesweeper.c

// Lecture de fichiers + args
void init_jeu(int argc, char* argv[], Game* g);
void init_jeu_avec_param(int argc, char* argv[], Game* g);
void lecture_fichier(FILE* fichier, Game* g);
int lecture_param(FILE* fichier);
void init_tableau(Game* g);
void ecrire_tableau(FILE* fichier, Game* g);
void ecrire_tableau_random(Game* g);
void lecture_arg_j(int i, char* argv[], Game* g);
void free_2d_tab(int** tab, int lignes);
int random_n(int min, int max);

// Graphique
void stop_affichage(void* data);
void affiche_lignes(Game g, int game_panel_width, int game_panel_height, int taille_case);
void affiche_boutons(Game g, int control_panel_width, int game_panel_height, int control_panel_height);
void affiche_grille(Game g, int taille_case);
void affiche_victoire(int game_panel_width, int game_panel_height);
void affiche_defaite(int game_panel_width, int game_panel_height);
void convert_screen_coords_to_grid_coords(int* x, int* y, int taille_case);
void play(Game g);
void action(Game g, int game_panel_width, int game_panel_height, int control_panel_height, int x, int y, int taille_case, int* arret);
void revele_propagation(Game* g, int x, int y, int taille_case);
void poser_drapeau(Game* g, int x, int y, int taille_case);
void dessine_drapeau(int x, int y, int taille_case);
void dessine_case_revelee(int x, int y, int taille_case);
void dessine_nombre(int x, int y, int taille_case, int nb);
void save(Game* g);

// Gestions du jeu
int perdu(Game g);
int victoire_g(Game* g);
void re_init(Game* g, int game_panel_width, int game_panel_height, int control_panel_height, int taille_case);
int hasmine_g(Game* g, int x, int y);
int nbmines_g(Game* g, int x, int y);
int Pied_g(Game* g, int x, int y);
void Drapeau_g(Game* g, int x, int y);

#endif
