#include <string.h>
#include "../unity/unity.h"
#include "../includes/users.h"

static char erreur[255];
char path[100]="../ressources/users.txt";

void createTest_user_deja_existant(void){
    TEST_ASSERT_EQUAL_UINT8(0, createNewUser("admin", path, "utilisateur-test", erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Le nom d utilisateur existe deja", erreur);
}
void createTest_user_fichier_non_ouvert(void){
    TEST_ASSERT_EQUAL_UINT8(0, createNewUser("utilisateur-test2", "ressources/existepas.txt", "utilisateur-test", erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Le fichier n as pas ete ouvert", erreur);
}
void createTest_user_creation_succes(void){
    TEST_ASSERT_EQUAL_UINT8(1, createNewUser("utilisateur-test3", path, "utilisateur-test", erreur));
}
void userExist_user_existe(void){
    TEST_ASSERT_EQUAL_UINT8(1, userExist("admin", path, erreur));
}

void userExist_user_existe_pas(void){
    TEST_ASSERT_EQUAL_UINT8(0, userExist("kskdlfjklsdjfizkflsdjklfjizojksdjfioe", path, erreur));
}

void userExist_user_fichier_non_ouvert(void){
    TEST_ASSERT_EQUAL_UINT8(0, userExist("utilisateur-test2", "ressources/existepas.txt", erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Le fichier n as pas ete ouvert", erreur);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(createTest_user_deja_existant);
    RUN_TEST(createTest_user_fichier_non_ouvert);
    RUN_TEST(createTest_user_creation_succes);
    RUN_TEST(userExist_user_existe);
    RUN_TEST(userExist_user_existe_pas);
    RUN_TEST(userExist_user_fichier_non_ouvert);
    UNITY_END();
    return 0;
}