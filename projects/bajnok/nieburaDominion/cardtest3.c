
/*Code style inspired by cardtest4.c provided on Canvas*/


#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "feast"


int main() {

	//print out what card we are testing
	printf("TESTING  CARD: %s \n", TESTCARD);

	int i = 0;
	int rSeed = 10; //seed num
	int player = 0; //current player
	int numPlayers = 2; //total players
	int handPos = 0, choice1 = embargo, choice2 = 0, choice3 = 0, bonus = 0;

	struct gameState state, preState; //holds game state
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room}; //cards in game

	//initialize the game state and player cards
	initializeGame(numPlayers, k, rSeed, &state);

	//add the feast card to players hand 
	state.hand[player][0] = feast;

	//gainCard(feast, &state, 2, player);
	memcpy(&preState, &state, sizeof(struct gameState));

	/*Pre-feastplayed*/

	int preHandCount = state.handCount[player];
	int prePlayerTwoCount = state.handCount[1];
	int prePlayedCount = state.playedCardCount;
	int preDiscardCount = state.discardCount[player];
	int preDeckCount = state.deckCount[player];


	/*feast Played*/
	cardEffect(feast, choice1, choice2, choice3, &state, handPos, &bonus);

	/*Post-feast played*/

	/*Testing*/

	printf("\nTest 1: Feast properly trashed from hand\n");

	if (fullDeckCount(player, feast, &state) == 0 && fullDeckCount(player, feast, &preState) == 1){
		printf("PASS: expected = %d, actual = %d\n", fullDeckCount(player, feast, &preState) - 1 , fullDeckCount(player, feast, &state));

	}
	else{
		printf("FAIL: expected = %d, actual = %d\n", fullDeckCount(player, feast, &preState) - 1 , fullDeckCount(player, feast, &state));

	}

	printf("\nTest 2: Feast is not in played pile\n");

	int check = 0;

	//check if card in played pile is equal to feast
	for(i = 0; i < state.playedCardCount; i++){
		if (state.playedCards[i] == TESTCARD){
			printf("FAIL: Feast card is in played pile\n");
			check = 1;
			break;
		}
		else
			check = 2;		
	}

	if (check == 2 ){
		printf("PASS: No feast card in played pile\n");
	}

	printf("\nTest 3: Player's hand is unchanged\n");

	if ((preHandCount) == state.handCount[player]){
		printf("PASS: expected = %d, actual = %d\n", (preHandCount) , state.handCount[player]);

	}
	else{
		printf("FAIL: expected = %d, actual = %d\n", (preHandCount) , state.handCount[player]);

	} 

	printf("\nTest 4: Player recieved 5 coins\n");

	if (state.coins == 5){
		printf("PASS: total coins expected = %d, actual = %d\n", (preState.coins + 5) - 2 , state.coins + 2);

	}
	else{
		printf("FAIL: total coins expected = %d, actual = %d\n",  (preState.coins + 5) - 2 , state.coins + 2);

	} 

	printf("\nTest 5: Can gain card costing < 5 coins (embargo = 2 coins)\n");

	if(fullDeckCount(player, embargo, &state) == ((fullDeckCount(player, embargo, &preState) +1))){
		printf("PASS: embargo count expected = %d, actual = %d\n", ((fullDeckCount(player, embargo, &preState) +1) , fullDeckCount(player, embargo, &state)));

	}
	else{
		printf("FAIL: embargo count expected = %d, actual = %d\n", ((fullDeckCount(player, embargo, &preState) +1) , fullDeckCount(player, embargo, &state)));

	}



	printf("\n");

	return 0;
}
