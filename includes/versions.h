#ifndef VERSIONS_H
#define VERSIONS_H

#define QUERY_LENGHT 1000
#define DIM 60

typedef struct {
    char *id;
    char *name;
    char *horsepower;
    char *modelNiceName;
} Version;

unsigned createTableVersion(MYSQL *sqlConnection, char *erreur);
unsigned mysqlInsertStructVersion(MYSQL *connexion, Version *version, char *erreur);
unsigned ajoutVersion(MYSQL connexion, char *path, char *erreur);

#endif