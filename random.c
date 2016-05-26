// Yehuda Gale
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "random.h"
unsigned int random_maker(unsigned int random_number)
{
    /*I seperated this into it's own file
     so it would be easy to change
     the method of random number generation*/
     //I used large prime numbers for both mult and add
    int mult = 236887691;   // multiplier
    int add = 961835761;  //aditive constant
    // Commenting out this line cripples the random number generator
    // random_number = random_number * mult + add;
    return random_number;
}
