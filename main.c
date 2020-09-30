#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main( int argc, char *argv[argc+1]) {

    //File name from arguments
    if (argc != 2 ){
        printf("Error\n");
        return EXIT_SUCCESS;
    }

    // Allocate memory and init
    unsigned int size = strlen(argv[1]);
    char *str = (char *)malloc(size*sizeof(char));
    strcpy(str, argv[1]);
//    printf("%s", str);
    for (int i = 0; i < size; ++i) {
        if ( ispunct(str[i]) ){
            char temp = str[i];
            // Run the func for symbols
        }


    }
    return EXIT_SUCCESS;
}
