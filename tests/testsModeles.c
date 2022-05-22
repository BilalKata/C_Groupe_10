#include <stdio.h>
#include <string.h>
#include <mysql.h>
#include "../unity/unity.h"
#include "../includes/connexion.h"
#include "../includes/modeles.h"
#include "../includes/marques.h"


char erreur[250];
char resultatModele[50][10];
 MYSQL *connect;

void setup(){
    connect = connexion_bd(HOSTNAME, USERNAME, PASSWORD, DB_NAME, erreur);
    mysql_query(connect, "DROP TABLE modele");
    
}

void clean(){
    fermerConnexion(connect);
}


void test_creation_table_succes(void){
    createTableMarque(connect,erreur);
    TEST_ASSERT_EQUAL_UINT(1,createTableModeles(connect,erreur));
}

void test_creation_table_modele_erreur(void){
    TEST_ASSERT_EQUAL_UINT(0, createTableModeles(connect, erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Impossible de creer la table modeles\n", erreur);
}


void test_insert_non_reussi(void){
    createTableModeles(connect,erreur);
    TEST_ASSERT_EQUAL_UINT(0,insertModeles(connect,"Acura_ILX","ILX","ilx","20000203812",erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Impossible de faire l'insertion dans la table modeles\n",erreur);
}

void test_insert_reussi(void){
    createTableModeles(connect,erreur);
    addMarques(connect,"../ressources/marques_modeles.txt",erreur);
    TEST_ASSERT_EQUAL_UINT(1,insertModeles(connect,"Acura_ILX","ILX","ilx","200002038",erreur));
}




void test_modeles_fichier_non_ouvert(void){
    createTableModeles(connect,erreur);
    TEST_ASSERT_EQUAL_UINT(0, ajoutDesModeles(connect, "ressources/existepas.txt", erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Impossible d'ouvrir le fichier\n", erreur);
}

void test_succes(void){
    createTableModeles(connect,erreur);
    TEST_ASSERT_EQUAL_UINT(1,ajoutDesModeles(connect,"../ressources/marques_modeles.txt",erreur));
}



void test_select_success(void){
    createTableModeles(connect,erreur);
    ajoutDesModeles(connect,"../ressources/marques_modeles.txt",erreur);
    TEST_ASSERT_EQUAL_UINT(1,select(connect,"audi",resultatModele,erreur));
}

void test_select_fail(void){
    createTableModeles(connect,erreur);
    ajoutDesModeles(connect,"../ressources/marques_modeles.txt",erreur);
    TEST_ASSERT_EQUAL_UINT(0,select(connect,"esfe",resultatModele,erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Mauvaise entree",erreur);
}







int main(void) {
    UNITY_BEGIN();
   
    setup();
    RUN_TEST(test_creation_table_succes);
    
    RUN_TEST(test_creation_table_modele_erreur);
    
    setup();
    RUN_TEST(test_insert_non_reussi);
    setup();
    RUN_TEST(test_insert_reussi);

    setup();
    RUN_TEST(test_modeles_fichier_non_ouvert);
    setup();
    RUN_TEST(test_succes);

    setup();
    RUN_TEST(test_select_success);
    setup();
    RUN_TEST(test_select_fail);
    
    

    UNITY_END();
    return 0;
}
