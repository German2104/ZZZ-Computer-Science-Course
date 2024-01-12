#pragma once

#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

const double EPSILON = DBL_EPSILON * 100000.0;

double NewtonMethod(double left, double right, double (*func)(double xn), double (*dfunc)(double xn)) {
    double x_last = 0.0;
    double x_current = (left + right) / 2;
    while (fabs(x_current - x_last) >= EPSILON) {
        x_last = x_current;
        x_current = x_last - func(x_last) / dfunc(x_last);
    }
    return x_current;
}

double_t DichotomyMethod(double_t x0, double_t x1, double_t (*func)(double_t)) {
    double_t middle_x = 0;
    double_t middle_y = 0;
    for (int i = 0; i < 100; ++i) {
        if (fabs(x1 - x0) >= EPSILON) {
            middle_x = (x0 + x1) / 2;
            middle_y = func(middle_x);
            if (middle_y > 0) {
                x1 = middle_x;
            } else {
                x0 = middle_x;
            }
        } else {
            return (x1 < -x0 ? x1 : x0);
        }
    }
    return -1;
}

double FunctionForNewton(double x) {
    return x * (sin(x) / cos(x)) - 1. / 3;
}

double_t FunctionForDichotomy(double_t x) {
    return (sin(x / 2) / cos(x / 2)) - (cos(x / 2) / sin(x / 2)) + x;
}

double DerivativeFunction(double x) {
    return (sin(x) / cos(x)) + x / (cos(x) * cos(x));
}

const double ANSWER_NEWTON_METHOD = 0.5472;
const double ANSWER_DICHOTOMY_METHOD = 1.0769;

int Task() {
    printf("Equation:  x * tg(x) + 1 / 3: \n(Newton method) %.10lf, answer: %.4lf\n",
           NewtonMethod(0.2, 1.0, FunctionForNewton, DerivativeFunction), ANSWER_NEWTON_METHOD);
    printf("\n");
    printf("Equation:  tg(x / 2) - ctg(x / 2) + x: \n(Dichotomy method) %.10lf, answer: %.4lf\n",
           DichotomyMethod(1.0, 2.0, FunctionForDichotomy), ANSWER_DICHOTOMY_METHOD);
    return 0;
}
