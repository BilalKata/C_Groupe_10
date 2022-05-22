#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <stdlib.h>

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

#endif