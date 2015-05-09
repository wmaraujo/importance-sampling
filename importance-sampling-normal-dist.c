/*
 * Author:  Wesley Araujo
 * License: Creative Commons Attribution 4.0
 *          http://creativecommons.org/licenses/by/4.0/
 *
 * Importance sampling simulation to find the probability
 * of a standard normal random variable exceeding 8
 * P(X > 8), where X is distributed according to the standard normal distribution.
 *
 * True value is about 6.220960574*10^-16
 * Obtained with WolframAlpha:
 * http://www.wolframalpha.com/input/?i=1+-+CDF[NormalDistribution[0%2C+1]%2C+8]
 * Note, it is required to press "more digits" on the WolframAlpha page to
 * get better accuracy and precession.
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void    seed(void);
double  uniformVar(void);
double  standardNormalVar(void);
double  normalVar(double mean, double sigma);
double  normal8var(void);

#define DEFAULT_N 155000000

int main(int argc, char* argv[]) {
    double sum = 0;
    double sumSquared = 0;
    double x;
    unsigned int n = DEFAULT_N;

    seed();
    puts("Simulation begins");
    for (unsigned int i=0; i < n; i++) {
        x = normal8var();
        if (x >= 8) { // indicator function
            sum += exp(32 - 8*x);
            sumSquared += exp(64 - 16*x); // used to calculate variance
        }
    }
    double mean =       sum/n;
    double variance =   (sumSquared - sum*sum/n) / (n - 1);
    double lower =      mean - 1.96*sqrt(variance/n);
    double upper =      mean + 1.96*sqrt(variance/n);
    printf("The parameter estimate is %.15e\n"
           "The variance is %.15e\n"
           "95%% CI: {%.15e, %.15e}\n", mean, variance, lower, upper);
    return EXIT_SUCCESS;
}

void seed(void) {
    FILE* urandom = fopen("/dev/urandom","r");
    if(urandom == NULL) {
        perror("Could not open urandom seed file:");
        exit(EXIT_FAILURE);
    }
    unsigned int seedval;
    if (fread(&seedval, sizeof(seedval), 1, urandom) < 1){
        perror("Could not read urandom seed file:");
        exit(EXIT_FAILURE);
    }
    srandom(seedval);
}

// generates uniform random number from 0 to 1
double uniformVar(void) {
    return random() / (double)RAND_MAX;
}

/*
 * generates normal random number with mean 0 and variance 1 (standard normal),
 * using the marsaglia polar method, a more efficient version of the
 * box-muller transform.
 * http://en.wikipedia.org/wiki/Marsaglia_polar_method
 *
 * Source of algorithm implementation:
 * S. M. Ross, "Generating Continuous Random Variables", in Simulation, 5th ed.
 * Waltham, Massachusetts: Academic Press, 2012, ch. 5, sec. 3, pp. 83
 */
double standardNormalVar(void) {
    double v1, v2, s = 2;
    while (s > 1) {
        v1 = 2*uniformVar() - 1;
        v2 = 2*uniformVar() - 1;
        s = v1*v1 + v2*v2;
    }
    return v1*sqrt(-2*log(s)/s);
}

// generates normal random number with a specified mean and standard deviation sigma.
double normalVar(double mean, double sigma) {
    return standardNormalVar()*sigma + mean;
}

double normal8var(void) {
    return standardNormalVar() + 8;
}