#include <string.h>
#include "../includes/json.h"
#include "../unity/unity.h"


static char json[100];                      // JSON sans tableau
static char tableau[1000];                  // JSON avec tableau
static char resultat[20];                   // retour sans tableau
static char resultat_tab[8][DIM];           // retour avec tableau
static char erreur[50];                     // message d'erreur


void setup(void) {
    strcpy(resultat, "");
    strcpy(erreur, "");
    strcpy(json,"{\"id\":\"Acura_ILX\",\"name\":\"ILX\",\"niceName\":\"ilx\"}");
    strcpy(tableau,"{\"id\":\"200002038\",\"name\":\"Acura\",\"niceName\":\"acura\",\"models\":[{\"id\":\"Acura_ILX\",\"name\":\"ILX\",\"niceName\":\"ilx\"},{\"id\":\"Acura_ILX_Hybrid\",\"name\":\"ILX Hybrid\",\"niceName\":\"ilx-hybrid\"},{\"id\":\"Acura_MDX\",\"name\":\"MDX\",\"niceName\":\"mdx\"},{\"id\":\"Acura_RDX\",\"name\":\"RDX\",\"niceName\":\"rdx\"},{\"id\":\"Acura_RLX\",\"name\":\"RLX\",\"niceName\":\"rlx\"},{\"id\":\"Acura_TL\",\"name\":\"TL\",\"niceName\":\"tl\"},{\"id\":\"Acura_TSX\",\"name\":\"TSX\",\"niceName\":\"tsx\"},{\"id\":\"Acura_TSX_Sport_Wagon\",\"name\":\"TSX Sport Wagon\",\"niceName\":\"tsx-sport-wagon\"}]}");
}

void test_attribut_non_trouve(void) {
    TEST_ASSERT_EQUAL_UINT(0, jsonPrimitive(json, "cle", resultat, 20, erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Attribut non trouve\n", erreur);
}

void test_resultat_trop_grand(void) {
    TEST_ASSERT_EQUAL_UINT(0, jsonPrimitive(json, "id", resultat, 4, erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: La taille de la valeur est trop grande\n", erreur);
}

void test_resultat_trouve(void) {
    TEST_ASSERT_EQUAL_UINT(1, jsonPrimitive(json, "id", resultat, 10, erreur));
    TEST_ASSERT_EQUAL_STRING("Acura_ILX", resultat);
}

void test_attribut_non_trouve_tableau(void) {
    static unsigned max_element = 8;            
    TEST_ASSERT_EQUAL_UINT(0, jsonArray(tableau, "tableaux", resultat_tab, &max_element, erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Attribut non trouve\n", erreur);
}

void test_resultat_trop_grand_tableau(void) {
    static unsigned max_element_short = 4;
    TEST_ASSERT_EQUAL_UINT(0, jsonArray(tableau, "models", resultat_tab, &max_element_short, erreur));
    TEST_ASSERT_EQUAL_STRING("ERREUR: Nombre d'elements superieur à la valeur demander\n", erreur);
}

void test_resultat_trouve_tableau(void) {
    const char retour[] = "{\"id\":\"Acura_ILX\",\"name\":\"ILX\",\"niceName\":\"ilx\"}";
    static unsigned max_element = 8;
    TEST_ASSERT_EQUAL_UINT(1, jsonArray(tableau, "models", resultat_tab, &max_element, erreur));
    TEST_ASSERT_EQUAL_STRING(retour, resultat_tab[0]);
}

int main(void) {
    UNITY_BEGIN();
    setup();
    RUN_TEST(test_attribut_non_trouve);
    setup();
    RUN_TEST(test_resultat_trop_grand);
    setup();
    RUN_TEST(test_resultat_trouve);
    setup();
    RUN_TEST(test_attribut_non_trouve_tableau);
    setup();
    RUN_TEST(test_resultat_trop_grand_tableau);
    setup();
    RUN_TEST(test_resultat_trouve_tableau);
    UNITY_END();
    return 0;
}