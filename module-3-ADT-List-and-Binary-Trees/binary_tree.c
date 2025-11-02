/*
 * The ADT Binary Tree
 * by Kate Programmer
 * September 29, 2019
 * 
 * This material is also covered in <A Book on C> chapter 10.8
 * Binary Trees are useful because searches through notes can be done
 * in logarithmic time.
 */

#include <stdio.h>
#include <stdlib.h>

typedef char DATA;
typedef struct node {
    DATA d;
    struct node* left;
    struct node* right;
} NODE;
typedef NODE* BTREE;  // Binary Tree is a pointer of type NODE

void inorder(BTREE root) {
    // in-order tree traversal
    if (root != NULL) {
        inorder(root -> left);  // recur to the left
        printf("%c ", root -> d);
        inorder(root -> right); // recur to the right
    }
}

BTREE new_node(void) {
    return malloc(sizeof(NODE));
}

BTREE init_node(DATA d1, BTREE p1, BTREE p2) {
    // initialize DATA, left pointer and right pointer
    BTREE t;
    t = new_node();
    t -> d = d1;
    t -> left = p1;
    t -> right = p2;
    return t;  // return NODE pointer
}

BTREE create_tree(DATA a[], int i, int size) {
    if (i >= size) {
        return NULL;
    } else {
        return init_node(a[i],
                         create_tree(a, 2*i + 1, size),
                         create_tree(a, 2*i + 2, size));
    }
}

int main() {
    char d[] = {'a', 'b', 'c', 'd', 'e'};
    BTREE b;
    b = create_tree(d, 0, 5);
    inorder(b);  // should print 'd b e a c'
    printf("\n\n");
    return 0;
}
