#include <stdio.h>
#include <stdarg.h>
#include <malloc.h>
enum StatusCode{
    MEMORY_ALLOCATION_ERROR = 1,

};
long long factorial(int n);
int polynomial_function(double,long long*,double,int, ...);
int main(void){
    int degree = 3;
    long long * result_coefficient = (long long *) malloc( (degree+1) * sizeof(long long));
    polynomial_function(0.001,result_coefficient, 1, degree, 5, 4 ,2,1);

    return 0;

}
int polynomial_function(double epsilon,long long*result_coefficient,double a,int degree, ...){
    va_list arguments;
    va_start(arguments, degree);

    long long * buffer_coefficient = (long long *) malloc( (degree+1) * sizeof(long long));

    if ( buffer_coefficient == NULL){
        free(result_coefficient);
        return MEMORY_ALLOCATION_ERROR;
    }

    for (int i = 0; i< (degree+1); i++){
        buffer_coefficient[i] = (long long ) va_arg(arguments,int);
    }



    int n = 2;
    int m = 1;
    long long C;





    for (int k = 0; k <= n; k++) {
        //Вычисляем биноминальный коэффициент
        if (k == 0 || k == n) {
            C = 1;
        } else {
            C = factorial(n) / (factorial(k) * factorial(n-k));
        }

        //Расчет значений result_coefficient в зависимости от k
        if (k == 0) {
            result_coefficient[0] = buffer_coefficient[0];
        } else {
            long long sum = 0;
            for (int i = 0; i < k; i++) {
                long long C1 = factorial(k) / (factorial(i) * factorial(k-i));
                sum += C1 * result_coefficient[i];
            }
            result_coefficient[k] = buffer_coefficient[k] + C * result_coefficient[k-1] - sum;
        }
        m = k;
    }


    for (int i = 0; i <= n; i++)
    {
        printf("%lld ", result_coefficient[i]);
    }
    printf("\n");

    free(buffer_coefficient);
    va_end(arguments);
    return 0;

}
long long factorial(int n) 
{
    long long fact = 1;
    for(int i = 2; i <= n; i++)
    {
       fact *= i;
    }
    return fact;
}
