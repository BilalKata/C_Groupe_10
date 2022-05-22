#ifndef VERSIONS_H
#define VERSIONS_H

#define QUERY_LENGHT 300

typedef struct {
    char *id;
    char *name;
    char *horsepower;
    char *modelNiceName;
} Version;

unsigned createTableVersion(MYSQL *connexion, char *erreur);
unsigned insertVersion(MYSQL *connexion, Version *version, char *erreur);
unsigned addVersions(MYSQL *connexion, char *path, char *erreur);
unsigned selectByNiceNameOrdered(MYSQL *connexion, char version[][2][50], unsigned *nbElements, char *modelNiceName, char *erreur);

#endif