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
    //verification de validite pour response avant return

    return response;
}

unsigned menu_simple(){
    int response = 0;
    printf("--------------- MENU ----------------\n");
    printf("=====================================\n");
    printf("  1.Afficher les marques\n");
    printf("  2.Afficher les modeles d'une marque\n");
    printf("  3.Afficher les versions d'un modele\n");
    printf("  4.Modifier son username\n");
    printf("  5.Modifier son mot de passe\n");
    printf("  6.Se deconnecter\n");
    scanf("   %d  ", &response);
    //verification de validite pour response avant return

    return response;
}

unsigned menu_admin(){
    int response = 0;
    printf("--------------- MENU ----------------\n");
    printf("=====================================\n");
    printf("  1.Afficher les utilisateurs\n");
    printf("  2.Supprimer un utilisateurs\n");
    printf("  3.Passer un user en administrateur\n");
    printf("  4.....\n");
    printf("  5.Se deconnecter\n");
    scanf("%d", &response);
    //verification de validite pour response avant return

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

unsigned modifier_username(char *current_username, char *erreur) {
    char username[25];
    char password[25];
    printf("------- MODIFIER VOTRE USERNAME -----\n");
    printf("=====================================\n");
    printf("Nouvel username: ");
    scanf("%s", username);
    printf("Mot de passe: ");
    scanf("%s", password);
    if (updateUsername(current_username, password, "../ressources/users.txt", username, erreur) == 1) return 1;

    return 0;
}

unsigned modifier_password(char *username, char *erreur) {
    char cpassword[25];
    char npassword[25];
    printf("------- MODIFIER VOTRE USERNAME -----\n");
    printf("=====================================\n");
    printf("Mot de passe actuel: ");
    scanf("%s", cpassword);
    printf("Nouveau mot de passe: ");
    scanf("%s", npassword);
    if (updatePassword(username, cpassword, "../ressources/users.txt", npassword, erreur) == 1) return 1;

    return 0;
}
