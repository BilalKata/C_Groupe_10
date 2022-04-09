#ifndef USERS_H
#define USERS_H



unsigned authenticateUser(char *username, char *password, char *path,char *erreur);
unsigned short createNewUser(char *username, char *path,char *encryptedPassword, char* erreur);
unsigned short userExist(char *username, char *path, char *erreur);
unsigned updateUsername(char *oldUsername, char *password, char *path, char *newUsername, char *erreur);
unsigned updatePassword(char *username, char *oldPassword, char *path, char *newPassword, char *erreur);
unsigned deleteUser(char *username, char *password, char *path, char *erreur);
void encryptPassword(char *password);

#endif