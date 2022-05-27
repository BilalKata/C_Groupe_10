#include <stdio.h> 
#include <string.h>
#include <mysql.h>
#include <stdlib.h>
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
    printf("  6.Se deconnecter\n\n");
    printf("   >  ");
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
    printf("  4.Initialiser la BDD\n");
    printf("  5.Supprimer les donnees\n");
    printf("  6.Se deconnecter\n\n");
    printf("   >  ");
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
    return authenticateUser(username, password, PATH, erreur);
}

unsigned signin(char *erreur) {
    char username[25];
    char password[25];

    printf("---------- CREER UN COMPTE ----------\n");
    printf("=====================================\n");

    printf("Username: ");
    scanf("%s", username);

    if (!userExist(username, PATH, erreur)) {
        printf("Password: ");
        scanf("%s", password);
        encryptPassword(password);
        createNewUser(username, PATH, password, erreur);
        return 1;
    }
    return 0;
}

void utilisateurs(void) {
    unsigned short type;
    char username[25];
    char password[25];
    char string_type[4];
    char c;
    FILE *file = fopen(PATH, "r");
    if (file != NULL) {
        printf("------------ UTILISATEURS -----------\n");
        printf("=====================================\n");
        printf("     EST ADMIN    |       NOM        \n");
        printf("-------------------------------------\n");
        while (fscanf(file, "%hd %s %s", &type, username, password) != EOF) {
            if(strcmp(username, "xxxxxxxxxxxxxxx") == 0) continue;
            (type == 1 ) ? strcpy(string_type, "OUI") : strcpy(string_type, "NON");
            printf("       %s        |  %9s\n", string_type, username);
        }
    }
    fflush(stdin);
    c = getchar();
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
    if (updateUsername(current_username, password, PATH, username, erreur) == 1) {
        strcpy(current_username, username);
        return 1;
    }
    
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
    if (updatePassword(username, cpassword, PATH, npassword, erreur) == 1) return 1;

    return 0;
}

unsigned delete_user(char *username, char *erreur) {
    char dusername[255];
    printf("------ SUPPRIMER UN UTILISATEUR -----\n");
    printf("=====================================\n");
    printf("Username a supprimer: ");
    scanf("%s", dusername);
    if (strcmp(username, dusername) != 0)
        if (deleteUser(dusername, PATH, erreur) == 1)
            return 1;
    return 0;
}

unsigned make_admin(char *erreur) {
    char username[255];
    printf("------ METTRE UN USER EN ADMIN ------\n");
    printf("=====================================\n");
    printf("Username: ");
    scanf("%s", username);
    if (makeUserAdmin(username, PATH, erreur) == 1) return 1;
    return 0;
}

void init(MYSQL *connexion, char *erreur) {
    if (createTableMarque(connexion, erreur) == 0) {
        fprintf(stderr, "%s", erreur);
        exit(1);
    }
    if (createTableModeles(connexion, erreur) == 0) {
        fprintf(stderr, "%s", erreur);
        exit(1);
    }
    if (createTableVersion(connexion, erreur) == 0) {
        fprintf(stderr, "%s", erreur);
        exit(1);
    }
    if (addMarques(connexion, "../ressources/marques_modeles.txt", erreur) == 0) {
        fprintf(stderr, "%s", erreur);
        exit(1);
    }
    if (ajoutDesModeles(connexion, "../ressources/marques_modeles.txt", erreur) == 0) {
        fprintf(stderr, "%s", erreur);
        exit(1);
    }
    if (addVersions(connexion, "../ressources/versions_moteurs.txt", erreur) == 0) {
        fprintf(stderr, "%s", erreur);
        exit(1);
    }
}

void reset(MYSQL *connexion) {
    if (mysql_query(connexion, "DROP TABLE IF EXISTS Version") != 0) {
        fprintf(stderr, "ERREUR: Impossible de supprimer la table Version");
        exit(1);
    }
    
    if (mysql_query(connexion, "DROP TABLE IF EXISTS Modele") != 0) {
        fprintf(stderr, "ERREUR: Impossible de supprimer la table Modele");
        exit(1);
    }
    
    if (mysql_query(connexion, "DROP TABLE IF EXISTS Marque") != 0) {
        fprintf(stderr, "ERREUR: Impossible de supprimer la table Marque");
        exit(1);
    }
void afficher_marques(MYSQL *connexion, char *erreur) {
    unsigned nbr_marques = 40;
    char c;
    Marque marques[nbr_marques];
    if (selectMarques(connexion, marques, &nbr_marques, erreur) == 0) {
        fprintf(stderr, "%s", erreur);
        exit(1);
    }
    printf("--------- Liste des marques ---------\n");
    printf("=====================================\n");
    printf("Il y a %d marques :\n", nbr_marques);
    printf("%s\t\t%s\t%15s\n", "Id", "Name", "NiceName");
    printf("=======================================\n");
    for (unsigned i = 0; i < nbr_marques; i++){
        printf("%s\t%s%15s\n", marques[i].id, marques[i].name, marques[i].niceName);
        free(marques[i].id);
        free(marques[i].name);
        free(marques[i].niceName);
    }
    fflush(stdin);
    c = getchar();
}

void afficher_modeles(MYSQL *connexion, char *erreur) {

    unsigned nbr_modeles = 40;
    char resultatModele[50][10];
    char marque[10];
    printf("Entrez le nom de la marque(en minuscule): \n> ");
    scanf("%s", &marque);
    char c;
    int i=0;
    printf("--------- Liste des modeles ---------\n");
    printf("=====================================\n");
    if (select(connexion, marque, resultatModele, &nbr_modeles, erreur) == 0){
        fprintf(stderr, "%s, Merci de recommencer!", erreur);
        fflush(stdin);
        c = getchar();
    }else{
        printf("Il y a %d modele(s) de la marque %s\n", nbr_modeles, marque);

        for (i = 0; i < nbr_modeles; i++)
        {
            printf(">%s\n", &resultatModele[i][0]);
        }
        printf("=======================================\n");
        fflush(stdin);
        c = getchar();
    }
}

void afficher_versions(MYSQL *connexion, char *erreur){
    char c;
    unsigned nbr_versions = 40;
    char version[3][2][50];
    char marque[50]="à definir";
    char modele[50];
    int i = 0;

    printf("Entrez le nom du modele(en minuscule): \n> ");
    scanf("%s", &modele);
    
    if (selectByNiceNameOrdered(connexion, version, &nbr_versions, modele, erreur) == 0){
        fprintf(stderr, "%s, Merci de recommencer!", erreur);
        fflush(stdin);
        c = getchar();
    }else{
        printf("--------- Liste des modeles ---------\n");
        printf("=====================================\n");
        printf("Il y a %d version(s) du modele(%s) %s\n", nbr_versions, modele, marque);

        for (i = 0; i < nbr_versions; i++)
        {
            printf(">%s >%s\n", &version[i][0], &version[i][1]);
        }
        printf("=======================================\n");
        fflush(stdin);
        c = getchar();
    }
    
    fflush(stdin);
    c = getchar();
}