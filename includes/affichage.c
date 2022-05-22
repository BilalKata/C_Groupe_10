#include <stdio.h> 
#include <stdlib.h>
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
    scanf("%d", &response);
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

unsigned login(char *erreur) {
    char username[25];
    char password[25];
    unsigned connected = 0;

    printf("------------- CONNEXION -------------\n");
    printf("=====================================\n");
    printf("Login: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);
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
