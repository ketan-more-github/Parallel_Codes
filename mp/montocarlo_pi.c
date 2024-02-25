#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_POINTS 1000000

int main() {
    int i, count = 0;
    double x, y, pi;

    // Seed the random number generator
    srand(time(NULL));

    // Perform Monte Carlo simulation
    for (i = 0; i < NUM_POINTS; i++) {
        // Generate random coordinates (x, y) in the range [0, 1]
        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;

        // Check if the point (x, y) is inside the unit circle
        if (x * x + y * y <= 1) {
            count++;
        }
    }

    // Estimate the value of Pi using the Monte Carlo method
    pi = 4.0 * count / NUM_POINTS;

    // Print the estimated value of Pi
    printf("Estimated value of Pi: %lf\n", pi);

    return 0;
}
