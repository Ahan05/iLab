//
//  main.cpp
//  Stack
//
//  Created by Ahan Shabanov on 21.02.16.
//  Copyright © 2016 Ahan Shabanov. All rights reserved.
//
#include <stdint.h>
#include <assert.h>

class CStack
{
private:
    int theData[20];
    int theSize;
    int theLast;
    static int theNumber;   // колличество созданных стэков, если число больше 1 требует заплатить деньги
public:
    CStack();  // constr
    ~CStack();  // destruct
    void push (int val);
    void pop (int& temp);
    void add ();
    int GetNumb();
};

#include <iostream>

int main()
{
    int temp;
    CStack s;
    s.push(10);
    s.push(15);
    s.add();
    s.pop(temp);
    printf("%d, %d\n",temp, s.GetNumb());
    return 0;
}

int CStack:: theNumber = 0;

CStack::CStack() :
theData(),
theSize(15),
theLast(0)
{theNumber++;
if (theNumber > 1)
{
    printf("Pay money for the Full Version\n");
    assert(0);
}
}

CStack::~CStack()
{
    theNumber--;
    theSize = 0;
    theData[9] = {};
}

void CStack:: push(int val)
{
    if (theLast == theSize)
    {
        printf("STACK is FULL");
        assert(0);
    }
    
    theData[theLast] = val;
    (theLast)++;
}

void CStack:: pop (int& temp)
{
    if (theLast <= 0)
    {
        printf("STACK is empty");
        assert(0);
    }
    temp = theData[--theLast];
    theData[theLast] = '\0';
}

int CStack:: GetNumb()
{
    return theNumber;
}

void CStack:: add ()
{
    int a,b;
    if (theLast <= 1)
    {
        printf("STACK is empty");
        assert(0);
    }
    pop(a);
    pop(b);
    push(a+b);
}










