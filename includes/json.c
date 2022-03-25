#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "json.h"

unsigned jsonPrimitive( char *chaineJson, char *nomAttribut, char *resultat, unsigned dim, char *messageErreur) {

    const char *separateurs = " :{}\"";
    int trouve = -1;
    char* chaine = (char *) malloc(sizeof(char) * (strlen(chaineJson) + 1));
    
    strcpy(chaine, chaineJson);

    char *cle = strtok (chaineJson,separateurs);

    while (cle != NULL) { 
        trouve = strcmp(cle, nomAttribut);
        if (trouve == 0) break;
        cle = strtok ( NULL, separateurs);
    }
    
    if (trouve != 0) {
        strcpy(messageErreur, "ERREUR: Attribut non trouve\n");
        return 0;
    }

    char* valeur = strstr(chaine, cle);
    valeur = strtok (valeur,",");
    valeur = valeur + strlen(cle);
    valeur = strtok (valeur," :{}\"");

    if (strlen(valeur) >= dim) {
        strcpy(messageErreur, "ERREUR: La taille de la valeur est trop grande\n");
        return 0;
    }
    
    strcpy(resultat, valeur);
    return 1;
}

unsigned jsonArray(char *chaineJson, char *nomAttribut, char resultats[][DIM], unsigned *nbElements, char *messageErreur) {

    const char *separateurs = " :{}\"";
    int trouve = -1;
    char* chaine = (char *) malloc(sizeof(char) * (strlen(chaineJson) + 1));
    
    strcpy(chaine, chaineJson);

    char *cle = strtok(chaineJson,separateurs);

    while (cle != NULL) { 
        trouve = strcmp(cle, nomAttribut);
        if (trouve == 0) break;
        cle = strtok( NULL, separateurs);
    }
    
    if (trouve != 0) {
        strcpy(messageErreur, "ERREUR: Attribut non trouve\n");
        return 0;
    }

    char* tableau = strstr(chaine, cle);
    tableau = strstr(chaine, "[");
    tableau = tableau + 1;
    char* finTableau = strchr(tableau, ']');
    *(finTableau) = '\0';
    
    int nbrElement = 0;
    for (int i = 0; i < strlen(tableau); i++) {
        if (tableau[i] == ',') 
            nbrElement++;
    }
    nbrElement++;

    if (nbrElement > *nbElements) {
        strcpy(messageErreur, "ERREUR: Nombre d'elements superieur à la valeur demander\n");
        return 0;
    }

    unsigned courant = 0;
    unsigned taille = strlen(tableau);
    char valeur[50];
    strcpy(valeur, "");
    for (unsigned i = 0; i < taille; i++) {
        if (tableau[i] == ',' || i == taille - 1) {
            strcpy(&(resultats[courant][0]), valeur);
            strcpy(valeur, "");
            courant++;
        } else {
            if (tableau[i] != '"') 
                strncat(valeur, &tableau[i], 1);
        }
    }
    
    return 1;
}