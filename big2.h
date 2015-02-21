typedef enum {
	DIAMONDS=0,
	CLUBS=1,
	HEARTS=2,
	SPADES=3
} Suit;

typedef struct {
	char value;
	Suit suit;
} Card;

typedef enum {
	STRAIGHT=0,
	FLUSH=1,
	FULL_HOUSE=2,
	FOUR_OF_A_KIND=3,
	STRAIGHT_FLUSH=4
} Combination;

