#ifndef MARQUES_H
#define MARQUES_H

#define     QUERY_LENGTH    255

/**
 * Represente une marque avec <char *id>, <char *name>, <char* niceName>
 * \struct Marque
 * 
 */
typedef struct marque {
    char *id;
    char *name;
    char *niceName;
} Marque;

unsigned creationTableMarque(MYSQL *connexion, char *erreur);
unsigned insertMarque(MYSQL *connexion, Marque *marque, char *erreur);

#endif