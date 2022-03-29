#include "users.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned short createNewUser(char *username, char *path, char *encryptedPassword, char *erreur){
    unsigned short retour = 0;
    FILE *file = fopen(path, "a");
    if (file != NULL) {
        if (userExist(username, path, erreur)) {
            strcpy(erreur, "ERREUR: Le nom d utilisateur existe deja");
            retour = 0;
        } else {
            fprintf(file, "\n%s %s", username, encryptedPassword);
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
        encryptedPassword[i] = currentChar;
    }
    strcpy(password, encryptedPassword);
}

unsigned short userExist(char *username, char *path, char *erreur){
    char uname[20];
    char password[20];
    unsigned short retour = 0;

    FILE *file = fopen(path, "r");
    
    if (file != NULL) {
        while (fscanf(file, "%s %s\n", uname, password)!=EOF){
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


