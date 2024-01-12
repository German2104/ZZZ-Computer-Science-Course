#pragma once

#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const double A = 0.0;
const double B = 1.0;
const int32_t MAX_ITERATION = 100;
const double N = 10.0;
const double EPS = DBL_EPSILON;
const double STEP = (B - A) / N;
const double K = 10.0;

long double Func(long double x) {
    // write your function here
    return cos(x);
    return 0.0;
}

int Task() {
    // write your solution here
    int n = 2;
    long double element = 1;
    long double sum = 1;
    long double difference = 1;
    int count_iterations = 1;
    printf(" ----------------------------------------------------------------\n");
    printf("  x   |     Taylor series      |      Function          | Iters |\n");
    printf(" ----------------------------------------------------------------\n");
    for (long double x = 0; x <= B; x += STEP) {
        element = 1;
        sum = 1;
        difference = 1;
        count_iterations = 1;
        n = 2;
        while (EPS * K <= difference && count_iterations < MAX_ITERATION) {
            element = -1 * (element * x * x / (n * (n - 1)));
            sum += element;
            n += 2;
            difference = fabs(Func(x) - sum);
            count_iterations++;
        }
        printf("%6.2Lf|%24.20Lf|%24.20Lf|%4d\n", x, sum, Func(x), count_iterations);
    }
    printf(" ----------------------------------------------------------------\n");
    return 0;
}
