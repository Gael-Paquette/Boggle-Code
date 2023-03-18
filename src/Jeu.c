/* Auteur : Gaël PAQUETTE && Anass OUSAID
 * Création : 24/03/2022
 * Dernière modification : 24/03/2022 */
/* Jeu.c */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#include <Jeu.h>

int mot_valide(ATR dico, ListeMot L, char* mot, int* score) {
    /*
    Fonction qui regarde si le mot passé par adresse est valide ou non.
    Si oui, alors on recalcule le score et on renvoie 1. Sinon, on renvoie -1.

    Renvoie un int :    1 si le mot est valide
                        -1 si le mot n'est pas valide.
    */
    if (dans_ATR(dico, mot) == 1) {
        if (!dans_Liste(L, mot)) {
            compte_score(mot, score);
            return 1;
        }
    }
    return -1;
}

void compte_score(char* mot, int* score) {
    /* 
    Fonction qui calcul le nouveau score à partir du mot passée par adresse et ajoute les points à la variable score passée par adresse.

    Renvoie rien.
    */
    int n, taille = strlen(mot);
    if (taille >= 3) {
        n = pow(2, taille - 3);
        *score += n;
    } else {
        n = 0;
        score += n;
    }
}

int fin_jeu(int tentative) {
    /*
    Fonction qui regarde si le nombre de tentative n'est pas inférieur ou égale 0.

    Renvoie un int :    1 si le nombre de tentative est supérieur à 0.
                        0 si le nombre est inférieur ou égale à 0.
    */
    if (tentative <= 0) 
        return 0;
    return 1;
}

char * construit_mot(char* mot, char lettre) {
    /*
    Fonction qui construit un nouveau mot à partir du mot passée par adresse et de la lettre passée par adresse.

    Renvoie un char * du nouveau mot.
    */
    int taille;

    assert(mot != NULL);

    taille = strlen(mot);

    if (taille >= MAX_LETTRES_MOT) {
        fprintf(stderr, "Fonction construit_mot : ERREUR TAILLE\n");
        exit(EXIT_FAILURE);
    }
    mot[taille] = lettre;   /* Ajout de la lettre */
    mot[taille + 1] = '\0';     /* Ajout du caractère de fin de chaîne */
    return mot;
}