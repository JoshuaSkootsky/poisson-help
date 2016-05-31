CFLAGS=-Wall

random_tester: ; gcc -o random_tester -O2 -std=c99 -pedantic random_tester.c random.c
