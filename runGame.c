#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "Game.h"

#define WIN_KPI 150
#define MIN_DICE_VALUE 2
#define MAX_DICE_VALUE 12

int rollDice(void);

int main (int argc, char *argv[]) {
	Game g  = newGame(int disciplines, int dice);
	int move = -1;
	int currentPlayer = 0;
	int diceValue = MIN_DICE_VALUE;
	
	while (getKPI (g, currentPlayer) < WIN_KPI) {
		// rolls the dice
		diceValue = rollDice();
		// advance a turn and give resources to players
		int x = g->universities[currentPlayer].students[student _THD];
		printf("%d\n", g->universities[currentPlayer].students[]);
		throwDice();
		
		
		//move = bestMove(g);
		printf("What is your action code?\n");
		printf("0 for PASS, 1 for BUILD_CAMPUS, 2 for BUILD_GO8, 3 for OBTAIN_ARC\n");
		printf("4 for START_SPINOFF and 7 for RETRAIN_STUDENTS\n");
		scanf("%d", &move);
		assert(move >= 0 && move <= 4) || (move = 7);
		
	while (move != PASS) {
		assert(isLegal(g, move));
		
			if (move.actionCode == START_SPINOFF) {
				diceValue = rollDice();
				Decide			
			}
		makeAction(g, move);
		}
	currentPlayer = nextPlayer(currentPlayer);
	}
	
	return EXIT_SUCCESS;
}

// function: rolls the dice
int rollDice(void) {
	int dice1, dice2;
	dice1 = rand(void) % 6 + 1;
	dice2 = rand(void) % 6 + 1;
	return (dice1 + dice2);
}
