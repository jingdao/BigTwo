#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "big2.h"
#define BUFFER_SIZE 64
#define MAX(x,y) (x>y?x:y)

int previousCombination;
int previousValue;
int previousNumCards=-1;
int currentCombination;
int numPasses=0;

int compCard (const void * c1, const void * c2) {
	Card* a = *(Card**)c1;
	Card* b = *(Card**)c2;
	if (a->value<b->value) return -1;
	else if (a->value>b->value) return 1;
	else if (a->suit<b->suit) return -1;
	else return 1;
}

	int getRanking(Card* cardsPlayed[],int numCardsPlayed) {
		int rank=0;
		if (numCardsPlayed==1) rank=cardsPlayed[0]->value*4+cardsPlayed[0]->suit;
		else if (numCardsPlayed==2) {
			rank=cardsPlayed[0]->value*4+MAX(cardsPlayed[0]->suit,cardsPlayed[1]->suit);
		} else if (numCardsPlayed==3) {
			rank=cardsPlayed[0]->value;
		} else if (numCardsPlayed==5) {
			if (currentCombination<previousCombination)
				return 0;
			else if (currentCombination>previousCombination)
				return 1;
			else if (currentCombination==STRAIGHT) {
				rank=MAX(cardsPlayed[0]->value*4+cardsPlayed[0]->suit,
					MAX(cardsPlayed[1]->value*4+cardsPlayed[1]->suit,
					MAX(cardsPlayed[2]->value*4+cardsPlayed[2]->suit,
					MAX(cardsPlayed[3]->value*4+cardsPlayed[3]->suit,
						cardsPlayed[4]->value*4+cardsPlayed[4]->suit))));
			} else if (currentCombination==FLUSH||currentCombination==STRAIGHT_FLUSH) {
				rank=MAX(cardsPlayed[0]->value+cardsPlayed[0]->suit*16,
					MAX(cardsPlayed[1]->value+cardsPlayed[1]->suit*16,
					MAX(cardsPlayed[2]->value+cardsPlayed[2]->suit*16,
					MAX(cardsPlayed[3]->value+cardsPlayed[3]->suit*16,
						cardsPlayed[4]->value+cardsPlayed[4]->suit*16))));
			} else if (currentCombination==FOUR_OF_A_KIND||currentCombination==FULL_HOUSE) {
				rank=cardsPlayed[0]->value;
			}
		}
		return rank;
	}

	int compareRanking(Card* cardsPlayed[],int numCardsPlayed) {
		int rank=getRanking(cardsPlayed,numCardsPlayed);
		if (previousNumCards<=0||rank>previousValue) {
			previousNumCards=numCardsPlayed;
			previousValue=rank;
			previousCombination=currentCombination;
			return 1;
		} else return 0;
	}

	int validate(Card* cardsPlayed[],int numCardsPlayed) {
		if(previousNumCards>0&&numCardsPlayed!=previousNumCards) return 0;
		if (numCardsPlayed<=0) return 0;
		else if (numCardsPlayed==1) return 1;
		else if (numCardsPlayed==2) {
			return cardsPlayed[0]->value==cardsPlayed[1]->value;
		} else if (numCardsPlayed==3) {
			return cardsPlayed[0]->value==cardsPlayed[1]->value&&cardsPlayed[0]->value==cardsPlayed[2]->value;
		} else if (numCardsPlayed==5) {
			//flush
			if (cardsPlayed[0]->suit==cardsPlayed[1]->suit&&
				cardsPlayed[0]->suit==cardsPlayed[2]->suit&&
				cardsPlayed[0]->suit==cardsPlayed[3]->suit&&
				cardsPlayed[0]->suit==cardsPlayed[4]->suit) {
				currentCombination=FLUSH;
				return 1;
			//straight
			 } else if ((cardsPlayed[0]->value==15&&cardsPlayed[1]->value==3||
				 	cardsPlayed[0]->value+1==cardsPlayed[1]->value)&&
					(cardsPlayed[1]->value==15&&cardsPlayed[2]->value==3||
					cardsPlayed[1]->value+1==cardsPlayed[2]->value)&&
					cardsPlayed[2]->value+1==cardsPlayed[3]->value&&
					cardsPlayed[3]->value+1==cardsPlayed[4]->value) {
						if (cardsPlayed[0]->suit==cardsPlayed[1]->suit&&
							cardsPlayed[0]->suit==cardsPlayed[2]->suit&&
							cardsPlayed[0]->suit==cardsPlayed[3]->suit&&
							cardsPlayed[0]->suit==cardsPlayed[4]->suit) 
							currentCombination=STRAIGHT_FLUSH;
				 		else
							currentCombination=STRAIGHT;
				 return 1;
			//four of a kind
			} else if (cardsPlayed[0]->value==cardsPlayed[1]->value&&
					cardsPlayed[0]->value==cardsPlayed[2]->value&&
					cardsPlayed[0]->value==cardsPlayed[3]->value&&
					cardsPlayed[0]->value==cardsPlayed[4]->value) {
				currentCombination=FOUR_OF_A_KIND;
				return 1;
			//full house
			} else if (cardsPlayed[0]->value==cardsPlayed[1]->value&&
					cardsPlayed[0]->value==cardsPlayed[2]->value&&
					cardsPlayed[3]->value==cardsPlayed[4]->value) {
				currentCombination=FULL_HOUSE;
				return 1;
			} else return 0;
		}
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
		if (i%5==4) printf(" |");
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
		int i,j=0;
		for (i=0;i<numCardsPlayed;i++) {
			displayCard(&hand[cardsPlayed[i]],1);
		}
		//fix card order
		for (i=0;i<handSize;i++) {
			if (j<numCardsPlayed&&i==cardsPlayed[j]) {
				j++;
			} else
				hand[i-j]=hand[i];
		}
		numPasses=0;
		printf("\n");
	} else {
		numPasses++;
		printf("Pass\n");
	}
}

int getAction(Card* hand[],int handSize,int playerId,int displayFlag) {
	int cardsPlayedIndex[5];
	int cardFlag;
	char buffer[BUFFER_SIZE];
	char* tok;
	int numCardsPlayed=0,i;
	Card* cardsPlayed[5] = {NULL,NULL,NULL,NULL};
	if (displayFlag) {
		while (1) {
			numCardsPlayed=0;
			cardFlag=0;
			displayCard(hand,handSize);
			printf("    >>");
			fgets(buffer,BUFFER_SIZE,stdin);
			if (buffer[0]=='0'&&previousNumCards>0) break;
//			printf("\033[A\033[2K"); //cursor up; clear line
			tok=strtok(buffer," ");
			while (tok&&numCardsPlayed<5) {
				int choice = atoi(tok)-1;
//				printf("%s %d %d\n",tok,cardFlag,1<<choice);
				if (choice>=0&&choice<handSize&&!(cardFlag&(1<<choice))) {
					cardsPlayedIndex[numCardsPlayed]=choice;
					cardsPlayed[numCardsPlayed++]=hand[choice];
					cardFlag|=(1<<choice);
				} else {
					numCardsPlayed=0;
					break;
				}
				tok=strtok(NULL," ");
			}
			if (validate(cardsPlayed,numCardsPlayed)&&compareRanking(cardsPlayed,numCardsPlayed)) break;
		}
	} else {
		displayCard(hand,handSize);
		printf("\n");
		if (previousNumCards<=0) {
			compareRanking(&hand[0],1);
			numCardsPlayed=1;
			cardsPlayed[0]=hand[0];
			cardsPlayedIndex[0]=0;
		} else if (previousNumCards==1) {
			for (i=0;i<handSize;i++) {
				if (compareRanking(&hand[i],1)) {
					numCardsPlayed=1;
					cardsPlayed[0]=hand[i];
					cardsPlayedIndex[0]=i;
					break;
				}
			}
		}
	}
	playCard(hand,handSize,playerId,cardsPlayedIndex,numCardsPlayed);
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
//	displayCard(p1,13); printf("\n");
//	displayCard(p2,13);printf("\n");
//	displayCard(p3,13);printf("\n");
//	displayCard(p4,13);printf("\n");
	//determine starting player (3 diamonds)
	int i;
	for (i=0;i<4;i++) {
		if (playerCards[i][0]==&deck[0]) {
			printf("Starting player is %d\n",i+1);
//			int j=0;
//			playCard(playerCards[i],handSize[i],i+1,&j,1);
//			i=(i+1)%4;
			break;
		}
	}
	while (1) {
		if (numPasses==3) {
			printf("Player %d leads.\n",i+1);
			numPasses=0;
			previousNumCards=-1;
		}
		handSize[i]=getAction(playerCards[i],handSize[i],i+1,/*i==*/0);
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
}
