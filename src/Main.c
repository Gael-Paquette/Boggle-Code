/* Auteur : Gaël PAQUETTE && Anass OUSAID
 * Création : 24/03/2022
 * Dernière modification : 24/03/2022 */
/* Main.c */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ncurses.h>

#include <Lettre.h>
#include <Mot.h>
#include <Jeu.h>
#include <Graphique.h>

static int creer_dico(ATR* dico, const char* fichier_dico) {
    /*
    Fonction qui creer l'arbre ternaire de recherche du dictionnare.

    Renvoie un int :    1 si tous c'est bien passé.
                        0 si il y a une erreur.
    */
    /* Déclaration des variables */
    FILE * fPointer;
    char mot_dico[MAX_LETTRES_MOT];

    fPointer = fopen(fichier_dico, "r");
    *dico = creer_ATR_vide();
    while (fscanf(fPointer, "%s", mot_dico) != EOF) {
        inserer_dans_ATR(dico, mot_dico);
    }
    return 1;
}

int main(int argc, char* argv[]) {
    /* Déclaration des variables */
    Liste de;
    ATR dico;
    ListeMot L = NULL;
    Plateau plate;
    char* mot;
    const char* fichier_dico;
    int tentative = 4, score = 0, sortie = 0;

    /* Initialisation de la fenêtre ncurses */
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(FALSE);
    
    /* Création du dictionnaire */
    if (argc != 2) {
        endwin();
        fprintf(stderr, "%s : Nombre d'arguments incorrect\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    fichier_dico = argv[1];
    if (creer_dico(&dico, fichier_dico) == 0) {
        endwin();
        fprintf(stderr, "Fonction creer dico : ERREUR INSERTION\n");
        exit(EXIT_FAILURE);
    }
    /* création du jeu (La liste contenant les dés et le tableau dynamique à deux dimensions) */
    de = initialise_de();
    plate = remplie_tab(&de);

    /*Lancement de la partie */
    afficher_regle();
    while (fin_jeu(tentative)) {
        afficher_score(score);
        afficher_lettre(plate, LINES, COLS);
        mot = saisie_mot(plate, LINES, COLS, &sortie);
        /* Si le joueur décide de quitter la partie */
        if (sortie == 1)
            break;
        if (mot_valide(dico, L, mot, &score) == -1) 
            tentative -= 1;
        else 
            insere_mot(&L, mot);
    }
    affiche_fin_jeu(score, LINES, COLS);
    usleep(5000000);

    /* Fermeture de la fenêtre graphique ncurses */
    endwin();

    /* libération de la mémoire */
    liberer_ATR(&dico);
    liberer_Liste(&de);
    liberer_Liste_mot(&L);
    liberer_plateau(&plate);
    return 0;
}