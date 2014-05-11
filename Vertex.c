/* Kevin NI
   10/05/14
   contains an abstract data type vertex for use with Game.c
*/

#include <stdio.h>
#include <stdlib.h>
#include "Vertex.h"

#define FILE_NAME "vertices.txt"

struct _vertex{
    int ID;
    int contents;
};


Vertex*** makeVertexMap(void){

    FILE *fin = fopen(FILE_NAME, "r");
    Vertex ***first = malloc(sizeof(Vertex**) * MAX_COORDINATE);

    // Creates blank map
    int countA = 0;
    while (countA < MAX_COORDINATE){

        Vertex **second = malloc(sizeof(Vertex*) * MAX_COORDINATE);

        int countB = 0;
        while (countB < MAX_COORDINATE){

            Vertex *third = malloc(sizeof(Vertex) * MAX_COORDINATE);

            int countC = 0;
            while (countC < MAX_COORDINATE){

                Vertex vertex = malloc(sizeof(struct _vertex));
                vertex->ID = -1;
                vertex->contents = 0;
                third[countC] = vertex;
                countC++;
            }
            second[countB] = third;
            countB++;
        }
        first[countA] = second;
        countA++;
    }

    int x, y, z;
    int count = 0;
    while (count < NUM_VERTICES){
        // loads valid vertices

        fscanf(fin, "%d %d %d", &x, &y, &z);
        first[x][y][z]->ID = count;
        count++;
    }
    return first;
}

int getID(Vertex vertex){
    return vertex->ID;
}

int getContents(Vertex vertex){
    return vertex->contents;
}

int changeContents(Vertex vertex, int newElement){
    return vertex->contents = newElement;
}

void freeMap(Vertex*** map){

    int countA = 0;

    while (countA < MAX_COORDINATE){

        int countB = 0;
        while (countB < MAX_COORDINATE){


            int countC = 0;
            while (countC < MAX_COORDINATE){
                free(map[countA][countB][countC]);
                countC++;
            }
            free(map[countA][countB]);
            countB++;
        }
        free(map[countA]);
        countA++;
    }
    free(map);
    return;
}

int sizeOfVertex(void){
    return sizeof(struct _vertex);
}

