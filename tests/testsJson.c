#include <string.h>
#include "../includes/json.h"
#include "../unity/unity.h"


static char json[100];
static char resultat[20];
static char erreur[50];

void reset(void) {
    strcpy(resultat, "");
    strcpy(erreur, "");
    strcpy(json,"{\"key\":\"value\",\"keys\":\"values\",\"cle\":\"valeur\"}");
}

void test_attribut_non_trouve(void) {
    reset();
    TEST_ASSERT_EQUAL_UINT(0, jsonPrimitive(json, "clef", resultat, 20, erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Attribut non trouve\n", erreur);
}

void test_resultat_trop_grand(void) {
    reset();
    TEST_ASSERT_EQUAL_UINT(0, jsonPrimitive(json, "cle", resultat, 4, erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: La taille de la valeur est trop grande\n", erreur);
}

void test_resultat_trouve(void) {
    reset();
    TEST_ASSERT_EQUAL_UINT(1, jsonPrimitive(json, "cle", resultat, 10, erreur));
    TEST_ASSERT_EQUAL_STRING("valeur", resultat);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_attribut_non_trouve);
    RUN_TEST(test_resultat_trop_grand);
    RUN_TEST(test_resultat_trouve);
    UNITY_END();
    return 0;
}