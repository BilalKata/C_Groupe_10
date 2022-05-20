#include <stdint.h> 
#include <stdio.h> 


unsigned afficherEcran1(){
    int response = 0;
    printf("------------- BIENVENUE -------------\n");
    printf("=====================================\n");
    printf("   1. Se connecter\n");
    printf("   2. S'inscrire\n");
    printf("   3. Quitter\n\n");
    printf("   >  ");
    scanf("%d", &response);

    printf("=====================================\n");
    printf("-------------- Voiture --------------\n");
    return 0;
}