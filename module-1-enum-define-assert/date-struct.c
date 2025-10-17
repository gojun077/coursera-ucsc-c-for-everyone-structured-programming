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
#include <assert.h>

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

// function signatures (stubs)
date nextday(date dt);
void printdate(date dt);
int are_dates_equal(date d1, date d2);

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

    // assert statements
    assert(are_dates_equal(nextday(date0), (date){ january, 2 }));
    assert(are_dates_equal(nextday(date1), (date){ march, 2 }));
    assert(are_dates_equal(nextday(date2), (date){ march, 15 }));
    assert(are_dates_equal(nextday(date3), (date){ november, 1 }));
    assert(are_dates_equal(nextday(date4), (date){ january, 1 }));

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

date nextday(date dt) {
    // create new 'date' struct to store results of nextday()
    date next_dt;

    // --- How to access struct members ---
    // Because 'dt' is a regular variable (not a pointer), we use the
    // dot (.) operator.
    // If 'dt' were a pointer (date *dt), we would use the arrow (->)
    // operator, like so: next_dt.m = dt -> m;

    // First, copy the current date into our new date variable.
    next_dt.m = dt.m;
    next_dt.d = dt.d;

    // Now, let's figure out the number of days in the current month.
    // Note: This simple version does not account for leap years.
    int days_in_month;
    switch (dt.m) {
        case january:
        case march:
        case may:
        case july:
        case august:
        case october:
        case december:
            days_in_month = 31;
            break;
        case april:
        case june:
        case september:
        case november:
            days_in_month = 30;
            break;
        case february:
            days_in_month = 28; // Ignoring leap years for simplicity
            break;
    }

    // Now we can calculate the next day.
    if (dt.d < days_in_month) {
        // It's not the end of the month, so just increment the day.
        next_dt.d = dt.d + 1;
    } else {
        // It's the end of the month, so reset the day to 1.
        next_dt.d = 1;
        // And increment the month:
        next_dt.m = (month)(dt.m + 1) % 12;
    }

    return next_dt;
}

/*
 * @brief Prints a date struct in a readable format.
 * @param dt The date to print.
*/
void printdate(date dt) {
    // Array of month names for easy printing
    const char *month_names[] = {
        "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    // We use the dot (.) operator here as because 'dt' is a struct
    // variable.
    printf("%s %d\n", month_names[dt.m], dt.d);
}

/*
 * @brief Compares two date structs for equality.
 * @param d1 The first date.
 * @param d2 The second date.
 * @return 1 (true) if the dates are the same, 0 (false) otherwise.
 *
 * Note: you cannot use 'assert()' directly with structs; i.e. the
 * following WON'T WORK:
 *
 * assert(nextday(date0) == (date){ january, 2 });
 * compiler error:
 * "invalid operands to binary == (have ‘date’ and ‘date’)"
 * assert only evaluates '0' (false) and '1' true
 */
int are_dates_equal(date d1, date d2) {
    // To be equal, both the day and the month must match.
    return (d1.d == d2.d) && (d1.m == d2.m);
}
