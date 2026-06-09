#ifndef PARSER_H
# define PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>



size_t MaxFileStringLength(char filename[], size_t mx_str_ln);

size_t MaxArgvStringLength(int argc, char *argv[], size_t maximum_string_length, size_t argv_start);

size_t StringCounter(size_t numberOfStrings, size_t maximum_string_length, char filename[]);

char **allocated_strings(size_t numberOfStrings, size_t maximum_string_length);

void Deallocate_string(char ***allocated_strings, size_t numberOfStrings);

void AllocateStringsFromFile(char filename[], size_t *allocation_position,char ***allocated_strings, size_t maximum_string_length, size_t numberOfStrings);




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

size_t MaxArgvStringLength(int argc, char *argv[], size_t maximum_string_length, size_t argv_start)
{
    if(argv_start >= argc)
    {
        printf("error: not enough arguments");
        return maximum_string_length;
    }
    
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

size_t StringCounter(size_t numberOfStrings, size_t maximum_string_length, char filename[])
{
    FILE *thefile;
    thefile = fopen(filename,"r");
    if(!thefile)
    {
        printf("error: the file is not real\n");
        return numberOfStrings;
    }
    char c = 0;
    size_t strings = numberOfStrings;
    while(c != EOF)
    {
        c = fgetc(thefile);
        if(c == '\n')
        {
            strings++;
        }
    }
    strings++;
            
    fclose(thefile);
    return strings;
}

char **allocated_strings(size_t numberOfStrings, size_t maximum_string_length)
{
    char **allocated_strings = malloc(numberOfStrings * sizeof(char*));
    if(!allocated_strings)
    {
        printf("error: could not allocate memory\n");
        return nullptr;
    }
    
    for(size_t i = 0; i < numberOfStrings; i++)
    {
        allocated_strings[i] = malloc(maximum_string_length);
        
        if(!allocated_strings[i])
        {
            printf("error: could not allocate memory\n");
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
        printf("error: allocated strings are not real\n");
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

void AllocateStringsFromFile(char filename[], size_t *allocation_position, char ***allocated_strings, size_t maximum_string_length, size_t numberOfStrings)
{
    if(!allocated_strings || !*allocated_strings)
    {
        printf("error: allocated strings are not real\n");
        return;
    }
    
    FILE *thefile;
    fpos_t filepos = 0;
    thefile = fopen(filename, "r");
    if(!thefile)
    {
        printf("error: file is not real\n");
        return;
    }
    
    if(*allocation_position > numberOfStrings)
    {
        printf("error: not enough memory allocated");
        return;
    }
    
    char c;
    while((c = fgetc(thefile)) != EOF)
    {
        fsetpos(thefile,&filepos);
        fgets((*allocated_strings)[*allocation_position], maximum_string_length,thefile);
        fgetpos(thefile,&filepos);
        (*allocation_position)++;
        if(*allocation_position > numberOfStrings)
        {
            printf("error: not enough memory allocated");
            return;
        }
    }
    
    
    fclose(thefile);
    return;
}

void AllocateStringsFromArgv(size_t argv_start, char *argv[], int argc, char ***allocated_strings, size_t *allocation_position, size_t numberOfStrings)
{
    if(!allocated_strings || !*allocated_strings)
    {
        printf("error: allocated strings are not real");
        return;
    }
    if(argv_start >= argc)
    {
        printf("error: not enough arguments");
        return;
    }
    if(*allocation_position > numberOfStrings)
    {
        printf("error: not enough memory allocated");
        return;
    }
    
    for(int i = argv_start; i < argc; i++)
    {
        
        strcpy((*allocated_strings)[*allocation_position], argv[i]);
        (*allocation_position)++;
        if(*allocation_position > numberOfStrings)
        {
            printf("error: not enough memory allocated");
            return;
        }
    }
    
    return;
}


// todo:
// everything involving floats
// comparison stuff maybe

#endif
