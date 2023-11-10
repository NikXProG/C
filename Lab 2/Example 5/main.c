#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <malloc.h>
#include <ctype.h>
#include <stdbool.h>

enum StatusCode{
    PROGRAM_COMPLETED_SUCCESSFULLY = 0,
    INVALID_COUNT_SPECIFICATION_PARAMETERS = 1,
    INCORRECTED_SPECIFICATION_FORMAT = 2,
    INCORRECTED_ROMAN_NUMBERS_FORMAT = 3,
    SPECITICATION_NOT_FOUND = 4,
    MEMORY_ALLOCATION_ERROR = 5
};

int overfscanf(char *, char *, ...);
int oversscanf(char *,char *, ...);
int main(void){
    char str[40];
    int a,b,c,d,e,f=16,h;
    unsigned int q;
    double flo;
    char wewq;   
    printf("FILE SCANF: \n");
    switch (overfscanf("hello 1 2 3 s XLIX 2a 2A 1010101", "%s %d %d %f %c %Ro %Cv %CV %Zr",str,&a,&b,&flo,&wewq,&d,&e,f,&h,16,&q))
    {
    case(0):
        printf("%s %d %d %f %c %d %d %d %u",str,a,b,flo,wewq,d,e,h,q);
        printf("\nthe program completed successfully");
        break;
    case(1):
        printf("INVALID_COUNT_SPECIFICATION_PARAMETERS");
        break;
    case(2):
        printf("INCORRECTED_SPECIFICATION_FORMAT");
        break;
    case(3):
        printf("INCORRECTED_ROMAN_NUMBERS_FORMAT");
        break;
    case(4):
        printf("SPECITICATION_NOT_FOUND");
        break;
    case(5):
        printf("MEMORY_ALLOCATION_ERROR");
        break;
    default:
        printf("unpredictable program operation");


    }
    printf("\n");

    printf("STRING SCANF: \n");
    switch (oversscanf("hello 1 2 3 s XLIX 2a 2A 1010101", "%s %d %d %f %c %Ro %Cv %CV %Zr",str,&a,&b,&flo,&wewq,&d,&e,f,&h,16,&q))
    {
    case(0):
        printf("%s %d %d %f %c %d %d %d %u",str,a,b,flo,wewq,d,e,h,q);
        printf("\nthe program completed successfully");
        break;
    case(1):
        printf("INVALID_COUNT_SPECIFICATION_PARAMETERS");
        break;
    case(2):
        printf("INCORRECTED_SPECIFICATION_FORMAT");
        break;
    case(3):
        printf("INCORRECTED_ROMAN_NUMBERS_FORMAT");
        break;
    case(4):
        printf("SPECITICATION_NOT_FOUND");
        break;
    case(5):
        printf("MEMORY_ALLOCATION_ERROR");
        break;
    default:
        printf("unpredictable program operation");


    }


    return 0;
}

int overfscanf(char *buf, char * format, ...){

    va_list arguments;
    va_start(arguments, format); 

    FILE *file= fopen("text.txt", "r");
    if (file == NULL) {
        printf("Failed to open file\n");
        return 1;
    }    

    int len =  strlen(format)+1; 
    
    char **buffer_string = (char **)malloc(len * sizeof(char *));
    
    if (buffer_string == NULL) {
        return MEMORY_ALLOCATION_ERROR;
    }
    for (int i = 0; i < len; i++) {
        buffer_string[i] = (char *)malloc(256 * sizeof(char));
        if (buffer_string[i] == NULL) {
            free(buffer_string);
            return MEMORY_ALLOCATION_ERROR;
        }
    }

    



    char c;
    char substring[256];
    int count = 0;
    char *ach;
    int count_buffer_string = 0;
    while(!feof (file)) {
        if (fgets(substring, 250, file)){
            int ch = '\n';
            ach=strchr(substring,ch);
            substring[ach-substring] = '\0';
            strcpy(buffer_string[count_buffer_string++], substring);   

        }
    }
   
    fclose(file);
    



    char **specification_buffer_string = (char **)malloc(len * sizeof(char *));
    if (specification_buffer_string == NULL) {
        free(buffer_string);
        for (int i = 0; i < len; i++) {
            free(buffer_string[i]);
        }
        return MEMORY_ALLOCATION_ERROR;
    }
    for (int i = 0; i < len; i++) {
        specification_buffer_string[i] = (char *)malloc(256 * sizeof(char));
        if (specification_buffer_string[i] == NULL) {
            free(specification_buffer_string);
            free(buffer_string);
            for (int i = 0; i < len; i++) {
                free(buffer_string[i]);
            }
            return MEMORY_ALLOCATION_ERROR;
        }
    }

    int old_count_buffer_string = count_buffer_string - 1;
    char as_substring[256];
    count_buffer_string = 0;
    int c_count = 0;

    for (char *formatPtr = format; *formatPtr != '\0'; formatPtr++){
        
        if (*formatPtr != ' '){
            as_substring[c_count++] = *formatPtr;

            if(*(formatPtr+1) == '\0'){

                as_substring[c_count] = '\0';
                strcpy(specification_buffer_string[count_buffer_string], as_substring);


            }
        }
        else{
            as_substring[c_count] = '\0';
            
            strcpy(specification_buffer_string[count_buffer_string++], as_substring);

            c_count = 0;
        }


    }

    if ( old_count_buffer_string != count_buffer_string){
        free(specification_buffer_string);
        free(buffer_string);
        for (int i = 0; i < len; i++) {
            free(buffer_string[i]);
        }
        for (int i = 0; i < len; i++) {
            free(specification_buffer_string[i]);
        }
        return INVALID_COUNT_SPECIFICATION_PARAMETERS;
    }
    bool flag_error_specification_characters = false;

    for (int i = 0;i< count_buffer_string+1 ;i++){
        if (strcmp(specification_buffer_string[i],"%d") == 0){
            int *val = va_arg(arguments,int*);
            *val = atoi(buffer_string[i]);   
        }
        else if(strcmp(specification_buffer_string[i],"%s") == 0){
            char * val = va_arg(arguments,char *);
            strcpy(val, buffer_string[i]);

        }
        else if(strcmp(specification_buffer_string[i],"%f") == 0){
            double *val = va_arg(arguments,double *);
            *val = atof(buffer_string[i]);     
        }
        else if((strcmp(specification_buffer_string[i],"%c") == 0)){
            if (strlen(buffer_string[i]) != 1){
                return INCORRECTED_SPECIFICATION_FORMAT;
            }
            char * val = va_arg(arguments, char *);   
            *val = buffer_string[i][0];

        }
        else if(strcmp(specification_buffer_string[i],"%Ro") == 0){
            int *val = va_arg(arguments,int*);
            int roman_numbers = 0;
            int sum_roman_numbers = 0;
            for (int j = 0;j<strlen(buffer_string[i]); j++){
                int old_roman_numbers = roman_numbers;
                switch(buffer_string[i][j]){
                    case('I'):
                        roman_numbers=1;
                        break;
                    case('V'):
                        roman_numbers=5;
                        break;
                    case('X'):
                        roman_numbers=10;
                        break;
                    case('L'):
                        roman_numbers=50;
                        break;
                    case('C'):
                        roman_numbers=100;
                        break;
                    case('D'):
                        roman_numbers=500;
                        break;
                    case('M'):
                        roman_numbers=1000;
                        break;
                    default:
                        if(j != strlen(buffer_string[i]) - 1 ){
                            return INCORRECTED_ROMAN_NUMBERS_FORMAT;
                        }

                }
                //  III 1(0)+1(1) +1 (2)
                // IV 1(0) + 4(1)
                if  ((j!=0) && (old_roman_numbers < roman_numbers)){
                        sum_roman_numbers += (roman_numbers-old_roman_numbers);
                        sum_roman_numbers -= old_roman_numbers;
            
                }
                else{
                    sum_roman_numbers += roman_numbers;

                }


            }
            

            *val = sum_roman_numbers;
        }
        
        else if(strcmp(specification_buffer_string[i],"%Zr") == 0){
            unsigned int *val = va_arg(arguments,unsigned int*);
            unsigned int number = 0;
            unsigned int prevFib = 1;
            unsigned int currentFib = 1;

            while (*buffer_string[i] != '\0') {
                if (*buffer_string[i] == '1') {
                        number += prevFib;
                }

                unsigned int nextFib = prevFib + currentFib;
                prevFib = currentFib;
                currentFib = nextFib;

                *(buffer_string[i]++);
            }

            *val = number;            
        }
        else if(strcmp(specification_buffer_string[i],"%Cv") == 0){
            int *val = va_arg(arguments,int*);
            int base = va_arg(arguments,int);
            
            if (base < 2 || base > 36) {
                base = 10;
            }
            
            int result = 0; 
            int sign = 1; 
            

            if (buffer_string[i][0] == '-') {
                sign = -1; 
            }
            

            for (int j = (buffer_string[i][0] == '-' ? 1 : 0); buffer_string[i][j] != '\0'; j++) {

                
                int digit;
                
  
                if (isdigit(buffer_string[i][j])) {
                    digit = buffer_string[i][j] - '0'; 
                } else {
                    digit = buffer_string[i][j] - 'a' + 10; 
                }
                

                if (digit >= 0 && digit < base) {
                    result = result * base + digit; 
                } else {
                    break; 
                }
            }
            

            *val = result * sign;
        }
        else if(strcmp(specification_buffer_string[i],"%CV") == 0){
            int *val = va_arg(arguments,int*);
            int base = va_arg(arguments,int);

            if (base < 2 || base > 36) {
                base = 10;
            }
            
            int result = 0; 
            int sign = 1;
            
           
            if (buffer_string[i][0] == '-') {
                sign = -1; 
            }
            
            
            for (int j = (buffer_string[i][0] == '-' ? 1 : 0); buffer_string[i][j] != '\0'; j++) {

                
                int digit;
                
                
                if (isdigit(buffer_string[i][j])) {
                    digit = buffer_string[i][j] - '0'; 
                } else {
                    digit = buffer_string[i][j] - 'A' + 10;
                }
                
                
                if (digit >= 0 && digit < base) {
                    result = result * base + digit; 
                } else {
                    break; 
                }
            }
            
            
            *val = result * sign;
        }
        else{
            free(specification_buffer_string);
            free(buffer_string);
            for (int i = 0; i < len; i++) {
                free(buffer_string[i]);
            }
            for (int i = 0; i < len; i++) {
                free(specification_buffer_string[i]);
            }
            return SPECITICATION_NOT_FOUND; 
        }

    }


    // Освобождение памяти
    for (int i = 0; i < len; i++) {
        free(specification_buffer_string[i]);
    }
    free(specification_buffer_string);   

    // Освобождение памяти
    for (int i = 0; i < len; i++) {
        free(buffer_string[i]);
    }
    free(buffer_string);    


    va_end(arguments);
    return PROGRAM_COMPLETED_SUCCESSFULLY;


}



int oversscanf(char *buf, char * format, ...){

    va_list arguments;
    va_start(arguments, format); 
    int len = strlen(buf)+1;


    char **buffer_string = (char **)malloc(len * sizeof(char *));
    
    if (buffer_string == NULL) {
        return MEMORY_ALLOCATION_ERROR;
    }
    for (int i = 0; i < len; i++) {
        buffer_string[i] = (char *)malloc(256 * sizeof(char));
        if (buffer_string[i] == NULL) {
            free(buffer_string);
            return MEMORY_ALLOCATION_ERROR;
        }
    }

    

    char substring[256];
    int count = 0;
    int count_buffer_string = 0;



    for (char* ptr = buf; *ptr != '\0'; ptr++){
           
        if (*ptr != ' '){
            substring[count++] = *ptr;
    
            if(*(ptr+1) == '\0'){
                substring[count] = '\0';
                strcpy(buffer_string[count_buffer_string], substring);   


            }
        }

        else{
            substring[count] = '\0';
            strcpy(buffer_string[count_buffer_string++], substring);
            count = 0;
        }
    
    }


    char **specification_buffer_string = (char **)malloc(len * sizeof(char *));
    if (specification_buffer_string == NULL) {
        free(buffer_string);
        for (int i = 0; i < len; i++) {
            free(buffer_string[i]);
        }
        return MEMORY_ALLOCATION_ERROR;
    }
    for (int i = 0; i < len; i++) {
        specification_buffer_string[i] = (char *)malloc(256 * sizeof(char));
        if (specification_buffer_string[i] == NULL) {
            free(specification_buffer_string);
            free(buffer_string);
            for (int i = 0; i < len; i++) {
                free(buffer_string[i]);
            }
            return MEMORY_ALLOCATION_ERROR;
        }
    }

    int old_count_buffer_string = count_buffer_string;
    char as_substring[256];
    count_buffer_string = 0;
    int c_count = 0;

    for (char *formatPtr = format; *formatPtr != '\0'; formatPtr++){
        
        if (*formatPtr != ' '){
            as_substring[c_count++] = *formatPtr;

            if(*(formatPtr+1) == '\0'){

                as_substring[c_count] = '\0';
                strcpy(specification_buffer_string[count_buffer_string], as_substring);


            }
        }
        else{
            as_substring[c_count] = '\0';
            
            strcpy(specification_buffer_string[count_buffer_string++], as_substring);

            c_count = 0;
        }


    }

    if ( old_count_buffer_string != count_buffer_string){
        free(specification_buffer_string);
        free(buffer_string);
        for (int i = 0; i < len; i++) {
            free(buffer_string[i]);
        }
        for (int i = 0; i < len; i++) {
            free(specification_buffer_string[i]);
        }
        return INVALID_COUNT_SPECIFICATION_PARAMETERS;
    }
    bool flag_error_specification_characters = false;

    for (int i = 0;i< count_buffer_string+1 ;i++){
        if (strcmp(specification_buffer_string[i],"%d") == 0){
            int *val = va_arg(arguments,int*);
            *val = atoi(buffer_string[i]);   
        }
        else if(strcmp(specification_buffer_string[i],"%s") == 0){
            char * val = va_arg(arguments,char *);
            strcpy(val, buffer_string[i]);

        }
        else if(strcmp(specification_buffer_string[i],"%f") == 0){
            double *val = va_arg(arguments,double *);
            *val = atof(buffer_string[i]);     
        }
        else if((strcmp(specification_buffer_string[i],"%c") == 0)){
            if (strlen(buffer_string[i]) != 1){
                return INCORRECTED_SPECIFICATION_FORMAT;
            }
            char * val = va_arg(arguments, char *);   
            *val = buffer_string[i][0];

        }
        else if(strcmp(specification_buffer_string[i],"%Ro") == 0){
            int *val = va_arg(arguments,int*);
            int roman_numbers = 0;
            int sum_roman_numbers = 0;
            for (int j = 0;j<strlen(buffer_string[i]); j++){
                int old_roman_numbers = roman_numbers;
                switch(buffer_string[i][j]){
                    case('I'):
                        roman_numbers=1;
                        break;
                    case('V'):
                        roman_numbers=5;
                        break;
                    case('X'):
                        roman_numbers=10;
                        break;
                    case('L'):
                        roman_numbers=50;
                        break;
                    case('C'):
                        roman_numbers=100;
                        break;
                    case('D'):
                        roman_numbers=500;
                        break;
                    case('M'):
                        roman_numbers=1000;
                        break;
                    default:
                        return INCORRECTED_ROMAN_NUMBERS_FORMAT;
                }
                //  III 1(0)+1(1) +1 (2)
                // IV 1(0) + 4(1)
                if  ((j!=0) && (old_roman_numbers < roman_numbers)){
                        sum_roman_numbers += (roman_numbers-old_roman_numbers);
                        sum_roman_numbers -= old_roman_numbers;
            
                }
                else{
                    sum_roman_numbers += roman_numbers;

                }


            }
            

            *val = sum_roman_numbers;
        }
        
        else if(strcmp(specification_buffer_string[i],"%Zr") == 0){
            unsigned int *val = va_arg(arguments,unsigned int*);
            unsigned int number = 0;
            unsigned int prevFib = 1;
            unsigned int currentFib = 1;

            while (*buffer_string[i] != '\0') {
                if (*buffer_string[i] == '1') {
                        number += prevFib;
                }

                unsigned int nextFib = prevFib + currentFib;
                prevFib = currentFib;
                currentFib = nextFib;

                *(buffer_string[i]++);
            }

            *val = number;            
        }
        else if(strcmp(specification_buffer_string[i],"%Cv") == 0){
            int *val = va_arg(arguments,int*);
            int base = va_arg(arguments,int);
            
            if (base < 2 || base > 36) {
                base = 10;
            }
            
            int result = 0; 
            int sign = 1; 
            

            if (buffer_string[i][0] == '-') {
                sign = -1; 
            }
            

            for (int j = (buffer_string[i][0] == '-' ? 1 : 0); buffer_string[i][j] != '\0'; j++) {

                
                int digit;
                
  
                if (isdigit(buffer_string[i][j])) {
                    digit = buffer_string[i][j] - '0'; 
                } else {
                    digit = buffer_string[i][j] - 'a' + 10; 
                }
                

                if (digit >= 0 && digit < base) {
                    result = result * base + digit; 
                } else {
                    break; 
                }
            }
            

            *val = result * sign;
        }
        else if(strcmp(specification_buffer_string[i],"%CV") == 0){
            int *val = va_arg(arguments,int*);
            int base = va_arg(arguments,int);

            if (base < 2 || base > 36) {
                base = 10;
            }
            
            int result = 0; 
            int sign = 1;
            
           
            if (buffer_string[i][0] == '-') {
                sign = -1; 
            }
            
            
            for (int j = (buffer_string[i][0] == '-' ? 1 : 0); buffer_string[i][j] != '\0'; j++) {

                
                int digit;
                
                
                if (isdigit(buffer_string[i][j])) {
                    digit = buffer_string[i][j] - '0'; 
                } else {
                    digit = buffer_string[i][j] - 'A' + 10;
                }
                
                
                if (digit >= 0 && digit < base) {
                    result = result * base + digit; 
                } else {
                    break; 
                }
            }
            
            
            *val = result * sign;
        }
        else{
            free(specification_buffer_string);
            free(buffer_string);
            for (int i = 0; i < len; i++) {
                free(buffer_string[i]);
            }
            for (int i = 0; i < len; i++) {
                free(specification_buffer_string[i]);
            }
            return SPECITICATION_NOT_FOUND; 
        }

    }


    // Освобождение памяти
    for (int i = 0; i < len; i++) {
        free(specification_buffer_string[i]);
    }
    free(specification_buffer_string);   

    // Освобождение памяти
    for (int i = 0; i < len; i++) {
        free(buffer_string[i]);
    }
    free(buffer_string);    


    va_end(arguments);
    return PROGRAM_COMPLETED_SUCCESSFULLY;


}