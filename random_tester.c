// Yehuda Gale, 2016
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "random.h"
#define big 4294967296.0 //range of random number generator 2^32

// I think there are problems with a custom factorial function that returns zero for numbers above 20... but I will fix this later
unsigned long int factorial(int num)
{
    if (num > 20) //20 factorial is the largest that can fit in int
    {
        return 0;
    }
    else{
        int i;
        unsigned long int ret = 1;
        for (i = num; i > 0; i--)
        {
            ret *= i;

        }
        return ret;
    }
}


int main(int argc, char const *argv[])
{
    int i, j, box_number;
    int dimensions, points, number, box, poisson_boxes = 0;
    double k, cube, fact, point, box_size1, poisson, poisson_fact, rootNk;
    unsigned int rn; //random number
    int *histogram;
    int *boxes;
    int *dimension_factor;
    
    printf("What is the number of dimensions?\n");
    scanf("%d", &dimensions);
    printf("What is the number of points?\n");
    scanf("%d", &points);
    printf("What are the lengths of the hyper-cube sides?\n");
    scanf("%lf", &cube);
    printf("How many boxes per side?\n");
    scanf("%d", &box);
    printf("What is the random seed?\n");
    scanf("%u", &rn);
    // number is the number of mini hypercubes
    number = pow(box, dimensions);
    // fact is the inverse of the biggest number we can deal with
    fact = (1 / big) * cube;
    box_size1 = box / cube;

    /*allocate memory*/
    dimension_factor = malloc (sizeof (int) * dimensions);
    boxes = malloc( sizeof (int) * number);
    histogram = malloc( sizeof(int) * points);
    dimension_factor[0] = 1;
    for (i = 1; i < dimensions; ++i)
        dimension_factor[i] = dimension_factor[i - 1] * box;
    for (i = 0; i <= number; ++i)
        boxes[i] = 0;
    for (i = 0; i < 10; ++i) //run the rng to try to mitigate seed picking biase
        rn = random_maker(rn);
    for (i = 0; i <= points; ++i)
    {
        box_number = 0;
        for (j = 0; j < dimensions; ++j)
        {
            rn = random_maker(rn);
            point = rn * fact;
            //printf("%lf\n", point);
            box_number += floor(point * box_size1) * dimension_factor[j];
        }
        boxes[box_number]++;
    }
    // Let's assume the bug is beyond this point
    for (i = 0; i < points; ++i) {
        histogram[i] = 0;
    }
    for (i = 0; i < number; ++i) { //create the histogram
        histogram[boxes[i]]++;
    }
    for (i = 0; i < points; ++i) { //use this for more info
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
    /*
    for(i = 21; i < points; i++) //since factorial is too large for int over 21, I assume poisson is 0
        if (histogram[i] == 0)
            poisson_boxes++;*/
    printf("%lf%%\n", 100 * ((double) poisson_boxes / (poisson_boxes + total)));
    return 0;
}
