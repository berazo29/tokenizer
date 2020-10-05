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
    while ( isdigit( ( (int)str[i]) ) != 0 || str[i] == '.' || tolower( (int)str[i] ) == 'e' || str[i] == '-' || str[i] == '+'){

        if ( str[i] == '.'){
            dot++;
        }
        if ( tolower( (int)str[i] ) == 'e' ){
            exp++;
        }
        if ( str[i] == '-'|| str[i] == '+' ){
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
    if (tolower( (int)str[i-2] ) == 'e' && (str[i-1] == '-'|| str[i] == '+') ){
        counter = counter-2;
    }
    // When last number end in e or - don't include them
    else if (tolower( (int)str[i-1] ) == 'e' || str[i-1] == '-' || str[i] == '+'){
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
    if (str[i] == '0' && tolower((int)str[i+1]) == 'x'){
        i = i+2;
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
    while (isalnum(str[i]) != 0 ){
        i++;
        counter++;
    }
    return counter;
}

int numberTypeCounter( char *str, int start){
    int counter = 0;
    int i = start;
    while (ishexnumber((int)str[i]) != 0 || tolower((int)str[i]) == 'x' || str[i] == '.' || str[i] == '-'){
        i++;
        counter++;
    }
    return counter;
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

    char tmp[size];

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

            int x = numberTypeCounter(str,i);

            if (str[i] == '0') {

                // Check for hexadecimal integer
                if ( hexadecimalCounter(str, i) ){
                    int posEnd = hexadecimalCounter(str,i);
                    char *operator;
                    operator = isNumberType(2);
                    char *hexNum = getSubstring(str,i,i+posEnd);
                    printf("%s: \"%s\"\n", operator, hexNum);
                    i = i+posEnd-1; // Relocate iterator location
                }
                // Check for Float point
                else if ( decimalFloatCounter(str, i) ){
                    int posEnd = decimalFloatCounter(str,i);
                    char *operator;
                    operator = isNumberType(3);
                    char *floatNum = getSubstring(str,i,i+posEnd);
                    printf("%s: \"%s\"\n", operator, floatNum);
                    i = i+posEnd-1; // Relocate iterator location
                }
                // Check for octal integer
                else if ( octalCounter(str, i) ){
                    int posEnd = octalCounter(str,i)+i;
                    char *operator;
                    operator = isNumberType(4);
                    char *octalNum = getSubstring(str,i,posEnd);
                    printf("%s: \"%s\"\n", operator, octalNum);
                    i = posEnd-1; // Relocate iterator location
                } else{
                    // Return an decimal integer
                    int posEnd = decimalCounter(str,i);
                    char *operator;
                    operator = isNumberType(1);
                    char *decimalNum = getSubstring(str,i,i+posEnd);
                    printf("%s: \"%s\"\n", operator, decimalNum);
                    i = i+posEnd-1; // Relocate iterator location
                }
            }else if ( isdigit( (int)str[i]) ) {
                //printf("Integer %c\n", str[i]);
                if ( decimalFloatCounter(str, i) ){
                    int posEnd = decimalFloatCounter(str,i);
                    char *operator;
                    operator = isNumberType(3);
                    char *floatNum = getSubstring(str,i,i+posEnd);
                    printf("%s: \"%s\"\n", operator, floatNum);
                    i = i+posEnd-1; // Relocate iterator location
                } else{
                    // Return an decimal integer
                    int posEnd = decimalCounter(str,i);
                    char *operator;
                    operator = isNumberType(1);
                    char *decimalNum = getSubstring(str,i,i+posEnd);
                    printf("%s: \"%s\"\n", operator, decimalNum);
                    i = i+posEnd-1; // Relocate iterator location
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
            if ( strcmp(word,"sizeof") == 0 ){
                printf("sizeof: \"%s\"\n", word);
                i=n+i-1; // Relocate the iterator to next location

                continue;
            }
            printf("word: \"%s\"\n", word);
            i=n+i-1; // Relocate the iterator to next location


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
                    continue;
                }
            }
            if ( strcmp(isOperator(str[i]),"bad token") != 0 ){
                operator = isOperator(str[i]);
                printf("%s: \"%c\"\n", operator, str[i]);
            }

        } else if ( isspace(str[i]) ){

        }
    }

    //Deallocate memory for string input
    free(str);

    return EXIT_SUCCESS;
}
