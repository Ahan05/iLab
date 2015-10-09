//
//  main.c
//  Onegin2
//
//  Created by Ahan Shabanov on 09.10.15.
//  Copyright © 2015 Ahan Shabanov. All rights reserved.
//

#include <stdio.h>

void sort(char** mass, const int n);

int main()
{
    char stish[256][256],p, *ukaz[256];
    int i,j = 0,n;
    printf("Введите количество строк ");
    scanf("%d", &n);
    scanf("%char",&p);
    
    
    for (i=0; i < n; i++)
    {
        for (j=0; (stish[i][j] = getchar()) != '\n';j++ )
        {
            if (j == 0) ukaz[i] = &stish[i][j];
        }
    }
    

    sort(ukaz, n);
    
    printf("Отсортированный массив:\n");
    
    for (i=0; i < n; i++)
     printf("%s", ukaz[i]);
    
    
    return 0;
}


void sort(char** mass, const int m)  //mass-массив  m-количество строк
{
    int t,j,ch;
    
    t = 0;
    while (t<(m-1))
    {
        if (*mass[t] > *mass[t+1])
        {
            ch = *mass[t];
            *mass[t] = *mass[t+1];
            *mass[t+1] = ch;
            j = t+1;
            if ((t-1) != -1)
                t = t-1;
        }
        else
            ++t;
        
    }
}