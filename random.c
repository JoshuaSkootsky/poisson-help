// Joshua Skootsky and Yehuda Gale, 2016
#include <stdint.h>

//Yehuda used large prime numbers for both mult and add
static uint32_t mult = 236887691;   // multiplier
static uint32_t add = 961835761;    //aditive constant
static uint32_t random = 123456789; // basic seed 

double random_maker() {
    
    //random = mult * random + add;
    return (double) random/ 0xFFFFFFFF;
    // 8 Fs is the largest unsigned int
    // result should be between 0 and 1
}

void seed(int random_seed) {
    random = random_seed;
}
