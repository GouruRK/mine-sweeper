#include <stdio.h>
#include <stdlib.h>

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

void lecture_arguments(int argc, char* argv[], Game* g);

void lecture_fichier(FILE* fichier, Game* g);

int lecture_param(FILE* fichier);

void init_tableau(Game* g);  // avec que des 0

void lecture_tableau(FILE* fichier, Game* g);  // supposons fichier bien formé.

void lecture(Game* g);

void free_2d_tab(int** tab, int lignes);

/* * * * * * * */
/*  Fonctions */
/* * * * * * * */

void lecture_arguments(int argc, char* argv[], Game* g) {
    int fichierOK = 0;
    if (argv[argc - 1][0] != '-') {  // pas un parametre
        printf("%s\n", argv[argc - 1]);
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
        for (int i = 1; i < argc - 1; i++) {
            if (argv[i][0] != '-') {  // pas un parametre
                FILE* f;
                f = fopen(argv[i], "r");
                if (f != 0) {  // le fichier existe
                    fprintf(stderr, "\x1B[31m" "/!\\ " "\x1B[0m" " 2 fichiers renseignés " "\x1B[31m" "/!\\" "\x1B[0m" "\n");
                    exit(1);
                }
            } else {
                printf("%c\n", argv[i][1]);
                printf("%s\n", argv[i + 1]);
                printf("%s\n", argv[i + 2]);
                printf("%s\n", argv[i + 3]);

                if (argv[i][1] == 'j') {
                    printf("%d", i);
                    int h = atoi(argv[i + 1]), l = atoi(argv[i + 2]), m = atoi(argv[i + 3]);
                    if (m >= l * h) {
                        fprintf(stderr, "Trop de mines\n");
                        exit(1);
                    }
                    g->height = atoi(argv[i + 1]);
                    g->width = atoi(argv[i + 2]);
                    g->mines = atoi(argv[i + 3]);
                    i += 3;
                    printf("%d", i);
                }
            }
        }
    }
}

void lecture_fichier(FILE* fichier, Game* g) {
    g->height = lecture_param(fichier);
    g->width = lecture_param(fichier);
    g->mines = lecture_param(fichier);
    init_tableau(g);
    lecture_tableau(fichier, g);
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

void lecture_tableau(FILE* fichier, Game* g) {
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
    lecture_arguments(argc, argv, &g);
    lecture(&g);
    free_2d_tab(g.terrain, g.height);
    // printf("\n");
    // printf("h : %d, l : %d nm : %d\n", g.height, g.width, g.mines);
    return 0;
}