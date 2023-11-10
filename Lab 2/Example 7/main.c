#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

typedef enum {
    AN_MemoryError = -1,
    AN_Success = 0
} Errors_AppendNumbers;

typedef enum {
    SN_MemoryError = -1,
    SN_ParametersError = 1,
    SN_Success = 0
} Errors_SumNumbers;

Errors_AppendNumbers appendNumber(int syst, char ** number1, const char * number2);   //Изменено
Errors_SumNumbers sumNumbers(char ** result, int syst, int count, ...);

int main(int argc, const char * argv[]) {
    char * result = NULL;
    if(sumNumbers(&result, 16, 3, "9A4", "444", "1B2D") != SN_Success) {
        printf("Error occurred\n");
        return -1;
    }
    printf("%s\n", result);
    free(result);
    return 0;
}

Errors_SumNumbers sumNumbers(char ** result, int syst,  int count, ...) {
    if(count == 0) return SN_ParametersError;

    va_list ap;
    va_start(ap, count);
    
    *result = strdup(va_arg(ap, char*));
    if(*result == NULL) return SN_MemoryError;

    for(int i=1; i<count; i++)
    {
        if(appendNumber(syst, result, va_arg(ap, char*)) != AN_Success) {
            va_end(ap);
            return SN_MemoryError;
        }
    }

    va_end(ap);
    return SN_Success;
}

Errors_AppendNumbers appendNumber (int syst, char ** number1, const char * number2) {
    size_t len1 = strlen(*number1), len2 = strlen(number2);  //Тут используем size_t, это допустимо и лучше для strlen
    size_t currentLen = (len1 >= len2 ? len1 : len2) + 2;

    const char *n1Ptr = *number1 + len1 - 1, *n2Ptr = number2 + len2 - 1;

    char * result = (char*)calloc(currentLen, sizeof(char));
    if(result == NULL) return AN_MemoryError;
    char * resultPtr = result + currentLen - 1;

    int stepsMemory = 0;
   
    while (n1Ptr != (*number1) - 1 || n2Ptr != number2 - 1) {
        int n1Val = (n1Ptr != (*number1) - 1) ? ((*n1Ptr >= 'A') ? toupper(*n1Ptr) - 'A' + 10 : *n1Ptr - '0') : 0;
        int n2Val = (n2Ptr != number2 - 1) ? ((*n2Ptr >= 'A') ? toupper(*n2Ptr) - 'A' + 10 : *n2Ptr - '0') : 0;
        if(n1Ptr != (*number1) - 1) n1Ptr--; 
        if(n2Ptr != number2 - 1) n2Ptr--;

        int currVal = n1Val + n2Val + stepsMemory;
        stepsMemory = currVal / syst;
        currVal %= syst;
        
        *resultPtr-- = (char)(currVal < 10 ? currVal + '0' : currVal - 10 + 'A');
    }

    if(stepsMemory != 0)
        *resultPtr-- = (char)(stepsMemory < 10 ? stepsMemory + '0' : stepsMemory - 10 + 'A');

    free(*number1);  
    *number1 = strdup(resultPtr + 1);  
    if(!*number1) {
        free(result);
        return AN_MemoryError;
    }

    free(result);
    return AN_Success;
}




