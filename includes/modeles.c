#include <stdlib.h>
#include <stdio.h>
#include <mysql.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>
#include "modeles.h"
#include "json.h"

unsigned createTableModeles(MYSQL *connect, char *erreur)
{
	int retourne = 1;
	char query[] = "                                                  \
                CREATE TABLE Modele(                                \
                id SMALLINT,                                        \
                name VARCHAR(50) NOT NULL,                          \
                niceName VARCHAR(50) NOT NULL,                      \
                makeId INT UNSIGNED NOT NULL,                           \
                PRIMARY KEY(id),                                    \
                UNIQUE(name),                                       \
                FOREIGN KEY(makeId) REFERENCES Marque(id))";

	if (mysql_query(connect, query))
	{
		strcpy(erreur, "ERREUR: Impossible de creer la table modeles\n");
		retourne = 0;
	}
	return retourne;
}

unsigned insertModeles(MYSQL *connect, char id, char name, char niceName, char makeId, char *erreur)
{
	char query[QUERY_LENGHT];
	sprintf(query, "INSERT INTO Modeles VALUES (%s, '%s', '%s',%s)", id, name, niceName, makeId);

	if (mysql_query(connect, query) != 0)
	{
		strcpy(erreur, "ERREUR: Impossible de faire l'insertion dans la table modeles\n");
		return 0;
	}
	return 1;
}

unsigned ajoutDesModeles(MYSQL *connect, char *chemin, char *erreur)
{
	FILE *fichier = fopen(chemin, "r");
	char id[20], name[50], niceName[50], makeId[50], resultat[50];
	int retour;
	unsigned int MAX = 30;
	if (fichier != NULL)
	{
		strcpy(erreur, "ERREUR: Impossible d'ouvrir le fichier\n");
	}
	else
	{
		char *buffer = (char *)malloc(2048);

		int ligne = 1;
		while (fscanf(fichier, "[\n", buffer) != EOF)
		{
			jsonPrimitive(buffer, "id", makeId, 10, erreur);

			jsonArray(buffer, "models", resultat, &MAX, erreur);

			for (int i = 0; i < MAX; i++)
			{
				jsonPrimitive(resultat[i], "id", id, 20, erreur);
				jsonPrimitive(resultat[i], "name", name, 20, erreur);
				jsonPrimitive(resultat[i], "niceName", niceName, 20, erreur);
				insertModeles(connect, id, name, niceName, makeId, erreur);
			}

			strcpy(buffer, "");
			fgetc(fichier);
		}
		free(buffer);
		retour = 0;
	}
}
