// Other people
// 30/04/14
// Tests Game.c (extensively)
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Game.h"

void test1(void);
void test2(void);
void test3(void);
void test4(void);
void test5(void);
void test6(void);
void test7(void);
void test8(void);
void test9 (void);
void test10(void);
void test11(void);
void test12(void);
void test13(void);
void test14(void);
void test15(void);
void test16(void);

int main(int argc, char const *argv[]) {
    // extensive testing here!
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9 ();
    test10();
    test11();
    test12();
    test13();
    test14();
    test15();
    test16();

    printf("All tests passed, you are Awesome!\n");
    return EXIT_SUCCESS;
}

// test we can build a campus
void test1(void) {
    printf("\n\n\n\n");
    action a;
    int disciplines[] = {2,5 ,3,5 ,3,1,4,4 ,1,4 ,2,3,2,0,3,5,4,2 ,1};
    int dice[] =        {9,10,8,12,6,5,3,11,3,11,4,6,4,9,9,2,8,10,5};
    Game g = newGame(disciplines, dice);
    throwDice(g, 4);
    a.actionCode = BUILD_CAMPUS;
    strncpy(a.destination, "RL", PATH_LIMIT - 1);
    a.destination[PATH_LIMIT - 1] = 0;
    a.disciplineFrom = 2, a.disciplineTo = 1;
    makeAction(g, a);
    assert (getCampus(g, a.destination) == 1);
}

// test isLegalAction() building GO8
void test2(void) {
    printf("\n\n\n\n");
    action a;
    int disciplines[] = {0,1,2,1,4,5,0,3,2,3,4,5,0,1,2,3,4,5,0};
    int dice[] = {12,11,10,9,8,7,6,5,4,3,2,12,11,10,9,8,7,6,5};
    Game g = newGame(disciplines, dice);
    throwDice(g, 5);
    throwDice(g, 5);
    throwDice(g, 12);
    throwDice(g, 12);
    a.actionCode = BUILD_GO8;
    strncpy(a.destination, "", PATH_LIMIT - 1);
    a.destination[PATH_LIMIT - 1] = 0;
    a.disciplineFrom = 3, a.disciplineTo = 2;
    isLegalAction(g, a);
    assert(isLegalAction (g, a) == 1);
}

void test3(void) {
    printf("\n\n\n\n");
    action a;
    int disciplines[] = {2,5,3,5,3,1,4,4,1,4,2,3,2,0,3,5,4,2,1};
    int dice[] = {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5};
    Game g = newGame(disciplines, dice);
    throwDice(g, 5);
    a.actionCode = BUILD_CAMPUS;
    strncpy(a.destination, "RL", PATH_LIMIT - 1);
    a.destination[PATH_LIMIT - 1] = 0;
    a.disciplineFrom = -1077724424, a.disciplineTo = 134527641;
    makeAction(g, a);
    assert(getCampus(g, "RL") == 1);
}

// test getExchangeRate
void test6(void) {
    printf("\n\n\n\n");
    action a;
    int disciplines[] = {2,5,3,5,3,1,4,4,1,4,2,3,2,0,3,5,4,2,1};
    int dice[] = {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5};
    Game g = newGame(disciplines, dice);
    throwDice(g, 5);
    a.actionCode = BUILD_CAMPUS;
    strncpy(a.destination, "R", PATH_LIMIT - 1);
    a.destination[PATH_LIMIT - 1] = 0;
    a.disciplineFrom = 1, a.disciplineTo = -1217678112;
    makeAction(g, a);
    assert(getExchangeRate (g, 1, 4, 1) == 2);
}

// test building ARC
void test4(void) {
    printf("\n\n\n\n");
    action a;
    int disciplines[] = {2,5,3,5,3,1,4,4,1,4,2,3,2,0,3,5,4,2,1};
    int dice[] = {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5};
    Game g = newGame(disciplines, dice);
    throwDice(g, 5);
    a.actionCode = OBTAIN_ARC;
    strncpy(a.destination, "L", PATH_LIMIT - 1);
    a.destination[PATH_LIMIT - 1] = 0;
    a.disciplineFrom = 134528624, a.disciplineTo = -1081831912;
    assert(isLegalAction(g, a) == 1);
    makeAction(g, a);
    a.actionCode = OBTAIN_ARC;
    strncpy(a.destination, "LR", PATH_LIMIT - 1);
    a.destination[PATH_LIMIT - 1] = 0;
    a.disciplineFrom = 134528624, a.disciplineTo = -1081831912;
    assert(isLegalAction(g, a) == 1);

}

// test getMostArcs
void test5(void) {
    printf("\n\n\n\n");
    action a;
    int disciplines[] = {4,2,5,4,2,2,3,5,1,3,5,4,4,4,3,5,4,0,5};
    int dice[] = {8,10,8,9,6,4,4,5,12,3,11,6,3,11,2,7,5,6,5};
    Game g = newGame(disciplines, dice);
    throwDice(g, 7);
    a.actionCode = OBTAIN_ARC;
    strncpy(a.destination, "L", PATH_LIMIT - 1);
    a.destination[PATH_LIMIT - 1] = 0;
    a.disciplineFrom = 0, a.disciplineTo = 0;
    makeAction(g, a);
    assert(getMostARCs(g) == 1);
}

// test regions are loaded properly
void test7(void) {
    printf("\n\n\n\n");
    int disciplines[] = {2,5,3,5,3,1,4,4,1,4,2,3,2,0,3,5,4,2,1};
    int dice[] = {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5};
    Game g = newGame(disciplines, dice);
    int region = 0;
    while (region < NUM_REGIONS) {
        assert(getDiceValue(g, region) >= 2 && getDiceValue(g, region) <=12);
        region++;
    }
}

void test8(void) {
    return;
}

// test starting spinoffs
void test9 (void) {
    action a;
    int disciplines[] = {2,5,3,5,3,1,4,4,1,4,2,3,2,0,3,5,4,2,1};
    int dice[] = {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5};
    Game g = newGame(disciplines, dice);
    throwDice(g, 8);
    a.actionCode = OBTAIN_ARC;
    strncpy(a.destination, "R", PATH_LIMIT - 1);
    a.destination[PATH_LIMIT - 1] = 0;
    a.disciplineFrom = -1217350860, a.disciplineTo = 7;
    makeAction(g, a);
    a.actionCode = OBTAIN_ARC;
    strncpy(a.destination, "RR", PATH_LIMIT - 1);
    a.destination[PATH_LIMIT - 1] = 0;
    a.disciplineFrom = -1217350860, a.disciplineTo = 7;
    makeAction(g, a);
    a.actionCode = PASS;
    strncpy(a.destination, "", PATH_LIMIT - 1);
    a.destination[PATH_LIMIT - 1] = 0;
    a.disciplineFrom = -1078711464, a.disciplineTo = 134586891;
    makeAction(g, a);
    throwDice(g, 5);
    a.actionCode = OBTAIN_ARC;
    strncpy(a.destination, "RRLRLL", PATH_LIMIT - 1);
    a.destination[PATH_LIMIT - 1] = 0;
    a.disciplineFrom = -1217350860, a.disciplineTo = 7;
    makeAction(g, a);
    a.actionCode = PASS;
    strncpy(a.destination, "", PATH_LIMIT - 1);
    a.destination[PATH_LIMIT - 1] = 0;
    a.disciplineFrom = -1078711464, a.disciplineTo = 134586891;
    makeAction(g, a);
    throwDice(g, 6);
    a.actionCode = OBTAIN_PUBLICATION;
    strncpy(a.destination, "", PATH_LIMIT - 1);
    a.destination[PATH_LIMIT - 1] = 0;
    a.disciplineFrom = 1, a.disciplineTo = 2329;
    printf("%d\n", getStudents(g, 3, 3));
    makeAction(g, a);
    assert(getStudents(g, 3, 3) == 1);
}

// some more isLegalAction testing
void test10 (void) {
    action a;
    int disciplines[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int dice[] = {6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6,6};
    Game g = newGame(disciplines, dice);
    throwDice(g, 6);
    throwDice(g, 6);
    throwDice(g, 6);
    throwDice(g, 6);
    a.actionCode = OBTAIN_ARC;
    strncpy(a.destination, "R", PATH_LIMIT - 1);
    a.destination[PATH_LIMIT - 1] = 0;
    a.disciplineFrom = 4, a.disciplineTo = 3;
    makeAction(g, a);
    a.actionCode = OBTAIN_ARC;
    strncpy(a.destination, "RR", PATH_LIMIT - 1);
    a.destination[PATH_LIMIT - 1] = 0;
    a.disciplineFrom = 4, a.disciplineTo = 3;
    makeAction(g, a);
    a.actionCode = BUILD_CAMPUS;
    strncpy(a.destination, "RR", PATH_LIMIT - 1);
    a.destination[PATH_LIMIT - 1] = 0;
    a.disciplineFrom = 4, a.disciplineTo = 3;
    assert(isLegalAction(g, a) == 1);
}

void test11 (void) {
    printf("\n\n\n\n");
    return;
}

void test12 (void) {
    printf("\n\n\n\n");
    return;
}

void test13 (void) {
    printf("\n\n\n\n");
    return;
}

void test14 (void) {
    printf("\n\n\n\n");
    return;
}

void test15 (void) {
    printf("\n\n\n\n");
    return;
}

void test16 (void) {
    printf("\n\n\n\n");
    return;
}
