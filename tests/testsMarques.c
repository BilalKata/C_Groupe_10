#include <string.h>
#include <mysql.h>
#include "../unity/unity.h"
#include "../includes/connexion.h"
#include "../includes/marques.h"

static char query[200];
static char erreur[200];
static MYSQL *connexion;

void setup(void) {
    strcpy(erreur, "");
    strcpy(query, "");
    connexion = connexion_bd(HOSTNAME, USERNAME, PASSWORD, DB_NAME, erreur);
    mysql_query(connexion, "DROP TABLE Marque");
}

void test_creation_table(void) {
    setup();
    TEST_ASSERT_EQUAL_UINT(1, creationTableMarque(connexion, erreur));
}

// impossible de creer la table 2 fois car elle existe deja
void test_table_existe(void) {
    setup();
    TEST_ASSERT_EQUAL_UINT(1, creationTableMarque(connexion, erreur)); 
    TEST_ASSERT_EQUAL_UINT(0, creationTableMarque(connexion, erreur));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_creation_table);
    RUN_TEST(test_table_existe);
    UNITY_END();
    return 0;
}
