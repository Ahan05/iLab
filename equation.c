//
//  main.c
//  Squared equasion
//
//  Created by Ahan Shabanov on 30.09.15.
//  Copyright © 2015 Ahan Shabanov. All rights reserved.
//

#include <stdio.h>
#include <assert.h>
#include <math.h>

void proverka(char* m);
void perevod(char* str, float* p);
void reshenie(float a, float b, float c, int* chek, float* x1, float* x2);

int main()
{
    char mass1[256], mass2[256], mass3[256];
    int  chek = 0;
    float a=0.0,b=0.0,c=0.0, x1=0.0, x2=0.0;
    
    printf("Введите число а = \n");
    scanf("%s",mass1);
    
    printf("Введите число b = \n");
    scanf("%s",mass2);
    
    printf("Введите число c = \n");
    scanf("%s",mass3);
    
    proverka(mass1);
    proverka(mass2);   
    proverka(mass3);
    
    perevod(mass1, &a);
    perevod(mass2, &b);
    perevod(mass3, &c);
    
    reshenie(a,b,c, &chek, &x1, &x2);
    
    if (chek == 1)
        printf("Бесконечно много решений");
    else if (chek == 2)
        printf("Решений нет");
    else if (chek == 3)
        printf("x1 = %f", x1);
    else if (chek == 0)
        printf("x1 = %f x2 = %f", x1, x2);
    printf("\n");
}

void proverka(char* str)   // проверяет на правильность ввода
{
    int i;
    for (i=0; str[i] != '\0'; ++i)
    {
        if (i>0)
            assert ( (str[i] != '-') || (str[i] != '+') );
        
        if ( (str[i] != '-') && (str[i] != '+') && (str[i] != '.') )
            assert( (str[i] >= '0') && (str[i] <= '9') );

    }
    
}


void perevod(char* str, float* p)   // перевод из символов в цифры
{
    int point=0, i;
    float del = 0.0;
    for (i=0; str[i] != '\0'; ++i)
    {
        if ((str[i] == '-') || (str[i] == '+'))
            continue;
        
        if (str[i] == '.')
        {
            assert(point < 2);
            point++;
            continue;
        }
        if (point == 0)
            *p = *p * 10 + (str[i] - '0');
        else
        {
            del = del / 10;
            *p = *p + del * (str[i] - '0');
        }
    }
    if (str[0] == '-')
        *p = *p * (-1);
}

void reshenie(float a, float b, float c, int* chek, float* x1, float* x2)
    {
        float d;
        if (a==0)
        {
            if ((b == 0) && (c == 0))
            {
                *chek = 1;  // 1 - бескончено много
            }
            
            if ((b == 0) && (c != 0))
            {
                *chek = 2;  // 2 - нет решений
            }
            
            if (b != 0)
            {
                *x1 = (-c/b);
                *chek = 3;    // 3 - одно решение
            }
        }
        else
        {
            d=b*b-4*a*c;
            if (d >= 0)
            {
                if (d == 0)
                {
                    *x1 = (-b/(2*a));
                    *chek = 3; // 3 - одно решение
                }
                else
                {
                    *x1= (-b+sqrtf(d))/(2*a);
                    *x2= (-b-sqrtf(d))/(2*a);
                    *chek = 0; // 0 - два решения
                }
                
            }
            else
                *chek = 2; //  2 - нет решений
        }

        
    }







