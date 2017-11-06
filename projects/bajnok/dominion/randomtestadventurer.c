
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTUNIT "adventurer"


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

		/*Pre-Adventurer Played*/

		int preTreasure = 0;
		int preHandCount = G.handCount[p];
		int prePlayedCount = G.playedCardCount;
		int preDiscardCount = G.discardCount[p];
		int preDeckCount = G.deckCount[p];


		for (i = 0; i < G.handCount[p]; i++){
		if(G.hand[p][i] == copper || G.hand[p][i] == silver || G.hand[p][i] == gold) 
			preTreasure++;
		}

		/*printf("Test %d pretreasure is %d\n", n, preTreasure);
		printf("Test %d handCount is %d\n", n, G.handCount[p]);
		printf("Test %d deckCount is %d\n", n, G.deckCount[p]);
		printf("Test %d discardCount is %d\n", n, G.discardCount[p]);
		printf("Test %d playerCount is %d\n", n, numPlayers);*/

		/*Adventurer Played*/
		cardEffect(adventurer, 1, 1, 1, &G, 0, 0);

		/*Post-adventurer played*/

		//treasures in hand after call
		int postTreasure = 0; 

		for (i = 0; i < G.handCount[p]; i++){
			if(G.hand[p][i] == copper || G.hand[p][i] == silver || G.hand[p][i] == gold) 
				postTreasure++;
		}

		int postDeckCount = G.deckCount[p];
		int postDiscardCount = G.discardCount[p];

		/*Testing*/

		//printf("\nTest 1: Adventurer properly played from hand\n");

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


		//printf("\nTest 2: Player's hand has +2 treasure cards\n");

		//test fails
		if ((preTreasure + 2) != postTreasure){
			printf("SEED %d FAIL: expected treasures in hand = %d, actual = %d\n", rSeed, (preTreasure + 2) , postTreasure);
			totalFails++;
			totalTests++;
		} 
		else{
			totalPass++;
			totalTests++;
		}
		//printf("\nTest 3: Player's hand only has +2 cards\n");

		//test fails
		if ((preHandCount + 1) != G.handCount[p]){
			printf("SEED %d FAIL: expected hand count = %d, actual = %d\n", (preHandCount + 1) , G.handCount[p]);
			totalFails++;
			totalTests++;
		}
		else{
			totalPass++;
			totalTests++;
		}
		//printf("\nTest 4: Non-treasure cards drawn were discarded\n");

		if( (preDiscardCount + ((preDeckCount - postDeckCount))) == postDiscardCount ){
			printf("SEED %d FAIL: expected non-treasure discard= %d, actual = %d\n",  preDiscardCount + ((preDeckCount - postDeckCount)), postDiscardCount);
			totalFails++;
			totalTests++;
		}
		else{
			totalPass++;
			totalTests++;
		}

	}

	printf("\nTotal tests: %d, Successful: %d, Failed: %d\n", totalTests, totalPass, totalFails);


	printf("\n");

	return 0;
}
