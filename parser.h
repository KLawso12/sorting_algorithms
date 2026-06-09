#ifndef PARSER_H
# define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>



size_t MaxFileStringLength(char filename[], size_t mx_str_ln);

size_t MaxArgvStringLength(int argc, char *argv[], size_t maximum_string_length, int argv_start);

char **allocated_strings(size_t numberOfStrings, size_t maximum_string_length);

void Deallocate_string(char ***allocated_strings, size_t numberOfStrings);



size_t MaxFileStringLength(char filename[], size_t mx_str_ln) //the idea here is that it will return a string, or mx_str_ln if not.
{
    FILE* fileptr;
    fpos_t filepos = 0;
    fpos_t filepos_last = 0;
    size_t maximum_string_length = 0;
    
    fileptr = fopen(filename, "r");
    if(!fileptr)
    {
        printf("error: the file is not real\n");
        return mx_str_ln;
    }
    else
    {
        char c;
        bool valid_terminate;
        size_t strsize = 4;
        char *thestring = malloc(strsize); // choosing to store a nebulous amount of data, if we need more, we'll just double it
        
        if(!thestring)
        {
            printf("error: could not allocate memory\n");
            return 0;
        }
        while ((c = fgetc(fileptr)) != EOF )
        {  
            fsetpos(fileptr, &filepos_last);
            getstring:
            valid_terminate = false;
            for(int i = 0; i < strsize; i++)
            {
                c = fgetc(fileptr);
                if(c == EOF)
                {
                    thestring[i] = '\0';
                    valid_terminate = true;
                    break;
                }
                thestring[i] = c;
                if(thestring[i] == '\n' && i < strsize - 1)
                {
                    thestring[i+1] = '\0';
                    valid_terminate = true;
                    break;
                }
            }
            fgetpos(fileptr, &filepos);
            if(!valid_terminate)
            {
                strsize *= 2;
                thestring = realloc(thestring, strsize);
                if(!thestring)
                {
                    printf("Error: could not reallocate memory\n");
                    free(thestring);
                    fclose(fileptr);
                    return 0;
                }
                fsetpos(fileptr, &filepos_last);
                goto getstring;
            }
            else
            {
                filepos_last = filepos;
                if(strlen(thestring) + 1 > maximum_string_length)
                {
                    maximum_string_length = strlen(thestring) + 1;
                }
            }
        }
        free(thestring);
        fclose(fileptr);
    }
    
    

    
    return (maximum_string_length > mx_str_ln) ? maximum_string_length : mx_str_ln;
}

size_t MaxArgvStringLength(int argc, char *argv[], size_t maximum_string_length, int argv_start)
{
    size_t max_string = 1;
    
    for(int i = argv_start; i < argc; i++)
    {
        if(strlen(argv[i]) > strlen(argv[max_string]))
        {
            max_string = i;
        }
    }
    
    if(strlen(argv[max_string])+1 > maximum_string_length)
    {
        maximum_string_length = strlen(argv[max_string])+1;
    }
    
    return max_string;
}



char **allocated_strings(size_t numberOfStrings, size_t maximum_string_length)
{
    char **allocated_strings = malloc(numberOfStrings * sizeof(char*));
    if(!allocated_strings)
    {
        return nullptr;
    }
    
    for(size_t i = 0; i < numberOfStrings; i++)
    {
        allocated_strings[i] = malloc(maximum_string_length);
        
        if(!allocated_strings[i])
        {
            for(int j = 0; j < i; j++)
            {
                free(allocated_strings[j]);
            }
            free(allocated_strings);
            return nullptr;
        }
    }
    return allocated_strings;
}

void Deallocate_string(char ***allocated_strings, size_t numberOfStrings)
{
    if(!allocated_strings || !*allocated_strings)
    {
        return;
    }
    
    for(int i = 0; i < numberOfStrings; i++)
    {
        free((*allocated_strings)[i]);
    }
    free(*allocated_strings);
    *allocated_strings = nullptr;
    return;
}

// todo:
// string number counter
// file strings to allocated strings
// argv strings to allocated strings
// everything involving floats
// comparison stuff maybe

#endif
