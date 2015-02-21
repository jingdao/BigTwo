#include <stdio.h>
#include <stdlib.h>
#include "big2.h"

void displayCard(Card c[],int numCards) {
	int i;
	for (i=0;i<numCards;i++) {
		char* suitChar;
		switch (c[i].suit) {
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
		}
		printf("%c%s\n",c[i].value,suitChar);
	}
}

void createDeck(Card deck[]){
	int val,suit,i; 
	for (val=1;val<=13;val++) {
		for (suit=0;suit<4;suit++) {
			if (val>=2&&val<=10) {
				deck[i].value=(char)(val+48);
			} else if (val==1) {
				deck[i].value='A';
			} else if (val==11) {
				deck[i].value='J';
			} else if (val==12) {
				deck[i].value='Q';
			} else if (val==13) {
				deck[i].value='K';
			}
			deck[i].suit=suit;
			i++;
		}
	}
}

void shuffleDeck(Card deck[],Card* p1[],Card* p2[],Card* p3[],Card* p4[]) {
	srand(time(NULL));
	Card* stack[52];
	int i;
	for (i=0;i<52;i++)
		stack[i]=&deck[i];
	for (i=0;i<13;i++) {

	}
}

int main() {
	Card deck[52];
	createDeck(deck);
	displayCard(deck,52);
	printf("Hello world\n");
}
