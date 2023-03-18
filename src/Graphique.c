/* Auteur : Gaël PAQUETTE && Anass OUSAID
 * Création : 24/03/2022
 * Dernière modification : 24/03/2022 */
/* Graphique.c */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ncurses.h>
#include <string.h>
#include <ctype.h>

#include <Graphique.h>

void afficher_regle(void) {
    /*
    Fonction qui affiche les reègles du jeu pour valider un mot et réinitialiser un mot/
    */
    mvprintw(0, 0, "Pour valider un mot, veuillez appuyer sur le touche 'ENTREE'");
    mvprintw(1, 0, "Pour valider une lettre, veuillez appuyer sur la touche 'q'");
    mvprintw(2, 0, "Pour réinitialiser un mot, veuillez appuyer sur la touche 'a'");
    mvprintw(3, 0, "Pour choisir une lettre, veuillez utiliser le pavé directionnelle");
    mvprintw(4, 0, "Pour quitter la partie, veuillez appuyer sur la touche 'r'");
    refresh();
}

void afficher_score(int score) {
    /*
    Fonction qui affiche sur la fenêtre en haut à gauche le score du joueur.

    Renvoie rien.
    */

    mvprintw(6, 0, "Score :     %d\r", score);
    refresh();
}

void afficher_lettre(Plateau plate, int LINES, int COLS) {
    /*
    Fonction qui affiche la structure du plateau à l'écran.

    Renvoie rien.
    */

    int i, j;
    for (i = 0; i < NB_CASES; ++i) {
        for (j = 0; j < NB_CASES; ++j) {
            attron(A_NORMAL);
            mvprintw((LINES / 3) + (i * TAILLE_CASE), (COLS / 3) + (j * (TAILLE_CASE * 2)), " %c ", plate.tab[i][j]);
            attroff(A_NORMAL);
        }
    }
    refresh();
}

void afficher_mot(char* mot) {
    /*
    Fonction qui affiche le mot 'mot' de type char passée par adresse. 

    Renvoie rien.
    */
    assert(mot != NULL);
    
    mvprintw(8, 0, "Mot construit :                                         \r");
    mvprintw(8, 0, "Mot construit :      %s\r", mot);
}

void surbrillance(Plateau plate, int LINES, int COLS, int x, int y) {
    /*
    Fonction que affiche en subrillance la lettre selectionner.

    Renvoie rien.
    */
    int i, j;
    for (i = 0; i < NB_CASES; ++i) {
        for (j = 0; j < NB_CASES; ++j) {
            if ((LINES / 3) + (i * TAILLE_CASE) == x && (COLS / 3) + (j * (TAILLE_CASE * 2)) == y) {
                attron(A_REVERSE);
                mvprintw((LINES / 3) + (i * TAILLE_CASE), (COLS / 3) + (j * (TAILLE_CASE * 2)), " %c ", plate.tab[i][j]);
                attroff(A_REVERSE);
            } else {
                attron(A_NORMAL);
                mvprintw((LINES / 3) + (i * TAILLE_CASE), (COLS / 3) + (j * (TAILLE_CASE * 2)), " %c ", plate.tab[i][j]);
                attroff(A_NORMAL);
            }
        }
    }
    refresh();
}

void affiche_fin_jeu(int score, int LINES, int COLS) {
    /*
    Fonction qui affiche proprement la fin de partie.
    
    Renvoie rien.
    */
    clear();
    mvprintw(LINES / 2, (COLS / 2) - 3, "Fin de partie");
    mvprintw((LINES / 2) + 5, (COLS / 2) - 3, "Votre score : %d", score);
    refresh();
}


char * saisie_mot(Plateau plate, int LINES, int COLS, int* sortie) {
    /* 
    Fonction qui permet de saisir un mot a l'écran.

    Renvoie rien.
    */
    int touche;
    char * new = (char*)malloc(sizeof(char) * MAX_LETTRES_MOT);
    int x = LINES / 3, y = COLS / 3, last_x = LINES / 3, last_y = LINES / 3, i = 0, j = 0;
    char lettre = tolower(plate.tab[i][j]);

    while (1) {
        surbrillance(plate, LINES, COLS, x, y);
        afficher_mot(new);
        refresh();
        touche = getch();
        if (touche != ERR) {
            /* Si l'utilisateur appuye sur la touche 'ENTREE', il valide le mot */ 
            if (touche == '\n')
                break;
            /* Si l'utilisateur appuye sur la touche 'r' , il quitte la partie */
            if (touche == 'r') {
                *sortie = 1;
                break;
            }
            /* Si l'utilisateur appuye sur la touche 'q' , il valide la lettre choisie */
            if (touche == 'q') {
                last_x = x;
                last_y = y;
                strcpy(new, construit_mot(new, lettre));
            }
            /* Si l'utilisateur appuye sur la touche 'a', il réinitialise le mot */
            if (touche == 'a')
                strcpy(new, "");
            /* Si l'utilisateur appuye sur la touche UP du pavé directionnelle */
            if (touche == KEY_UP) {
                if (x > LINES / 3) {
                    x = x - (1 * TAILLE_CASE);
                    /* Le mot est vide */
                    if (strcmp(new, "") == 0) {
                        i = (x - (LINES / 3)) / TAILLE_CASE;
                        j = (y - (COLS / 3)) / (2 * TAILLE_CASE);
                        lettre = tolower(plate.tab[i][j]);
                    } else {
                        /* le mot n'est pas vide */
                        if (x < (last_x - (1 * TAILLE_CASE))) {
                            x = last_x - (1 * TAILLE_CASE);
                            continue;
                        } else if (x == last_x)
                            continue;
                        else {
                            i = (x - (LINES / 3)) / TAILLE_CASE;
                            j = (y - (COLS / 3)) / (2 * TAILLE_CASE);
                            lettre = tolower(plate.tab[i][j]);
                        }
                    }
                }
            }
            /* Si l'utilisateur appuye sur la touche DOWN du pavé directionnelle */
            if (touche == KEY_DOWN) {
                if (x < ((LINES / 3) + (3 * TAILLE_CASE))) {
                    x = x + (1 * TAILLE_CASE);
                    /* Le mot est vide */
                    if (strcmp(new, "") == 0) {
                        i = (x - (LINES / 3)) / TAILLE_CASE;
                        j = (y - (COLS / 3)) / (2 * TAILLE_CASE);
                        lettre = tolower(plate.tab[i][j]);
                    } else {
                        /* Le mot n'est pas vide */
                        if (x > (last_x + (1 * TAILLE_CASE))) {
                            x = last_x + (1 * TAILLE_CASE);
                            continue;
                        } else if (x == last_x)
                            continue;
                        else {
                            i = (x - (LINES / 3)) / TAILLE_CASE;
                            j = (y - (COLS / 3)) / (2 * TAILLE_CASE);
                            lettre = tolower(plate.tab[i][j]);
                        }
                    }
                }
            }
            /* Si l'utilisateur appuye sur la touche LEFT du pavé directionnelle */
            if (touche == KEY_LEFT) {
                if (y > COLS / 3) {
                    y = y - (2 * TAILLE_CASE);
                    /* Le mot est vide */
                    if (strcmp(new, "") == 0) {
                        i = (x - (LINES / 3)) / TAILLE_CASE;
                        j = (y - (COLS / 3)) / (2 * TAILLE_CASE);
                        lettre = tolower(plate.tab[i][j]);
                    } else {
                        /* Le mot n'est pas vide */
                        if (y < (last_y - (2 * TAILLE_CASE))) {
                            y = last_y - (2 * TAILLE_CASE);
                            continue;
                        } else if (y == last_y)
                            continue;
                        else {
                            i = (x - (LINES / 3)) / TAILLE_CASE;
                            j = (y - (COLS / 3)) / (2 * TAILLE_CASE);
                            lettre = tolower(plate.tab[i][j]);
                        }
                    }
                }
            }
            /* Si l'utilisateur appuye sur la touche RIGHT du pavé directionnelle */
            if (touche == KEY_RIGHT) {
                if (y < ((COLS / 3) + (6 * TAILLE_CASE))) {
                    y = y + (2 * TAILLE_CASE);
                    /* Le mot est vide */
                    if (strcmp(new, "") == 0) {
                        i = (x - (LINES / 3)) / TAILLE_CASE;
                        j = (y - (COLS / 3)) / (2 * TAILLE_CASE);
                        lettre = tolower(plate.tab[i][j]);
                    } else {
                        /* Le mot n'est pas vide */
                        if (y > (last_y + (2 * TAILLE_CASE))) {
                            y = last_y + (2 * TAILLE_CASE);
                            continue;
                        } else if (y == last_y)
                            continue;
                        else {
                            i = (x - (LINES / 3)) / TAILLE_CASE;
                            j = (y - (COLS / 3)) / (2 * TAILLE_CASE);
                            lettre = tolower(plate.tab[i][j]);
                        }
                    }
                }
            }
        }
    }
    return new;
}