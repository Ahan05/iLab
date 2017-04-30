//
//  main.c
//  Assembler
//
//  Created by Ahan Shabanov on 17.11.15.
//  Copyright © 2015 Ahan Shabanov. All rights reserved.
//

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "Cmd_List.h"
// функции без аргрументов должны быть превращаться в нечетные числа!!!!


#define DEF_CMD(l)\
if (strcmp(str, Mass[l].name) == 0)\
{\
fprintf(out,"%d ", Mass[l].num);\
ptr_arg = Mass[l].num;\
}


void clean_str(char *);
int search_int (char*);

int main()
{
    int l=0,i, j, ptr_arg = 0; // ptr_arg говорит есть ли зависимый аргумент l - счетчик по Mass
    char sym;
    char *str;// sym - считываемый символ, str - строка из input
    
    FILE * in = fopen("input.txt", "r");
    FILE * out = fopen ("output.txt", "w");
    
    str = (char*) calloc(10, sizeof(char));
    
    if(in == NULL)
    {
        printf("не могу открыть файл '%s'",str);
        assert(0);
    }
    
    
    for (i=0, j=0; feof(in) == 0; i++, j++)
    {
        sym = fgetc(in);
        str[j] = sym;
        for (l=0; l < (sizeof(Mass) / sizeof(struct MassOfCmd)); l++)
            DEF_CMD(l);
        
        if (str[j] == '\n')
        {
            if ((ptr_arg % 2) == 0)
                fprintf(out,"%d ",search_int(str));
            clean_str(str);
            j = (-1);
        }
    }
    fclose(in);
    fclose(out);
    return 0;
}

void clean_str(char * str)
{
    int i;
    for (i=0; str[i] != '\0'; i++)
    {
        str[i] = '\0';
    }
}

int search_int (char* str)
{
    int i, ch = 0;
    for (i=0; str[i] != '\n'; i++)
    {
        if ( (str[i] >= '0') && ( str[i] <= '9') )
            ch = (ch*10 + (str[i] - '0')) ;
    }
    return ch;
}
