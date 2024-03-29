#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <stdlib.h>
#include <mysql.h>

#define     PATH    "../ressources/users.txt"

#ifdef _WIN32
    #define     CLEAN   system("cls");
#else
    #define     CLEAN   system("clear");
#endif

unsigned ecran_acceuil(void);
unsigned menu_simple();
unsigned menu_admin();
unsigned login(char *user, char *erreur);
unsigned signin(char *erreur);
void utilisateurs(void);
unsigned modifier_username(char *current_username, char *erreur);
unsigned modifier_password(char *username, char *erreur);
unsigned delete_user(char *username, char *erreur);
unsigned make_admin(char *erreur);
void init(MYSQL *connexion, char *erreur);
void reset(MYSQL *connexion);
void afficher_marques(MYSQL *connexion, char *erreur);
void afficher_modeles(MYSQL *connexion, char *erreur);
void afficher_versions(MYSQL *connexion, char *erreur);
#endif