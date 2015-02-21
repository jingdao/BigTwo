#include <stdio.h>
#include <stdlib.h>
#include "big2.h"
#include <time.h>

int compCard (const void * c1, const void * c2) {
	Card* a = *(Card**)c1;
	Card* b = *(Card**)c2;
	if (a->value<b->value) return -1;
	else if (a->value>b->value) return 1;
	else if (a->suit<b->suit) return -1;
	else return 1;
}

void displayCard(Card** c,int numCards) {
	int i;
//	for (i=0;i<numCards;i++) {
//		if ((*c[i]).value==11)
//			printf("  J");
//		else if ((*c[i]).value==12)
//			printf("  Q");
//		else if ((*c[i]).value==13)
//			printf("  K");
//		else if ((*c[i]).value==14)
//			printf("  A");
//		else if ((*c[i]).value==15)
//			printf("  2");
//		else 
//			printf("%3d",(*c[i]).value);
//	}
//	printf("\n");
	for (i=0;i<numCards;i++) {
		if ((*c[i]).value==11)
			printf("  J");
		else if ((*c[i]).value==12)
			printf("  Q");
		else if ((*c[i]).value==13)
			printf("  K");
		else if ((*c[i]).value==14)
			printf("  A");
		else if ((*c[i]).value==15)
			printf("  2");
		else 
			printf("%3d",(*c[i]).value);
		char* suitChar;
		switch ((*c[i]).suit) {
			case SPADES:
				suitChar="\xe2\x99\xa0";
				break;
			case HEARTS:
				suitChar="\xe2\x99\xa1";
				break;
			case CLUBS:
				suitChar="\xe2\x99\xa3";
				break;
			case DIAMONDS:
				suitChar="\xe2\x99\xa2";
				break;
			default:
				suitChar="\xe2\x99\xa0";
				break;
		}
		printf("%s",suitChar);
	}
//	printf("\n");
}

void createDeck(Card deck[]){
	int val,suit,i=0; 
	for (val=3;val<=15;val++) {
		for (suit=0;suit<4;suit++) {
			deck[i].value=val;
			deck[i].suit=(Suit)suit;
			i++;
		}
	}
}

void shuffleDeck(Card deck[],Card* p1[],Card* p2[],Card* p3[],Card* p4[]) {
	Card *stack[52];
	int stackSize=52;
	int i,j;
	for (i=0;i<52;i++)
		stack[i]=&deck[i];
	for (i=0;i<13;i++) {
		j=rand()%stackSize;
		p1[i]=stack[j];
		stack[j]=stack[--stackSize];
		j=rand()%stackSize;
		p2[i]=stack[j];
		stack[j]=stack[--stackSize];
		j=rand()%stackSize;
		p3[i]=stack[j];
		stack[j]=stack[--stackSize];
		j=rand()%stackSize;
		p4[i]=stack[j];
		stack[j]=stack[--stackSize];
	}
}

void playCard(Card* hand[],int handSize,int playerId,int cardsPlayed[],int numCardsPlayed) {
	printf("Player %d: ",playerId);
	if (numCardsPlayed>0) {
		int i;
		for (i=0;i<numCardsPlayed;i++) {
			displayCard(&hand[cardsPlayed[i]],1);
		}
		printf("\n");
	} else {
		printf("Pass\n");
	}
}

int getAction(Card* hand[],int handSize,int playerId,int displayFlag) {
	int cardsPlayed[5];
	int numCardsPlayed=0;
	if (displayFlag) {
		displayCard(hand,handSize);
		char buffer[16];
		printf("    >>");
		fgets(buffer,16,stdin);
		printf("\033[A\033[2K"); //cursor up; clear line
		int choice = atoi(buffer)-1;
		if (choice>=0&&choice<handSize) {
			cardsPlayed[0]=choice;
			numCardsPlayed++;
		}
	}
	playCard(hand,handSize,playerId,cardsPlayed,numCardsPlayed);
	return handSize-numCardsPlayed;
}

void newGame(Card deck[]) {
	Card* p1[13];
	Card* p2[13];
	Card* p3[13];
	Card* p4[13];
	shuffleDeck(deck,p1,p2,p3,p4);
	qsort(p1,13,sizeof(Card*),compCard);
	qsort(p2,13,sizeof(Card*),compCard);
	qsort(p3,13,sizeof(Card*),compCard);
	qsort(p4,13,sizeof(Card*),compCard);
	Card** playerCards[] = {p1,p2,p3,p4};
	int handSize[] ={13,13,13,13};
//	displayCard(p1,13);
//	displayCard(p2,13);
//	displayCard(p3,13);
//	displayCard(p4,13);
	//determine starting player (3 diamonds)
	int i;
	for (i=0;i<4;i++) {
		if (playerCards[i][0]==&deck[0]) {
			printf("Starting player is %d\n",i+1);
			int j=0;
			playCard(playerCards[i],handSize[i],i+1,&j,1);
			i=(i+1)%4;
			break;
		}
	}
	while (1) {
		handSize[i]=getAction(playerCards[i],handSize[i],i+1,i==0);
		if (handSize[i]==0) {
			printf("Player %d won!\n",i+1);
			break;
		}
		i=(i+1)%4;
	}


}

int main() {
	srand((unsigned int)time(NULL));
	Card deck[52];
	createDeck(deck);
	newGame(deck);
	newGame(deck);
}
