#include <string.h>
#include "../unity/unity.h"
#include "../includes/users.h"


static char erreur[255];
char password[]="atome";
char path[]= "../ressources/usersTest.txt";

void setup(){
    strcpy(erreur, "");

    // RESET du fichier
    FILE *file= fopen(path, "w");
    fprintf(file, "%s %s                                  \n", "admin", "admin");
    fprintf(file, "%s %s                                  \n", "root", "rootroot");
    fprintf(file, "%s %s                                  \n", "mainUser", "123");
    fprintf(file, "%s %s                                  \n", "", "");
    fprintf(file, "%s %s                                  \n", "", "");
    fclose(file);
}

void createTest_user_deja_existant(void){
    setup();
    TEST_ASSERT_EQUAL_UINT8(0, createNewUser("admin", path, "utilisateur-test", erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Le nom d utilisateur existe deja", erreur);
}
void createTest_user_fichier_non_ouvert(void){
    setup();
    TEST_ASSERT_EQUAL_UINT8(0, createNewUser("utilisateur-test2", "ressources/existepas.txt", "utilisateur-test", erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Le fichier n as pas ete ouvert", erreur);
}
void createTest_user_creation_succes(void){
    setup();
    TEST_ASSERT_EQUAL_UINT8(1, createNewUser("User1", path, "234", erreur));
}
void userExist_user_existe(void){
    setup();
    TEST_ASSERT_EQUAL_UINT8(1, userExist("admin", path, erreur));
}

void userExist_user_existe_pas(void){
    setup();
    TEST_ASSERT_EQUAL_UINT8(0, userExist("kskdlfjklsdjfizkflsdjklfjizojksdjfioe", path, erreur));
}

void userExist_user_fichier_non_ouvert(void){
    setup();
    TEST_ASSERT_EQUAL_UINT8(0, userExist("utilisateur-test2", "ressources/existepas.txt", erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Le fichier n as pas ete ouvert", erreur);
}

void cryptPassword_users(void){
    setup();
    encryptPassword(password);
    TEST_ASSERT_EQUAL_STRING("RFj^`@", password);
}

void updateUser_succes(void){
    setup();
    TEST_ASSERT_EQUAL_UINT(1, updateUsername("mainUser","123", path,"mainUser1234",erreur));
}

void updateUser_failPassword(void){
    setup();
    TEST_ASSERT_EQUAL_UINT(2, updateUsername("mainUser","123456", path,"test3",erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Mauvais mot de passe", erreur);
}

void updateUser_failUsedName(void){
    setup();
    TEST_ASSERT_EQUAL_UINT(4, updateUsername("test2","test", path,"admin",erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Nom d'utilisateur deja pris", erreur);
}

void updatePassword_succes(void){
    setup();
    TEST_ASSERT_EQUAL_UINT(1, updatePassword("mainUser","123", path,"test2",erreur));
}

void updatePassword_failPassword(void){
    setup();
    TEST_ASSERT_EQUAL_UINT(2, updatePassword("mainUser","qsdqsd", path,"ldqmldqs",erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Mauvais mot de passe", erreur);
}

void deleteUser_succes(void){
    setup();
    TEST_ASSERT_EQUAL_UINT(1, deleteUser("mainUser", "123",  path, erreur));

}

void deleteUser_failPassword(void){
    setup();
    TEST_ASSERT_EQUAL_UINT(2, deleteUser("mainUser", "456",  path, erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Mauvais mot de passe", erreur);
}

void authUser_succes(void){
    setup();
    TEST_ASSERT_EQUAL_UINT(1, authenticateUser("mainUser", "123",  path, erreur));
}

void authUser_failPassword(void){
    setup();
    TEST_ASSERT_EQUAL_UINT(2, authenticateUser("mainUser", "hjdsdkq",  path, erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Mauvais identifiant de connexion", erreur);
}

void authUser_failUsername(void){
    setup();
    TEST_ASSERT_EQUAL_UINT(3, authenticateUser("mainUser1", "123",  path, erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Mauvais identifiant de connexion", erreur);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(createTest_user_deja_existant);
    RUN_TEST(createTest_user_fichier_non_ouvert);
    RUN_TEST(createTest_user_creation_succes);
    RUN_TEST(userExist_user_existe);
    RUN_TEST(userExist_user_existe_pas);
    RUN_TEST(userExist_user_fichier_non_ouvert);
    RUN_TEST(cryptPassword_users);
    RUN_TEST(updateUser_succes);
    RUN_TEST(updateUser_failPassword);
    RUN_TEST(updateUser_failUsedName);
    RUN_TEST(updatePassword_succes);
    RUN_TEST(updatePassword_failPassword);
    RUN_TEST(deleteUser_succes);
    RUN_TEST(deleteUser_failPassword);
    RUN_TEST(authUser_succes);
    RUN_TEST(authUser_failPassword);
    RUN_TEST(authUser_failUsername);

    UNITY_END();
    return 0;
}