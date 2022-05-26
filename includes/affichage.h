#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <stdlib.h>

#ifdef _WIN32
    #define     CLEAN   system("cls");
    #define     PATH    "ressources/users.txt"
#else
    #define     CLEAN   system("clear");
    #define     PATH    "../ressources/users.txt"
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
#endif