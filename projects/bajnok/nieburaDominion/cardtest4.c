#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "mine"


int main() {

	//print out what card we are testing
	printf("TESTING  CARD: %s \n", TESTCARD);

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

	/*Pre-mine played*/

	int preHandCount = state.handCount[player];
	int prePlayerTwoCount = state.handCount[1];
	int prePlayedCount = state.playedCardCount;
	int preDiscardCount = state.discardCount[player];
	int preDeckCount = state.deckCount[player];

	/*Mine Played*/
	//cardEffect(mine, choice1, choice2, choice3, &state, handPos, &bonus);

	/*Testing*/

	printf("\nTest 1: Card gained is < 3 coins of trashed card (Trash copper for silver)\n");
	choice1 = copper;
	choice2 = silver;

	//make sure cards are in hand
	state.hand[player][0] = mine;
	state.hand[player][1] = choice1;

	memcpy(&preState, &state, sizeof(struct gameState));

	/*Mine Played*/
	cardEffect(mine, choice1, choice2, choice3, &state, handPos, &bonus);



	printf("\nTest 1.1: Treasure card properly trashed from hand\n");

	if (fullDeckCount(player, copper, &state) ==  ( fullDeckCount(player, copper, &preState) - 1)){
		printf("PASS: expected = %d, actual = %d\n", fullDeckCount(player, copper, &preState) - 1 , fullDeckCount(player, copper, &state));
	}

	else{
		printf("FAIL: expected = %d, actual = %d\n", fullDeckCount(player, copper, &preState) - 1 , fullDeckCount(player, copper, &state));

	}

	printf("\nTest 1.2: Carded gained in hand correctly\n");

	if (fullDeckCount(player, silver, &state) == ( fullDeckCount(player, silver, &preState) + 1)){
		printf("PASS: expected = %d, actual = %d\n", ( fullDeckCount(player, silver, &preState) + 1) , fullDeckCount(player, silver, &state));

	}
	else{
		printf("FAIL: expected = %d, actual = %d\n", ( fullDeckCount(player, silver, &preState) + 1) , fullDeckCount(player, silver, &state));

	} 

	printf("\nTest 2: Card gained is not > 3 coins of trashed card (Trash copper for gold\n");

	//reset hand
	state.handCount[player] = preState.handCount[player];
	for (i = 0; i < preState.handCount[player]; i++){
		state.hand[player][i] = preState.hand[player][i];
	}

	choice1 = copper;
	choice2 = gold;

	//make sure cards are in hand
	state.hand[player][0] = mine;	
	state.hand[player][1] = choice1;

	memcpy(&preState, &state, sizeof(struct gameState));

	/*Mine Played*/
	cardEffect(mine, choice1, choice2, choice3, &state, handPos, &bonus);

	printf("\nTest 2.1: Treasure card not trashed\n");

	if (fullDeckCount(player, copper, &state) ==  ( fullDeckCount(player, copper, &preState))){
		printf("PASS: expected = %d, actual = %d\n", fullDeckCount(player, copper, &preState), fullDeckCount(player, copper, &state));
	}

	else{
		printf("FAIL: expected = %d, actual = %d\n", fullDeckCount(player, copper, &preState) , fullDeckCount(player, copper, &state));

	}

	printf("\nTest 2.2: Carded is not gained in hand\n");

	if (fullDeckCount(player, gold, &state) == ( fullDeckCount(player, gold, &preState))){
		printf("PASS: expected = %d, actual = %d\n", ( fullDeckCount(player, gold, &preState)) , fullDeckCount(player, gold, &state));

	}
	else{
		printf("FAIL: expected = %d, actual = %d\n", ( fullDeckCount(player, gold, &preState)) , fullDeckCount(player, gold, &state));

	} 




	
	printf("\n");

	return 0;
}
