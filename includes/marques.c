#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
#include "marques.h"
#include "json.h"

/**
 * Cree directement la table Marque selon le modele
 *
 * \param connexion (MYSQL *) connextion a la base de donnee
 * \param erreur (char *) garnie si une erreur survient
 * 
 * \return (unsined) 1 si la creation a ete effectue avec succes sinon 0
 */
unsigned creationTableMarque(MYSQL *connexion, char *erreur) {
    char query[] = "                            \
                CREATE TABLE Marque(            \
                id INT UNSIGNED,                \
                name VARCHAR(50) NOT NULL,      \
                niceName VARCHAR(50) NOT NULL,  \
                PRIMARY KEY(id),                \
                UNIQUE(name))";

    if (mysql_query(connexion, query)) {
        strcpy(erreur, "ERREUR: Impossible de creer la table marques\n");
        return 0;
    }
    return 1;    
}

/**
 * Insere la marque donnee dans la bd
 *
 * \param connexion (MYSQL *) connextion a la base de donnee
 * \param marque (Marque *) une marque a insere dans la bd
 * \param erreur (char *) garnie si une erreur survient
 * 
 * \return (unsined) 1 si la creation a ete effectue avec succes sinon 0
 */
unsigned insertMarque(MYSQL *connexion, Marque *marque, char *erreur) {
    char query[QUERY_LENGTH];
    sprintf(query, "INSERT INTO Marque VALUES (%s, '%s', '%s')", marque->id, marque->name, marque->niceName);
    
    if (mysql_query(connexion, query) != 0) {
        strcpy(erreur, "ERREUR: Impossible de faire l'insertion dans la table marque\n");
        return 0;
    }
    return 1;
}

/**
 * Parcourt un fichier contenant des marques et insere le chaque marque 
 * en faisant appel a insertMarque
 * 
 * \param connexion (MYSQL *) connextion a la base de donnee
 * \param chemin_fichier (char *) le chemin du fichier contenant les marques
 * \param erreur (char *) garnie si une erreur survient
 * 
 * \return (unsined) 1 si la creation a ete effectue avec succes sinon 0
 */
unsigned ajoutDesMarque(MYSQL* connexion, char *chemin_fichier, char *erreur) {
    FILE* fichier = fopen(chemin_fichier, "r");
    Marque *marque = (Marque *) malloc((sizeof(char) * 20) + (sizeof(char) * 100) + (sizeof(char) * 100));
    marque->id = (char *) malloc(sizeof(char) * 20);
    marque->name = (char *) malloc(sizeof(char) * 100);
    marque->niceName = (char *) malloc(sizeof(char) * 100);
    size_t buffer_size = 2048;
    char *buffer = (char *) malloc(buffer_size);

    if (fichier == NULL) {
        strcpy(erreur, "ERREUR: Impossible d'ouvrir le fichier\n");
        free(marque->niceName);
        free(marque->name);
        free(marque->id);
        free(marque);
        free(buffer);
        fclose(fichier);
        return 0;
    }

    while (getline(&buffer, &buffer_size, fichier) != EOF) {
        // recherche chaque element d une marque et l'inserre
        if (jsonPrimitive(buffer, "id", marque->id, 20, erreur))
            if (jsonPrimitive(buffer, "name", marque->name, 100, erreur))
                if (jsonPrimitive(buffer, "niceName", marque->niceName, 100, erreur))
                    if (!insertMarque(connexion, marque, erreur)) break;
        
        // remet les valeurs a vide
        strcpy(marque->niceName, "");
        strcpy(marque->name, "");
        strcpy(marque->id, "");
        strcpy(buffer, "");
    }
    
    free(marque->niceName);
    free(marque->name);
    free(marque->id);
    free(marque);
    free(buffer);
    fclose(fichier);
    if (strcmp(erreur, "") != 0) {
        return 0;
    }
   
    return 1;
}
