/*
 * seven-card-stud.c
 * Created on: Fri 17 Oct 2025
 * Last Updated: Sun 26 Oct 2025
 * gopeterjun@naver.com
 * C for Everyone: Structured Programming
 * Module 2 Honors Assignment
 *
 * Use a struct to define a card as an enumerated member that is its suit
 * value and a short that is its pips value.
 * - suits: Club ♧ 'c', Diamond ♢ 'd', Heart ♡ 'd', Spade ♤ 's'
 * - pips: 1 for Ace, 11 for Jack, 12 for Queen, 13 for King,
 *         n is n (for 2 to 10)
 *
 * Write a function that randomly shuffles the deck.
 *
 * Deal out 7-card hands and evaluate the probability that a hand has:
 * - no pair (all 7 cards have different pips)
 * - one pair (2 of 7 cards have the same pip)
 * - two pair (2 cards have pip 'a', 2 cards have pip 'b'
 * - three of a kind (3 cards have the same pip)
 * - full house
 *   + 'three of a kind' and 'one pair'
 *   + 'three of a kind' and 2nd 'three of a kind'
 *   + 'three of a kind' and 'two pair'
 * - four of a kind (4 cards have the same pip)
 *
 * This is a Monte Carlo method to get an approximation to these
 * probabilities.  Use at least 1 million randomly generated hands.
 *
 * Check against probabilities found in a standard table for Seven
 * Card Stud Poker https://wizardofodds.com/games/poker/
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DECK 52  // 52 cards in a deck of cards for blackjack/poker

enum hand_name {
    royal_flush,
    straight_flush,
    four_ofa_kind,
    full_house,
    flush,
    straight,
    three_ofa_kind,
    two_pair,
    one_pair,
    ace_high_orless,
    HAND_COUNT
};
typedef enum hand_name hand;

// stats for a single hand
typedef struct hand_stats {
    hand name;
    int combinations;
    double probability;
} stats;

enum suit {
    club,
    diamond,
    heart,
    spade,
    SUIT_COUNT
};
typedef enum suit suit;

enum card_name {
    ace = 1,
    two = 2,
    three = 3,
    four = 4,
    five = 5,
    six = 6,
    seven = 7,
    eight = 8,
    nine = 9,
    ten = 10,
    jack = 11,
    queen = 12,
    king = 13,
    NAME_COUNT
};
typedef enum card_name cname;

// 'card' struct containing attributes 'suit' and 'pip'
typedef struct card {
    short pips;
    suit c_suit;
} card;

// function signatures
void deal_seven(card deck[DECK], card hand[7]);
void fill_deck(card deck[DECK]);
void count_pips(card hand[7], int histogram[14]);
void analyze_hist(int histogram[14]);
void print_cards(card cards[], int size);
void shuffle(card deck[DECK]);
void swap(card *a, card *b);

int main(void) {
    // array of 'stats' structs
    stats scs_poker_hands[HAND_COUNT] = {
        // designated initializer syntax
        [royal_flush] = {royal_flush, 4324, 0.00003232},
        [straight_flush] = {straight_flush, 37260, 0.00027851},
        [four_ofa_kind]   = {four_ofa_kind, 224848, 0.00168067},
        [full_house]      = {full_house, 3473184, 0.02596102},
        [flush]           = {flush, 4047644, 0.03025494},
        [straight]        = {straight, 6180020, 0.04619382},
        [three_ofa_kind]  = {three_ofa_kind, 6461620, 0.04829870},
        [two_pair]        = {two_pair, 31433400, 0.23495536},
        [one_pair]        = {one_pair, 58627800, 0.43822546},
        [ace_high_orless] = {ace_high_orless, 23294460, 0.17411920}
    };

    int pip_counts[14] = {0};  // initialize integer array to 0's
    srand((unsigned)time(NULL));  // seed RNG before calling 'rand()'

    for (int j = 0; j < 10; j++) {
        printf("Hand No. %d\n:", j+1);
        card new_deck[DECK] = {0};  // array of 'struct card', 52 card deck
        card hand[7];  // array of struct 'card' for 7-card hand
        fill_deck(new_deck);  // pass new_deck to make_deck() to populate it
        shuffle(new_deck);

        deal_seven(new_deck, hand);
        count_pips(hand, pip_counts);
        print_cards(hand, 7);
    }

    printf("--- Pip Frequency Counts ---\n");
    const char *pip_names[] = {
    "Invalid", "Ace", "Two", "Three", "Four", "Five", "Six", "Seven",
    "Eight", "Nine", "Ten", "Jack", "Queen", "King"
    };
    int tot_count = 0;
    for (int k = 1; k < 14; k++) {
        printf("%s count: %d\n", pip_names[k], pip_counts[k]);
        tot_count += pip_counts[k];
    }
    printf("Total number of cards: %d\n\n", tot_count);

    /* debug printf() statements
    print_cards(new_deck, DECK);
     */

    printf("--- Four of a Kind ---\n");
    printf("Combinations: %d\t",
           scs_poker_hands[four_ofa_kind].combinations);
    // specify 8 decimal places of precision (default is 6)
    printf("Probability: %.08f\n",
           scs_poker_hands[four_ofa_kind].probability);

    return 0;
}

void fill_deck(card deck[DECK]) {
    /* populate 52 cards, 4 suits Clubs, Diamonds, Hearts, Spades w/ 13
       cards each 1 to 13, in order.

       NOTE: fill_deck() MUTATES the array of struct card 'deck[]'
       passed into it, so no 'return' needed
    */

    int i = 0; // loop start index 0; 'i' will go up to 51

    // Outer loop: iterate through all suits from club: 0 to spade: 3
    for (suit s = club; s < SUIT_COUNT; s++) {
        // Inner loop: iterate through all pips from ace: 1 to king: 13
        for (cname p = ace; p < NAME_COUNT; p++) {
            // assign current suit and pip value to current card
            deck[i].c_suit = s;
            deck[i].pips = p;
            i++;
        }
    }
}

void print_cards(card cards[], int size) {
    const char *suit_names[] = {"Clubs", "Diamonds", "Hearts", "Spades"};
    const char *pip_names[] = {
        "Invalid", "Ace", "Two", "Three", "Four", "Five", "Six", "Seven",
        "Eight", "Nine", "Ten", "Jack", "Queen", "King"
    };
    printf("--- Printing Cards ---\n");
    for (int i = 0; i < size; i++) {
        printf("Card %2d: %-5s of %s\n", i + 1,
               pip_names[cards[i].pips],
               suit_names[cards[i].c_suit]);
    }
    printf("\n");
}

void shuffle(card deck[DECK]) {
    /* Use Fisher-Yates shuffle algorithm (Durstenfeld variation)
     * introduced in Donald Knuth's 'Art of Programming' textbook; O(n)
     * time complexity
     * https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
     */
    int minN = 0;
    for (int i = DECK - 1; i > 0; i--) {
        int maxN = i;
        // generate random 'j' s.t. 0 <= j <= i
        int j = (rand() % (maxN - minN + 1)) + minN;
        // swap values at deck[] indices 'j' and 'i'
        swap(&deck[j], &deck[i]);
    }
}

// swap indices in array of 'card' structs
void swap(card *a, card *b) {
    card temp = *a;
    *a = *b;
    *b = temp;
}

void deal_seven(card deck[DECK], card hand[7]) {
    /*
     * This function deals a 7-card hand from the top of the deck
     * into the 'hand' array provided by the caller. This function has
     * no 'return' b/c it mutates 'card hand[7] directly!
    */
    for (int i = 0; i < 7; i++) {
        hand[i] = deck[i];
    }
}

void count_pips(card hand[7], int histogram[14]) {
    /* Int array 'histogram' is a pip frequency array. Time complexity
     * O(n) where 'n' is size of int array. No 'return' as int array
     * 'histogram' is directly mutated!
     *
     * Int array 'histogram' indices 1 to 13 represent 1: Ace to
     * 13: King
     */
    for (int i = 0; i < 7; i++) {
        histogram[hand[i].pips]++;
    }
}

/*
 * After this loop, your pips_count array will look like:
 * [0, 0, 1, 0, 0, 3, 0, 0, 0, 0, 2, 0, 0, 1]
 *
 * pip_counts[2] = 1, pip_counts[5] = 3, pip_counts[10] = 2,
 * pip_counts[13] = 1
 * Now all you have to do is iterate from 1 to 13 and check the counts
*/
