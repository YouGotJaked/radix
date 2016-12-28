/* 
 * File:  radix.c
 * Author: Jake Day
 * Class: COEN 12
 * Instructor: Atkinson
 * Section: T 5:15-8pm
 * Created on May 10, 2016, 5:29 PM
 * Description: This function uses a sorting algorithm called radix sorting. It reads in a sequence of non-negative integers from the standard input and then writes them in the sorted order on the standard output.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "deque.h"

//define a radix of r = 10
#define r 10

int main(int argc, char** argv) {
    DEQUE *list = createDeque();
    DEQUE * bins[r];

    int input, max, maxDigits, binNum, temp, div = 1;

    printf("Enter some non-negative integers to sort. Press enter after each number. Return any other key to exit data entry:\n");

    //reads user input until an invalid entry is entered and adds them to the deque
    while (scanf("%d", &input) == 1) {
        //makes sure the input is non-negative
        if (input < 0) {
            printf("Please enter a non-negative number\n");
            return -1;
        }
        
        //finds the maximum input
        if (input > max) {
            max = input;
        }

        addFirst(list, input);
    }
    
    //creates bins for the size of the radix being used
    for (int i = 0; i < r; i++) {
        bins[i] = createDeque();
    }

    //number of digits in the largest value
    maxDigits = ceil((log(max + 1) / log(r)));

    //loops through all the digits up until the maximum
    for (int i = 0; i < maxDigits; i++) {
        //takes all the numbers and puts them into their respective bins
        while (numItems(list) != 0) {
            temp = removeFirst(list);
            binNum = (temp / div) % 10;
            addLast(bins[binNum], temp);
        }
        
        //takes numbers from their buckets and adds them back to the list
        for (int j = 0; j < r; j++) {
            while (numItems(bins[j]) != 0) {
                temp = removeLast(bins[j]);
                addFirst(list, temp);
            }
        }

        div *= 10;
    }
    
    printf("The sorted list:\n");

    //prints out the sorted list
    while (numItems(list) != 0) {
        temp = removeLast(list);
        printf("%d\n", temp);
    }
    
    //destroys the deque when finished
    destroyDeque(list);

    return (EXIT_SUCCESS);
}