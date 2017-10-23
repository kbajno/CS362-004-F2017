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

#define UNITTEST "supplyCount"


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

	state.supplyCount[adventurer] = 5;
	int count = supplyCount(adventurer, &state);


	/*Testing*/

	printf("\nTest 1: Proper supply count\n");

	if (count == 5){
		printf("PASS: Supply expected: %d, got: %d\n", 5, count);

	}
	else{
		printf("FAIL: Supply expected: %d, got: %d\n", 5, count);

	}

	printf("\nTest 1: Embargo supply wasn't adjusted\n");

	if (state.supplyCount[embargo] == preState.supplyCount[embargo]){
		printf("PASS: Supply expected: %d, got: %d\n", preState.supplyCount[embargo], state.supplyCount[embargo]);

	}
	else{
		printf("FAIL: Supply expected: %d, got: %d\n", preState.supplyCount[embargo], state.supplyCount[embargo]);

	}

	printf("\nTest 1: village supply wasn't adjusted\n");

	if (state.supplyCount[village] == preState.supplyCount[village]){
		printf("PASS: Supply expected: %d, got: %d\n", preState.supplyCount[village], state.supplyCount[village]);

	}
	else{
		printf("FAIL: Supply expected: %d, got: %d\n", preState.supplyCount[village], state.supplyCount[village]);

	}

	printf("\nTest 1: minion supply wasn't adjusted\n");

	if (state.supplyCount[minion] == preState.supplyCount[minion]){
		printf("PASS: Supply expected: %d, got: %d\n", preState.supplyCount[minion], state.supplyCount[minion]);

	}
	else{
		printf("FAIL: Supply expected: %d, got: %d\n", preState.supplyCount[minion], state.supplyCount[minion]);

	}

	printf("\nTest 1: cutpurse supply wasn't adjusted\n");

	if (state.supplyCount[cutpurse] == preState.supplyCount[cutpurse]){
		printf("PASS: Supply expected: %d, got: %d\n", preState.supplyCount[cutpurse], state.supplyCount[cutpurse]);

	}
	else{
		printf("FAIL: Supply expected: %d, got: %d\n", preState.supplyCount[cutpurse], state.supplyCount[cutpurse]);

	}


	printf("\n");

	return 0;
}
