/*
 * date-struct.c
 * Created on: Fri 17 Oct 2025
 * gopeterjun@naver.com
 * C for Everyone: Structured Programming
 * Module 1 Assignment
 *
 * Write enumerated types that supports dates—such as december 12. Then add
 * a function that produces a next day. So nextday(date) of december 12 is
 * december 13. Also write a function printdate(date) that prints a date
 * legibly.The function can assume that February has 28 days and it most
 * know how many days are in each month. Use a struct with two members; one
 * is the month and the second is the day of the month—an int (or short).
 *
 * Then print out the date January 1 and print the next day Jan 2. Do this
 * for the following dates: February 28, March 14, October 31, and December
 * 31.
*/

#include <stdio.h>

enum month {
    january,
    february,
    march,
    april,
    may,
    june,
    july,
    august,
    september,
    october,
    november,
    december
};

typedef enum month month;

typedef struct date {
    month m;
    short d;
} date;

date nextday(date dt);
void printdate(date dt);

int main(void) {  // main takes no arguments
    date date0 = { january, 1};
    date date1 = { february, 28};
    date date2 = { march, 14 };
    date date3 = { october, 31};
    date date4 = { december, 31};

    printf("======================\n");
    printf("Intial Dates: \n");
    printf("date0: ");
    printdate(date0);
    printf("date1: ");
    printdate(date1);
    printf("date2: ");
    printdate(date2);
    printf("date3: ");
    printdate(date3);
    printf("date4: ");
    printdate(date4);
    printf("======================\n");

    printf("\nCalculating the next date for each date above...\n");

    date next_date0 = nextday(date0);
    date next_date1 = nextday(date1);
    date next_date2 = nextday(date2);
    date next_date3 = nextday(date3);
    date next_date4 = nextday(date4);

    printf("======================\n");
    printf("The day after date0 is: ");
    printdate(next_date0);  // expected: 'January 2'
    printf("The day after date1 is: ");
    printdate(next_date1);  // expected: 'March 2'
    printf("The day after date2 is: ");
    printdate(next_date2);  // expected: 'March 15'
    printf("The day after date3 is: ");
    printdate(next_date3);  // expected: 'November 1'
    printf("The day after date4 is: ");
    printdate(next_date4);  // expected: 'January 1'

    return 0;
}
