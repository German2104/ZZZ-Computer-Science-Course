#pragma once

#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

const long double LEFT_BORDER = 0.1;
const long double RIGHT_BORDER = 0.6;
const int64_t MAX_ITERATION = 100;
const int64_t K = 1;  // ?

long double Abs(long double num) {
    if (num < 0) {
        return -num;
    }
    return num;
}

bool Equals(long double a, long double b) {
    if (Abs(a - b) < DBL_EPSILON * K) {
        return true;
    } else {
        return false;
    }
}

long double AltSign(int64_t num) {
    if (num % 2 == 1) {
        return (long double)-1;
    } else {
        return (long double)1;
    }
}

long double Pow(long double base, int64_t power) {
    long double res = 1;
    if (power < 0) {
        return -1;
    } else if (power == 0) {
        return 1;
    } else {
        while (power != 0) {
            if (power % 2 == 1) {
                res *= base;
            }
            power /= 2;
            base *= base;
        }
    }
    return res;
}

int64_t Factorial(int64_t left, int64_t right) {
    int64_t res = 1;
    if (left > right) {
        return res;
    }
    if (left == right) {
        return left;
    }
    if (right - left == 1) {
        return left * right;
    }
    int64_t middle = (left + right) / 2;
    return Factorial(left, middle) * Factorial(middle + 1, right);
}

long double Taylor(long double x, int64_t* iteration_counter) {
    long double result = 0;
    *iteration_counter = 0;
    long double portion = 1;
    while (!Equals(portion, 0) && (*iteration_counter <= 101)) {
        result += portion;
        ++(*iteration_counter);
        portion = AltSign(*iteration_counter) * (2 * (*iteration_counter) * (*iteration_counter) + 1) /
                  Factorial(1, 2 * (*iteration_counter)) * Pow(x, 2 * (*iteration_counter));
    }
    return result;
}

long double Function(long double x) {
    long double result = (1 - x * x / 2) * cosl(x) - (x / 2) * sinl(x);
    return result;
}

void PrintLine(long double x, long double taylor_res, long double true_res, int64_t iterations_count) {
    printf("| %.5Lf | %.15Lf | %.15Lf | %17ld |\n", x, taylor_res, true_res, iterations_count);
}

int Task() {
    int64_t iterations_number = 20;
    int64_t iterations_counter = 0;
    long double step = 0;
    long double taylor_result = 0;
    printf("Enter the number of iterations:\n");
    scanf("%ld", &iterations_number);
    step = (RIGHT_BORDER - LEFT_BORDER) / (iterations_number);
    printf("| %7s | %17s | %17s | %3s |\n", "x", "Taylor series", "True function", "Iterations number");
    for (long double x = LEFT_BORDER; x <= RIGHT_BORDER + step; x += step) {
        taylor_result = Taylor(x, &iterations_counter);
        PrintLine(x, taylor_result, Function(x), iterations_counter);
    }
    return 0;
}
