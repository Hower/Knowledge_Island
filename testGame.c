// Adley, Kevin, Mark, Keerti, Andrew
// 30/04/14
// Tests Game.c (extensively)
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Game.h"

int main(int argc, char const *argv[]) {
    // extensive testing here!

    action action1;
    action1.actionCode = PASS;
    // action1.destination[0] = 'L';
    // action1.destination[1] = '\0';

    int disciplines[NUM_REGIONS] = {STUDENT_THD, STUDENT_BPS, STUDENT_BQN, STUDENT_MJ, STUDENT_MTV, STUDENT_MMONEY, STUDENT_MTV, STUDENT_MTV, STUDENT_MTV, STUDENT_MTV, STUDENT_MTV, STUDENT_MTV, STUDENT_MTV, STUDENT_MTV, STUDENT_MTV, STUDENT_MTV, STUDENT_MTV, STUDENT_MTV,
        STUDENT_MTV};

    int dice[NUM_REGIONS] = {6, 10, 8, 12, 6, 5, 3, 11, 3, 11, 4, 6, 4, 7, 9, 2, 8, 10, 5};
    Game g = newGame(disciplines, dice);
    assert(getWhoseTurn(g) == NO_ONE);
    assert(getTurnNumber(g) == -1);

    // test all dice values
    int x = 2;
    while (x < 13) {
        makeAction(g, action1);
        throwDice(g, x);
        assert(getWhoseTurn(g) == getTurnNumber(g) % 3 + 1);
        x++;
    }
    assert(getTurnNumber(g) == 10);
    x = 0;
    // test the regions contain the right disc values
    while (x < NUM_REGIONS) {
        assert(getDiceValue(g, x) == dice[x]);
        x++;
    }
    // test the regions contain the right discipline values
    x = 0;
    while (x < NUM_REGIONS) {
        assert(getDiscipline(g, x) == disciplines[x]);
        x++;
    }
    disposeGame(g);

    printf("All tests passed, you are Awesome!\n");
    return EXIT_SUCCESS;
}
