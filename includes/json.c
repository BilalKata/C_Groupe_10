#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "json.h"

/**
 * Recherche une cle dans un tableau JSON et retourne la valeur en fontion des restrictions
 *
 * \param chaineJson (char *) chaine au format JSON
 * \param nomAttribut (char *) l attribut rechercher dans la chaine
 * \param resultat (char *) garnie si l attribut existe
 * \param dim (unsined) dimension maximale de resultat
 * \param messageErreur (char *) garnie si une erreur survient
 * 
 * \return (unsined) 1 si l attribut a ete trouve et le resultat ne depasse pas dim sinon 0
 */
unsigned jsonPrimitive(char *chaineJson, char *nomAttribut, char *resultat, unsigned dim, char *messageErreur) {

    const char *separateurs = " :{}\"";
    int trouve = -1;
    char* chainecle = (char *) malloc(sizeof(char) * (strlen(chaineJson) + 1));
    char* chainevaleur = (char *) malloc(sizeof(char) * (strlen(chaineJson) + 1));
    
    strcpy(chainecle, chaineJson);
    strcpy(chainevaleur, chaineJson);

    char *cle = strtok (chainecle,separateurs);

    while (cle != NULL) { 
        trouve = strcmp(cle, nomAttribut);
        if (trouve == 0) break;
        cle = strtok ( NULL, separateurs);
    }
    
    if (trouve != 0) {
        strcpy(messageErreur, "ERREUR: Attribut non trouve\n");
        free(chainecle);
        free(chainevaleur);
        return 0;
    }

    char* valeur = strstr(chainevaleur, cle);
    valeur = strtok (valeur,",");
    valeur = valeur + strlen(cle);
    valeur = strtok (valeur,":{}\"");

    if (strlen(valeur) >= dim) {
        strcpy(messageErreur, "ERREUR: La taille de la valeur est trop grande\n");
        free(chainecle);
        free(chainevaleur);
        return 0;
    }
    
    strcpy(resultat, valeur);
    free(chainecle);
    free(chainevaleur);
    return 1;
}

/**
 * Recherche un tableau JSON et retourne les elements de celui ci en fontion des restrictions
 *
 * \param chaineJson (char *) chaine au format JSON
 * \param nomAttribut (char *) l attribut rechercher dans la chaine
 * \param resultats (char **) garnie si l attribut existe
 * \param nbElements (unsined *) nombre d'elelement maximum dans le taleau
 * \param messageErreur (char *) garnie si une erreur survient
 * 
 * \return (unsined) 1 si le tableau a ete trouve et le nombre d element ne depasse pas nbElements sinon 0
 */
unsigned jsonArray(char *chaineJson, char *nomAttribut, char resultats[][DIM], unsigned *nbElements, char *messageErreur) {

    const char *separateurs = " ,():{}\"";
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
        free(chaine);
        return 0;
    }

    char* tableau = strstr(chaine, cle);
    tableau = strstr(tableau, "[");
    tableau += 2;
    char* finTableau = strchr(tableau, ']');
    *(finTableau) = '\0';
    
    int nbrElement = 0;
    for (int i = 0; i < strlen(tableau); i++) {
        if (tableau[i] == '}') 
            nbrElement++;
    }

    if (nbrElement > *nbElements) {
        strcpy(messageErreur, "ERREUR: Nombre d'elements superieur à la valeur demander\n");
        free(chaine);
        return 0;
    }
    *nbElements = nbrElement;
    
    unsigned courant = 0;
    unsigned taille = strlen(tableau);
    char valeur[DIM];
    strcpy(valeur, "");
    strncat(valeur, "{", 1);
    for (unsigned i = 0; i < taille; i++) {
        if (tableau[i] == '}') {
            strncat(valeur, &tableau[i], 1);
            strncat(valeur, "\0", 1);
            strcpy(&(resultats[courant][0]), valeur);
            strcpy(valeur, "");
            courant++;
        } else {
            if (tableau[i+1] != '{')
                strncat(valeur, &tableau[i], 1);
        }
    }

    
    free(chaine);
    return 1;
}
