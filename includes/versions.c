#include <mysql.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "versions.h"
//#include <connexion.h>



unsigned createTableVersion(MYSQL *sqlConnection, char *erreur){
    int retour=1;
    char query[] = "                                                        \
                    CREATE TABLE Version(                                   \
                        id SMALLINT,                                        \
                        name VARCHAR(50) NOT NULL,                          \
                        versionPower SMALLINT NOT NULL,                     \
                        modelNiceName SMALLINT NOT NULL,                    \
                        PRIMARY KEY(id),                                    \
                        UNIQUE(name),                                       \
                        FOREIGN KEY(modelNiceName) REFERENCES Modele(id))";
    if (mysql_query(sqlConnection, query)){
        strcpy(erreur, "ERREUR: Impossible de creer la table version\n");
        retour = 0;
    }
    return retour;
}

unsigned mysqlInsertStructVersion(MYSQL *connexion, Version *version, char *erreur){
    char query[QUERY_LENGHT];
    sprintf(query, "INSERT INTO Version (id, name, horsepower, modelNiceName) VALUES (%s, '%s', %s, '%s')", version->id , version->name, version->horsepower, version->modelNiceName);
    int retour=1;
    if(mysql_query(connexion, query){
        erreur="ERREUR: Insertion impossible\n";
        retour=0;
    }
    return retour;
}


