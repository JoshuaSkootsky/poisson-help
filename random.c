// Yehuda Gale
// Joshua Skootsky
// Returns a number between 0 and 1, with a max cycle of 2^32
#include <stdint.h> // using guarenteed and specified 32 bit numbers

static uint32_t mult = 236887691;           // multiplier
static uint32_t add = 961835761;            //aditive constant

double random_maker(uint32_t rand32)
{
    rand32 = rand32 * mult + add;
    return (double) rand32 / 0xFFFFFFFF;
    // largest 32 bit unsigned int is 8 Fs in hexadecidaml;
}
