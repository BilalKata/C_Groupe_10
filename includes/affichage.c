#include <stdio.h> 
#include <string.h>
#include <mysql.h>
#include "../includes/affichage.h"
#include "../includes/users.h"
#include "../includes/marques.h"
#include "../includes/modeles.h"
#include "../includes/versions.h"


unsigned ecran_acceuil(void){
    int response = 0;
    printf("------------- BIENVENUE -------------\n");
    printf("=====================================\n");
    printf("   1. Se connecter\n");
    printf("   2. S'inscrire\n");
    printf("   3. Quitter\n\n");
    printf("   >  ");
    scanf("%d", &response);
    return response;
}

unsigned menu_simple(void){
    int response = 0;
    printf("--------------- MENU ----------------\n");
    printf("=====================================\n");
    printf("  1.Afficher les marques\n");
    printf("  2.Afficher les modeles d'une marque\n");
    printf("  3.Afficher les versions d'un modele\n");
    printf("  4.Modifier votre username\n");
    printf("  5.Modifier votre mot de passe\n");
    printf("  6.Se deconnecter\n");
    scanf("%d", &response);
    return response;
}

unsigned menu_admin(void){
    int response = 0;
    printf("--------------- MENU ----------------\n");
    printf("=====================================\n");
    printf("  1.Afficher les utilisateurs\n");
    printf("  2.Supprimer un utilisateurs\n");
    printf("  3.Passer un user en administrateur\n");
    printf("  4.Se deconnecter\n");
    scanf("%d", &response);
    return response;
}

unsigned login(char *user, char *erreur) {
    char username[25];
    char password[25];
    unsigned connected = 0;

    printf("------------- CONNEXION -------------\n");
    printf("=====================================\n");
    printf("Login: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
    strcpy(user, username);
    return authenticateUser(username, password, "../ressources/users.txt", erreur);
}

unsigned signin(char *erreur) {
    char username[25];
    char password[25];

    printf("---------- CREER UN COMPTE ----------\n");
    printf("=====================================\n");

    printf("Username: ");
    scanf("%s", username);

    if (!userExist(username, "../ressources/users.txt", erreur)) {
        printf("Password: ");
        scanf("%s", password);
        encryptPassword(password);
        createNewUser(username, "../ressources/users.txt", password, erreur);
        return 1;
    }
    return 0;
}

void utilisateurs(void) {
    unsigned short type;
    char username[25];
    char password[25];
    char string_type[4];
    FILE *file = fopen("../ressources/users.txt", "r");
    if (file != NULL) {
        printf("------------ UTILISATEURS -----------\n");
        printf("=====================================\n");
        printf("     EST ADMIN    |       NOM        \n\n");
        while (fscanf(file, "%hd %s %s", &type, username, password) != EOF) {
            (type == 1 ) ? strcpy(string_type, "OUI") : strcpy(string_type, "NON");
            printf("       %s        |  %9s\n", string_type, username);
        }
    }
}
