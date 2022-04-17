#include <string.h>
#include "../unity/unity.h"
#include "../includes/versions.h"
#include "../includes/connexion.h"

static char erreur[255];

void setup(){
    Version *myTestVersion = (Version *) malloc(470);
    myTestVersion->id = (char *) malloc(sizeof(char) * 20);
    myTestVersion->name = (char *) malloc(sizeof(char) * 150);
    myTestVersion->horsepower = (char *) malloc(sizeof(char) * 150);
    myTestVersion->modelNiceName = (char *) malloc(sizeof(char) * 150);
    strcpy(myTestVersion->id,"200485020");
    strcpy(myTestVersion->name,"S PZEV 4dr Wagon (2.5L 5cyl 5M)");
    strcpy(myTestVersion->horsepower,"140");
    strcpy(myTestVersion->modelNiceName,"jetta-sportwagen");
}

void clean(){
    free(myTestVersion->modelNiceName);
    free(myTestVersion->name);
    free(myTestVersion->horsepower);
    free(myTestVersion->id);
    free(myTestVersion);
}

void createTabletest_succes(){
    TEST_ASSERT_EQUAL_UINT8(1, createTableVersion(connexion, erreur));
}
void createTabletest_impossible(){
    TEST_ASSERT_EQUAL_UINT8(0, createTableVersion(connexion, erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Impossible de creer la table version\n", erreur);
}

void mysqlInsertStructVersion_succes(){
    setup();
    TEST_ASSERT_EQUAL_UINT8(0, mysqlInsertStructVersion(connexion, myTestVersion, erreur));
    clean();
}

void mysqlInsertStructVersion_impossible(){
    setup();
    TEST_ASSERT_EQUAL_UINT8(1, mysqlInsertStructVersion(connexion, myTestVersion, erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Insertion impossible\n", erreur);
    clean();
}

int main(void) {
    UNITY_BEGIN();
    //RUN_TEST(createTabletest_succes);
    //RUN_TEST(createTabletest_impossible);
    RUN_TEST(mysqlInsertStructVersion_succes);
    RUN_TEST(mysqlInsertStructVersion_impossible);
    UNITY_END();
    return 0;
}