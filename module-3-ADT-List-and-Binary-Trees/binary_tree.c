/*
 * The ADT Binary Tree
 * by Kate Programmer
 * September 29, 2019
 *
 * Updated on: Sun 02 Nov 2025
 * Updated by: gopeterjun@naver.com
 *
 * This material is also covered in <A Book on C> chapter 10.8
 * Binary Trees are useful because searches through notes can be done
 * in logarithmic time.
 *
 * This program introduces the "In-order Traversal", which visits tree
 * nodes in the order: "Left subtree, root, Right subtree". This traversal
 * is mainly used for Binary Search Trees, where it returns values in
 * ascending order.
 *
 * It is a kind of Depth First Search (DFS), where each node is visited
 * in a certain order.
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
    // In-order tree traversal
    // (1) Traverse left subtree
    // (2) Traverse Root node
    // (3) Traverse Right subtree
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

/*
 *                            +-------+
 *                          |   a   |
 *                +---+    |--------|     +---+
 *               |- b |-----        -|    | c |
 *              |-+---|              -----+---+
 *             |-     ---|
 *        +---+-        ++--+
 *        | d |         | e |
 *        +---+         +---+
 *
 * The is my crude ASCII drawing of the binary tree represented by the
 * character array {'a', 'b', 'c', 'd', 'e'}
 *
 * On the call stack (LIFO), we will have the following recursive calls to
 * inorder():
 *
 * 1. [ inorder('a') ]                      // call from main
 * 2. [ inorder('b'), inorder('a') ]          // a calls left child
 * 3. [ inorder('d'), inorder('b'), inorder('a') ] // b calls left child
 *    - inorder('d') prints 'd', no right child, returns
 * 4. [ inorder('b'), inorder('a') ]          // resume in b, print b
 * 5. [ inorder('e'), inorder('b'), inorder('a') ] // b calls right child
 *    - inorder(e) prints e, no right child, returns
 * 6. [ inorder('b'), inorder('a') ]          // b finishes, return to a
 * 7. [ inorder('a') ]                      // print a, call right child
 * 8. [ inorder('c'), inorder('a') ]          // a calls right child
 *    - inorder('c') prints c, no right child, returns
 * 9. [ inorder('a') ]                      // a finishes, return to main
 *
 * So the stack holds inorder('a') the whole time; inorder('b') only
 * returns after both 'd' and 'e' are processed, and then 'a' can continue
 * with its right subtree.
 *
 * Note that body of 'inorder()' takes 3 actions:
 *
 *    if (root != NULL) {
 *      inorder(root -> left);  // recur to the left
 *      printf("%c ", root -> d);  // print DATA d
 *      inorder(root -> right);  // recur to the right
 *    }
 *
 */
