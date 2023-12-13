#pragma once

#include <float.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>

const double a = -1.0;
const double b = 1.0;
const double n = 10.0;
const double precision = 10000.0;

const size_t MAX_ITERATIONS = 100;

void Prepare(double* powers_of_two) {
    powers_of_two[0] = 1.0;
    for (size_t power = 1; power <= MAX_ITERATIONS; ++power) {
        powers_of_two[power] = powers_of_two[power - 1] * 2.0;
    }
}

long double Func(long double x) {
    return logl(2 + x);
}

double Taylor(double x, size_t* iterations, double* powers_of_two) {
    double answer = log(2);
    size_t i = 1;  // количество итераций
    double power_x = x;
    while (i <= MAX_ITERATIONS) {
        double raise = power_x / (i * powers_of_two[i]);  // Добавочек нового члена ряда
        raise *= ((i - 1) % 2) ? -1 : 1;                  // вычитаем, если i - 1 нечётный

        // если добавочек мал, заканчиваем считать
        if (fabs(raise) < DBL_EPSILON * precision) {
            *iterations = i - 1;
            return answer;
        }

        answer += raise;
        power_x *= x;
        ++i;
    }

    *iterations = MAX_ITERATIONS;
    return answer;
}

int Task() {
    // Предпосчитаем степени двоек
    double powers_of_two[MAX_ITERATIONS + 1];
    Prepare(powers_of_two);

    size_t iterations = 0;
    char space[] = "         ";
    long double y_func = 0.0;
    double y_taylor = 0.0;

    // шапка таблицы
    printf("|                                        Result of program for function ln(2 + x) |\n");
    printf("-----------------------------------------------------------------------------------\n");
    printf("|   x    |         Func(x)        |       Taylor(x)        | number of iterations |\n");
    printf("-----------------------------------------------------------------------------------\n");

    double delta = (b - a) / n;
    for (double x = a; x <= b; x += delta) {
        iterations = 0;
        y_func = Func(x);
        y_taylor = Taylor(x, &iterations, powers_of_two);
        printf("| %6.3lf | %22.20Lf | %22.20lf | %20lu |\n", x, y_func, y_taylor, iterations);
    }
    return 0;
}