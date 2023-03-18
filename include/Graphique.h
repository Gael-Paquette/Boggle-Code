/* Auteur : Gaël PAQUETTE && Anass OUSAID
 * Création : 24/03/2022
 * Dernière modification : 24/03/2022 */
/* Graphique.h */

#ifndef __GRAPHIQUE__
#define __GRAPHIQUE__

    #include <Lettre.h>
    #include <Mot.h>
    #include <Jeu.h>

    /* Déclaration de la macro TAILLE_CASE */
    #define TAILLE_CASE 5

    /* Déclaration de la fonction afficher_regle */
    void afficher_regle(void);
    
    /* Déclaration de la fonction afficher_score */
    void afficher_score(int score);

    /* Déclaration de la fonction afficher_plateau */
    void afficher_lettre(Plateau plate, int LINES, int COLS);

    /* Déclaration de la fonction afficher_mot */
    void afficher_mot(char* mot);

    /* Déclaration de la fonction subrillance */
    void surbrillance(Plateau plate, int LINES, int COLS, int x, int y);

    /* Déclaration de la fonction affiche_fin_jeu */
    void affiche_fin_jeu(int score, int LINES, int COLS);

    /* Déclaration de la fonction saisie_mot */
    char * saisie_mot(Plateau plate, int LINES, int COLS, int* sortie);

#endif