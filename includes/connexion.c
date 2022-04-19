#include <mysql.h>
#include <string.h>
#include "connexion.h"

/**
 * Fonction qui permet de se connecter a la base de donnee si la connexion existe deja elle la renvoi (static) sans refaire une nouvelle tentative
 * 
 * \param hostname (char *) adresse ip ou nom de domaine de la base de donnee    
 * \param username (char *) nom de d utilisateur pour la connexion a la base de donnee
 * \param password (char *) mot de passe de l utilisateur de la base de donnee
 * \param db_name (char *) nom de la base de donne
 * \param erreur (char *) garnie si une erreur survient
 * \return connexion (struct MYSQL*) renvoi une structure MYSQL contenant les informations de connexion ou null si echec de connexion 
 */
MYSQL *connexion_bd(char *hostname, char *username, char *password, char* db_name, char *erreur) {
    static MYSQL *connexion; 

    if (connexion == NULL) {
        connexion =  mysql_init(NULL);
    
        if (connexion == NULL) {
            strcpy(erreur, "ERREUR: Impossible d'initialiser la connection\n");
            return NULL;
        }

        if (mysql_real_connect(connexion, hostname, username, password, db_name, 3306, NULL, 0) == NULL) {
            strcpy(erreur, "ERREUR: Impossible de se connecter a la base de donnee\n");
            fermerConnexion(connexion);
            return NULL;
        }
    }
    
    return connexion;
}

/**
 * Ferme la connexion
 * 
 * \param connexion (struct MYSQL*) la connexion deja etablie
 */
void fermerConnexion(MYSQL *connexion) {
    mysql_close(connexion);
}
