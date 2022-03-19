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
    return 0;
}