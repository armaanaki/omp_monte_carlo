#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <random>

void usage(char* prog_name);
double doubleRand(double min, double max);

int main(int argc, char* argv[]) {
    unsigned long long throws;
    unsigned long long hits = 0;
    long thread_count;
    double pi_estimate;

    // get required args
    if (argc != 2) usage(argv[0]);
    throws = strtol(argv[1], NULL, 10);
    if (throws < 1) usage(argv[0]);


# pragma omp parallel for private(throws) reduction(+: hits)
    for (int i = 0; i < throws; i++) {
        /* generate x and y --- note that this is not a balanced random number generator due to the nature of rand()*/
        double x = doubleRand(-1, 1);
        double y = doubleRand(-1, 1);

        double distance_squared = x*x + y*y;
        if (distance_squared <= 1) hits++;
    }

    /* finalize monte carlo guess then print it */
    pi_estimate = 4*hits/(double) throws;
    printf("pi guess: %.6f\n", pi_estimate);
}

/*
 * Function: 	doubleRand
 * Purpose:	 	generate a random number in a threadsafe fashion
 * In args:		min, max
 * DISCLAIMER:	this solution was found from the following: https://stackoverflow.com/questions/29709897/c-thread-safe-uniform-distribution-random-number-generation
 */
double doubleRand(double min, double max) {
    thread_local std::mt19937 generator(std::random_device{}());
    std::uniform_real_distribution<double> distribution(min, max);
    return distribution(generator);
}

/*
 * Function:    usage
 * Purpose:     print usage if program run incorrectly
 * In args:     prog_name
 */

void usage(char* prog_name) {
    fprintf(stderr, "usage: %s  <number of throws>\n", prog_name);
    fprintf(stderr, "number of throws must be greater than 0\n");
    exit(1);
}
