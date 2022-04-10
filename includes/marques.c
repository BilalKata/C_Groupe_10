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
    char query[QUERY_LENGTH] = "INSERT INTO Marque VALUES (";
    strcat(query, marque->id);
    strcat(query, ", '");
    strcat(query, marque->name);
    strcat(query, "', '");
    strcat(query, marque->niceName);
    strcat(query, "')");

    if (mysql_query(connexion, query) != 0) {
        strcpy(erreur, "ERREUR: Impossible de faire l'insertion dans la table marque\n");
        return 0;
    }
    return 1;
}
