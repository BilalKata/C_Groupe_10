#include <stdlib.h>
#include <stdio.h>
#include <mysql.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>
#include "json.h"

void initialiserConnexion();


void cloturerConnexion();
void creerTables();
void remplirTables();
void trouver();
void extraire(char *ligne);

int main(void)
{
    trouver();
}

MYSQL *sqlConnection = NULL;

void extraire(char *ligne)
{

    char *resultatId;
    char *resultatName;
    char *resultatNiceName;
    int captureid = 0;
    int captureName = 0;
    int captureNiceName = 0;
  
    

    for (int a = 0; a < strlen(ligne); a++)
    {
        if (ligne[a] == 'i' && ligne[a + 1] == 'd' && ligne[a + 2] == '"' && ligne[a + 3] == ':')
        {
            a = a + 5;
            captureid = 0;

            while (ligne[a] != '"')
            {
                resultatId[captureid] = ligne[a];
                a++;
                captureid++;
                if (ligne[a] == '"')
                {
                    resultatId[captureid] = '\0';
                }
            }
          // printf("%s\n",resultatId);
        }
        

        if (ligne[a] == 'n' && ligne[a+1] == 'a' && ligne[a+2] == 'm' && ligne[a+3] == 'e')
        {
          a=a+7;
          captureName=0;
          while (ligne[a] == '\"' || ligne[a] == ':' || ligne[a] == '{' || ligne[a] == '}' || ligne[a] == ','|| ligne[a] == '[' || ligne[a] == ']')
          {
            a++;
          }
          while (ligne[a] != '\"')
          {
            resultatName[captureName]=ligne[a];
            a++;
            captureName++;
            
            if(ligne[a]=='\"')
            {
              resultatName[captureName]='\0';
            }
          }
          printf("%s\n",resultatName);
        }

    }
}


void trouver()
{
    FILE *fichier;

    fichier = fopen("C:\\Users\\abdel\\OneDrive\\Bureau\\C_Groupe_10\\ressources\\marques_modeles.txt", "r");
    if (fichier == NULL)
    {
        printf("Erreur");
    }

    char *chaineJson = (char *)malloc(2000);

    while (fgets(chaineJson, 2000, fichier) != NULL) // lire le fichier tant qu'on est pas a la fin
    {
        extraire(chaineJson);
    }
}















void initialiserConnexion()
{
    sqlConnection = mysql_init(NULL);
    if (sqlConnection == NULL)
    {
        fprintf(stderr, "%s\n", mysql_error(sqlConnection));
        exit(EXIT_FAILURE);
    }

    // Connect the Database and check the result
    if (!mysql_real_connect(sqlConnection, "localhost", "root",
                            NULL, NULL, 3306, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(sqlConnection));
        exit(EXIT_FAILURE);
    }
}

/*
void creerTables()
{
  executerSQL("DROP DATABASE IF EXISTS labo6");
  executerSQL("CREATE DATABASE labo6 CHARACTER SET = 'latin1' COLLATE = 'latin1_general_cs'");
  executerSQL("USE labo6");
  executerSQL("CREATE TABLE Personne(Id_Personne INT(11), nom_pers VARCHAR(50), prenom_pers VARCHAR(50), qualification_pers VARCHAR(50), PRIMARY KEY(Id_Personne))");
  executerSQL("CREATE TABLE Train(Id_Train INT(11), nbr_wagons INT, entretien_en_cours INT, PRIMARY KEY(Id_Train))");
  executerSQL("CREATE TABLE Gare(Id_Gare INT(11), ville_gare VARCHAR(50), Id_Personne_ChefDeGare INT NOT NULL, PRIMARY KEY(Id_Gare), FOREIGN KEY(Id_Personne_ChefDeGare) REFERENCES Personne(Id_Personne))");
  executerSQL("CREATE TABLE Voyage(Id_Voyage INT(11), date_depart DATETIME, Id_Gare_Depart INT NOT NULL, Id_Gare_Arrivee INT NOT NULL, Id_Personne_Conducteur INT NOT NULL, Id_Train INT NOT NULL, PRIMARY KEY(Id_Voyage), FOREIGN KEY(Id_Gare_Depart) REFERENCES Gare(Id_Gare), FOREIGN KEY(Id_Gare_Arrivee) REFERENCES Gare(Id_Gare), FOREIGN KEY(Id_Personne_Conducteur) REFERENCES Personne(Id_Personne), FOREIGN KEY(Id_Train) REFERENCES Train(Id_Train))");
}
*/






/*
void cloturerConnexion()
{
  if (sqlConnection != NULL)
  {
    mysql_close(sqlConnection);
  }
}

void executerSQL(char *instructionSQL)
{
  if (mysql_query(sqlConnection, instructionSQL))
  {
    fprintf(stderr, "%s\n", mysql_error(sqlConnection));
    mysql_close(sqlConnection);
    exit(EXIT_FAILURE);
  }
}

int insererDonnee(char *instructionSQL)
{
  if (mysql_query(sqlConnection, instructionSQL))
  {
    fprintf(stderr, "%s\n", mysql_error(sqlConnection));
    mysql_close(sqlConnection);
    exit(EXIT_FAILURE);
  }
  MYSQL_RES *sqlResult = mysql_store_result(sqlConnection);
  if (sqlResult == NULL)
  {
    fprintf(stderr, "%s\n", mysql_error(sqlConnection));
    mysql_close(sqlConnection);
    exit(EXIT_FAILURE);
  }
  MYSQL_ROW sqlRow = mysql_fetch_row(sqlResult);
  if (sqlRow == NULL)
  {
    fprintf(stderr, "%s\n", mysql_error(sqlConnection));
    mysql_close(sqlConnection);
    exit(EXIT_FAILURE);
  }
  int id = atoi(sqlRow[0]);
  return id;
}

void remplirTables()
{
  // zone tampon pour les contenus avec valeurs a inserer
  char *inserer = (char *)malloc(1024);
  // Chefs de gare
  int IdAlice = 1;
  sprintf(inserer, "INSERT INTO personne (Id_Personne, nom_pers, prenom_pers, qualification_pers) VALUES (%d, 'Merveille', 'Alice', 'Cheffe de gare')", IdAlice);
  executerSQL(inserer);
  int IdBob = 2;
  sprintf(inserer, "INSERT INTO personne (Id_Personne, nom_pers, prenom_pers, qualification_pers) VALUES (%d, 'Leponge', 'Bob', 'Chef de gare')", IdBob);
  executerSQL(inserer);
  int IdCharlie = 3;
  sprintf(inserer, "INSERT INTO personne (Id_Personne, nom_pers, prenom_pers, qualification_pers) VALUES (%d, 'Hebdo', 'Charlie', 'Chef de gare')", IdCharlie);
  executerSQL(inserer);
}
*/



// stderr : ce dernier flux est associé à la sortie standard d'erreur de votre application. Tout comme stdout, ce flux est normalement redirigé sur la console de l'application.
