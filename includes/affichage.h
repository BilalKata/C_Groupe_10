#ifndef AFFICHAGE_H
#define AFFICHAGE_H

unsigned ecran_acceuil(void);
unsigned menu_simple();
unsigned menu_admin();
unsigned login(char *user, char *erreur);
unsigned signin(char *erreur);
void utilisateurs(void);
#endif