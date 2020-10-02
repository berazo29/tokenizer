#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int wordCounter(char *str, int start){
    int counter = 0;
    int i = start;
    while (isalnum(str[i]) != 0 && !isspace( (int)isalnum(str[i]))){
        i++;
        counter++;
    }
    return counter;
}

char* getSubstring(char *str, int start, int end){

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
    if(strlen(str)>3){
        return "sizeof";
    }else if(strlen(str)==3){
        if(strcmp(str,">>=")==0){
            return "shift right equals";
        }else if(strcmp(str,"<<=")==0){
            return "shift left equals";
        }
    }else if(strlen(str)==2){
        if(str[1]=='>'){
            if(strcmp(str,">>")==0){
                return "shift right";
            }else if(strcmp(str,"->")==0){
                return "structure pointer";
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
    }else if(str[1]=='='){
        if(strcmp(str,"==")==0){
            return "equality test";
        }else if(strcmp(str,"!=")==0){
            return "inequality test";
        }else if(strcmp(str,"<=")==0){
            return "less than or equal test";
        }else if(strcmp(str,">=")==0){
            return "greater than or equal test";
        }else if(strcmp(str,"+=")==0){
            return "plus equals";
        }else if(strcmp(str,"-=")==0){
            return "minus equals";
        }else if(strcmp(str,"*=")==0){
            return "times equals";
        }else if(strcmp(str,"/=")==0){
            return "divide equals";
        }else if(strcmp(str,"%=")==0){
            return "mod equals";
        }else if(strcmp(str,"&=")==0){
            return "bitwise AND equals";
        }else if(strcmp(str,"|=")==0){
            return "bitwise OR equals";
        }else if(strcmp(str,"^=")==0) {
            return "bitwise XOR equals";
        }
    }
    return "bad token";
}

void printArgumentsTest(char *str){
    printf("\nTEST\n");
    for (int i = 0; i < strlen(str); ++i) {
        printf("%c", str[i]);
    }
    printf("\n");
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
//    printf("%s", str);

    // Traverse the string
    for (int i = 0; i < size; ++i) {

        //Check for a word
        if ( (int)isalpha(str[i]) ){

            int n = wordCounter(str, i);

            // Handle one character
            if (n == 1){
                printf("word: \"%c\"\n", str[i]);
                i++;
                continue;
            }
            //printf("SIZE %d\n",n);
            char *word = getSubstring(str,i,i+n);
            printf("word: \"%s\"\n", word);
            i=n+i-1; // Relocate the iterator to next location
            free(word); // Free the memory

        } else if ( isdigit( (int)str[i] )){
            printf("Number %c\n", str[i]);


        } else if ( ispunct((str[i])) ){

            char *operator;
            operator = isOperator(str[i]);
            printf("%s: \"%c\"\n", operator, str[i]);

        } else if ( isspace(str[i]) ){

        }


    }

    //For testing only
    printArgumentsTest(str);
    free(str);

    return EXIT_SUCCESS;
}
