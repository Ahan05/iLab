//
//  main.c
//  STACK
//
//  Created by Ahan Shabanov on 17.11.15.
//  Copyright © 2015 Ahan Shabanov. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "Cmd_List.h"

void push (int*, int, int*);
void pop (int*, int*, int*);
void add (int*, int*);


int main()
{
    FILE * in = fopen("output.txt", "r");
    int stack[50];
    int i,ch, elm = (-1), last; // ch - считываемое число  elm - элемент массива  last - индекс последенго элемента
    
    if(in == NULL)
    {
        printf("не могу открыть файл");
        assert(0);
    }
    
    for (i=0; feof(in) == 0; i++)
    {
        fscanf(in,"%d", &ch);
        //if ((ch % 2) == 0)
        if (ch == cmd_PUSH)
        {
            fscanf(in,"%d", &ch);
            push(stack, ch, &last);
            continue;
        }
        
        if (ch == cmd_POP)
        {
            pop(stack, &elm, &last);
            continue;
        }
        
        if (ch == cmd_ADD)
        {
            add(stack, &last);
            continue;
        }
    }
    printf("%d\n", elm);
    
    fclose(in);
    return 0;
}

void push (int* stack, int ch, int* last)
{
    stack[*last] = ch;
    (*last)++;
}

void pop (int* stack, int* elm, int* last)
{
    *elm = stack[*last];
    stack[*last] = '\0';
    (*last)--;
}

void add (int* stack, int* last)
{
    (*last) -= 2;
    push(stack, stack[*last+1] + stack[*last], last);
    stack[*last] = '\0';
    
}








