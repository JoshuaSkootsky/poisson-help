// Yehuda Gale, 2016
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "random.h"

// I think there are problems with a custom factorial function that returns zero for numbers above 20... but I will fix this later
unsigned long int factorial(int num) {
    // really a table of the first 20 factorials would be better
    if (num > 20) { //20 factorial is the largest that can fit in int
        return 0;
    }
    else {
        int i;
        unsigned long int ret = 1; // get the max size on this
        while (num > 0) {
            ret *= i;
            num--;
        }
        return ret;
    }
}

// custom integer power function - uses exponentiation by squaring
int ipow(int base, int exp) {
    int value = 1;
    while (exp) { // while exp is nonzero
        if (exp & 1) { // if exp is odd
            value *= base;
        }
        exp >>= 1;
        base *= base;
    }
    return value;
}

int main()
{
    int random_seed, i, j, which_box, dimensions, points, number, box_num, side_num, box_count, poisson_boxes;
    double k, point, box_size, poisson, poisson_fact, rootNk, rn;
    int *histogram, *boxes;
    
    printf("What is the number of dimensions?\n");
    scanf("%d", &dimensions);
    printf("What is the number of points?\n");
    scanf("%d", &points);
    printf("How many minihypercubes per side length?\n");
    scanf("%d", &box_num);
    // assume the cube is of unit length, what is the length of the sides of the mini cubes?
    box_size = 1/box_num;
    
    printf("What is the random seed? Provide a 32 bit integer\n");
    scanf("%d", &random_seed);
    // use the seed function from the random.c file, which is extern in random.h
    seed(random_seed);
 
    // number is the number of mini hypercubes
    number = ipow(box_num, dimensions);
    printf("\nThis is how many mini-hypercubes you have: %d \n", number);
    printf("This is how many dimensions: %d \n", dimensions);
    printf("This is how many points: %d \n", points);

    // set the boxes and histogram initially to zero, so use calloc
    // boxes an array, each spot representing a mini hypercube.
    boxes =  calloc ( number, sizeof (int) ); // Each piece of memory in boxes represents a minihypercube
    histogram = calloc( number, sizeof (int) ); // Really, I should only need boxes number of memory...
    
    // Run the RNG a few times just to get away from your seed
    for (i = 0; i < 10; i++) {
        rn = random_maker();
    }
    
    // Generate the points, place into boxes.
    for (i = 0; i < points; i++) {
        which_box = 0;
        // dimensions is the number of dimensions the hypercubes exist in
        for (j = 1; j <= dimensions; j++) {
            // random_maker must return a number between 0 and 1
            rn = random_maker();
            // BAD CODE EXAMPLE DO NOT USE if
            // which_box += floor(rn * box_num) * j;
            // then maxvalue of which_box is ~35
            // which in a 10x10x10 cube means that 95% of the mini cubes will be empty
            // needs to range from 0 to number
            side_num = floor(rn * box_num);
            which_box += ipow(side_num, j);
        }
        // boxes is of size number. number is box_num to the power of dimension
        boxes[which_box]++; //increment the count of boxes for each box "filled"
        printf("box number: %d", which box);    
    }
    // Now we have a filled array of boxes, filled with points 
    
    // Histogram those points by making an ordered frequnecy count
    for (i = 0; i < number; i++) {
        // each pass increments the histogram
        box_count = boxes[i];
        histogram[box_count]++;
    }

    // this prints out the interesting values of the histogram for us
    for (i = 0; i < number; i++) {
        if (histogram[i] != 0) {
            printf("boxes with %d: %d\n", i, histogram[i]);
        }
    }
    
    // Now we do math to calculate what the average distribution should be
    // number is the number of boxes. Therefore k an average number of points in each box
    k = points / number;
    int total = 0;
    poisson_fact = exp(-k);
    // this implementation can only go up to 21
    for (i = 0; i < 21 && i < points; i++) { //above 21 I aproximate the poisson distribution as 0
        if (histogram[i] != 0) {
            rootNk = 1 / sqrt(histogram[i]); // using sqrt instead of pow 0.5
            poisson = (poisson_fact * ipow(k, i)) / factorial(i);
            if((histogram[i] / points >= poisson - poisson * rootNk) && (histogram[i] / points <= poisson + poisson * rootNk))
                poisson_boxes++;
            else {
                total++;
            }
        }
    }
    printf("%d\n", total);
    printf("%d\n", poisson_boxes);
    
    for(i = 21; i < points; i++) //since factorial is too large for int over 21, I assume poisson is 0
        if (histogram[i] == 0)
            poisson_boxes++;

    // this prints out the difference between our count and our expected count.
    // or, more accurately, should
    printf("%lf%%\n", 100 * ((double) poisson_boxes / (poisson_boxes + total)));
    return 0;
}
