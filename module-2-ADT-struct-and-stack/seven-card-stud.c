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
 * NOTE: we will ignore suits for this homework, so hands like
 * 'royal flush', 'straight flush', and 'flush' (these require cards
 * to all have the same suit) will not be counted. Also, 'straight'
 * (a hand containing consecutive pip values like '2, 3, 4, 5, 6, 7')
 * will also be ignored for this homework.
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
#define MC_MAX 100000  // Monte Carlo Analysis max iterations

// global immutable character array
const char *hand_names[] = {
    "Four of a Kind", "Full House",
    "Three of a Kind", "Two Pair", "One Pair", "No Pair"
};
// global immutable character array
const char *suit_names[] = {"Clubs", "Diamonds", "Hearts", "Spades"};
// global immutable character array
const char *pip_names[] = {
    "Invalid", "Ace", "Two", "Three", "Four", "Five", "Six", "Seven",
    "Eight", "Nine", "Ten", "Jack", "Queen", "King"
};

enum hand_name {
    four_ofa_kind,
    full_house,
    three_ofa_kind,
    two_pair,
    one_pair,
    no_pair,
    HAND_COUNT
};
typedef enum hand_name hand;

// stats for a single hand
typedef struct hand_stats {
    hand name;
    unsigned int count;
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
void classify_hand(card hand[7], stats hands[MC_MAX]);
void deal_seven(card deck[DECK], card hand[7]);
void fill_deck(card deck[DECK]);
void print_cards(card cards[], int size);  // useful for debugging
void print_mc_analysis(stats hands[MC_MAX]);
void print_ptable(stats ptable[HAND_COUNT]);
void shuffle(card deck[DECK]);
void swap(card *a, card *b);

int main(void) {
    // array of struct 'stats'
    stats scs_poker_hands[HAND_COUNT] = {
        // designated initializer syntax
        // data from https://wizardofodds.com/games/poker/
        [four_ofa_kind]   = {four_ofa_kind, 0, 0.00168067},
        [full_house]      = {full_house, 0, 0.02596102},
        [three_ofa_kind]  = {three_ofa_kind, 0, 0.04829870},
        [two_pair]        = {two_pair, 0, 0.23495536},
        [one_pair]        = {one_pair, 0, 0.43822546},
        [no_pair] = {no_pair, 0, 0.17411920}
    };

    stats hand_results[MC_MAX] = {0};  // array of struct 'stats'
    srand((unsigned)time(NULL));  // seed RNG before calling 'rand()'

    // deal multiple 7-card hands for Monte Carlo Analysis
    for (int j = 0; j < MC_MAX; j++) {
        //printf("Hand No. %d\n:", j+1);
        card new_deck[DECK] = {0};  // array of 'struct card', 52 card deck
        card hand[7];  // array of struct 'card' for 7-card hand
        fill_deck(new_deck);  // pass new_deck to fill_deck() to populate it
        shuffle(new_deck);  // shuffle 'new_deck'
        deal_seven(new_deck, hand);  // deal 7-card hand from top of deck
        classify_hand(hand, hand_results);  // update 'hand_results'
        //print_cards(hand, 7);
    }

    // Add probabilities to array of struct 'stats' aka 'hand_results'
    for (hand i = four_ofa_kind; i < HAND_COUNT; i++) {
        hand_results[i].probability = (
            hand_results[i].count / (double)MC_MAX); // force conversion
    }

    print_mc_analysis(hand_results);
    print_ptable(scs_poker_hands);

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
    printf("--- Printing Cards ---\n");
    for (int i = 0; i < size; i++) {
        printf("Card %2d: %-5s of %s\n", i + 1,
               pip_names[cards[i].pips],
               suit_names[cards[i].c_suit]);
    }
    printf("\n");
}

void print_mc_analysis(stats hand_results[MC_MAX]) {
    printf("--- Monte Carlo Analysis of %d Hands ---\n", MC_MAX);
    for (hand i = four_ofa_kind; i < HAND_COUNT; i++) {
        printf("%s\t count: %d\t\t probability: %.08f\n",
               hand_names[i], hand_results[i].count,
               hand_results[i].probability);
    }
    printf("\n");
}

void print_ptable(stats ptable[HAND_COUNT]) {
    printf("--- Reference Table of 7-card stud Poker Probabilities ---\n");
    for (hand i = four_ofa_kind; i < HAND_COUNT; i++) {
        printf("%s\t probability: %.08f\n", hand_names[i],
               ptable[i].probability);
    }
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

void classify_hand(card hand[7], stats hand_results[MC_MAX]) {
    /* Int array 'hand_results' is a frequency array of poker hand types
     * like 'Four of a Kind', 'One Pair', etc. Time complexity O(n) where
     * 'n' is size of int array. No 'return' as int array 'hand_results' is
     * directly mutated!
     *
     * Step One: Initialize int array 'histogram' where indices 1 to 13
     * represent 1: Ace to 13: King. Index '0' is unused.
     *
     * Step Two: Iterate over array of card struct 'hand[7]' and record
     * the frequency of each card pip from 'hand' in 'histogram' (freq
     * array).
     *
     * Step Three: Classify the hand based on pip frequency counts.
     * - 'quads': 4 cards each with the same pip value
     * - 'trips': 3 cards each with the same pip value
     * - 'pairs': 2 cards each with the same pip value
     * NOTE: it is important to to check from the BEST hand down to the
     * WORST!
     */
    unsigned short pairs = 0;
    unsigned short trips = 0;
    unsigned short quads = 0;
    int histogram[14] = {0};
    for (int i = 0; i < 7; i++) {
        histogram[hand[i].pips]++;
    }

    // count quads, trips, pairs
    for (int j = 1; j < 14; j++) {
        if (histogram[j] == 4) {
            quads++;
        } else if (histogram[j] == 3) {
            trips++;
        } else if (histogram[j] == 2) {
            pairs++;
        }
    }

    // classify hand
    if (quads > 0) {
        hand_results[four_ofa_kind].count++;
    } else if ((trips > 0 && pairs > 0) || trips > 1) {
        // the above condition covers "3 of a kind + one pair",
        // TWO "3 of a kinds", and "3 of a kind and two pairs"
        hand_results[full_house].count++;
    } else if (trips > 0) {
        hand_results[three_ofa_kind].count++;
    } else if (pairs >= 2) {
        hand_results[two_pair].count++;
    } else if (pairs == 1) {
        hand_results[one_pair].count++;
    } else {
        hand_results[no_pair].count++;
    }
}
