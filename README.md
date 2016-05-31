Copyright Joshua Skootsky and Yehuda Gale, 2016

This code may be licensed under the terms and conditions of the Apache 2.0
License. A copy of this licence should accompany your copy of this program, and may be accessed online on the Apache Foundation website: http://www.apache.org/licenses/LICENSE-2.0

In the absence of such licensure, copyright over created works prevents their unauthorized usage. So, hold on to your copy of the LICENSE file, as well as this README.md file, because they allow you to use this program according to the terms and conditions of the Apache 2.0 License.

# poisson-help
Have you ever wondered how well a randomly generated set of points in n-dimensional space fills the n-dimensional hypercubes? Have you ever wanted to statistically test your own random number generator?

This program generates such a set of points, according to your specification, using a random number generator.

You can use the included random number generator, replace it with your own, or replace it with a totally bogus and crippled random number generator. The program will test the goodness of the RNG.

The program will test your implementation of an RNG for conformation to the expected mathematical distribution of points in n-space to the Poisson distribution.

#How to run:

Like this:

`$ ./random_tester < random_tester.inp`

You can also do it like this:

`$ ./random_tester`

and get text prompts for the program. You can then copy and paste your text inputs into an input file to test different implementations of RNGs.

To do that, you will need to recompile the program

#How to compile

A Makefile is included in this directory

$ make random_tester

You may want to edit the Makefile to use your favorite, standards conforming C compiler.

The test.sh script compiles the program and runs it with sample input.

# Valgrind

Check for memory leaks using Valgrind like this:

valgrind --leak-check=yes ./random_tester

Very useful for developing programs in C.


