#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
#include "json.h"
#include "versions.h"

unsigned createTableVersion(MYSQL *connexion, char *erreur){
    int retour=1;
    char query[] = "CREATE TABLE Version(                                       \
                    id INT UNSIGNED NOT NULL,                                   \
                    name VARCHAR(50) NOT NULL,                                  \
                    versionPower SMALLINT NOT NULL,                             \
                    modelNiceName VARCHAR(50) NOT NULL,                         \
                    PRIMARY KEY(id),                                            \
                    UNIQUE(name),                                               \
                    FOREIGN KEY(modelNiceName) REFERENCES Modele(niceName))";
    if (mysql_query(connexion, query) != 0){
        strcpy(erreur, "ERREUR: Impossible de creer la table version\n");
        retour = 0;
    }
    return retour;
}

unsigned insertVersion(MYSQL *connexion, Version *version, char *erreur) {
    char query[QUERY_LENGHT];
    sprintf(query, "INSERT INTO Version VALUES (%s, '%s', %s, '%s')", version->id , version->name, version->horsepower, version->modelNiceName);
    int retour=1;
    if(mysql_query(connexion, query) != 0){
        strcpy(erreur, "ERREUR: Insertion impossible\n");
        retour=0;
    }
    return retour;
}

unsigned addVersions(MYSQL *connexion, char *path, char *erreur) {
    FILE* file = fopen(path, "r");

    unsigned MAX = 5;
    char resultats[MAX][DIM];
    int retour;
    if(file == NULL){
        strcpy(erreur, "ERREUR: Fichier non ouvert");
        retour=1;
    } else {
        Version *version = (Version *) malloc(120);
        version->id = (char *) malloc(sizeof(char) * 10);
        version->name = (char *) malloc(sizeof(char) * 50);
        version->horsepower = (char *) malloc(sizeof(char) * 10);
        version->modelNiceName = (char *) malloc(sizeof(char) * 50);

        char* buffer = (char*) malloc(500);
        
        while (fscanf(file, "%[^\n]", buffer) != EOF) {
            jsonPrimitive(buffer, "id", version->id, 10, erreur);
            jsonPrimitive(buffer, "name", version->name, 50, erreur);
            jsonPrimitive(buffer, "horsepower", version->horsepower, 10, erreur);
            jsonPrimitive(buffer, "modelNiceName", version->modelNiceName, 50, erreur);

            insertVersion(connexion, version, erreur);

            strcpy(version->id, "");
            strcpy(version->name, "");
            strcpy(version->modelNiceName, "");
            strcpy(version->horsepower, "");
            strcpy(buffer, "");
            fgetc(file);
        }
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

unsigned selectByNiceNameOrdered(MYSQL *connexion, char version[][2][50], unsigned *nbElements, char *modelNiceName, char *erreur){
    MYSQL_ROW row;
    char query[255];
    unsigned retour;
    int i;
    sprintf(query, "SELECT name, versionPower FROM version WHERE modelNiceName='%s' ORDER BY name ASC;", modelNiceName);
    if(mysql_query(connexion, query)==0){
        MYSQL_RES *result = mysql_store_result(connexion);
        while ((row = mysql_fetch_row(result))){
            strcpy(&(version[i][0][0]),row[0]);
            strcpy(&(version[i][1][0]),row[1]);
            i++;
        }
        *nbElements=i;
        retour=1;
    }else{
        strcpy(erreur, "ERREUR: La version demande n est pas repertorie");
        retour=0;
    }

    return retour;
}
