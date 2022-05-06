#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
#include "../unity/unity.h"
#include "../includes/versions.h"
#include "../includes/connexion.h"

static char erreur[255];
static char path[]="../ressources/versions_moteurs.txt";
Version *version_t;
MYSQL *connexion;


void setup(void) {
    connexion = connexion_bd(HOSTNAME, USERNAME, PASSWORD, DB_NAME, erreur);
    mysql_query(connexion, "DROP TABLE version");
        
    version_t = (Version *) malloc(120);
    version_t->id = (char *) malloc(10);
    version_t->name = (char *) malloc(50);
    version_t->horsepower = (char *) malloc(10);
    version_t->modelNiceName = (char *) malloc(50);
    
    strcpy(erreur, "");
    strcpy(version_t->id, "200485020");
    strcpy(version_t->name, "S PZEV 4dr Wagon (2.5L 5cyl 5M)");
    strcpy(version_t->horsepower, "140");
    strcpy(version_t->modelNiceName, "jetta-sportwagen");
}

void clean(void) {
    free(version_t->id);
    free(version_t->name);
    free(version_t->horsepower);
    free(version_t->modelNiceName);
    free(version_t);
    fermerConnexion(connexion);
}

void createTabletest_succes(){
    TEST_ASSERT_EQUAL_UINT8(1, createTableVersion(connexion, erreur));
}
void createTabletest_impossible(){
    createTableVersion(connexion, erreur);
    TEST_ASSERT_EQUAL_UINT8(0, createTableVersion(connexion, erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Impossible de creer la table version\n", erreur);
}

void mysqlInsertStructVersion_succes(){
    createTableVersion(connexion, erreur);
    TEST_ASSERT_EQUAL_UINT8(1, insertVersion(connexion, version_t, erreur));
}

void mysqlInsertStructVersion_impossible(){
    createTableVersion(connexion, erreur);
    insertVersion(connexion, version_t, erreur);
    TEST_ASSERT_EQUAL_UINT8(0, insertVersion(connexion, version_t, erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Insertion impossible\n", erreur);
}

void ajoutVersion_succes(){
    createTableVersion(connexion, erreur);
    TEST_ASSERT_EQUAL_UINT8(0, addVersions(connexion, path, erreur));
    mysql_query(connexion, "SELECT * FROM version WHERE id=200471912");
    MYSQL_RES *result = mysql_store_result(connexion);
    MYSQL_ROW row;
    row = mysql_fetch_row(result);
    TEST_ASSERT_EQUAL_STRING("200471912", row[0]);
    TEST_ASSERT_EQUAL_STRING("Technology Package 4dr Sedan (2.0L 4cyl 5A)", row[1]);
    TEST_ASSERT_EQUAL_STRING("150", row[2]);
    TEST_ASSERT_EQUAL_STRING("ilx", row[3]);
    mysql_free_result(result);
}

void ajoutVersion_fichierNonOuvert(){
    TEST_ASSERT_EQUAL_UINT8(1, addVersions(connexion, "test.txt", erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Fichier non ouvert", erreur);
}

int main(void) {
    UNITY_BEGIN();
    setup();
    RUN_TEST(createTabletest_succes);
    setup();
    RUN_TEST(createTabletest_impossible);
    setup();
    RUN_TEST(mysqlInsertStructVersion_succes);
    setup();
    RUN_TEST(mysqlInsertStructVersion_impossible);
    setup();
    RUN_TEST(ajoutVersion_succes);
    setup();
    RUN_TEST(ajoutVersion_fichierNonOuvert);
    clean();
    UNITY_END();
    return 0;
}