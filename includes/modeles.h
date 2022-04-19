#ifndef MODELES_H
#define MODELES_H

#define QUERY_LENGHT 1000

typedef struct{
    char *id;
    char *name;
    char *niceName;
}Modeles;

unsigned createTbaleModeles(MYSQL *connect, char *erreur);
unsigned insertModeles(MYSQL *connect, Modeles *modeles, char *erreur);
unsigned ajoutDesModeles(MYSQL *connect, char *chemin, char *erreur);