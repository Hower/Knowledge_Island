// Other people
// 30/04/14
// Tests Game.c (extensively)
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "Game.h"

int main(int argc, char const *argv[]) {
    // extensive testing here!

    int disciplines[] = {-1218344971,-1216720112,134526603,-1217126412,0,0,-1078839512,-1218445754,1,-1078839468,-1078839460,-1216802104,-1216694879,24641422,-1216663564,134513566,1,-1078839536,-1216722538};
    int dice[] = {2,5,3,5,3,1,4,4,1,4,2,3,2,0,3,5,4,2,1};
    Game g = newGame(disciplines, dice);
    throwDice(g, 7);
    printf("%d\n", (getStudents(g, 1, 0) == 2));
    assert(getStudents(g, 1, 0) == 2);
    printf("All tests passed, you are Awesome!\n");
    return EXIT_SUCCESS;
}
