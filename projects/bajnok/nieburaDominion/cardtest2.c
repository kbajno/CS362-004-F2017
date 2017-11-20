/*
 * Include the following lines in your makefile:
 *
 * cardtest2: cardtest2.c dominion.o rngs.o
 *      gcc -o cardtest2 -g  cardtest2.c dominion.o rngs.o $(CFLAGS)
 */

/*Code style inspired by cardtest4.c provided on Canvas*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "smithy"


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
	memcpy(&preState, &state, sizeof(struct gameState));

	/*Pre-smithy played*/

	int preHandCount = state.handCount[player];
	int prePlayerTwoCount = state.handCount[1];
	int prePlayedCount = state.playedCardCount;
	int preDiscardCount = state.discardCount[player];
	int preDeckCount = state.deckCount[player];

	/*Smithy Played*/
	cardEffect(smithy, choice1, choice2, choice3, &state, handPos, &bonus);

	/*Post-smithy played*/




	/*Testing*/

	printf("\nTest 1: Smithy properly played from hand\n");

	if (state.playedCardCount == (prePlayedCount+1)){
		printf("PASS: Played pile increased = %d\n", (state.playedCardCount - prePlayedCount));

	}
	else{
		printf("FAIL: Played pile increased = %d, expected = 1\n", (state.playedCardCount - prePlayedCount));

	}


	printf("\nTest 2: Player's hand has +3 cards\n");

	if ((preHandCount + 2) == state.handCount[player]){
		printf("PASS: expected = %d, actual = %d\n", (preHandCount + 2) , state.handCount[player]);

	}
	else{
		printf("FAIL: expected = %d, actual = %d\n", (preHandCount + 2) , state.handCount[player]);

	} 

	printf("\nTest 3: Player's deck has -3 cards\n");

	if ( (preDeckCount - 3) == state.deckCount[player]){
		printf("PASS: expected = %d, actual = %d\n", (preDeckCount-3) , state.deckCount[player]);

	}
	else{
		printf("FAIL: expected = %d, actual = %d\n", (preDeckCount-3) , state.deckCount[player]);

	} 

	printf("\nTest 4: No change to player 2's hand\n");

	if(prePlayerTwoCount == state.handCount[1] ){
		printf("PASS: expected cards = %d, actual cards = %d\n", prePlayerTwoCount , state.handCount[1]);

	}
	else{
		printf("FAIL: expected cards = %d, actual cards = %d\n", prePlayerTwoCount , state.handCount[1]);

	}

	printf("\nTest 5: No change to kingdom or victory piles\n");

	for (i = curse; i <= treasure_map; i++)
	{
		//printf("Card %d - supply count before: %d, supply count after: %d\n", i, startG.supplyCount[i], G.supplyCount[i]);
		if (state.supplyCount[i] == preState.supplyCount[i]){
			printf("PASS: card %d expected = %d, actual = %d\n", i, preState.supplyCount[i], state.supplyCount[i]);
		}

		else{
			printf("FAIL: card %d expected = %d, actual = %d\n", i, preState.supplyCount[i], state.supplyCount[i]);
		}
	}

	printf("\n");

	return 0;
}
