#include <stdio.h>
#include <math.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

enum StatusCode{
    NEGATIVE_NUBMERS,
    DIVIDE_BY_ZERO,
    INPUT_ERROR
};

double geometric_mean(int, ...);
double recursion_power(double, int);

int main() {

    enum StatusCode STATUS_GEOM_MEAN = geometric_mean(3, -2.0, -2.4, 4.2);
    if ( STATUS_GEOM_MEAN == NEGATIVE_NUBMERS){
        printf("Input Error: The program cannot calculate a number in complex format. \n");
        return 1;
    }
    else if(STATUS_GEOM_MEAN == DIVIDE_BY_ZERO){
        printf("Division Error: You can't divide by zero.\n");
    }
    else{

        printf("RESULT GEOM MEAN: \n%f\n",geometric_mean(3, -2.0, -2.4, 4.2));
    }

    enum StatusCode STATUS_POW = recursion_power(3.5, 6);

    if (  STATUS_POW == NEGATIVE_NUBMERS){
        printf("Input Error: The program cannot calculate a number in complex format. \n");
        return 1;
    }
    else{
        printf("RESULT RECURSION POWER: \n%f \n", recursion_power(3.5, 6) );       
    }


    return 0;
}



double geometric_mean(int count, ...) {
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


    return pow(product, 1.0 / count);
}



double recursion_power(double number, int degree)
{
    if  (degree < 0){
        return NEGATIVE_NUBMERS;
    }
    if (degree != 0) {
        return  number * recursion_power(number, degree - 1);
    }
    return 1;
}
