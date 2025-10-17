/*
 * seven-card-stud.c
 * Created on: Fri 17 Oct 2025
 * Last Updated: Fri 17 Oct 2025
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

    // initialize array of struct 'card'
    card deck_of_cards[DECK];

    int i = 0;  // index for 'deck_of_cards[DECK]'

    // Outer loop: iterate through all suits from club: 0 to spade: 3
    for (suit s = club; s < SUIT_COUNT; s++) {
        // Inner loop: iterate through all pipes from ace: 1 to king: 13
        for (cname p = ace; p < NAME_COUNT; p++) {
            // assign current suit and pip value to current card
            deck_of_cards[i].c_suit = s;
            deck_of_cards[i].pips = p;
            i++;
        }
    }

    const char *suit_names[] = {"Clubs", "Diamonds", "Hearts", "Spades"};
    const char *pip_names[] = {
        "Invalid", "Ace", "Two", "Three", "Four", "Five", "Six", "Seven",
        "Eight", "Nine", "Ten", "Jack", "Queen", "King"
    };
    printf("--- Initialized Deck of Cards ---\n");
    for (i = 0; i < DECK; i++) {
        printf("Card %2d: %-5s of %s\n", i,
               pip_names[deck_of_cards[i].pips],
               suit_names[deck_of_cards[i].c_suit]);
    }

    printf("--- Four of a Kind ---\n");
    printf("Combinations: %d\t",
           scs_poker_hands[four_ofa_kind].combinations);
    // specify 8 decimal places of precision (default is 6)
    printf("Probability: %.08f\n",
           scs_poker_hands[four_ofa_kind].probability);

    return 0;
}

// TODO 0: add deck shuffling function

// TODO 1: Move deck initialization and population to separate function

/* TODO 2: implement 7-card poker hand analysis (pips only)
 * I first thought about sorting the pip values using 'qsort()'
 * from <stdlib.h>, but this operation is O(n log n) time complexity.
 * For small arrays of just 7 values, this will happen almost
 * instantaneously.
 *
 * But a better approach would be to use a 'frequency array', aka
 * HISTOGRAM, and just count the pip occurrences in a single pass. This has
 * time complexity O(n). For 7 values, you won't really be able to tell a
 * difference between O(n) and O(n log n), but the HISTOGRAM approach is
 * better because it can be implemented with less code. First create your
 * histogram:
 *
 * // indices 1 to 13 will store pip counts for Ace:1 to King: 13
 * int pip_counts[14] = {0};  // initialize empty array
 *
 * Now assuming your 7 card pips are [5, 10, 5, 13, 10, 5, 2]
 *
 * // 'deck_of_cards' is an array of struct card from main() above
 * for (int i = 0; i < 7; i++) {
 *     pip_counts[deck_of_cards[i].pips]++;
 * }
 *
 * After this loop, your pips_count array will look like:
 * [0, 0, 1, 0, 0, 3, 0, 0, 0, 0, 2, 0, 0, 1]
 *
 * pip_counts[2] = 1, pip_counts[5] = 3, pip_counts[10] = 2,
 * pip_counts[13] = 1
 * Now all you have to do is iterate from 1 to 13 and check the counts
*/
