#ifndef _DOMINION_HELPERS_H
#define _DOMINION_HELPERS_H

#include "dominion.h"

int drawCard(int player, struct gameState *state);
int updateCoins(int player, struct gameState *state, int bonus);
int discardCard(int handPos, int currentPlayer, struct gameState *state, 
		int trashFlag);
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player);
int getCost(int cardNumber);
int cardEffect(int card, int choice1, int choice2, int choice3, 
	       struct gameState *state, int handPos, int *bonus);

/*Assign 2 Refractoring*/
int Adventurer(struct gameState * state);
int Smithy(struct gameState * state, int handPos);
int Feast(struct gameState * state, int choice1);
int Gardens(struct gameState * state);
int Mine(struct gameState * state, int choice1, int choice2);
int Cutpurse(struct gameState * state, int handPos);

#endif
