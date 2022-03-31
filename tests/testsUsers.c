#include <string.h>
#include "../unity/unity.h"
#include "../includes/users.h"

static char erreur[255];
char password[]="atome";
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

void cryptPassword_users(void){
    encryptPassword(password);
    TEST_ASSERT_EQUAL_STRING("SGj_`", password);
}

void updateUser_succes(void){
    TEST_ASSERT_EQUAL_UINT(1, updateUsername("test","test","../ressources/users.txt","test2",erreur));
}

void updateUser_failPassword(void){
    TEST_ASSERT_EQUAL_UINT(2, updateUsername("test2","test2","../ressources/users.txt","test3",erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Mauvais mot de passe", erreur);
}

void updateUser_failUsedName(void){
    TEST_ASSERT_EQUAL_UINT(4, updateUsername("test2","test","../ressources/users.txt","admin",erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Nom d'utilisateur deja pris", erreur);
}

int main(void) {
    UNITY_BEGIN();
    //RUN_TEST(createTest_user_deja_existant);
    //RUN_TEST(createTest_user_fichier_non_ouvert);
    //RUN_TEST(createTest_user_creation_succes);
    //RUN_TEST(userExist_user_existe);
    //RUN_TEST(userExist_user_existe_pas);
    //RUN_TEST(userExist_user_fichier_non_ouvert);
    //RUN_TEST(cryptPassword_users);
    RUN_TEST(updateUser_succes);
    RUN_TEST(updateUser_failPassword);
    RUN_TEST(updateUser_failUsedName);
    UNITY_END();
    return 0;
}