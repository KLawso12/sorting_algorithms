#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

int main(int argc, char* argv[argc+1])
{
    
    if(argc < 3)
    {
        printf("error, not enough arguments");
        return EXIT_FAILURE;
    }
    
    printf("Hello, world!");

    return EXIT_SUCCESS;
}
