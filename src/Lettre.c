/* Auteur : Gaël PAQUETTE && Anass OUSAID
 * Création : 24/03/2022
 * Dernière modification : 24/03/2022 */
/* Lettre.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <Lettre.h>

De * alloue_de(char* tab) {
    /*
    Fonction qui alloue un dé à six face et renvoie ce dé.

    Renvoie un dé de type De.
    */
    De * new = (De*)malloc(sizeof(De));
    new->L = (char*)malloc(sizeof(char) * MAX_LETTRES);
    if (new == NULL) {
        fprintf(stderr, "Fonction alloue_de : ERREUR MALLOC\n");
        return NULL;
    }
    strcat(new->L, tab);
    new->next = NULL;
    return new;
}

Cellule * allouer_Cellule_mot(char* mot) {
    /*
    Fonction qui alloue de la place mémoire à une Cellule et initialise celle ci avec la chaine de caractère 'mot'(description par variable).
    
    Renvoie l'adresse de cette Cellule 'new_cell'.
    */
    Cellule * new_cell = (Cellule*)malloc(sizeof(Cellule));
    new_cell->mot = (char*)malloc(sizeof(char) * 30);
    if (new_cell == NULL){
        fprintf(stderr, "Fonction allouer_Cellule_mot : ERREUR MALLOC");
        return NULL;
    }
    strcpy(new_cell->mot, mot);
    new_cell->next = NULL;
    return new_cell;
}

int insere_de(Liste* new, char* tab) {
    /*
    Fonction qui insere un dé à six face dans la liste 'new'.

    Renvoie :   0 si l'ajout c'est mal passé
                1 si l'ajout c'est bien passé.
    */
    Liste tmp = NULL;
    tmp = alloue_de(tab);
    if (!tmp)
        return 0;
    tmp->next = *new;
    *new = tmp;
    return 1;
}

int insere_mot(ListeMot* L, char* mot) {
    /*
    Fonction qui insere en tête de la liste 'L' (passée par adresse) la cellule correspondant au mot 'mot'(description par variable)

    Renvoie 1 si l'opération est un succès
            0 si l'adresse de la nouvelle cellule est NULL 
    */
    ListeMot tmp = NULL;
    tmp = allouer_Cellule_mot(mot);
    if (!tmp) 
        return 0;
    tmp->next = *L;
    *L = tmp;
    return 1;
}

Liste initialise_de(void) {
    /*
    Fonction qui initialise la liste de.

    Renvoie la liste de.
    */
    Liste new = NULL;
    char* de = "";
    de = "ETUKNO";
    insere_de(&new, de);
    de = "EVGTIN";
    insere_de(&new, de);
    de = "DECAMP";
    insere_de(&new, de);
    de = "IELRUW";
    insere_de(&new, de);
    de = "EHIFSE";
    insere_de(&new, de);
    de = "RECALS";
    insere_de(&new, de);
    de = "ENTDOS";
    insere_de(&new, de);
    de = "OFXRIA";
    insere_de(&new, de);
    de = "NAVEDZ";
    insere_de(&new, de);
    de = "EIOATA";
    insere_de(&new, de);
    de = "GLENYU";
    insere_de(&new, de);
    de = "BMAQJO";
    insere_de(&new, de);
    de = "TLIBRA";
    insere_de(&new, de);
    de = "SPULTE";
    insere_de(&new, de);
    de = "AIMSOR";
    insere_de(&new, de);
    de = "ENHRIS";
    insere_de(&new, de);
    return new;
}

void afficher_Liste(Liste de){
    /* 
    Fonction qui affiche les dés suivants le chainage de la liste.

    Renvoie rien.
    */
    Liste tmp = de;
    size_t i;
    while (tmp != NULL) {
        for (i = 0; i < sizeof(tmp->L); ++i) {
            printf("%c, ", tmp->L[i]);
        }
        printf("\n");
        tmp = tmp->next;
    }
}

int dans_Liste(ListeMot L, char *mot){
    /*
    Fonction qui vérifie si le mot/chaine de caractère 'mot'(description par variable) est contenu dans la Liste 'L'.

    Renvoie 1 si oui
            0 sinon
    */
    if (L == NULL) return 0;
    if (mot == NULL) return 0;
    if (strcmp(L->mot, mot) == 0) return 1;
    return dans_Liste(L->next, mot);
}

void liberer_Liste(Liste* de) {
    /*
    Fonction qui supprime la Liste 'de' (passée par adresse) et libère la mémoire.

    Renvoie rien.
    */
    Liste tmp = *de;
    Liste tmp2;
    while (tmp != NULL) {
        tmp2 = tmp;
        tmp = tmp->next;
        if (tmp2->L == NULL) free(tmp2->L);
        free(tmp2);
    }
    *de = NULL;
}

void liberer_Liste_mot(ListeMot* L) {
    /* 
    Fonction qui supprime la Liste 'L' (passée par adresse) et libère la mémoire.

    Renvoie rien.
    */
    ListeMot tmp = *L;
    ListeMot tmp2;
    while (tmp != NULL) {
        tmp2 = tmp;
        tmp = tmp->next;
        if (tmp2->mot != NULL) free(tmp2->mot);
        free(tmp2);
    }
    L = NULL;
}

char tirage_lettre(Liste* de, int tir1, int tir2) {
    /*
    Fonction qui renvoie une lettre appartenant à un dé de la liste et place ce dé à la fin 
    de la liste chainé.

    Renvoie une lettre majuscule de type char.
    */
    int i = 0;
    char lettre;
    Liste tmp = *de;
    Liste tmp2 = NULL;

    /* tirage du dé */
    while (i < tir1 - 1) {
        tmp = tmp->next;
        ++i;
    }
    tmp2 = tmp->next;
    tmp->next = tmp2->next;
    tmp2->next = NULL;

    /* Tirage de la lettre */
    lettre = tmp2->L[tir2];

    while (tmp->next != NULL) 
        tmp = tmp->next;
    tmp->next = tmp2;

    return lettre;
}

Plateau alloue_tab(void) {
    /* 
    Fonction qui alloue un Plateau à deux dimensions de manière dynamique.

    Renvoie une tableau dynamique à deux dimensions dont toutes les cases ont pour valeur ' '.
    */
    int i, j;
    Plateau new;
    new.tab = (char**)malloc(sizeof(char*) * NB_CASES);
    if (new.tab == NULL) {
        fprintf(stderr, "Fonction alloue_tab : ERREUR MALLOC\n");
        exit(EXIT_FAILURE);
    }
    for (i = 0; i < NB_CASES; ++i) {
        new.tab[i] = (char*)malloc(sizeof(char) * NB_CASES);
        if (new.tab[i] == NULL) {
            fprintf(stderr, "Fonction alloue_tab : ERREUR MALLOC\n");
            exit(EXIT_FAILURE);
        }
        for (j = 0; j < NB_CASES; ++j)
            new.tab[i][j] = ' ';
    }
 
    return new;
}

Plateau remplie_tab(Liste* de) {
    /* 
    Fonction qui remplie aléatoirement le plateau avec les dés.

    Renvoie un tableau dynamique avec des lettres.
    */
    Plateau new = alloue_tab();
    int i, j, tirage1, tirage2;
    int n1 = 15, n2 = 5;
    char lettre;
    srand(time(NULL));

    for (i = 0; i < NB_CASES; ++i) {
        for (j = 0; j < NB_CASES; ++j) {
            if (n1 == 0)
                n1 = 15;
            tirage1 = rand() % n1;
            tirage2 = rand() % n2;
            lettre = tirage_lettre(de, tirage1, tirage2);
            new.tab[i][j] = lettre;
            n1 -= 1;
        }
    }
    return new;
}

void afficher_plateau(Plateau plate) {
    /* 
    Fonction qui affiche le plateau de jeu.

    Renvoie rien.
    */
    int i, j;
    for (i = 0; i < NB_CASES; ++i){
        for (j = 0; j < NB_CASES; ++j) {
            printf("%c ", plate.tab[i][j]);
        }
        printf("\n");
    }
}

void liberer_plateau(Plateau* plate) {
    /*
    Fonction qui supprime le Plateau 'plate' (passé par adresse) et libère la mémoire.

    Renvoie rien.
    */
    int i;
    for (i = 0; i < NB_CASES; ++i) {
        free(plate->tab[i]);
        plate->tab[i] = NULL;
    }
    free(plate->tab);
    plate->tab = NULL;
}