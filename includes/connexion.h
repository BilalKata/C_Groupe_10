#ifndef DATABASE_H
#define DATABASE_H

#define HOSTNAME    "127.0.0.1"
#define USERNAME    "root"
#define PASSWORD    ""
#define DB_NAME     "voiture"

MYSQL *connexion_bd(char *hostname, char *username, char *password, char* db_name, char *erreur);
void fermerConnexion(MYSQL *connexion);

#endif