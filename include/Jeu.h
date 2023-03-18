/* Auteur : Gaël PAQUETTE && Anass OUSAID
 * Création : 24/03/2022
 * Dernière modification : 24/03/2022 */
/* Jeu.h */

#ifndef __JEU__
#define __JEU__

    #include <Lettre.h>
    #include <Mot.h>

    /* Déclaration de la fonction mot_valide */
    int mot_valide(ATR dico, ListeMot L, char* mot, int* score);

    /* Déclaration de la fonction compte_score */
    void compte_score(char* mot, int* score);

    /* Déclaration de la fonction fin_jeu */
    int fin_jeu(int tentative);

    /* Déclaration de la fonction construit_mot */
    char * construit_mot(char* mot, char lettre);

#endif