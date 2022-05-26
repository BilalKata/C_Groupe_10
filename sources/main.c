#include <stdio.h>
#include "../includes/affichage.h"
#include "../includes/users.h"

int main(int argc, char **argv) {
    char erreur[255];
    char username[25];
    unsigned state = 1;
    unsigned choise = 1;
    CLEAN
    choise = ecran_acceuil();
    while (state) {
        switch (choise) {
            case 1: CLEAN if (login(username, erreur) == 1) choise = 4; break;
            case 2: CLEAN if (signin(erreur) == 1) choise = 1; break;
            case 3: CLEAN state = 0; break;
            case 4: CLEAN 
                if (is_admin(username, "../ressources/users.txt", erreur)) {
                    do {
                        choise = menu_admin(username, erreur);
                        CLEAN
                        switch (choise) {
                            case 1: CLEAN utilisateurs(); fgetc(stdin); break;
                            case 2:
                            case 3: CLEAN choise = 4; break;
                            case 4: CLEAN break;
                            default: CLEAN break;
                        }
                    } while (choise != 4);
                    
                }
                else {
                    do {
                        CLEAN
                        choise = menu_simple(username, erreur);
                        switch (choise) {
                            case 1:
                            case 2:
                            case 3: CLEAN choise = 6; break;
                            case 4: CLEAN modifier_username(username, erreur); break;
                            case 5: CLEAN modifier_password(username, erreur); break;
                            default: CLEAN choise = 6; break;
                        }
                    } while (choise != 6);
                }
            default: CLEAN choise = ecran_acceuil(); break;
        }
    }

    return 0;
}