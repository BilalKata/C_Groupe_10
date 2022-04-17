#ifndef VERSIONS_H
#define VERSIONS_H

#define QUERY_LENGHT 1000

typedef struct {
    char *id;
    char *name;
    char *horsepower;
    char *modelNiceName;
} Version;

unsigned createTableVersion(MYSQL *sqlConnection, char *erreur);
unsigned mysqlInsertStructVersion(MYSQL *connexion, Version *version, char *erreur);

#endif