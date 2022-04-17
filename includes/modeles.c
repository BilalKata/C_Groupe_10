#include <stdlib.h>
#include <stdio.h>
#include <mysql.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>
#include "json.h"

void Connexion();
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
    char resultatNiceName[1500];
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
          //printf("%s\n",resultatId);
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

        if (ligne[a] == 'n' && ligne[a+1] == 'i' && ligne[a+2] =='c' && ligne[a+3]=='e' && ligne[a+4] =='N' && ligne[a+5] == 'a' && ligne[a+6] == 'm' && ligne[a+7]=='e')
        {
          a=a+11;
          captureNiceName=0;
          while (ligne[a] == '\"' || ligne[a] == ':' || ligne[a] == '{' || ligne[a] =='}' || ligne[a] ==',' || ligne[a] == '['|| ligne[a] ==']')
          {
            a++;
          }
          captureNiceName=0;
          while (ligne[a] != '\"')
          {
            resultatNiceName[captureNiceName]=ligne[a];
            a++;
            captureNiceName++;
          if (ligne[a]=='\"')
          {
            resultatNiceName[captureNiceName]='\0';
          }

          }
          //printf("%s\n",resultatNiceName);
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











/*

int Connect;

void Connexion()
//Fonction connexion
{
  Connect = mysql_init(NULL);
  if (Connect == NULL)//Si pas de Bd
  {
    fprintf(stderr, "%s\n", mysql_error(Connect));//On signale une erreur 
    exit(EXIT_FAILURE);
  }

  if (!mysql_real_connect(Connect, "localhost", "root", NULL, "Voitures", 3306, NULL, 0))//Si on peut pas se connecter à la db
  {
    fprintf(stderr, "%s\n", mysql_error(Connect));//signale une erreur
    exit(EXIT_FAILURE);
  }
}

void executerSQL(char *instructionSQL)
//Fonction executerSQL
{
  if (mysql_query(Connect, instructionSQL))
  {
    fprintf(stderr, "%s\n", mysql_error(Connect));
    mysql_close(Connect);
    exit(EXIT_FAILURE);
  }
}

void garnir(char *id, char *name, char *nicename)
{
  char *inserer = (char *)malloc(1024);//Buffer pour inserer dans la table
  sprintf(inserer, "INSERT INTO modeles (ID_modele,NAME_Modele , NICENAME_Modele) VALUES ('%s', '%s', '%s')", id, name, nicename);
  executerSQL(inserer);
}

void cloturerConnexion()
//Fonction cloturerConnexion
{
  if (Connect != NULL)
  {
    mysql_close(Connect);
  }
}

void creerTables()
//Fonction creerTables 
{
  executerSQL("DROP DATABASE IF EXISTS voiture");
  executerSQL("CREATE DATABASE voiture CHARACTER SET = 'latin1' COLLATE = 'latin1_general_cs'");
  executerSQL("USE voiture");
  executerSQL("CREATE TABLE modeles (ID_Modele VARCHAR(75),NAME_Modele VARCHAR(75), NICENAME_Modele VARCHAR(75))");//Crée les champs de la table
}
*/







// stderr : ce dernier flux est associé à la sortie standard d'erreur de votre application. Tout comme stdout, ce flux est normalement redirigé sur la console de l'application.
