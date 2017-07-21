/*
* Copyright (c) 2017 , LAIN
* All rights reserved
*
* name : ArraySort.h
* contents : 
*
* developed by Comcx
* created time : prefecting...
*
*/

#ifndef ARRAYSORT_H
#define ARRAYSORT_H

#include "lain.h"

bool less(int a , int b)	//比较函数
{
	return a<b?TRUE:FALSE;
}

template<class T>
void exch(T a[] , int i , int j)
{
	T temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

//-------------------------------------------------------------------
//Sort Algorithms

template<class T>//selection sort
void selectSort(T a[] , int len , bool(*less)(T,T))
{
	for(int i=0 ; i<len ; i++)
	{
		for(int j=i ; j<len ; j++)
		{
			if( less(a[j],a[i]) )
			{
				exch(a,i,j);
			}
		}
	}
}


template<class T>//insertion sort
void insertSort(T a[] , int len , bool(*less)(T,T))
{
    for (int j=1; j<len; j++)
    {
        T key = a[j];
        int i = j-1;
        while (i>=0 && less(key,a[i]))
        {
            a[i+1] = a[i];
            i--;
        }
        a[i+1] = key;
    }
}



#endif
