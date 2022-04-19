#include <string.h>
#include <mysql.h>
#include "../unity/unity.h"
#include "../includes/versions.h"
#include "../includes/connexion.h"

static char erreur[255];
static char path[]="";
MYSQL *connexion;




void createTabletest_succes(){
    connexion = connexion_bd("localhost", "root", "", "voiture", erreur);
    TEST_ASSERT_EQUAL_UINT8(1, createTableVersion(connexion, erreur));
    fermerConnexion(connexion);
}
void createTabletest_impossible(){
    connexion = connexion_bd("localhost", "root", "", "voiture", erreur);
    TEST_ASSERT_EQUAL_UINT8(0, createTableVersion(connexion, erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Impossible de creer la table version\n", erreur);
    fermerConnexion(connexion);
}

void mysqlInsertStructVersion_succes(){
    connexion = connexion_bd("localhost", "root", "", "voiture", erreur);
    Version *myTestVersion = (Version *) malloc(470);
    myTestVersion->id = (char *) malloc(sizeof(char) * 20);
    myTestVersion->name = (char *) malloc(sizeof(char) * 150);
    myTestVersion->horsepower = (char *) malloc(sizeof(char) * 150);
    myTestVersion->modelNiceName = (char *) malloc(sizeof(char) * 150);
    strcpy(myTestVersion->id,"200485020");
    strcpy(myTestVersion->name,"S PZEV 4dr Wagon (2.5L 5cyl 5M)");
    strcpy(myTestVersion->horsepower,"140");
    strcpy(myTestVersion->modelNiceName,"jetta-sportwagen");
    TEST_ASSERT_EQUAL_UINT8(0, mysqlInsertStructVersion(connexion, myTestVersion, erreur));
    free(myTestVersion->modelNiceName);
    free(myTestVersion->name);
    free(myTestVersion->horsepower);
    free(myTestVersion->id);
    free(myTestVersion);
    fermerConnexion(connexion);
    
}

void mysqlInsertStructVersion_impossible(){
    
    connexion = connexion_bd("localhost", "root", "", "voiture", erreur);
    Version *myTestVersion = (Version *) malloc(470);
    myTestVersion->id = (char *) malloc(sizeof(char) * 20);
    myTestVersion->name = (char *) malloc(sizeof(char) * 150);
    myTestVersion->horsepower = (char *) malloc(sizeof(char) * 150);
    myTestVersion->modelNiceName = (char *) malloc(sizeof(char) * 150);
    strcpy(myTestVersion->id,"200485020");
    strcpy(myTestVersion->name,"S PZEV 4dr Wagon (2.5L 5cyl 5M)");
    strcpy(myTestVersion->horsepower,"140");
    strcpy(myTestVersion->modelNiceName,"jetta-sportwagen");
    TEST_ASSERT_EQUAL_UINT8(1, mysqlInsertStructVersion(connexion, myTestVersion, erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Insertion impossible\n", erreur);
    free(myTestVersion->modelNiceName);
    free(myTestVersion->name);
    free(myTestVersion->horsepower);
    free(myTestVersion->id);
    free(myTestVersion);
    fermerConnexion(connexion);
    
}

void ajoutVersion_succes(){
    //base de donnee existante
    connexion = connexion_bd("localhost", "root", "", "voiture", erreur);
    TEST_ASSERT_EQUAL_UINT8(0, ajoutVersion(connexion, path, erreur));
    mysql_query(connexion, "SELECT * FROM Marque");
    MYSQL_RES *result = mysql_store_result(connexion);
    MYSQL_ROW row;
    row = mysql_fetch_row(result);
    TEST_ASSERT_EQUAL_STRING("200471912", row[0]);
    TEST_ASSERT_EQUAL_STRING("Technology Package 4dr Sedan (2.0L 4cyl 5A)", row[1]);
    TEST_ASSERT_EQUAL_STRING("acura", row[2]);
    TEST_ASSERT_EQUAL_STRING("150", row[3]);
    mysql_free_result(result);
    fermerConnexion(connexion);
}



void ajoutVersion_fichierNonOuvert(){
    //base de donnee existante
    connexion = connexion_bd("localhost", "root", "", "voiture", erreur);
    TEST_ASSERT_EQUAL_UINT8(1, ajoutVersion(connexion, "test.txt", erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Fichier non ouvert", erreur);
    fermerConnexion(connexion);
}


int main(void) {
    UNITY_BEGIN();
    //RUN_TEST(createTabletest_succes);
    //RUN_TEST(createTabletest_impossible);
    //RUN_TEST(mysqlInsertStructVersion_succes);
    //RUN_TEST(mysqlInsertStructVersion_impossible);
    RUN_TEST(ajoutVersion_fichierNonOuvert);
    RUN_TEST(ajoutVersion_succes);
    fermerConnexion(connexion);
    UNITY_END();
    return 0;
}