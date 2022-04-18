#include <mysql.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "versions.h"
#include "json.h"
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
    sprintf(query, "INSERT INTO Version (id, name, versionPower, modelNiceName) VALUES (%s, '%s', %s, '%s')", version->id , version->name, version->horsepower, version->modelNiceName);
    int retour=1;
    if(mysql_query(connexion, query)){
        erreur="ERREUR: Insertion impossible\n";
        retour=0;
    }
    return retour;
}

unsigned ajoutVersion(MYSQL *connexion, char *path, char *erreur){
    FILE* file = fopen("../ressources/versions_moteurs.txt", "r");

    unsigned MAX = 5;
    char resultats[MAX][DIM];
    char resultat[MAX];
    int retour;
    if(file == NULL){
        strcpy(erreur, "ERREUR: Fichier non ouvert");
        retour=1;
    } else{
        Version *version = (Version *) malloc(470);
        version->id = (char *) malloc(sizeof(char) * 20);
        version->name = (char *) malloc(sizeof(char) * 150);
        version->horsepower = (char *) malloc(sizeof(char) * 150);
        version->modelNiceName = (char *) malloc(sizeof(char) * 150);

        size_t buffer_size = 300;
        char* buffer = (char*) malloc(buffer_size);
        
        int ligne=1;
        while (fscanf(file, "%[^\n]", buffer) != EOF) {
            jsonPrimitive(buffer, "name", resultat, 100, erreur);
            strcpy(version->name, resultat);

            strcpy(resultat, "");
            jsonPrimitive(buffer, "modelNiceName", resultat, 100, erreur);
            strcpy(version->modelNiceName, resultat);
            strcpy(resultat, "");
            jsonPrimitive(buffer, "id", resultat, 100, erreur);
            strcpy(version->id, resultat);
            if (jsonArray(buffer, "engine", resultats, &MAX, erreur) == 1) {
                strcpy(resultat, "");
                jsonPrimitive(resultats[3], "horsepower", resultat, 10, erreur);
                strcpy(version->horsepower, resultat);
            }
            strcpy(buffer, "");
            strcpy(resultat, "");
            fgetc(file);
            
        }
        mysqlInsertStructVersion(connexion, version, erreur);
        free(version->modelNiceName);
        free(version->name);
        free(version->horsepower);
        free(version->id);
        free(version);
        free(buffer);
        retour=0;
    }
    fclose(file);
    return retour;
}



