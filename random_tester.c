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


int main()
{
    int seed, i, j, which_box, dimensions, points, number, box_num, box_count, poisson_boxes = 0;
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
    scanf("%d", &seed);
    // divide the 32 bit integer by the largest unsigned 32 bit integer
    rn = (double) seed / 0xFFFFFFFF;
    
    // number is the number of mini hypercubes
    number = pow(box_num, dimensions);
    printf("\n %d \n", number);

    // set the boxes and histogram initially to zero, so use calloc
    // boxes an array, each spot representing a mini hypercube.
    boxes =  calloc ( number, sizeof (int) ); // Each piece of memory in boxes represents a minihypercube
    histogram = calloc( number, sizeof (int) ); // Really, I should only need boxes number of memory...
    
    // Run the RNG a few times just to get away from your seed
    for (i = 0; i < 10; i++) {
        rn = random_maker(rn);
    }
    
    // Generate the points, place into boxes.
    for (i = 0; i < points; i++) {
        which_box = 0;
        // dimensions is the number of dimensions the hypercubes exist in
        for (j = 1; j <= dimensions; j++) {
            // random_maker must return a number between 0 and 1
            rn = random_maker(rn);
            printf("rn: %f\n", rn);
            which_box += floor(rn * box_num * j);
            printf("which_box: %d\n", which_box);
        }
        boxes[which_box]++; //increment the count of boxes for each box "filled"
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
            poisson = (poisson_fact * pow(k, i)) / factorial(i);
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
