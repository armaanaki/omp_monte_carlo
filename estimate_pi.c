#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void usage(char* prog_name);

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
        hits++;
    }

    /* finalize monte carlo guess then print it */

    //pi_estimate = 4*number_hits/(double) number_throws;
    // printf("pi guess: %.4f\n", pi_estimate);
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
