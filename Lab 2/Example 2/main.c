#include <stdio.h>
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

enum StatusCode{
    SUCCESS,
    NEGATIVE_NUBMERS,
    DIVIDE_BY_ZERO,
    INPUT_ERROR
};

enum StatusCode geometric_mean(double *,int, ...);
enum StatusCode recursion_power(double *, double, int);

int main() {
    double division_result;

    enum StatusCode STATUS_GEOM_MEAN = geometric_mean(&division_result ,3, -2.0, -2.4, 34.2);

    switch (STATUS_GEOM_MEAN) {
        case SUCCESS:
            printf("RESULT GEOMETRIC MEAN: %.2f\n", division_result);
            break;
        case DIVIDE_BY_ZERO:
            printf("Division Error: You can't divide by zero.\n");
            return 1;
            break;
        case NEGATIVE_NUBMERS:
            printf("Input Error: The program cannot calculate a number in complex format. \n");
            return 2;
            break;
        default:
            printf("Input Error: Incorrected input \n");
            return 3;
    }   

    double result_recursion_power;
    enum StatusCode STATUS_RECS_POW = recursion_power(&result_recursion_power, 3.5, 6);
    switch (STATUS_RECS_POW) {
        case SUCCESS:
            printf("RESULT POWER: %.2f\n", result_recursion_power);
            break;
        default:
            printf("Input Error: Incorrect input\n");
            return 4;
    }

    return 0;
}



enum StatusCode geometric_mean(double *result,int count, ...) {
    va_list args;
    double product = 1.0, num;
    int arg_count_error = 0, arg_negative_numbers_err = 0, i;

    // Если количество аргументов равно 0 (возникает корень в бесконечности => это ошибка. Он неопределен)

    if ( count == 0){
        return DIVIDE_BY_ZERO;
    }

    // снова считываем и находим среднее геометрическое.

    va_start(args, count);

    for (i = 0; i < count; i++) {
        num = va_arg(args, double);
        if (num < 0){
            arg_negative_numbers_err++;
        }
        product *= num;
    }

    va_end(args);
    
    // проверка на неотрицательное число в корне

    if ( arg_negative_numbers_err % 2 != 0 ){
        return NEGATIVE_NUBMERS;
    }

    *result = pow(product, 1.0 / count);

    return SUCCESS;
}



enum StatusCode recursion_power(double *result, double number, int degree)
{
    if (degree < 0) {
        return INPUT_ERROR;
    }

    if (degree == 0) {
        *result = 1;
        return SUCCESS;
    }

    enum StatusCode status = recursion_power(result, number, degree - 1);

    if (status != SUCCESS) {
        return status;
    }

    *result *= number;

    return SUCCESS;
}
