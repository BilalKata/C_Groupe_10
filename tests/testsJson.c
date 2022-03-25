#include <string.h>
#include "../includes/json.h"
#include "../unity/unity.h"


static char json[100];                      // JSON sans tableau
static char tableau[100];                   // JSON avec tableau
static char resultat[20];                   // retour sans tableau
static char resultat_tab[5][20];            // retour avec tableau
static char erreur[50];                     // message d'erreur


void reset(void) {
    strcpy(resultat, "");
    strcpy(erreur, "");
    strcpy(json,"{\"key\":\"value\",\"keys\":\"values\",\"cle\":\"valeur\"}");
    strcpy(tableau,"{\"tableau\":[\"value1\",\"value2\",\"value3\",\"value4\",\"value5\"],\"keys\":\"values\",\"cle\":\"valeur\"}");
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

void test_attribut_non_trouve_tableau(void) {
    static unsigned max_element = 5;            
    reset();
    TEST_ASSERT_EQUAL_UINT(0, jsonArray(tableau, "tableaux", resultat_tab, &max_element, erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Attribut non trouve\n", erreur);
}

void test_resultat_trop_grand_tableau(void) {
    static unsigned max_element_short = 4;
    reset();
    TEST_ASSERT_EQUAL_UINT(0, jsonArray(tableau, "tableau", resultat_tab, &max_element_short, erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Nombre d'elements superieur à la valeur demander\n", erreur);
}

void test_resultat_trouve_tableau(void) {
    const char *retour[] = {"value1", "value2", "value3", "value4", "value5"};
    static unsigned max_element = 5;
    reset();
    TEST_ASSERT_EQUAL_UINT(1, jsonArray(tableau, "tableau", resultat_tab, &max_element, erreur));
    TEST_ASSERT_EQUAL_STRING_ARRAY(retour, tableau, 5);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_attribut_non_trouve);
    RUN_TEST(test_resultat_trop_grand);
    RUN_TEST(test_resultat_trouve);
    RUN_TEST(test_attribut_non_trouve_tableau);
    RUN_TEST(test_resultat_trop_grand_tableau);
    RUN_TEST(test_resultat_trouve_tableau);
    UNITY_END();
    return 0;
}