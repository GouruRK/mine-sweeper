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

void lecture_tableau(FILE* fichier, Game* g);

void lecture(Game* g);

/* * * * * * * */
/*  Fonctions */
/* * * * * * * */

void lecture_arguments(int argc, char* argv[], Game* g) {
    // for (int i = 1; i < argc; i++) {
    //     if (argv[i][0] != '-') {  // pas un parametre
    //         FILE* f;
    //         f = fopen(argv[i], "r");
    //         if (f != 0) {  // le fichier existe
    //             lecture_fichier(f, g);
    //             fclose(f);
    //         }
    //     }
    // }
    FILE* f = fopen("./test.txt", "r");
    lecture_fichier(f, g);
    fclose(f);
}

void lecture_fichier(FILE* fichier, Game* g) {
    g->height = lecture_param(fichier);
    g->width = lecture_param(fichier);
    g->mines = lecture_param(fichier);
    // printf("ok");
    lecture_tableau(fichier, g);
}

int lecture_param(FILE* fichier) {
    char* endPtr;  // pour strol
    int val = 0;
    char c;
    do {
        c = fgetc(fichier);
        if (c != ' ' && c != '\n') {
            val = val * 10 + strtol(&c, &endPtr, 10);  // converti char en entier(evite Ã©tape par ascii)
            // printf("val*puiss=%d val=%d\n",val*10,val);
        }
    } while (c != EOF && c != ' ' && c != '\n');
    return val;
}

void lecture_tableau(FILE* fichier, Game* g) {
    // init tab
    int** tab = calloc(g->height, sizeof(int*));
    for (int i = 0; i < g->height; i++) {
        int* l = calloc(g->width, sizeof(int));
        tab[i] = l;
    }
    // printf("\n\n%d\n",tab[1][1]);
    g->terrain = tab;

    // lecture(g);
    // printf("Fini\n");

    // remplir tab
    char* endPtr;  // pour strol
    int x = 0, y = 0, val = 0, negatif = 0;
    char c = fgetc(fichier);

    while (c != EOF) {
        if (c == '-') {
            negatif = 1;
        } else if (c == ' ') {
            if (negatif == 1) {
                g->terrain[x][y] = -val;
                negatif = 0;
            } else {
                g->terrain[x][y] = val;
            }
            // printf("%d ", g->terrain[x][y]);
            val = 0;
            y++;
        } else if (c == '\n') {
            // printf("Coucou x=%d\n", x);
            if (negatif == 1) {
                g->terrain[x][y] = -val;
                negatif = 0;
            } else {
                g->terrain[x][y] = val;
            }
            // printf("%d\n", g->terrain[x][y]);
            val = 0;
            y = 0;
            x++;
        } else {
            val = val * 10 + strtol(&c, &endPtr, 10);
        }
        c = fgetc(fichier);
    }
    g->terrain[x][y] = val;
        // printf("x:%d y:%d ", x, y);
        // printf("%c\n", c);
} 

    /*
    printf("\n");
    for(int i = 0; i < g->height; i++){
        printf("\n");
        for(int j = 0; j < g->width; j++){
            printf("%d ",g->terrain[i][j]);
        }
    }
    */


void lecture(Game* g) {
    for (int i = 0; i < g->height; i++) {
        for (int j = 0; j < g->width; j++) {
            printf("%d ", g->terrain[i][j]);
        }
        printf("\n");
    }
}

/* * * * * * * */
/*    main     */
/* * * * * * * */

int main(int argc, char* argv[]) {
    Game g;
    lecture_arguments(argc, argv, &g);
    //printf("\n");
    lecture(&g);
    // for (int i = 0; i < g.height; i++) {
    //     printf("\n");
    //     for (int j = 0; j < g.width; j++) {
    //         printf("%d ", g.terrain[i][j]);
    //     }
    // }
    return 0;
}