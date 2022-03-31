#ifndef USERS_H
#define USERS_H

unsigned short createNewUser(char *username, char *path,char *encryptedPassword, char* erreur);
unsigned short userExist(char *username, char *path,char *erreur);
unsigned updateUsername(char *oldUsername, char *password, char *path, char *newUsername, char *erreur);
void encryptPassword(char *password);

#endif