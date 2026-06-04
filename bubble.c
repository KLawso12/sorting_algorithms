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
    
    unsigned int max_string = 1;
    
    for(int i = 2; i < argc; i++)
    {
        if(sizeof(argv[i]) > sizeof(argv[i-1]))
        {
            max_string = i;
        }
    }
    
    char temp_string[sizeof(argv[max_string])] = {};
    
    printf("the largest string is %llu characters long", sizeof(argv[max_string]));
    
    bool is_sorted = false;
    unsigned int array_size = argc - 1;
    
    do
    {
        is_sorted = true;
        for(int i = 0; i < array_size; i++)
        {
            true;
        }
    }
    while(!is_sorted);

    return EXIT_SUCCESS;
}


