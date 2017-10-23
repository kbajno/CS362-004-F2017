
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTUNIT "buyCard"


int main() {

	//print out what card we are testing
	printf("TESTING  UNIT: %s \n", TESTUNIT);

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

	//test no more buys
	state.numBuys = 0;
	int cardBuyNoMore = buyCard(adventurer, &state);

	//reset the game
	memcpy(&state, &preState, sizeof(struct gameState));

	//test no card type
	state.supplyCount[adventurer] = 0;
	int cardBuyNoAvail = buyCard(adventurer, &state);

	//reset the game
	memcpy(&state, &preState, sizeof(struct gameState));

	//test no enough money
	state.coins = 0;
	int cardBuyNoCoins = buyCard(adventurer, &state);

	//reset the game
	memcpy(&state, &preState, sizeof(struct gameState));

	//test card buy success
	int cardBuySuccess = buyCard(adventurer, &state);

	/*Testing*/

	printf("\nTest 1: Adventurer buy success\n");

	if (cardBuySuccess == 0){
		printf("PASS: Player hand pile increased = %d, expected = 1\n", (state.handCount[player] - preState.handCount[player]));
	}

	else{
		printf("FAIL: Player hand pile increased = %d, expected = 1\n", (state.handCount[player] - preState.handCount[player]));

	}

	printf("\nTest 2: Buy fails because no buys are left\n");

	if (cardBuyNoMore == -1){
		printf("PASS: Hand count expected = %d, actual = %d\n", preState.handCount[player] , state.handCount[player] );
	}

	else{
		printf("FAIL: Hand count expected = %d, actual = %d\n", preState.handCount[player] , state.handCount[player] );

	}

	printf("\nTest 3: Buy fails because no card available\n");
	
	if (cardBuyNoAvail == -1){
		printf("PASS: Hand count expected = %d, actual = %d\n", preState.handCount[player] , state.handCount[player] );
	}

	else{
		printf("FAIL: Hand count expected = %d, actual = %d\n", preState.handCount[player] , state.handCount[player] );
	}

	printf("\nTest 4: Buy fails because no money\n");

	if (cardBuyNoCoins == -1){
		printf("PASS: Hand count expected = %d, actual = %d\n", preState.handCount[player] , state.handCount[player] );
	}

	else{
		printf("FAIL: Hand count expected = %d, actual = %d\n", preState.handCount[player] , state.handCount[player] );
	}


	printf("\nTest 5: Card is added to hand\n");

	if (preState.handCount[player] + 1 == state.handCount[player]){
		printf("PASS: Hand count expected = %d, actual = %d\n", preState.handCount[player] + 1 , state.handCount[player] );
	}

	else{
		printf("FAIL: Hand count expected = %d, actual = %d\n", preState.handCount[player] + 1 , state.handCount[player] );
	}	

	printf("\nTest 6: Check for proper coins\n");

	if (state.coins == preState.coins + getCost(adventurer)){
		printf("PASS: Coins expected = %d, actual = %d\n", preState.coins + getCost(adventurer) , state.coins);
	}

	else{
		printf("FAIL: Coins expected = %d, actual = %d\n", preState.coins + getCost(adventurer), state.coins);
	}

	printf("\n");

	return 0;
}