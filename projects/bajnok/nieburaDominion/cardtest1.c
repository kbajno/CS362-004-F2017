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

#define TESTCARD "adventurer"


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


	/*Pre-adventurer played*/

	int preTreasure = 0;
	int preHandCount = state.handCount[player];
	int prePlayerTwoCount = state.handCount[1];
	int prePlayedCount = state.playedCardCount;
	int preDiscardCount = state.discardCount[player];
	int preDeckCount = state.deckCount[player];


	for (i = 0; i < state.handCount[0]; i++){
		if(state.hand[player][state.handCount[i]] == copper || state.hand[player][state.handCount[i]] == silver || state.hand[player][state.handCount[i]] == gold) 
			preTreasure++;
	}

	//printf("preTreasure = %d, preHandCount = %d\n", preTreasure, preHandCount);

	/*Adventurer Played*/
	cardEffect(adventurer, choice1, choice2, choice3, &state, handPos, &bonus);

	/*Post-adventurer played*/


	//treasures in hand after call
	int postTreasure = 0; 

	for (i = 0; i < state.handCount[0]; i++){
		if(state.hand[player][state.handCount[i]] == copper || state.hand[player][state.handCount[i]] == silver || state.hand[player][state.handCount[i]] == gold) 
			postTreasure++;
	}

	int postDeckCount = state.deckCount[player];
	int postDiscardCount = state.discardCount[player];



	//printf("postTreasure = %d, postHandCount = %d\n", postTreasure, state.handCount[player]);


	/*Testing*/

	printf("\nTest 1: Adventurer properly played from hand\n");

	if (state.playedCardCount == (prePlayedCount+1)){
		printf("PASS: Played pile increased = %d\n", (state.playedCardCount - prePlayedCount));

	}
	else{
		printf("FAIL: Played pile increased = %d, expected = 1\n", (state.playedCardCount - prePlayedCount));

	}


	printf("\nTest 2: Player's hand has +2 treasure cards\n");

	if ((preTreasure + 2) == postTreasure){
		printf("PASS: expected = %d, actual = %d\n", (preTreasure + 2) , postTreasure);

	}
	else{
		printf("FAIL: expected = %d, actual = %d\n", (preTreasure + 2) , postTreasure);

	} 

	printf("\nTest 3: Player's hand only has +2 cards\n");

	if ((preHandCount + 1) == state.handCount[player]){
		printf("PASS: expected = %d, actual = %d\n", (preHandCount + 1) , state.handCount[player]);

	}
	else{
		printf("FAIL: expected = %d, actual = %d\n", (preHandCount + 1) , state.handCount[player]);

	} 

	printf("\nTest 4: Non-treasure cards drawn were discarded\n");

	if( (preDiscardCount + ((preDeckCount - postDeckCount))) == postDiscardCount ){
		printf("PASS: expected = %d, actual = %d\n",  preDiscardCount + ((preDeckCount - postDeckCount)), postDiscardCount);

	}
	else{
		printf("FAIL: expected = %d, actual = %d\n",  preDiscardCount + ((preDeckCount - postDeckCount)), postDiscardCount);

	}

	printf("\nTest 5: No change to player 2's hand\n");

	if(prePlayerTwoCount == state.handCount[1] ){
		printf("PASS: expected cards = %d, actual cards = %d\n", prePlayerTwoCount , state.handCount[1]);

	}
	else{
		printf("FAIL: expected cards = %d, actual cards = %d\n", prePlayerTwoCount , state.handCount[1]);

	}

	printf("\nTest 6: No change to kingdom or victory piles\n");

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
