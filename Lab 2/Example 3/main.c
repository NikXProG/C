#include <stdio.h>
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>

double geometric_mean(int count, ...) {
    va_list args;
    double product = 1.0;

    va_start(args, count);
    for (int i = 0; i < count; i++) {
        double num = va_arg(args, double);
        product *= num;
    }
    va_end(args);

    return pow(product, 1.0 / count);
}

int main() {

    double result = geometric_mean(4, 2.0, 4.0, 8.0, 2.0);
    printf("%f\n", result); // Выведет результат вычисления среднего геометрического

    return 0;
}