#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTUNIT "cutpurse"


int main() {


	int i, j, n, p, deckCount, discardCount, handCount, rSeed, numPlayers;
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
		int randTreasure = 0;

		for (i = 0; i < numPlayers; i++){
			G.handCount[p] = handCount;
			G.hand[p][0] = cutpurse;

			for (j = 1; j < handCount; j++){
				randTreasure = rand() % 3;
				if (randTreasure == 0){
					G.hand[i][j] = copper;

				}
				else if (randTreasure == 1){
					G.hand[i][j] = silver;
				}
				else{
					G.hand[i][j] = gold;
				}

			}
		}

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

		/*Pre-Cutpurse Played*/

		int preHandCount = G.handCount[p];
		int prePlayedCount = G.playedCardCount;
		int preDiscardCount = G.discardCount[p];
		int preDeckCount = G.deckCount[p];
		int preTreasure = 0;

		//collect copper count of all players
		int preCopper[numPlayers];
		int count = 0;

		for (i = 0; i < numPlayers; i++){
			for (j = 0; j < G.handCount[p]; j++){
				if(G.hand[i][j] == copper) 
				count++;
			}
			preCopper[i] = count;
			count = 0;		
		}

		for (i = 0; i < numPlayers; i++){
			preCopper[i] = 0;
		}

		//collect treasure count of current player
		for (i = 0; i < G.handCount[p]; i++){
		if(G.hand[p][i] == copper || G.hand[p][i] == silver || G.hand[p][i] == gold) 
			preTreasure++;
		}

		/*Cutpurse played*/
		cardEffect(cutpurse, 0, 0, 0, &G, 0, 0);

		int postTreasure = 0;
		for (i = 0; i < G.handCount[p]; i++){
		if(G.hand[p][i] == copper || G.hand[p][i] == silver || G.hand[p][i] == gold) 
			postTreasure++;
		}


		//collect copper count of all players
		int postCopper[numPlayers];

		for (i = 0; i < numPlayers; i++){
			for (j = 0; j < G.handCount[p]; j++){
				if(G.hand[i][j] == copper) 
				count++;
			}
			postCopper[i] = count;
			count = 0;
			
		}

		/*Testing*/

		//check to see cutpurse properly played from hand

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

		//check current players coins to see if silver was added 

		//check current players coins to see if total values is +2

		if (postTreasure-2 != preTreasure){
			printf("SEED %d FAIL: Player's coins increased = %d, expected = 2\n", rSeed, postTreasure - preTreasure);
			totalFails++;
			totalTests++;
		}
		else{
			totalPass++;
			totalTests++;
		}

		//check other players to see if 1 copper was discarded if they had one

		for (i = 0; i < numPlayers; i++){
			if (i != p){
				if (postCopper[i] != preCopper[i]+1){
					printf("SEED %d FAIL: Player's copper = %d, expected = 2\n", rSeed, postCopper[i], preCopper[i]+1);
					totalFails++;
					totalTests++;
				}
				else{
					totalPass++;
					totalTests++;
				}


			}
		}



	}

	printf("\nTotal tests: %d, Successful: %d, Failed: %d\n", totalTests, totalPass, totalFails);


	printf("\n");

	return 0;
}
