/*
 * Include the following lines in your makefile:
 *
 * cardtest1: cardtest1.c dominion.o rngs.o
 *      gcc -o cardtest1 -g  cardtest1.c dominion.o rngs.o $(CFLAGS)
 */

/*Code style inspired by cardtest4.c provided on Canvas*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define UNITTEST "whoseTurn"


int main() {

	//print out what card we are testing
	printf("Unit Test: %s \n", UNITTEST);

	int i = 0;
	int rSeed = 10; //seed num
	int player = 0; //current player
	int numPlayers = 2; //total players
	int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;

	struct gameState state, preState; //holds game state
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room}; //cards in game

	//initialize the game state and player cards
	initializeGame(numPlayers, k, rSeed, &state);
	memcpy(&preState, &state, sizeof(struct gameState));


	/*Pre-adventurer played*/

	int turn = state.whoseTurn;
	int stateTurn = whoseTurn(&state);



	/*Testing*/

	printf("\nTest 1: Is correct turn\n");

	if (stateTurn == turn){
		printf("PASS: Turn for player expected: %d, got: %d\n", turn, stateTurn);

	}
	else{
		printf("FAIL: Turn for player expected: %d, got: %d\n", turn, stateTurn);

	}

	printf("\nTest 2: Is correct turn compared to prevState\n");

	if (whoseTurn(&state) == whoseTurn(&preState)){
		printf("PASS: Turn for player expected: %d, got: %d\n", whoseTurn(&preState), whoseTurn(&state));

	}
	else{
		printf("FAIL: Turn for player expected: %d, got: %d\n", whoseTurn(&preState), whoseTurn(&state));

	}


	printf("\n");

	return 0;
}
