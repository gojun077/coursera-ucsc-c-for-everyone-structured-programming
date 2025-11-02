/*
 * The ADT List
 * by Shelly Sysmom
 * Created on: Aug 29, 2019
 * Updated on: Sun 02 Nov 2025 by gopeterjun@naver.com
 *
 * Note that searching for an element in a list has time complexity O(n)
 * whereas searching for an element in an array is O(1)
 *
 * However, list ADT offers greater flexibility over an array; for
 * example, adding and removing elements is easier in a list.
 *
 * <stdio.h> is needed for 'printf()'
 * <stdlib.h> is needed for 'malloc()'
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    int data;
    struct list *next;
} list;

int is_empty(const list *l) {
    return (l == NULL);
}

list* create_list(int d) {
    list* head = malloc(sizeof(list));
    head -> data = d;
    head -> next = NULL;
    return head;
}

list* add_to_front(int d, list* h) {
    list* head = create_list(d);
    head -> next = h;  // 'next' now points to the old head, 'h'
    return head;
}

list* array_to_list(int d[], int size) {
    list* head = create_list(d[0]);
    for (int i = 1; i < size; i++) {
        head = add_to_front(d[i], head);
    }
    return head;
}

void print_list(list *h, char *title) {
    printf("%s\n", title);
    while (h != NULL) {
        printf("%d :", h -> data);
        h = h -> next;
    }
}

int main() {
    list* head = NULL;
    int data[6] = {2,3,5,7,8,9};
    head = array_to_list(data, 6);
    print_list(head, "multi element list");
    printf("\n\n");
    return 0;
}
