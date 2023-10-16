#include <stdio.h>
#include <limits.h>
#include <errno.h>
#include <stdlib.h>
#include <stdbool.h>
#include <malloc.h>
#include <ctype.h>

int fuct_strcmp(const char *, const char *);
char * fuct_memcpy(char *, const char *, size_t);
int fuct_strlen(const char *);
char * fuct_reversed(const char *);
char * fuct_noeven_toupper(const char *);
char * fuct_sort(const char *);

int main(int argc, char *argv[]){
    unsigned int char_concatenation;
    // терминальный нуль + строка состоящая из 2 символов флага
    if (argc != 3){
        errno = EINVAL;
        perror("An invalid number of arguments was entered");
        return errno;        
    }
    /*if (sscanf(argv[1],"%s") != 1){
        errno = EINVAL;
        perror("Error: you probably entered something other than an const char * type (enter a string value) ");     
        return errno;
    }*/

    if (fuct_strcmp(argv[1],"-l") == 0){
        printf("%d",fuct_strlen(argv[2]));
    }
    if (fuct_strcmp(argv[1],"-r") == 0){

        if (fuct_reversed(argv[2]) == NULL){
            errno = ENOMEM;
            perror("Unfortunately, a memory non-allocation error occurred");
            return errno; 
        }

        printf("%s",fuct_reversed(argv[2]));        
    }
    if (fuct_strcmp(argv[1],"-u") == 0){

        if (fuct_noeven_toupper(argv[2]) == NULL){
            errno = ENOMEM;
            perror("Unfortunately, a memory non-allocation error occurred");
            return errno; 
        }
    
        printf("%s",fuct_noeven_toupper(argv[2]));            
    }
    if (fuct_strcmp(argv[1],"-n") == 0){
        if (fuct_sort(argv[2]) == NULL){
            errno = ENOMEM;
            perror("Unfortunately, a memory non-allocation error occurred");
            return errno; 
        }
        printf("%s",fuct_sort(argv[2]));  
    }
    
    return 0;
    /*if ( (sscanf(argv[2],"%u",&char_concatenation) || sscanf(argv[1],"%s", char_buffer_array)) != 1) {
        errno = EIO;
        perror("Error: you probably entered something other than an Unsigned Int type (enter a value range from 0 to 4,294,967,295) ");     
        return errno;
    }
    else if(sscanf(argv[1],"%s", char_buffer_array) == 1){

    }*/

    /*if (strcmp(argv[1],"-c") == 0){

        if (!((atoll(argv[2]) >= 0) && (atoll(argv[2]) <= UINT_MAX))){
            errno = ERANGE;
            perror("The entered number is not in the range unsigned __int32 (Unsigned int)");
            return errno;
        }

        if (sscanf(argv[2],"%u",&char_concatenation) != 1){
            errno = EINVAL;
            perror("Error: you probably entered something other than an Unsigned Int type (enter a value range from 0 to 4,294,967,295) ");     
            return errno;
        }

    }
    if (sscanf(argv[2],"%s", char_buffer_array) == 1){
        errno = EINVAL;
        perror("Error: you probably entered something other than an const char * type (enter a string value) ");     
        return errno;
    }*/
}

int fuct_strcmp(const char * argv, const char * flag){
    int index = 0;
    bool check_flag = true;
    if (sizeof(argv) != sizeof(flag)){
        return 1;
    }
    while (argv[index++] != '\0'){
        if (argv[index] != flag[index]){
            check_flag = false;
        }
    }
    return check_flag ? 0 : 1;
}
char * fuct_memcpy(char* destination, const char * source, size_t n){
    for (size_t i = 0; i < n; i++) {
        destination[i] = source[i];
    }
    return destination;
}

int fuct_strlen(const char * string){
    int i, count_char = 0;
    while (string[count_char] != '\0'){
        count_char++;
    }
    return count_char;
}

char * fuct_reversed(const char * string){
    int i, new_count = 0;


    char * array_string = (char *) malloc( (fuct_strlen(string) + 1) * sizeof(char) );
    if (array_string == NULL){
        return NULL;
    }

    for(i=(fuct_strlen(string)-1); i>= 0; i--){
        array_string[new_count++] = string[i];
    }

    array_string[new_count] = '\0';
    return array_string;
}

char * fuct_noeven_toupper(const char * string){
    int i,new_count = 0;
    char * array_string = (char *) malloc( (fuct_strlen(string) + 1) * sizeof(char) );
    if (array_string == NULL){
        return NULL;
    }

    for(i=0;i<fuct_strlen(string); i++){
        array_string[i] = string[i];
        if (i%2 == 0){
            array_string[i] = toupper(string[i]);
        }

    }

    array_string[i] = '\0';

    return array_string;
}

char * fuct_sort(const char * string){
    int i, strlen = (fuct_strlen(string) + 1);
    char * digits  = (char *) malloc( strlen * sizeof(char) ); 
    char * letters =  (char *) malloc( strlen * sizeof(char) ); 
    char * symbols =  (char *) malloc( strlen * sizeof(char) ); 
    char * array_string = (char *) malloc( strlen * sizeof(char) );  

    for(i=0;i<strlen-1; i++){
        if (isdigit(string[i])){
            digits[i] = string[i];
        }
        else if (isalpha(string[i])){
            letters[i] = string[i];
        }
        else{
            symbols[i] = string[i];
        }

    }
    int size1 = (fuct_strlen(digits) + 1);
    int size2 = (fuct_strlen(letters) + 1);
    int size3 = (fuct_strlen(symbols) + 1);
    printf("%d %d %d\n",size1,size2,size3);
    fuct_memcpy(array_string,  digits , strlen * sizeof(char) );
    fuct_memcpy(array_string + strlen,  letters , strlen * sizeof(char) );
    fuct_memcpy(array_string + 2*strlen,  symbols , strlen * sizeof(char) );   
    //memcpy(array_string + 2 * strlen, symbols, strlen * sizeof(int));
    return array_string;
}