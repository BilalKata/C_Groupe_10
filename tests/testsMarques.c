#include <stdio.h>
#include <string.h>
#include <mysql.h>
#include "../unity/unity.h"
#include "../includes/connexion.h"
#include "../includes/marques.h"

char query[200];
char erreur[200];
MYSQL *connexion;
Marque *marque;

void setup(void) {
    connexion = connexion_bd(HOSTNAME, USERNAME, PASSWORD, DB_NAME, erreur);
    mysql_query(connexion, "DROP TABLE Marque");
        
    marque = (Marque *) malloc(30);
    marque->id = (char *) malloc(10);
    marque->name = (char *) malloc(10);
    marque->niceName = (char *) malloc(10);
    
    strcpy(erreur, "");
    strcpy(query, "");
    strcpy(marque->id, "2000");
    strcpy(marque->name, "Mercedes");
    strcpy(marque->niceName, "mercedes");
}

void clear(void) {
    free(marque->id);
    free(marque->name);
    free(marque->niceName);
    free(marque);
    fermerConnexion(connexion);
}

void test_creation_table(void) {
    TEST_ASSERT_EQUAL_UINT(1, creationTableMarque(connexion, erreur));
}

// impossible de creer la table 2 fois car elle existe deja
void test_table_existe(void) {
    creationTableMarque(connexion, erreur);
    TEST_ASSERT_EQUAL_UINT(0, creationTableMarque(connexion, erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Impossible de creer la table marques\n", erreur);
}

void test_insertion_reussie(void) {
    creationTableMarque(connexion, erreur);
    TEST_ASSERT_EQUAL_UINT(1, insertMarque(connexion, marque, erreur));
}

// impossible d'avoir 2 fois la meme marque
void test_insertion_non_reussie(void) {
    creationTableMarque(connexion, erreur);
    insertMarque(connexion, marque, erreur);
    insertMarque(connexion, marque, erreur);
    TEST_ASSERT_EQUAL_STRING("ERREUR: Impossible de faire l'insertion dans la table marque\n", erreur);
}

int main(void) {
    UNITY_BEGIN();
    setup();
    RUN_TEST(test_creation_table);
    setup();
    RUN_TEST(test_table_existe);
    setup();
    RUN_TEST(test_insertion_reussie);
    setup();
    RUN_TEST(test_insertion_non_reussie);
    clear();
    UNITY_END();
    return 0;
}
