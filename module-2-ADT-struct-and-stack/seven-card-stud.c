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
 * Deal out 7-card hands and evaluate the probability that a hand has no
 * pair, one pair, two pair, three of a kind, full house (3 of a kind + 1
 * pair) and 4 of a kind.
 *
 * This is a Monte Carlo method to get an approximation to these
 * probabilities.  Use at least 1 million randomly generated hands.
 *
 * Check against probabilities found in a standard table for Seven
 * Card Stud Poker https://wizardofodds.com/games/poker/
*/

#include <stdio.h>

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

enum suit {
    club = 'c',
    diamond = 'd',
    heart = 'h',
    spade = 's'
};
typedef enum suit suit;

// stats for a single hand
typedef struct hand_stats {
    hand name;
    int combinations;
    double probability;
} stats;

// 'card' struct containing attributes 'suit' and 'pip'
struct card {
    short pips;
    suit c_suit;
};

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

    printf("--- Four of a Kind ---\n");
    printf("Combinations: %d\t",
           scs_poker_hands[four_ofa_kind].combinations);
    // specify 8 decimal places of precision (default is 6)
    printf("Probability: %.08f\n",
           scs_poker_hands[four_ofa_kind].probability);

    return 0;
}
