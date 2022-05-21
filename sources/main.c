#include <stdio.h>
#include "../includes/affichage.h"

int main(int argc, char **argv) {
    char erreur[255];
    unsigned state = 1;
    unsigned choise = 1;

    choise = afficher_ecran_acceuil();
    while (state) {
        switch (choise) {
            case 1: if (login(erreur) == 1) choise = 4; break;
            case 2: if (signin(erreur) == 1) choise = 1; break;
            case 3: state = 0; break;
            case 4:
            default: state = 0; break;
        }
    }

    return 0;
}