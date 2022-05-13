#include <stdio.h>
#include <string.h>
#include <mysql.h>
#include "../unity/unity.h"
#include "../includes/connexion.h"
#include "../includes/modeles.h"
#include "../includes/marques.h"


char erreur[250];
 MYSQL *connect;

void setup(){
    connect = connexion_bd(HOSTNAME, USERNAME, PASSWORD, DB_NAME, erreur);
}



void test_creation_table_succes(void){
    createTableMarque(connect,erreur);
    TEST_ASSERT_EQUAL_UINT(1,createTableModeles(connect,erreur));
}

void test_creation_table_modeles(void){
    TEST_ASSERT_EQUAL_UINT(0, createTableModeles(connect, erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Impossible de creer la table modeles\n", erreur);
}


void test_insert_non_reussi(void){
    TEST_ASSERT_EQUAL_UINT(0,insertModeles(connect,"Acura_ILX","ILX","ilx","200002038",erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Impossible de faire l'insertion dans la table modeles\n",erreur);
}

void test_insert_reussi(void){
    addMarques(connect,"../ressources/marques_modeles.txt",erreur);
    TEST_ASSERT_EQUAL_UINT(1,insertModeles(connect,"Acura_ILX","ILX","ilx","200002038",erreur));
}






void test_modeles_fichier_non_ouvert(void){
    TEST_ASSERT_EQUAL_UINT(0, ajoutDesModeles(connect, "ressources/existepas.txt", erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Impossible d'ouvrir le fichier\n", erreur);
}

void test_succes(void){
    TEST_ASSERT_EQUAL_UINT(1,ajoutDesModeles(connect,"../ressources/marques_modeles.txt",erreur));
}





int main(void) {
    UNITY_BEGIN();
    setup();
    RUN_TEST(test_creation_table_succes);
    RUN_TEST(test_creation_table_modeles);
    
    RUN_TEST(test_insert_non_reussi);
    RUN_TEST(test_insert_reussi);

    RUN_TEST(test_modeles_fichier_non_ouvert);
    RUN_TEST(test_succes);
    
    

    UNITY_END();
    return 0;
}
