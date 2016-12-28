/* 
 * File:  radix.c
 * Author: Jake Day
 * Class: COEN 12
 * Instructor: Atkinson
 * Section: T 5:15-8pm
 * Created on May 3, 2016, 5:29 PM
 * Description: This program implements a deque abstract data type using a circular, doubly-linked list with a sentinel or dummy node
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deque.h"

struct node {
    struct node *next;
    struct node *prev;
    int data;
};

struct deque {
    int count;
    struct node *dummy;
};

/*
 * Big-O Notation: O(1)
 * Returns a pointer to a new deque
 */
DEQUE *createDeque(void) {
    DEQUE *dp;

    dp = malloc(sizeof (DEQUE));
    assert(dp != NULL);

    dp->count = 0;

    dp->dummy = malloc(sizeof (struct node));
    assert(dp->dummy != NULL);

    dp->dummy->next = dp->dummy;
    dp->dummy->prev = dp->dummy;

    return dp;
}

/*
 * Big-O Notation: O(n)
 * Deallocates memory associated with the deque pointed to by dp
 */

void destroyDeque(DEQUE *dp) {
    assert(dp != NULL);

    struct node *pDel;

    for (int i = 0; i < dp->count; i++) {
        pDel = dp->dummy->next;
        dp->dummy->next = pDel->next;
        free(pDel);
    }
}

/*
 * Big-O Notation: O(1)
 * Returns the number of items in the deque pointed to by dp
 */
int numItems(DEQUE *dp) {
    assert(dp != NULL);

    return dp->count;
}

/*
 * Big-O Notation: O(1)
 * Adds x as the first item in the deque pointed to by dp
 */
void addFirst(DEQUE *dp, int x) {
    assert(dp != NULL);

    struct node *pAdd;
    pAdd = malloc(sizeof (struct node));
    assert(pAdd != NULL);

    pAdd->data = x;

    pAdd->prev = dp->dummy;
    pAdd->next = dp->dummy->next;

    dp->dummy->next->prev = pAdd;
    dp->dummy->next = pAdd;

    dp->count++;
}

/*
 * Big-O Notation: O(1)
 * Adds x as the last item in the deque pointed to by dp
 */
void addLast(DEQUE *dp, int x) {
    assert(dp != NULL);

    struct node *pAdd;
    pAdd = malloc(sizeof (struct node));
    assert(pAdd != NULL);

    pAdd->data = x;

    pAdd->next = dp->dummy;
    pAdd->prev = dp->dummy->prev;
    
    dp->dummy->prev->next = pAdd;
    dp->dummy->prev = pAdd;

    dp->count++;
}

/*
 * Big-O Notation: O(1)
 * Removes and returns the first item in the deque pointed to by dp; the deque must not be empty
 */
int removeFirst(DEQUE *dp) {
    assert(dp != NULL);

    int data;

    struct node *pDel = dp->dummy->next;
    struct node *tempNext = pDel->next;

    data = pDel->data;

    dp->dummy->next = tempNext;
    
    tempNext->prev = dp->dummy;
    tempNext->next = pDel->next->next;

    free(pDel);

    dp->count--;

    return data;
}

/*
 * Big-O Notation: O(1)
 * Removes and returns the last item in the deque pointed to by dp; the deque must not be empty
 */
int removeLast(DEQUE *dp) {
    assert(dp != NULL);

    int data;

    struct node *pDel = dp->dummy->prev;
    struct node *tempLast = pDel->prev;

    data = pDel->data;

    dp->dummy->prev = pDel->prev;
    
    tempLast->next = dp->dummy;
    dp->dummy->prev = tempLast;

    free(pDel);

    dp->count--;
    
    return data;
}

/*
 * Big-O Notation: O(1)
 * Returns, but does not remove, the first item in the deque pointed to by dp; the deque must not be empty
 */
int getFirst(DEQUE *dp) {
    assert(dp != NULL && dp->count != 0);

    return dp->dummy->next->data;
}

/*
 * Big-O Notation: O(1)
 * Returns, but does not remove, the last item in the deque pointed to by dp; the deque must not be empty
 */
int getLast(DEQUE *dp) {
    assert(dp != NULL && dp->count != 0);

    return dp->dummy->prev->data;
}