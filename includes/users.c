#include "users.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned authenticateUser(char *username, char *password, char *path, char *erreur){
    unsigned short retour = 0;
    unsigned short type;
    char fileUsername[50];
    char filePassword[50];
    FILE *file = fopen(path, "r");
    if (file != NULL) {
        while (fscanf(file, "%hd %s %s", &type, fileUsername, filePassword) != EOF) {
            if (strcmp(fileUsername, username) == 0) {
                encryptPassword(password);
                if(strcmp(filePassword, password)==0){
                    retour=1;
                    break;
                } else{
                    strcpy(erreur, "ERREUR: Mauvais identifiant de connexion");
                    retour=2;
                    break;
                }
            }
        }
            if (retour != 1 && retour != 2){
                    strcpy(erreur, "ERREUR: Mauvais identifiant de connexion");
                    retour=3;
                    
                }
    }else{
        strcpy(erreur, "ERREUR: Le fichier n as pas ete ouvert");
        retour = 0;
    }
    fclose(file);
    return retour;
}

unsigned short createNewUser(char *username, char *path, char *encryptedPassword, char *erreur){
    unsigned short retour = 0;
    FILE *file = fopen(path, "a");
    if (file != NULL) {
        if (userExist(username, path, erreur)) {
            strcpy(erreur, "ERREUR: Le nom d utilisateur existe deja");
            retour = 0;
        } else {
            fprintf(file, "\n%d %s                    %s                    ", 0, username, encryptedPassword);
            retour = 1;
        }
    }else{
        strcpy(erreur, "ERREUR: Le fichier n as pas ete ouvert");
        retour = 0;
    }
    fclose(file);
    return retour;
}

void encryptPassword(char *password){
    unsigned length = strlen(password);
    char encryptedPassword[length];
    char currentChar;
    for (int i = 0; i <= length; i++) {
        currentChar=password[i];
        if (i%3==0){
            //changement de valeur du bit en fonction de la position du bit
            currentChar ^= 0x20;
            currentChar ^= 0x10;
            currentChar ^= 0x2;
        } else if (i%2==0){
            //Codage asymetrique
            currentChar ^= 0x5;
        } else{
            //swap sur 4 bit
            currentChar = ((currentChar & 0xf0) >> 4) | ((currentChar & 0x0f) << 4);
        }
        currentChar = currentChar | 0x40;
        currentChar = currentChar & 0x7F;
        currentChar = currentChar & 0xFE;//permet d'eviter les caracteres speciaux en debut de table ascii et delete
        encryptedPassword[i] = currentChar;
    }
    strcpy(password, encryptedPassword);
}

unsigned short userExist(char *username, char *path, char *erreur){
    char uname[20];
    char password[20];
    unsigned type;
    unsigned short retour = 0;

    FILE *file = fopen(path, "r");
    
    if (file != NULL) {
        while (fscanf(file, "%d %s %s\n", &type, uname, password)!=EOF){
            if (strcmp(uname, username) == 0){
                retour = 1;
                break;
            }
        }
    } else {
        strcpy(erreur, "ERREUR: Le fichier n as pas ete ouvert");
        retour = 0;
    }
    fclose(file);
    return retour;
}

unsigned updateUsername(char *oldUsername, char *password, char *path, char *newUsername, char *erreur){

    char filePassword[50];
    char fileUsername[50];
    unsigned type;
    int retour;

    FILE* file = fopen(path, "r+");

    if (file == NULL){
        strcpy(erreur, "ERREUR: Le fichier n as pas ete ouvert");
        retour=0;
    }

    if (userExist(newUsername, path, erreur)==0){
        while (fscanf(file, "%d %s %s", &type, fileUsername, filePassword) != EOF) {
            if (strcmp(fileUsername, oldUsername) == 0) {
                encryptPassword(password);
                if(strcmp(filePassword, password)==0){
                    fseek(file, (2+strlen(fileUsername)+20+strlen(filePassword)) * -1, SEEK_CUR);
                    fprintf(file, "%d %s                    %s                    ", type, newUsername, filePassword);
                    retour=1;
                    break;
                } else{
                    strcpy(erreur, "ERREUR: Mauvais mot de passe");
                    retour=2;
                    break;
                }
            }
        }
    }
    else {
        strcpy(erreur, "ERREUR: Nom d'utilisateur deja pris");
        retour=4;
    }
    fclose(file);
    return retour;
}

unsigned updatePassword(char *username, char *oldPassword, char *path, char *newPassword, char *erreur){

    char filePassword[50];
    char fileUsername[50];
    unsigned type;
    int retour;

    FILE* file = fopen(path, "r+");

    if (file == NULL){
        strcpy(erreur, "ERREUR: Le fichier n as pas ete ouvert");
        retour=0;
    }

    while (fscanf(file, "%d %s %s", &type, fileUsername, filePassword) != EOF) {
        if (strcmp(fileUsername, username) == 0) {
            encryptPassword(oldPassword);
            if(strcmp(filePassword, oldPassword)==0){
                encryptPassword(newPassword);
                fseek(file, (2+strlen(fileUsername)+20+strlen(filePassword)) * -1, SEEK_CUR);
                fprintf(file, "%d %s                    %s                    ",type, username, newPassword);
                retour=1;
                break;
            } else{
                strcpy(erreur, "ERREUR: Mauvais mot de passe");
                retour=2;
                break;
            }
        }
    }
    fclose(file);
    return retour;
}

unsigned deleteUser(char *username, char *path, char *erreur){

    char filePassword[50];
    char fileUsername[50];
    unsigned type;
    int retour;

    FILE* file = fopen(path, "r+");

    if (file == NULL){
        strcpy(erreur, "ERREUR: Le fichier n as pas ete ouvert");
        retour=0;
    }

    while (fscanf(file, "%d %s %s", &type, fileUsername, filePassword) != EOF) {
        if (strcmp(fileUsername, username) == 0) {
            fseek(file, (2+strlen(fileUsername) + 20 + strlen(filePassword)) * -1, SEEK_CUR);
            fprintf(file, "%d %s     %s     ", 0,"xxxxxxxxxxxxxxx", "xxxxxxxxxxxxxxx");
            retour=1;
            break;
        }
    }
    fclose(file);
    return retour;
}

unsigned is_admin(char *user, char *path, char *erreur) {
    unsigned short type;
    char username[50];
    char password[50];
    FILE *file = fopen(path, "r");

    while (fscanf(file, "%hd %s %s", &type, username, password) != EOF) 
        if (strcmp(user, username) == 0) break;

    return type;
}
