#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

void lecture(Game* g);

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

/* * * * * * * */
/*  Fonctions */
/* * * * * * * */

void init_jeu(int argc, char* argv[], Game* g) {
    int fichierOK = 0;
    if (argv[argc - 1][0] != '-') {  // pas un parametre
        FILE* f;
        f = fopen(argv[argc - 1], "r");
        if (f != 0) {  // le fichier existe
            fichierOK = 1;
            lecture_fichier(f, g);
            fclose(f);

        } else {
            f = fopen("mine.ga", "r");
            if (f != 0) {  // le fichier de secours existe
                fichierOK = 1;
                lecture_fichier(f, g);
                fclose(f);
            }
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
                fprintf(stderr, "\x1B[31m /!\\ \x1B[0m 2 fichiers renseignés \x1B[31m /!\\ \x1B[0m \n");
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
        printf("i=%d j=%d\n", i, j);
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
            val = val * 10 + strtol(&c, &endPtr, 10);  // converti char en entier(evite etape par ascii)
            // printf("val*puiss=%d val=%d\n",val*10,val);
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

void lecture(Game* g) {
    for (int i = 0; i < g->height; i++) {
        for (int j = 0; j < g->width; j++) {
            printf("%d ", g->terrain[i][j]);
        }
        printf("\n");
    }
}

void free_2d_tab(int** tab, int lignes) {
    for (int i = 0; i < lignes; i++) {
        free(tab[i]);
    }
    free(tab);
}

/* * * * * * * */
/*    main     */
/* * * * * * * */

int main(int argc, char* argv[]) {
    Game g;
    init_jeu(argc, argv, &g);
    lecture(&g);
    free_2d_tab(g.terrain, g.height);
    printf("\n");
    printf("h : %d, l : %d nm : %d\n", g.height, g.width, g.mines);
    return 0;
}