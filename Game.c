// Adley, Kevin, Mark, Keerti, Andrew
// 30/04/14
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "Game.h"
#include "Vertex.h"

#define DEFAULT_DISCIPLINES {STUDENT_BQN, STUDENT_MMONEY, STUDENT_MJ, STUDENT_MMONEY, STUDENT_MJ, STUDENT_BPS, STUDENT_MTV, STUDENT_MTV, STUDENT_BPS,STUDENT_MTV, STUDENT_BQN, STUDENT_MJ, STUDENT_BQN, STUDENT_THD, STUDENT_MJ, STUDENT_MMONEY, STUDENT_MTV, STUDENT_BQN, STUDENT_BPS}

#define DEFAULT_DICE {9,10,8,12,6,5,3,11,3,11,4,6,4,7,9,2,8,10,5}

#define DOWN_RIGHT   0
#define ACROSS_RIGHT 1
#define UP_RIGHT     2
#define UP_LEFT      3
#define ACROSS_LEFT  4
#define DOWN_LEFT    5

#define X 1
#define Y 2
#define Z 3

#define FILE_NAME "regions.txt"
#define NUM_VERTICES_IN_A_REGION 6

typedef struct _coordinate {
    int x, y, z;
} coordinate;

typedef struct _university {
    int students[6];
    int KPIpoints;
    int ARCs;
    int GO8s;
    int campuses;
    int IPs;
    int publications;
} university;

typedef struct _region {
    int ID;
    coordinate vertices[NUM_VERTICES_IN_A_REGION];
} region;

struct _game {
    // the map
    int disciplines[NUM_REGIONS], dice[NUM_REGIONS];
    int currentTurn;
    int **edges;
    Vertex ***map;
    // number of students that each player owns
    university universities[NUM_UNIS];
    region regions[NUM_REGIONS];
};

int directionToIndex(char direction);
coordinate coordinateFromPath(Game g, path requestPath);
int** makeEdgeMap(Vertex ***vertices);
int IDFromCoordinate(Game g, coordinate coord);
Vertex vertexFromCoordinate(Game g, coordinate coord);
int greatestOfThree (int a, int b, int c);
int checkEdge(int player, int **edges, int verOne, int verTwo);

// int main(int argc, char const *argv[]) {
//     int disciplines[] = DEFAULT_DISCIPLINES;
//     int dice[] = DEFAULT_DICE;
//     Game g = newGame (disciplines, dice);
//     coordinate coord = coordinateFromPath(g, "LRRLRR");
//     printf("(%d, %d, %d)\n", coord.x, coord.y, coord.z);
//     return EXIT_SUCCESS;
// }

Game newGame (int discipline[], int dice[]) {
    Game g = malloc(sizeof(struct _game));
    // populate the map
    int x = 0, i = 0;
    while (x < NUM_REGIONS) {
        g->disciplines[x] = discipline[x];
        g->dice[x] = dice[x];
        x++;
    }
    g->currentTurn = -1;
    university startScores;
    startScores.students[STUDENT_THD] = 0;
    startScores.students[STUDENT_BPS] = 3;
    startScores.students[STUDENT_BQN] = 3;
    startScores.students[STUDENT_MJ]  = 1;
    startScores.students[STUDENT_MTV] = 1;
    startScores.students[STUDENT_MMONEY] = 1;
    startScores.KPIpoints = 0;
    startScores.ARCs = 0;
    startScores.GO8s = 0;
    startScores.campuses = 0;
    startScores.IPs = 0;
    startScores.publications = 0;
    x = 0;
    while (x < NUM_UNIS) {
        g->universities[x] = startScores;
        x++;
    }
    g->map = makeVertexMap();
    x = 0;
    i = 0;
    // load in the regions and their associated vertices
    FILE *fin = fopen(FILE_NAME, "r");
    while (x < NUM_REGIONS) {
        g->regions[x].ID = x;
        while (i < NUM_VERTICES_IN_A_REGION) {
            fscanf(fin, "%d %d %d",
                &(g->regions[x].vertices[i].x),
                &(g->regions[x].vertices[i].y),
                &(g->regions[x].vertices[i].z));
            i++;
        }
        i = 0;
        x++;
    }
    g->edges = makeEdgeMap(g->map);
    return g;
}

void disposeGame (Game g) {
    free(g);
}

void makeAction (Game g, action a) {
    // arrays are indexed from 0
    int currentPlayer = getWhoseTurn(g) - 1;
    if (a.actionCode == PASS) {
        return;
    }
    if (a.actionCode == BUILD_CAMPUS) {
        coordinate coord = coordinateFromPath(g, a.destination);
        changeContents(vertexFromCoordinate(g, coord), currentPlayer);

        g->universities[currentPlayer].students[STUDENT_BPS] -= 1;
        g->universities[currentPlayer].students[STUDENT_BQN] -= 1;
        g->universities[currentPlayer].students[STUDENT_MJ] -= 1;
        g->universities[currentPlayer].students[STUDENT_MTV] -= 1;

        g->universities[currentPlayer].KPIpoints += 10;
        g->universities[currentPlayer].campuses += 1;
    }
    if (a.actionCode == BUILD_GO8) {
        coordinate coord = coordinateFromPath(g, a.destination);
        changeContents(vertexFromCoordinate(g, coord), currentPlayer + 3);

        g->universities[currentPlayer].students[STUDENT_MJ] -= 2;
        g->universities[currentPlayer].students[STUDENT_MMONEY] -= 3;

        g->universities[currentPlayer].KPIpoints += 10;
        g->universities[currentPlayer].campuses -= 1;
        g->universities[currentPlayer].GO8s += 1;
    }
    if (a.actionCode == OBTAIN_ARC) {
        int pathLen = strlen(a.destination);
        coordinate firstVertex = coordinateFromPath(g, a.destination);
        path destinationMinusOne;

        strncpy(destinationMinusOne, a.destination, pathLen - 1);
        destinationMinusOne[pathLen - 1] = '\0';

        coordinate secondVertex = coordinateFromPath(g, destinationMinusOne);
        int firstVertexID = IDFromCoordinate(g, firstVertex);
        int secondVertexID = IDFromCoordinate(g, secondVertex);

        g->universities[currentPlayer].students[STUDENT_BPS] -= 1;
        g->universities[currentPlayer].students[STUDENT_BQN] -= 1;

        g->edges[firstVertexID][secondVertexID] = currentPlayer;
        g->universities[currentPlayer].ARCs += 1;
        g->universities[currentPlayer].KPIpoints += 2;
    }
    if (a.actionCode == OBTAIN_PUBLICATION) {
        g->universities[currentPlayer].publications++;
    }
    if (a.actionCode == OBTAIN_IP_PATENT) {
        g->universities[currentPlayer].IPs++;
    }
    if (a.actionCode == RETRAIN_STUDENTS) {
        int from = a.disciplineFrom;
        int to = a.disciplineTo;
        // if player owns a retraining center set the ratio to 2:1
        // code that later...
        // int ratio = getExchangeRate(g, currentPlayer, from, to);
        int ratio = 3;
        int retrained = g->universities[currentPlayer].students[from] / ratio;
        g->universities[currentPlayer].students[from] -= retrained;
        g->universities[currentPlayer].students[to] += retrained;

    }
}

void throwDice (Game g, int diceScore) {
    g->currentTurn += 1;
    int regionID = 0;
    int x;
    int player;
    coordinate vertexCoord;
    Vertex vertex;
    int vertexContents;
    while (regionID < NUM_REGIONS) {
        if (getDiceValue(g, regionID) == diceScore) {
            x = 0;
            // check all the surrounding vertices to see if
            // they belong to anyone and if they do, give the owner
            // the stuff
            while (x < NUM_VERTICES_IN_A_REGION) {
                vertexCoord = g->regions[regionID].vertices[x];
                vertex = vertexFromCoordinate(g, vertexCoord);
                vertexContents = getContents(vertex);
                // if the vertex contains a campus
                if (vertexContents >= CAMPUS_A &&
                         vertexContents <= CAMPUS_C) {
                    // arrays are indexed from 0
                    player = vertexContents - 1;
                    g->universities[player].students[getDiscipline(g, regionID)] += 1;
                }
                else if (vertexContents >= GO8_A) {
                    player = (vertexContents % 4 + 1) - 1;
                    g->universities[player].students[getDiscipline(g, regionID)] += 2;
                }
                x++;
            }
        }
        regionID++;
    }
}

int getDiscipline (Game g, int regionID) {
    return g->disciplines[regionID];
}
int getDiceValue (Game g, int regionID) {
    return g->dice[regionID];
}

int getMostARCs (Game g) {
    int a = g->universities[UNI_A].ARCs;
    int b = g->universities[UNI_B].ARCs;
    int c = g->universities[UNI_C].ARCs;
    return greatestOfThree(a, b, c);
}

int getMostPublications (Game g) {
    int a = g->universities[UNI_A].publications;
    int b = g->universities[UNI_B].publications;
    int c = g->universities[UNI_C].publications;
    return greatestOfThree(a, b, c);
}

int greatestOfThree (int a, int b, int c) {
    int leading = NO_ONE;
    if (a == 0 && b == 0 && c == 0) {
        leading = NO_ONE;
    }

    if (a > b) {
        if (a > c) {
            leading = UNI_A;
        }
        else {
            leading = UNI_C;
        }
    }
    else if (b > c) {
        leading = UNI_B;
    }
    else {
        leading = UNI_C;
    }
    return leading;
}

int getTurnNumber (Game g) {
    return g->currentTurn;
}

int getWhoseTurn (Game g) {
    int whoseTurn;
    if (g->currentTurn == - 1) {
        whoseTurn = NO_ONE;
    }
    else {
        whoseTurn = (g->currentTurn % 3) + 1;
    }
    return whoseTurn;
}

int getCampus (Game g, path pathToVertex) {
    coordinate coord = coordinateFromPath(g, pathToVertex);
    Vertex vertex = vertexFromCoordinate(g, coord);
    return getContents(vertex);
}

int getKPIpoints (Game g, int player) {
    return g->universities[player].KPIpoints;
}

int getARCs (Game g, int player) {
    return g->universities[player].ARCs;
}

int getGO8s (Game g, int player) {
    return g->universities[player].GO8s;
}

int getCampuses (Game g, int player) {
    return g->universities[player].campuses;
}

int getIPs (Game g, int player) {
    return g->universities[player].IPs;
}

int getPublications (Game g, int player) {
    return g->universities[player].publications;
}

int getStudents (Game g, int player, int discipline) {
    return g->universities[player].students[discipline];
}

int directionToIndex(char direction) {
    int returnValue = 0;
    if (direction == 'L') {
        returnValue = 0;
    }
    else if (direction == 'R') {
        returnValue = 1;
    }
    else if (direction == 'B') {
        returnValue = 2;
    }
    return returnValue;
}

coordinate coordinateFromPath(Game g, path requestPath) {
    int curOrientation = DOWN_RIGHT;
    char curDirection;
    coordinate coord;
    coord.x = 2;
    coord.y = 0;
    coord.z = 0;
    int count = 0;
    int pathLen = strlen(requestPath);
    int orientationTable[6][3][2] = {
        {
            {X, ACROSS_RIGHT},
            {Z, DOWN_LEFT},
            {-Y, UP_LEFT}
        },
        {
            {-Z, UP_RIGHT},
            {Y, DOWN_RIGHT},
            {-X, ACROSS_LEFT}
        },
        {
            {-Y, UP_LEFT},
            {X, ACROSS_RIGHT},
            {Z, DOWN_LEFT}
        },
        {
            {-X, ACROSS_LEFT},
            {-Z, UP_RIGHT},
            {Y, DOWN_RIGHT}
        },
        {
            {Z, DOWN_LEFT},
            {-Y, UP_RIGHT},
            {X, ACROSS_RIGHT}
        },
        {
            {Y, DOWN_RIGHT},
            {-X, ACROSS_LEFT},
            {-Z, UP_RIGHT}
        }
    };
    int updateCoord, index;
    int x, y, z;
    int update;
    Vertex curVertex;
    while (count < pathLen) {
        curDirection = requestPath[count];
        index = directionToIndex(curDirection);
        updateCoord = orientationTable[curOrientation][index][0];

        if (updateCoord > 0) {
            update = 1;
        }
        else {
            update = -1;
        }

        if (abs(updateCoord) == X) {
            coord.x += update;
        }
        else if (abs(updateCoord) == Y) {
            coord.y += update;
        }
        else {
            coord.z += update;
        }
        // check that the coordinate we are on exists
        x = coord.x;
        y = coord.y;
        z = coord.z;
        printf("%d %d %d\n", x, y, z);
        curVertex = g->map[x][y][z];
        assert(getID(curVertex) != -1);
        assert(x < MAX_COORDINATE);
        assert(y < MAX_COORDINATE);
        assert(z < MAX_COORDINATE);
        assert(x >= 0);
        assert(y >= 0);
        assert(z >= 0);
        curOrientation = orientationTable[curOrientation][index][1];
        count++;
    }
    return coord;
}

int IDFromCoordinate(Game g, coordinate coord) {
    return getID(vertexFromCoordinate(g, coord));
}

Vertex vertexFromCoordinate(Game g, coordinate coord) {
    return g->map[coord.x][coord.y][coord.z];
}

// int getExchangeRate (Game g, int player, int disciplineFrom, int disciplineTo) {

// }
int** makeEdgeMap(Vertex ***vertices){
    int **first = malloc(sizeof(int*) * NUM_VERTICES);

    int d = 0;
    while (d < NUM_VERTICES){

        int *second = malloc(sizeof(int) * NUM_VERTICES);
        int e = 0;
        while (e < NUM_VERTICES){

            second[e] = -1;
            e++;
        }
        first[d] = second;
        d++;
    }

    int a = 0;
    while (a < MAX_COORDINATE){

        int b = 0;
        while (b < MAX_COORDINATE){

            int c = 0;
            while (c < MAX_COORDINATE){
                //do stuff
                int tempA = getID(vertices[a][b][c]);
                if (tempA != -1){

                    if (a != 0){

                        int tempB = getID(vertices[a - 1][b][c]);
                        if (tempB != -1){

                            first[tempA][tempB] = 0;
                        }
                    }
                    if (a != 5){

                        int tempB = getID(vertices[a + 1][b][c]);
                        if (tempB != -1){

                            first[tempA][tempB] = 0;
                        }
                    }
                    if (b != 0){

                        int tempB = getID(vertices[a][b - 1][c]);
                        if (tempB != -1){

                            first[tempA][tempB] = 0;
                        }
                    }
                    if (b != 5){

                        int tempB = getID(vertices[a][b + 1][c]);
                        if (tempB != -1){

                            first[tempA][tempB] = 0;
                        }
                    }
                    if (c != 0){

                        int tempB = getID(vertices[a][b][c - 1]);
                        if (tempB != -1){

                            first[tempA][tempB] = 0;
                        }
                    }
                    if (c != 5){

                        int tempB = getID(vertices[a][b][c + 1]);
                        if (tempB != -1){

                            first[tempA][tempB] = 0;
                        }
                    }
                }
                c++;
            }
            b++;
        }
        a++;
    }

    return first;
}

int checkEdge(int player, int **edges, int verOne, int verTwo){
    int valid = 0;

    //loops over the array that has one vertex in common with the one
    //in question
    int count = 0;
    while(count < MAX_COORDINATE){
        if(edges[verOne][count] == player){
            valid = 1;
        }
        if(edges[verTwo][count] == player){
            valid = 1;
        }
        count++;
    }
    return valid;
}
