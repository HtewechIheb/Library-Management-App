#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <openssl/evp.h>
#include "general.h"

char* str_tolower(char* str){
    int i; // Counter variable
    char* str_lower; // Lowercase string to return

    if(!str){
        return NULL;
    }

    // Allocate the same amount of memory as str (+1 for the NULL terminator)
    str_lower = (char*)malloc((strlen(str)+1) * sizeof(char));

    if(!str_lower){
        printf("\nError! Could not allocate memory!");
        return NULL;
    }

    strcpy(str_lower, str);

    for(i = 0; i < strlen(str_lower); i++){
        *(str_lower+i) = tolower(*(str_lower+i));
    }
    return str_lower;
}
