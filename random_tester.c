// Yehuda Gale and Joshua Skootsky, 2016
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "random.h"

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
    scanf("%d", &side_num);
    // assume the cube is of unit length, what is the length of the sides of the mini cubes?
    box_size = 1/side_num;
    
    printf("What is the random seed? Provide a 32 bit integer\n");
    scanf("%d", &random_seed);
    // use the seed function from the random.c file, which is extern in random.h
    seed(random_seed);
 
    // number is the number of mini hypercubes
    number = ipow(side_num, dimensions);
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
        rn = random_maker();
        // just put it in a kosher box
        which_box = floor(rn * number);
        // boxes is of size number. number is side_num to the power of dimension
        boxes[which_box]++; // increment the count of points in each boxes for each box when it is "filled"
    }
    // Now we have an array of boxes, filled with points 
    
    // Histogram those points by making a frequnecy count
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
    
    // Poisson distribution P(k) = exp(-<k><k>^k / k!
    // where <k> = points / number
    // 68% confidence interval of  N_k /N is P(k) / sqrt N, where N_k is the number of boxes
    //      with exactly k points.
    // if histogram is outside of the predicted bounds for more than 68% of the values of k,
    //      then the RNG does not pass this statistical test

    // do this in log space
    
    
    // print out closeness of created fit to random distribution
    
    return 0;
}
