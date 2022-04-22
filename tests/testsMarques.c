#include <stdio.h>
#include <string.h>
#include <mysql.h>
#include "../unity/unity.h"
#include "../includes/connexion.h"
#include "../includes/marques.h"

char erreur[200];
char query[50];
char path[50];
char  marques[40][NAME_LENGTH];
unsigned nbr_element;
MYSQL *connexion;
Marque *marque;
MYSQL_ROW row;

void setup(void) {
    connexion = connexion_bd(HOSTNAME, USERNAME, PASSWORD, DB_NAME, erreur);
    mysql_query(connexion, "DROP TABLE Version");
    mysql_query(connexion, "DROP TABLE Modele");
    mysql_query(connexion, "DROP TABLE Marque");
        
    marque = (Marque *) malloc(30);
    marque->id = (char *) malloc(10);
    marque->name = (char *) malloc(10);
    marque->niceName = (char *) malloc(10);
    
    strcpy(erreur, "");
    strcpy(query, "");
    strcpy(path, "");
    strcpy(marque->id, "2000");
    strcpy(marque->name, "Mercedes");
    strcpy(marque->niceName, "mercedes");
    strcpy(path, "../ressources/marques_modeles.txt");

}

void clear(void) {
    free(marque->id);
    free(marque->name);
    free(marque->niceName);
    free(marque);
    fermerConnexion(connexion);
}

void test_creation_table(void) {
    TEST_ASSERT_EQUAL_UINT(1, createTableMarque(connexion, erreur));
}

// impossible de creer la table 2 fois car elle existe deja
void test_table_existe(void) {
    createTableMarque(connexion, erreur);
    TEST_ASSERT_EQUAL_UINT(0, createTableMarque(connexion, erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Impossible de creer la table marques\n", erreur);
}

void test_insertion_reussie(void) {
    createTableMarque(connexion, erreur);
    TEST_ASSERT_EQUAL_UINT(1, insertMarque(connexion, marque, erreur));
}

// impossible d'avoir 2 fois la meme marque
void test_insertion_non_reussie(void) {
    createTableMarque(connexion, erreur);
    insertMarque(connexion, marque, erreur);
    insertMarque(connexion, marque, erreur);
    TEST_ASSERT_EQUAL_STRING("ERREUR: Impossible de faire l'insertion dans la table marque\n", erreur);
}

void test_insertion_avec_fichier(void) {
    createTableMarque(connexion, erreur);
    TEST_ASSERT_EQUAL_UINT(1, addMarques(connexion, path, erreur));
}

void test_trouver_un_element(void) {
    strcpy(query, "SELECT * FROM Marque WHERE id = 200002305");
    createTableMarque(connexion, erreur);
    addMarques(connexion, path, erreur);
    mysql_query(connexion, query);
    row = mysql_fetch_row(mysql_store_result(connexion));
    TEST_ASSERT_EQUAL_STRING("200002305", row[0]);
    TEST_ASSERT_EQUAL_STRING("MINI", row[1]);
    TEST_ASSERT_EQUAL_STRING("mini", row[2]);
}

void test_insertion_avec_info_manquante(void) {
    strcpy(path, "../ressources/versions_moteurs.txt");
    createTableMarque(connexion, erreur);
    TEST_ASSERT_EQUAL_UINT(0, addMarques(connexion, path, erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Attribut non trouve\n", erreur);
}

void test_select_reussie(void) {
    const char result[40][20] = {"Acura","Aston Martin","Audi","Bentley","BMW","Buick","Cadillac","Chevrolet","Chrysler","Dodge","Ferrari","FIAT","Ford","GMC","Honda","Hyundai","Infiniti","Jaguar","Jeep","Kia","Lamborghini","Land Rover","Lexus","Lincoln","Lotus","Maserati","Mazda","Mercedes-Benz","MINI","Mitsubishi","Nissan","Porsche","Ram","Rolls-Royce","Scion","Subaru","Tesla","Toyota","Volkswagen","Volvo"};
    createTableMarque(connexion, erreur);
    addMarques(connexion, path, erreur);
    TEST_ASSERT_EQUAL_UINT(1, selectMarques(connexion, marques, &nbr_element, erreur));
    TEST_ASSERT_EQUAL_STRING_ARRAY(result, marques, 40);
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
    setup();
    RUN_TEST(test_insertion_avec_fichier);
    setup();
    RUN_TEST(test_trouver_un_element);
    setup();
    RUN_TEST(test_insertion_avec_info_manquante);
    setup();
    RUN_TEST(test_select_reussie);
    clear();
    UNITY_END();
    return 0;
}
