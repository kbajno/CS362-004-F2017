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

#define UNITTEST "updateCoins"


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

	state.hand[player][0] == copper;
	state.hand[player][1] == silver;
	state.hand[player][2] == gold;

	int result = updateCoins(player, &state, 5);

	int coinTotal = state.coins;



	/*Testing*/

	printf("\nTest 1: Coins properly counted\n");

	if (coinTotal == 14){
		printf("PASS: Coins expected: %d, got: %d\n", 14, coinTotal);

	}
	else{
		printf("FAIL: Coins expected: %d, got: %d\n", 14, coinTotal);

	}


	printf("\n");

	return 0;
}
