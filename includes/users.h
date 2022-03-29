#ifndef USERS_H
#define USERS_H

unsigned short createNewUser(char *username, char *path,char *encryptedPassword, char* erreur);
unsigned short userExist(char *username, char *path,char *erreur);
void encryptPassword(char *password);

#endif