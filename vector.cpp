//
//  main.cpp
//  vector
//
//  Created by Ahan Shabanov on 12.03.16.
//  Copyright © 2016 Ahan Shabanov. All rights reserved.
//

#include <iostream>
#include <assert.h>

class Cvector
{
private:
    int size_;
    int *data_;
    
public:
    Cvector(int n);  // constr
    Cvector();
    ~Cvector();  // destruct
    Cvector(const Cvector &a);
    int& operator [] (int index)
    {
        assert((index >= 0) && (index < size_));
        return data_[index];
    }
    Cvector operator += (Cvector &v1)
    {
        int i;
        for (i=0; i<size_; i++)
        {
            data_[i] = v1.data_[i] + data_[i];
        }
        return *this;
    }
    void print_vec()
    {
        int i;
        for (i=0; i<size_; i++)
        {
            printf("%d ", data_[i]);
        }
        printf("\n");
    }
    Cvector operator +(Cvector &v1)
    {
        Cvector temp;
        int i;
        for (i=0; i<size_; i++)
        {
            temp[i] = data_[i] + v1.data_[i];
        }
        return temp;
    }
    Cvector operator = (Cvector v1)
    {
        int i;
        for (i=0; i<size_; i++)
        {
            data_[i] = v1[i];
        }
        return *this;
    }
    Cvector operator * (int k)
    {
        int i;
        for (i=0; i<size_; i++)
        {
            data_[i] = data_[i]*k;
        }
        return *this;
    }
    friend Cvector operator * (int k, Cvector& v1)
    {
        int i;
        for (i=0; i<v1.size_; i++)
        {
            v1.data_[i] = v1.data_[i]*k;
        }
        return v1;
    }
    

};

int main()
{
    Cvector v1(5), v2(5), v3(5), v4(5);
    v1[0] = 1;
    v2[2] = 5;
    v1 += v2;
    v1.print_vec();
    v2.print_vec();

    v3 = v1 + v2;
    v4 = v1 + v2;
    
    v4.print_vec();
    v3.print_vec();
    
    v3*4;
    4*v4;
    v3.print_vec();
    v4.print_vec();
    return 0;
}

Cvector::~Cvector()
{
    delete [] data_;
    size_ = 0;
}

Cvector::Cvector(int n)
{
    data_ = new int[n];
    if (!data_) assert(0);
    int i;
    for (i=0; i<n; i++)
    {
        data_[i] = 0;
    }
    size_ = n;
}

Cvector::Cvector()
{
    data_ = new int[10];
    int i;
    for (i=0; i<10; i++)
    {
        data_[i] = 0;
    }
    if (!data_) assert(0);
        size_ = 10;
}

Cvector::Cvector(const Cvector &a)
{
    int i;
    data_ = new int[a.size_];
    if ( !data_) exit(1);
    for(i=0; i<a.size_; i++) data_[i] = a.data_[i];
}













