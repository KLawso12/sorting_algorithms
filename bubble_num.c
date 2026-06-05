#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>



int main(int argc, char* argv[argc+1])
{
    unsigned int exit = EXIT_SUCCESS;
    if(argc < 3)
    {
        printf("error, not enough arguments\n");
        exit = EXIT_FAILURE;
        goto cleanup;
    }
    
    double temp_double = {};
    double *sorted_list = malloc(sizeof(double)*(argc-1));
    
    if(!sorted_list)
    {
        printf("error, could not successfully allocate memory");
        exit = EXIT_FAILURE;
        goto cleanup;
    }
    
    char *end;
    for(int i = 1; i < argc; i++)
    {
        sorted_list[i-1] = strtod(argv[i],&end);
        if(end != '\0')
        {
            printf("error, not a double, it is %s", end);
            exit = EXIT_FAILURE;
            goto cleanup;
        }
    }
    

    
    bool is_sorted = false;
    unsigned int array_size = argc - 1;
    
    do
    {
        is_sorted = true;
        for(int i = 0; i < array_size-1; i++)
        {
            if(sorted_list[i] > sorted_list[i+1])
            {
                is_sorted = false;
                temp_double = sorted_list[i+1];
                sorted_list[i+1] = sorted_list[i];
                sorted_list[i] = temp_double;
            }
        }
        array_size--;
    }
    while(!is_sorted);
    
    for(int i = 0; i < argc - 1; i++)
    {
        printf("%f\n", sorted_list[i]);
    }

    cleanup:
    free(sorted_list);
    return exit;
}


