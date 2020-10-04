#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int octalCounter(char *str, int start){
    int counter = 0;
    int i = start;

    // Handle one char
    if (str[start] != '0'){
        return 0;
    }
    while (isdigit(((int)str[i])) != 0 ){
        if ( str[i] == '8' || str[i] == '9' ){
            return 0;
        }
        i++;
        counter++;
    }
    return counter;
}

int decimalCounter(char *str, int start){
    int counter = 0;
    int i = start;
    while (isdigit(((int)str[i])) != 0){
        i++;
        counter++;
    }
    return counter;
}

int decimalFloatCounter(char *str, int start){
    int counter = 0;
    int dot = 0;
    int exp = 0;
    int sign = 0;
    int i = start;
    // Handle the dot in the first position
    if ( str[i] == '.' ){
        return 0;
    }
    while ( isdigit( ( (int)str[i]) ) != 0 || str[i] == '.' || tolower( (int)str[i] ) == 'e' || str[i] == '-' ){

        if ( str[i] == '.'){
            dot++;
        }
        if ( tolower( (int)str[i] ) == 'e' ){
            exp++;
        }
        if ( str[i] == '-' ){
            sign++;
        }
        if ( dot == 2 || exp == 2 || sign == 2 ){
            break;
        }

        // Check for correct sign precedence: dot then exponent then sign
        if ( dot < exp || dot < sign || exp < sign){
            break;
        }
        i++;
        counter++;
    }
    int integer = 0;
    // Check if the number is integer and return 0
    for (int j = start; j < i; ++j) {
        if (isdigit( (int)str[j] )){
            integer++;
        }
        if (integer == counter){
            return 0;
        }
        // Check for .e in the string since it will make the number an integer
        if ( str[j]== '.' && tolower((int)str[j+1]) == 'e'){
            return 0;
        }
    }
    if ( str[i-1] == '.' ){
        counter = 0;
    }

    // When last number finish in e- don't include them
    if (tolower( (int)str[i-2] ) == 'e' && str[i-1] == '-'){
        counter = counter-2;
    }
    // When last number end in e or - don't include them
    else if (tolower( (int)str[i-1] ) == 'e' || str[i-1] == '-'){
        counter--;
    }

    return counter;
}

int hexadecimalCounter(char *str, int start){
    int counter = 0;
    int i = start;

    if ( strlen(str) < 3){
        return 0;
    }
    if (str[start] == '0' && tolower((int)str[start+1]) == 'x'){
        i = start+2;
        counter=2;

        while ( isxdigit(((int)str[i])) != 0 ){
            counter++;
            i++;
        }
        if ( counter == 2 ){
            return 0;
        }
    }

    return counter;
}

int symbolCounter(char *str, int start){
    int counter = 0;
    int i = start;
    while (ispunct(str[i]) != 0 && counter < 3){
        i++;
        counter++;
    }
    return counter;
}

int wordCounter(char *str, int start){
    int counter = 0;
    int i = start;
    while (isalnum(str[i]) != 0 && !isspace( (int)isalnum(str[i])) ){
        i++;
        counter++;
    }
    return counter;
}

// Count all types of number symbols
int numberTypeCounter( char *str, int start){
    int counter = 0;
    int i = start;
    while (ishexnumber((int)str[i]) != 0 || tolower((int)str[i]) == 'x' || str[i] == '.' || str[i] == '-'){
        i++;
        counter++;
    }
    return counter;
}

// Doc return 0 if none invalid type, 1 Integer, 2 HexInteger, 3 float, 4 Octal
int numberType(char *str, int start, int end){
    int i = start;
    // One character;
    if (i == end ){
        if (str[i] == '8' || str[i] == '9'){
            return 1;
        } else if ( isdigit((int)str[i] != 0)){
            return 4;
        }
    }
    for (int j = start+1; j < end; ++j) {
        if (tolower((int)str[i]) == 'x'){
            return 2;
        }
        if (str[j] == '.'){
            return 3;
        }
        if ( str[start] == '0' && ( (int)(str[j]-'0') < 8 ) ){
            return 4;
        }
    }
    return 0;
}

char* isNumberType(int numberType){
    switch (numberType) {
        case 1:
            return "decimal integer";
            break;
        case 2:
            return "hexadecimal integer";
            break;
        case 3:
            return "floating point";
            break;
        case 4:
            return "octal integer";
            break;
        default:
            return "error type";
    }
}

// Allocate dynamic memory and get the substring from position a to b
char* getSubstring(char const *str, int start, int end){

    int size = end - start;
    char *tmp = (char *)malloc(size*sizeof(char *));
    int k=0;
    for (int i = start; i < end; ++i) {
        tmp[k] = str[i];
        k++;
    }
    return tmp;
}

char* isOperator(char str) {
    switch (str) {
        case '(':
            return "left parenthesis";
            break;
        case ')':
            return "right parenthesis";
            break;
        case '[':
            return "left bracket";
            break;
        case ']':
            return "right bracket";
            break;
        case '.':
            return "structure member";
            break;
        case ',':
            return "comma";
            break;
        case '!':
            return "negate";
            break;
        case '~':
            return "1s complement";
            break;
        case '^':
            return "bitwise XOR";
            break;
        case '|':
            return "bitwise OR";
            break;
        case '+':
            return "addition";
            break;
        case '/':
            return "division";
            break;
        case '?':
            return "conditional true";
            break;
        case ':':
            return "conditional false";
            break;
        case '<':
            return "less than test";
            break;
        case '>':
            return "greater than test";
            break;
        case '=':
            return "assignment";
            break;
        case '&':
            return "AND/address operator";
            break;
        case '-':
            return "minus/subtract operator";
            break;
        case '*':
            return "multiply/dereference operator";
            break;
        default:
            return "bad token";
            break;
    }
    return "bad token";
}

char* isLongOperator(char* str) {
    if(strlen(str)==3){
        if(strcmp(str,">>=")==0){
            return "shift right equals";
        }else if(strcmp(str,"<<=")==0){
            return "shift left equals";
        }
    }else if(strlen(str)==2){
        if(str[1]=='>') {
            if (strcmp(str, ">>") == 0) {
                return "shift right";
            } else if (strcmp(str, "->") == 0) {
                return "structure pointer";
            }
        }else if(str[1]=='=') {
            if (strcmp(str, "==") == 0) {
                return "equality test";
            } else if (strcmp(str, "!=") == 0) {
                return "inequality test";
            } else if (strcmp(str, "<=") == 0) {
                return "less than or equal test";
            } else if (strcmp(str, ">=") == 0) {
                return "greater than or equal test";
            } else if (strcmp(str, "+=") == 0) {
                return "plus equals";
            } else if (strcmp(str, "-=") == 0) {
                return "minus equals";
            } else if (strcmp(str, "*=") == 0) {
                return "times equals";
            } else if (strcmp(str, "/=") == 0) {
                return "divide equals";
            } else if (strcmp(str, "%=") == 0) {
                return "mod equals";
            } else if (strcmp(str, "&=") == 0) {
                return "bitwise AND equals";
            } else if (strcmp(str, "|=") == 0) {
                return "bitwise OR equals";
            } else if (strcmp(str, "^=") == 0) {
                return "bitwise XOR equals";
            }
        }else if(strcmp(str,"<<")==0){
            return "shift left";
        }else if(strcmp(str,"++")==0){
            return "increment";
        }else if(strcmp(str,"--")==0){
            return "decrement";
        }else if(strcmp(str,"||")==0){
            return "logical OR";
        }else if(strcmp(str,"&&")==0){
            return "logical AND";
        }
    }
    return "bad token";
}

void printArgumentsTest(char *str){
    printf("\nTEST\n");
    printf("INPUT:");
    for (int i = 0; i < strlen(str); ++i) {
        printf("%c", str[i]);
    }
    printf("\n");
    char *word = "m099";
    int x = octalCounter(word,0);
    printf("STRING:%s    c:%c    Size:%d\n",word, word[x], x);
}

int main( int argc, char **argv) {

    //Check the argument input
    if (argc != 2 ){
        printf("Incorrect number of arguments\n");
        return EXIT_SUCCESS;
    }
    if(strlen(argv[1])==0){
        printf("Empty string, no tokens to parse\n");
        return EXIT_SUCCESS;
    }

    // Allocate memory and init
    unsigned int size = strlen(argv[1]);
    char *str = (char *)malloc(size*sizeof(char));

    // Copy input to a local string
    strcpy(str, argv[1]);

    // Traverse the string
    for (int i = 0; i < size; ++i) {

        if ( isdigit( (int)str[i] )) {
            //printf("TEST Number %c\n", str[i]);

            //printf("TEST SIZE NUMBER %d\n", n);

            if (str[i] == '0') {
                //printf("TEST Zero %c\n", str[i]);
                // Check for hexadecimal integer
                if ( hexadecimalCounter(str, i) ){
                    int posEnd = hexadecimalCounter(str,i);
                    char *operator;
                    operator = isNumberType(2);
                    char *floatNum = getSubstring(str,i,i+posEnd);
                    printf("%s: \"%s\"\n", operator, floatNum);
                    i = i+posEnd-1; // Relocate iterator location
                    free(floatNum);
                }
                // Check for Float point
                else if ( decimalFloatCounter(str, i) ){
                    int posEnd = decimalFloatCounter(str,i);
                    char *operator;
                    operator = isNumberType(3);
                    char *floatNum = getSubstring(str,i,i+posEnd);
                    printf("%s: \"%s\"\n", operator, floatNum);
                    i = i+posEnd-1; // Relocate iterator location
                   free(floatNum);
                }
                // Check for octal integer
                else if ( octalCounter(str, i) ){
                    int posEnd = octalCounter(str,i);
                    char *operator;
                    operator = isNumberType(4);
                    char *octalNum = getSubstring(str,i,i+posEnd);
                    printf("%s: \"%s\"\n", operator, octalNum);
                    i = i+posEnd-1; // Relocate iterator location
                    free(octalNum);

                } else{
                    // Return an decimal integer
                    int posEnd = decimalCounter(str,i);
                    char *operator;
                    operator = isNumberType(1);
                    char *decimalNum = getSubstring(str,i,i+posEnd);
                    printf("%s: \"%s\"\n", operator, decimalNum);
                    i = i+posEnd-1; // Relocate iterator location
                    free(decimalNum);
                }
            }
            else if ( isdigit( (int)str[i]) ) {
                //printf("Integer %c\n", str[i]);
                if ( decimalFloatCounter(str, i) ){
                    int posEnd = decimalFloatCounter(str,i);
                    char *operator;
                    operator = isNumberType(3);
                    char *floatNum = getSubstring(str,i,i+posEnd);
                    printf("%s: \"%s\"\n", operator, floatNum);
                    i = i+posEnd-1; // Relocate iterator location
                    free(floatNum);
                } else{
                    // Return an decimal integer
                    int posEnd = decimalCounter(str,i);
                    char *operator;
                    operator = isNumberType(1);
                    char *decimalNum = getSubstring(str,i,i+posEnd);
                    printf("%s: \"%s\"\n", operator, decimalNum);
                    i = i+posEnd-1; // Relocate iterator location
                    free(decimalNum);
                }

            }
        } else if ( (int)isalpha(str[i]) ){

            int n = wordCounter(str, i);

            // Handle one character
            if (n == 1){
                printf("word: \"%c\"\n", str[i]);
                continue;
            }
            //printf("SIZE %d\n",n);
            char *word = getSubstring(str,i,i+n);

            // Check if sizeof exist and continue;
            if (strcmp(word,"sizeof") == 0){
                printf("sizeof: \"%s\"\n", word);
                i=n+i-1; // Relocate the iterator to next location
                free(word);
                continue;
            }
            printf("word: \"%s\"\n", word);
            i=n+i-1; // Relocate the iterator to next location
            free(word); // Free the memory

        } else if ( ispunct((str[i])) ){
            int n = symbolCounter(str,i);
            //printf("SIZE %d\n",n);
            // Check for match in the n <= 3
            char *operator;
            char *word = getSubstring(str,i,i+n);
            //printf("TEST: %s\n", word);
            if ( n == 3 ){
                if ( strcmp(isLongOperator(word),"bad token") != 0 ){
                    operator = isLongOperator(word);
                    printf("%s: \"%s\"\n", operator, word);
                    i = i+2;
                    free(word);
                    continue;
                }
                n--;
                word = getSubstring(str,i,i+n);
            }
            if ( n == 2 ){
                if ( strcmp(isLongOperator(word),"bad token") != 0 ){
                    operator = isLongOperator(word);
                    printf("%s: \"%s\"\n", operator, word);
                    i = i+1;
                    free(word);
                    continue;
                }
                free(word);
            }
            if ( strcmp(isOperator(str[i]),"bad token") != 0 ){
                operator = isOperator(str[i]);
                printf("%s: \"%c\"\n", operator, str[i]);
            }

        } else if ( isspace(str[i]) ){

        }
    }

    //For testing only
    printArgumentsTest(str);
    free(str);

    return EXIT_SUCCESS;
}
