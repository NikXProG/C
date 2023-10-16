#include <stdio.h>
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

enum StatusCode{
    INVALID_INPUT,
    SUCCESS,
    NEGATIVE_NUBMERS,
    DIVIDE_BY_ZERO
};

enum StatusCode geometric_mean(double *,int, ...);
double recursion_power(double, int);

int main() {
    double division_result;
    enum StatusCode STATUS_GEOM_MEIN = geometric_mean(&division_result ,2, 2.0, 2.4);
    double result_recursion_power = recursion_power(3.5, 6);

    switch (STATUS_GEOM_MEIN) {
        case SUCCESS:
            printf("RESULT: %.2f\n", division_result);
            exit(1);
            break;
        case DIVIDE_BY_ZERO:
            printf("Division Error: You can't divide by zero.\n");
            exit(2);
            break;
        case NEGATIVE_NUBMERS:
            printf("Input Error: The program cannot calculate a number in complex format. \n");
            exit(3);
            break;
        case INVALID_INPUT:
            printf("Input Error: Incorrected input \n");
            exit(4);
            break;
    }

    printf("%f\n", result_recursion_power); 
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


    // Первый проход

    va_start(args, count);

    while (arg_count_error < count) {
        // Приводим тип аргумента к double
        num = va_arg(args, double);
        arg_count_error++;
    }
    
    va_end(args);

    // проверка на равенство исконно входящего кол-ва аргументов и кол-во в действительности аргументов

    if (arg_count_error != count){
        return INVALID_INPUT;
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

double recursion_power(double number, int degree)
{
    if(degree!=0) 
        return number*recursion_power(number,degree-1);
    return 1;
}