#include <stdlib.h>
#include <stdio.h>
#include <mysql.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>
#include "modeles.h"
#include "json.h"
#include "connexion.h"

unsigned createTableModeles(MYSQL *connect, char *erreur)
{
	unsigned retour = 1;
	char query[] = "CREATE TABLE Modele(						\
					id VARCHAR(50) NOT NULL,					\
					name VARCHAR(50) NOT NULL,					\
					niceName VARCHAR(50) NOT NULL,				\
					makeId INT UNSIGNED NOT NULL,				\
					PRIMARY KEY( niceName),						\
					UNIQUE(id, name),							\
					FOREIGN KEY(makeId) REFERENCES Marque(id))";

	if (mysql_query(connect, query))
	{
		strcpy(erreur, "ERREUR: Impossible de creer la table modeles\n");
		retour = 0;
	}
	return retour;
}

unsigned insertModeles(MYSQL *connect, char *id, char *name, char *niceName, char *makeId, char *erreur)
{
	unsigned retour = 1;
	char query[QUERY_LENGHT];
	sprintf(query, "INSERT INTO Modele VALUES ('%s', '%s', '%s',%s)", id, name, niceName, makeId);

	if (mysql_query(connect, query) != 0)
	{
		strcpy(erreur, "ERREUR: Impossible de faire l'insertion dans la table modeles\n");
		return 0;
	}
	return retour;
}

unsigned ajoutDesModeles(MYSQL *connect, char *chemin, char *erreur)
{
	FILE *fichier = fopen(chemin, "r");
	char id[20], name[50], niceName[50], makeId[50], resultat[50][DIM];
	int retour;
	unsigned int MAX = 30;
	char query[250];
	if (fichier == NULL)
	{
		strcpy(erreur, "ERREUR: Impossible d'ouvrir le fichier\n");
		retour = 0;
	}
	else
	{
		char *buffer = (char *)malloc(2048);

		int ligne = 1;
		while (fscanf(fichier, "%[^\n]", buffer) != EOF)
		{
			MAX = 30;
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
		retour = 1;
	}
	return retour;
}

unsigned select(MYSQL *connect, char *given_NiceName, char resultatModele[][10], char *erreur)
{

	MYSQL_ROW row;
	MYSQL_RES *resultat;
	char getted_id[20];
	int i = 0;
	char query[QUERY_LENGHT];
	unsigned retour = 1;

	sprintf(query, "SELECT id FROM marque WHERE niceName='%s'", given_NiceName);

	if (mysql_query(connect, query) == 0)
	{
		resultat = mysql_store_result(connect);

		if ( mysql_affected_rows(connect)!= 0)
		{
			row = mysql_fetch_row(resultat);

			strcpy(getted_id, row[0]);

			sprintf(query, "SELECT name FROM modele WHERE makeId='%s' ORDER BY name ASC", getted_id);
			if (mysql_query(connect, query) == 0)
			{
				resultat = mysql_store_result(connect);
				while ((row = mysql_fetch_row(resultat)))
				{
					strcpy(&(resultatModele[i][0]), row[0]);
					i++;
				}
			}
			else
			{
				strcpy(erreur, "ERREUR: Mauvaise entree");
				retour = 0;
			}
		}
		else
			{
				strcpy(erreur, "ERREUR: Mauvaise entree");
				retour = 0;
			}
	}
	else
	{
		strcpy(erreur, "ERREUR: Mauvaise entree");
		retour = 0;
	}

	return retour;
}
