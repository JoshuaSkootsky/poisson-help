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

// custom, numerically stable poisson distribution in log space
double log_poisson_d(int k, int lambda) {
        // exp and log are base "e"
        return exp( (k * log(lambda) )  - lambda - lgamma(k + 1) );
}

int main()
{
    int random_seed, i, j, which_box, dimensions, points, number, box_num, side_num, box_count, poisson_boxes;
    double box_size, rn;
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
    histogram = calloc( points, sizeof (int) ); // Need number of points b/c how histogram is built
    
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

    // Histogram those points by making a frequnecy count. Need as much memory as points.
    for (i = 0; i < points; i++) {
        // each pass increments the histogram
        box_count = boxes[i];
        histogram[box_count]++;
    }

    // Now we do math to calculate what the average distribution should be

    // do this in log space
    // Write Poisson mass probability like this:
    // f(k; lambda) = exp{k ln lambda - lambda - ln gamma (k + 1)
    // which uses Stirling's approximation, log rearranging, and k! = gamma(k+1)

    // C language has "lgamma" to calculate the log of gamma directly, C99 standard
    // see the function log_poisson_d(k, lambda) that I wrote for this purpose

    // note: i = number of points in the box, histogram[i] is the number of boxes that contain
    // that number of points inside 
    int num_points_in_box, num_boxes_same_points, k, lambda;
    double result;
    for (i = 0; i < number; i++) {
        if (histogram[i] != 0) {
            num_points_in_box = i;    
            num_boxes_same_points = histogram[i];
            
            k = num_points_in_box;
            lambda = num_boxes_same_points;
            
            result = log_poisson_d(k, lambda);
            printf("Result = %f, points in box = %d, boxes with that number of points = %d \n", result, i, histogram[i]);
        }
    }    
    
    // print out closeness of created fit to random distribution 
    return 0;
}
