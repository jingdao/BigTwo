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

