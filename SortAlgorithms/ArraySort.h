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
bool isSorted(T a[] , int lo , int hi , bool (*less)(T,T))
{
	bool flag = TRUE;
	for(int i=lo ; i<hi ; i++)
	{
		if( less(a[i+1],a[i]) )
			flag = FALSE;
	}
	return flag;
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


template<class T>//bubble sort
void bubbleSort(T a[] , int len , bool(*less)(T,T))
{
	int swap = 0;
	for(int i=0 ; i<len-1 ; i++)
	{
		for(int j=0 ; j<len-i-1 ; j++)
		{
			if( less(a[j+1],a[j]) )
			{
				exch(a,j,j+1);
				swap++;
			}
		}
		if(swap==0)	break;
	}
}


template<class T>//insertion sort
void insertSort(T a[] , int len , bool(*less)(T,T))
{
    for (int i=1; i<len; i++)
    { 
        for(int j = i ; j>0 && less(a[j],a[j-1]) ; j--)
        {
            exch(a,j,j-1);
        }
    }
}

template<class T>//insertion sort
void insertSort(T a[] , int lo , int hi , bool(*less)(T,T))
{
    for (int i=lo; i<=hi; i++)
    { 
        for(int j = i ; j>lo && less(a[j],a[j-1]) ; j--)
        {
            exch(a,j,j-1);
        }
    }
}

template<class T>//shell sort
void shellSort(T a[] , int len , bool(*less)(T,T))
{
	int h = 1;
	while(h < len/3)	h = 3 * h + 1;
	while(h >= 1)
	{
		for(int i=h ; i<len ; i++)
		{
			for(int j=i ; j>=h && less(a[j],a[j-h]) ; j-=h)
				exch(a,j,j-1);
		}
		h = h / 3;
		if( isSorted(a,0,len-1,less) )		break;
	}
}


template<class T>
void mergeSort(T a[] , int lo , int hi , bool(*less)(T,T))
{
	const int CUTOFF = 5;
	//if(hi <= lo)	return;
	if(hi-lo <= CUTOFF)	//use insertion sort to improve merge sort
	{
		insertSort(a,lo,hi,less);
		return;
	}

	int mid = (hi + lo)/2;
	if( !isSorted(a,lo,mid,less) )		mergeSort(a , lo , mid , less);
	if( !isSorted(a,mid+1,hi,less) )	mergeSort(a , mid+1 , hi , less);
	if( !less(a[mid] , a[mid+1]) )		merge(a , lo , mid , hi);
}

template<class T>
void merge(T a[] , int lo , int mid , int hi)
{
	int i = lo , j = mid+1;
	T *aux = new T[hi-lo+1];
	
	for(int k=lo ; k<=hi ; k++)
		aux[k-lo] = a[k];

	for(int k=lo ; k<=hi ; k++)
	{
		if(i > mid)							a[k] = aux[(j++)-lo];
		else if(j > hi)						a[k] = aux[(i++)-lo];
		else if(less(aux[i-lo] , aux[j-lo]))	a[k] = aux[(i++)-lo];
		else								a[k] = aux[(j++)-lo];
	}
	delete [] aux;
}



#endif
