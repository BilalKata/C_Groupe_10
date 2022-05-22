#ifndef MODELES_H
#define MODELES_H

#define QUERY_LENGHT 300

unsigned createTableModeles(MYSQL *connect, char *erreur);
unsigned insertModeles(MYSQL *connect, char *id, char *name, char *niceName, char *makeId, char *erreur);
unsigned ajoutDesModeles(MYSQL *connect, char *chemin, char *erreur);
unsigned select(MYSQL *connect, char *given_NiceName,char resultatModele[][10],char *erreur);

#endif