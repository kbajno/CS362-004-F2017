
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTUNIT "smithy"


int main() {


	int i, n, p, deckCount, discardCount, handCount, rSeed, numPlayers;
	int totalFails = 0;
	int totalPass = 0;
	int totalTests = 0;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room}; //cards in game
	//int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;


	struct gameState G, preG;

	//print out what card we are testing
	printf("RANDOM TESTING: %s \n", TESTUNIT);

	for (n = 0; n < 2000; n++){
		
		/*initialize game state (num of players, cards, and seed)*/

		i = 0;
		rSeed = rand(); //seed num
		numPlayers = rand() % 3 + 2; //total players btwn 2-4
		initializeGame(numPlayers, k, rSeed, &G); //initialize
		memcpy(&preG, &G, sizeof(struct gameState)); //cpy over to save pre-state before calling card

		/*generate random cards and decks for players*/

		p = whoseTurn(&G); //get cur player for adjusting deck

		//rand cards in deck
		deckCount = rand() % MAX_DECK;
		G.deckCount[p] = deckCount;

		for (i = 0; i < deckCount; i++){
			G.deck[p][i] = rand() % treasure_map;
		}

		//rand cards in hand
		handCount = rand() % MAX_HAND;
		G.handCount[p] = handCount;

		for (i = 0; i < handCount; i++){
			G.hand[p][i] = rand() % treasure_map;
		}

		//rand cards in discard
		discardCount = rand() % MAX_DECK;
		G.discardCount[p] = discardCount;

		for (i = 0; i < discardCount; i++){
			G.discard[p][i] = rand() % treasure_map;
		}

		/*Pre-Smithy Played*/

		int preHandCount = G.handCount[p];
		int prePlayedCount = G.playedCardCount;
		int preDiscardCount = G.discardCount[p];
		int preDeckCount = G.deckCount[p];

		/*Smithy Played*/
		cardEffect(smithy, 0, 0, 0, &G, 0, 0);

		/*Post-smithy played*/

		/*Testing*/

		//printf("\nTest 1: Smithy properly played from hand\n");

		//test fails
		if (G.playedCardCount != (prePlayedCount+1)){
			printf("SEED %d FAIL: Played pile increased = %d, expected = 1\n", rSeed, (G.playedCardCount - prePlayedCount));
			totalFails++;
			totalTests++;
		}
		else{
			totalPass++;
			totalTests++;

		}


		//printf("\nTest 2: Player's hand has +3 cards\n");

		//test fails
		if ((preHandCount + 2) != G.handCount[p]){
			printf("SEED %d FAIL: expected hand count = %d, actual = %d\n", rSeed, (preHandCount + 2) , G.handCount[p]);
			totalFails++;
			totalTests++;
		}
		else{
			totalPass++;
			totalTests++;		

		} 

		//printf("\nTest 3: Player's deck has -3 cards\n");

		//test fails
		if ( (preDeckCount - 3) != G.deckCount[p]){
			printf("SEED %d FAIL: expected deck count = %d, actual = %d\n", rSeed, (preDeckCount-3) , G.deckCount[p]);
			totalFails++;
			totalTests++;
		}
		else{
			totalPass++;
			totalTests++;	
		} 

		//printf("\nTest 4: No change to kingdom or victory piles\n");

		for (i = curse; i <= treasure_map; i++)
		{
			//printf("Card %d - supply count before: %d, supply count after: %d\n", i, startG.supplyCount[i], G.supplyCount[i]);
			//test fails
			if (G.supplyCount[i] != preG.supplyCount[i]){
				printf("SEED %d FAIL: card %d expected supply = %d, actual = %d\n", rSeed, i, preG.supplyCount[i], G.supplyCount[i]);
				totalFails++;
				totalTests++;
			}

			else{
				totalPass++;
				totalTests++;

			}
		}


	}

	printf("\nTotal tests: %d, Successful: %d, Failed: %d\n", totalTests, totalPass, totalFails);


	printf("\n");

	return 0;
}
