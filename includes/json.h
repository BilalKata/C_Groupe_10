#ifndef JSON_H
#define JSON_H

#define DIM 20

unsigned jsonPrimitive(char *chaineJson, char *nomAttribut, char *resultat, unsigned dim, char *messageErreur);
unsigned jsonArray(char *chaineJson, char *nomAttribut, char resultats[][DIM], unsigned *nbElements, char *messageErreur);

#endif