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
    int seed, i, j, box_number;
    int dimensions, points, number, box, poisson_boxes = 0;
    double k, point, box_size1, poisson, poisson_fact, rootNk;
    double rn; //random number
    int *histogram;
    int *boxes;
    int *dimension_factor;
    
    printf("What is the number of dimensions?\n");
    scanf("%d", &dimensions);
    printf("What is the number of points?\n");
    scanf("%d", &points);
    printf("How many boxes per side?\n");
    scanf("%d", &box);
    
    printf("What is the random seed? Provide a 32 bit integer\n");
    scanf("%d", &seed);
    // divide the 32 bit integer by the largest unsigned 32 bit integer
    rn = (double) seed / 0xFFFFFFFF;
    
    // number is the number of mini hypercubes
    number = pow(box, dimensions);
    printf("\n %d \n", number);

    // allocate memory
    dimension_factor = malloc (dimensions * sizeof (int*) );
    // set the boxes initially to zero, so use calloc
    // boxes an array, each spot representing a mini hypercube.
    puts("Assigning memory to boxes \n");
    boxes =  calloc ( number, sizeof (int) );
    puts("It worked to assign memory to boxes!\n");
    
    // may as well do the same for the histograms
    histogram = calloc( points, sizeof (int) );

    // Why does this happen?
    dimension_factor[0] = 1;
    for (i = 1; i < dimensions; i++) {
        dimension_factor[i] *= box;
    }
    
    // Run the RNG a few times just to get away from your seed
    for (i = 0; i < 10; i++) {
        rn = random_maker(rn);
    }

    // Now something happens
    // the boxes array was set to zero with calloc
    
    for (i = 0; i < points; ++i)
    {
        box_number = 0;
        // dimensions is the number of dimensions the hypercubes exist in
        for (j = 0; j < dimensions; j++)
        {
            // random_maker must return a number between 0 and 1
            rn = random_maker(rn);
            // if I'm using the random number directly, I don't need a "point" variable
            point = rn;
            
            // wait what the heck 
            box_number += floor(point * box_size1) * dimension_factor[j];
        }
        boxes[box_number]++;
    }
    
    // number is the number of mini hypercubes
    // boxes is an indexed array of all the hypercubes
    for (i = 0; i < number; i++) {
        //create the histogram
        // how op
        histogram[boxes[i]]++;
    }
    for (i = 0; i < points; i++) { //use this for more info
        if (histogram[i] != 0) {
            printf("boxes with %d: %d\n", i, histogram[i]);
        }
    }
    // number is the number of boxes. Therefore k an average
    // So, let's take a look at this
    k = points / number;
    int total = 0;
    poisson_fact = exp(-k);
    for (i = 0; i < 21 && i < points; i++) { //above 21 I aproximate the poisson distribution as 0
        if (histogram[i] != 0) {
            rootNk = 1 / pow(histogram[i], 0.5);
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
    printf("%lf%%\n", 100 * ((double) poisson_boxes / (poisson_boxes + total)));
    return 0;
}
