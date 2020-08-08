/* #include directievs go here */
#include <stdio.h>
#include <stdbool.h>

/* #define directives go here */
#define NUM_RANKS (13)
#define NUM_SUITS (4)
#define NUM_CARDS (5)

/* declarations of external variables go here */
int num_in_rank[NUM_RANKS];
int num_in_suit[NUM_SUITS];

bool straight, flush, four, three;
int pairs;

/* prototype */
void read_card(void);
void analyze_hand(void);
void print_result(void);

/* main function */
int main(void)
{
	for (;;) {
		read_card();
		analyze_hand();
		print_result();
	}

	return 0;
}

/* function definitions */
void read_card(void)
{
	bool card_exist[NUM_RANKS][NUM_SUITS];
	char ch, rank_ch, suit_ch;
	int rank, suit;
	bool bad_card;
	int cards_read = 0;

	for(rank = 0; rank < NUM_RANKS; rank++){
		num_in_rank[rank] = 0;
		for(suit = 0; suit < NUM_SUITS; suit++)
			card_exist[rank][suit] = false;
	}

	for(suit = 0; suit < NUM_SUITS; suit++)
		num_in_suit[suit] = 0;

	while(cards_read < NUM_CARDS)
	{
		bad_card = false;

		printf("Enter a card : ");

		rank_ch = getchar();
		switch(rank_ch){
			case '2':	rank = 0;			break; 
			case '3':	rank = 1;			break;
			case '4':	rank = 2;			break;
			case '5':	rank = 3;			break;
			case '6':	rank = 4;			break;
			case '7':	rank = 5;			break;
			case '8':	rank = 6;			break;
			case '9':	rank = 7;			break;
			case '0':	rank = 8;			break;
			case 'A':	rank = 9;			break;
			case 'K':	rank = 10;			break;
			case 'Q':	rank = 11;			break;
			case 'J':	rank = 12;			break;
			default:	bad_card = true;		break;
		}
		
		suit_ch = getchar();
		switch(suit_ch){
			case 'D': case 'd': suit = 0;	break; 
			case 'S': case 's': suit = 1;	break;
			case 'C': case 'c': suit = 2;	break;
			case 'H': case 'h': suit = 3;	break;
			default:  bad_card = true;	break;
		}

		while((ch = getchar()) != '\n')
			if(ch != ' ') bad_card = true;

		if(bad_card)
			printf("Bad card; ignored.\n");
		else if(card_exist[rank][suit])
			printf("Duplicate card; ignored.\n");
		else{
			num_in_rank[rank]++;
			num_in_suit[suit]++;
			card_exist[rank][suit] = true;
			cards_read++;
		}
	}
}

void analyze_hand(void)
{
	int num_consec = 0;
	int rank, suit;

	straight = false;
	flush = false;
	four = false;
	three = false;
	pairs = 0;

	for(suit = 0; suit < NUM_SUITS; suit++)
		if(num_in_suit[suit] == NUM_CARDS)
			flush = true;

	rank = 0;
	while(num_in_rank[rank] == 0)	rank++;
	for(; rank < NUM_RANKS && num_in_rank[rank] > 0; rank++)
		num_consec++;
	if(num_consec == NUM_CARDS){
		straight = true;
		return;
	}

	for(rank = 0; rank < NUM_RANKS; rank++){
		if(num_in_rank[rank] == 4)	four = true;
		if(num_in_rank[rank] == 3)	three = true;
		if(num_in_rank[rank] == 2)	pairs++;
	}
}

void print_result(void)
{
	if (straight && flush)
		printf("Result: Straight flush");
	else if (four)
		printf("Result: Four-of-a-kind");
	else if (three && pairs == 1)
		printf("Result: Full house");
	else if (flush)
		printf("Result: Flush");
	else if (straight)
		printf("Result: Straight");
	else if (three)
		printf("Result: Tree-of-a-kind");
	else if (pairs == 2)
		printf("Result: Two-pair");
	else if (pairs == 1)
		printf("Result: Pair");
	else
		printf("Result: High card");

	printf("\n\n");
}
