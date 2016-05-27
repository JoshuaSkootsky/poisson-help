Copyright 2016, Joshua Skootsky and Yehuda Gale
This code may be licensed under the terms and conditions of the Apache 2.0
License. A copy of this licence may be found included along with this code, or, in the case of some kind of disaster, accessed online on the Apache Foundation website: http://www.apache.org/licenses/LICENSE-2.0

In the absence of such licensure, copyright over created works prevents their unauthorized usage. So, hold on to your copy of the license and this README.md if you want to use this program. You may use this program according to the terms and conditions of the Apache 2.0 License.


# poisson-help
Have you ever wondered how well a randomly generated set of points in n-dimensional space fills the n-dimensional hypercubes? Is such randomness in line with the expected Poisson distribution? This program generates such a set of points, according to your specification, using a random number generator.

You can use the included random number generator, replace it with your own, or replace it with a totally bogus and crippled random number generator.

You can do that, because then the program will test your implementation of an RNG for conformation to the expected mathematical distribution of points in n-space to the Poisson distribution.

#How to run:

Like this:

$ ./random_tester_exe < random_tester_input

You can also do it like this:

$ ./random_tester_exe

and get text prompts for the program. You can then copy and paste your text inputs into an input file to test different implementations of RNGs.

To do that, you will need to recompile the program

#How to compile

On a Mac, it's easy, because I made a Makefile

$ make random_tester

You may want to edit the Makefile to use your favorite, standards conforming C compiler
