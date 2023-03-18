/* Auteur : Gaël PAQUETTE && Anass OUSAID
 * Création : 24/03/2022
 * Dernière modification : 24/03/2022 */
/* Lettre.h */

#ifndef __LETTRE__
#define __LETTRE__

    #define MAX_LETTRES 6
    #define NB_CASES 4

    /* Déclaration du type structuré Liste_de*/
    typedef struct __cell__ {
        char* L;
        struct __cell__ *next;
    } De, *Liste;

    /* Déclaration du type structuré Liste_mot */
    typedef struct cell {
        char* mot;
        struct cell *next;
    } Cellule, *ListeMot;

    /* Déclaration du type structuré Plateau */
    typedef struct {
        char** tab;
    } Plateau;

    /* Déclaration de la fonction alloue_de */
    De * alloue_de(char* tab);

    /* Déclaration de la fonction alloue_Cellule_mot */
    Cellule * alloue_Cellule_mot(char* mot);

    /* Déclaration de la fonction insere_de */
    int insere_de(Liste* new, char* tab);

    /* Déclaration de la fonction inser_mot */
    int insere_mot(ListeMot* L, char* mot);

    /* Déclaration de la fonction initialise_de */
    Liste initialise_de(void);

    /* Déclaration de la fonction afficher_Liste */
    void afficher_Liste(Liste de);

    /* Déclaration de la fonction dans_Liste */
    int dans_Liste(ListeMot L, char* mot);

    /* Déclaration de la fonction liberer_Liste*/
    void liberer_Liste(Liste* de);

    /* Déclaration de la fonction liberer_Liste_mot */
    void liberer_Liste_mot(ListeMot* L);

    /* Déclaration de la fonction tirage lettre */
    char tirage_lettre(Liste* de, int tir1, int tir2);

    /* Déclaration de la fonction alloue_tab */
    Plateau alloue_tab(void);

    /* Déclaration de la fonction remplie_tab */
    Plateau remplie_tab(Liste* de);

    /* Déclaration de la fonction afficher_plateau */
    void afficher_plateau(Plateau plate);

    /* Déclaration de la fonction liberer_plateau */
    void liberer_plateau(Plateau* plate);

#endif