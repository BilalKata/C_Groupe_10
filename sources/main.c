#include <stdio.h>
#include "../includes/affichage.h"
#include "../includes/users.h"

int main(int argc, char **argv) {
    char erreur[255];
    char username[25];
    unsigned state = 1;
    unsigned choise = 1;

    choise = ecran_acceuil();
    while (state) {
        switch (choise) {
            case 1: if (login(username, erreur) == 1) choise = 4; break;
            case 2: if (signin(erreur) == 1) choise = 1; break;
            case 3: state = 0; break;
            case 4: 
                if (is_admin(username, "../ressources/users.txt", erreur)) menu_admin();
                else menu_simple();
            default: choise = ecran_acceuil(); break;
        }
    }

    return 0;
}