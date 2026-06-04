#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>



int main(int argc, char* argv[argc+1])
{
    
    if(argc < 3)
    {
        printf("error, not enough arguments\n");
        return EXIT_FAILURE;
    }
    
    unsigned int max_string = 1;
    
    for(int i = 2; i < argc; i++)
    {
        if(strlen(argv[i]) > strlen(argv[max_string]))
        {
            max_string = i;
        }
    }
    
    char temp_string[strlen(argv[max_string])+1] = {};
    char (*sorted_list)[strlen(argv[max_string])+1] = malloc((strlen(argv[max_string])+1)*(argc-1));
    
    if(!sorted_list)
    {
        printf("error, could not successfully allocate memory");
        goto cleanup;
    }
    
    for(int i = 1; i < argc; i++)
    {
        strcpy(sorted_list[i-1],argv[i]);
    }
    
    bool is_sorted = false;
    unsigned int array_size = argc - 1;
    
    do
    {
        is_sorted = true;
        for(int i = 0; i < array_size-1; i++)
        {
            if(strcmp(sorted_list[i],sorted_list[i+1]) > 0)
            {
                is_sorted = false;
                strcpy(temp_string,sorted_list[i+1]);
                strcpy(sorted_list[i+1],sorted_list[i]);
                strcpy(sorted_list[i],temp_string);
            }
        }
        array_size--;
    }
    while(!is_sorted);
    
    for(int i = 0; i < argc - 1; i++)
    {
        printf("%s\n", sorted_list[i]);
    }

    cleanup:
    free(sorted_list);
    return EXIT_SUCCESS;
}


