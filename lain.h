/*
* Copyright (c) 2017 , LAIN
* All rights reserved
*
* name : lain.h
* contents : 
*
* developed by Comcx
* created time : prefecting...
*
*/

#ifndef LAIN_H
#define LAIN_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <cctype>
#include <cmath>

#define OK 1
#define ERROR -1
#define TRUE 1
#define FALSE 0
#define STOP 0

//=========================================================================
//Arsenal

template<class T>
class Comparable{
public:
	virtual ~Comparable() {}
	virtual bool compareTo(T a , T b , bool (*less)(T,T)) const = 0;
	virtual void exch(int i , int j) = 0;
	virtual bool isSorted(int lo , int hi , bool (*less)(T,T)) = 0;
	virtual void sort(bool (*less)(T,T)) = 0;
	virtual void sort(void (*_sort)(T a[] , int len , bool(*less)(T,T)) , bool(*less)(T,T)) = 0;
	virtual void sort(void (*_sort)(T a[] , int lo , int hi , bool(*less)(T,T)) , bool(*less)(T,T) , int lo , int hi) = 0;

};


//-------------------------------------------------------------------------
//the abstract class of linear list

template<class T>
class LinearList{
public:
	virtual ~LinearList() {};
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual T& get(int theIndex) const = 0;
	virtual int indexOf(const T& theElem) const = 0;
	virtual void erase(int theIndex) = 0;
	virtual void insert(int theIndex , const T& theElem) = 0;
	virtual void show(std::ostream& out) const = 0;

};

//------------------------------------------------------------------------

//node defination for linked list 
template<class T>
struct ChainNode{
	T elem;
	ChainNode<T> *next;

	ChainNode() {}
	ChainNode(const T& theElem) {this->elem = theElem;}
	ChainNode(const T& theElem , ChainNode<T> *next){
		this->elem = theElem;
		this->next = next;
	}
};

//the linked list which extends from linear list
template<class T>
class LinkedList : public LinearList<T>{
protected:
	int listSize;
	ChainNode<T> *firstNode;
	void checkIndex(int theIndex) const;

public:
	LinkedList(int initialCapacity = 20);											//construction
	LinkedList(const LinkedList<T>&);												//copy to struct
	~LinkedList();																	//delete the whole linked list

	bool empty() const {return listSize==0;}
	int size() const {return listSize;}
	T& get(int theIndex) const;														//get the element of theIndex
	inline ChainNode<T> *findPrior(int theIndex);
	inline ChainNode<T> *findLast();
	int indexOf(const T& theElem) const;											//return the index of theElem
	void erase(int theIndex);														//erase the theIndexth node
	void insert(int theIndex , const T& theElem);									//	insert theElem to make the node be the
																					//									theIndexth node
	void pushBack(const T &theElem);
	T popBack();
	void show(std::ostream& out) const;

};

template<class T>
class LinkedStack : public LinkedList<T> {};

template<class T>
LinkedList<T>::LinkedList(int initialCapacity)
{
	if(initialCapacity < 1)
    {
    	std::ostringstream s;
    	s << "initialCapacity = " << initialCapacity << "Must be > 0";
    	std::cerr << s.str();
    }
    this->firstNode = NULL;
    this->listSize = 0;
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& theList)
{
	this->listSize = theList.listSize;

	if(listSize == 0)
	{
		this->firstNode = NULL;
		return;
	}

	ChainNode<T> *sourceNode = theList.firstNode;
	firstNode = new ChainNode<T>(sourceNode->elem);
	sourceNode = sourceNode->next;
	ChainNode<T> *targetNode = firstNode;
	while(sourceNode != NULL)
	{
		targetNode->next = new ChainNode<T>(sourceNode->elem);
		targetNode = targetNode->next;
		sourceNode = sourceNode->next;
	}
	targetNode->next = NULL;
}

template<class T>
LinkedList<T>::~LinkedList()
{
	while(firstNode != NULL)
	{
		ChainNode<T> *nextNode = firstNode->next;
		delete firstNode;
		firstNode = nextNode;
	}
}

template<class T>
T& LinkedList<T>::get(int theIndex) const
{
	ChainNode<T> *currentNode = this->firstNode;
	for(int i=0 ; i<theIndex ; i++)
	{
		currentNode = currentNode->next;
	}

	return currentNode->elem;
}

template<class T>
ChainNode<T>* LinkedList<T>::findPrior(int theIndex)
{
	ChainNode<T> *priorNode = this->firstNode;
	for(int i=0 ; i<theIndex-1 ; i++)										//find the prior node of the theIndexth node
	{
		priorNode = priorNode->next;
	}
	return priorNode;
}

template<class T>
ChainNode<T> *LinkedList<T>::findLast()
{
	ChainNode<T> *currentNode = this->firstNode;
	while(currentNode->next != NULL)
	{
		currentNode = currentNode->next;
	}
	return currentNode;
}

template<class T>
int LinkedList<T>::indexOf(const T& theElem) const
{
	ChainNode<T> *currentNode = this->firstNode;
	int index = 0;
	while(currentNode != NULL &&
		  currentNode->elem != theElem)
	{
		currentNode = currentNode->next;
		index++;
	}

	if(currentNode == NULL)	return FALSE;
	else
		return index;
}

template<class T>
void LinkedList<T>::erase(int theIndex)
{
	checkIndex(theIndex);
	ChainNode<T> *targetNode = this->firstNode;

	if(theIndex == 0)
	{
		
		this->firstNode = this->firstNode->next;
	}
	else
	{
		ChainNode<T> *priorNode = findPrior(theIndex);
		targetNode = priorNode->next;
		priorNode->next = priorNode->next->next;
	}
	
	delete targetNode;
	this->listSize--;
}

template<class T>
void LinkedList<T>::insert(int theIndex , const T& theElem)
{
	if(theIndex<0 || theIndex>listSize)
	{
		std::ostringstream os;
		os << "index = " << theIndex << " size = " << listSize;
		std::cerr << os.str();
		return;
	}

	if(theIndex == 0)
	{
 		this->firstNode = new ChainNode<T>(theElem , firstNode);
	}
	else
	{
		ChainNode<T> *priorNode = findPrior(theIndex);
		ChainNode<T> *targetNode = new ChainNode<T>(theElem , priorNode->next);
		priorNode->next = targetNode;
	}
	
	this->listSize++;
}

template<class T>
void LinkedList<T>::pushBack(const T &theElem)
{
	insert(listSize , theElem);
}

template<class T>
T LinkedList<T>::popBack()
{
	T target = get(listSize-1);
	erase(listSize-1);
	return target;
}

template<class T>
void LinkedList<T>::show(std::ostream &out) const
{
	ChainNode<T> *currentNode = this->firstNode;
	while(currentNode != NULL)
	{
		out << currentNode->elem << " ";
		currentNode = currentNode->next;
	}
}

template<class T>
void LinkedList<T>::checkIndex(int theIndex) const
{
	if(theIndex<0 || theIndex>listSize-1)
	{
		std::ostringstream os;
		os << "index = " << theIndex << " size = " << listSize;
		std::cerr << os.str();
	}
}

template<class T>
std::ostream& operator<<(std::ostream& out , const LinkedList<T> &x)
{
	x.show(out);
	return out;
}



//---------------------------------------------------------------------------
//ArrayList(Stack)
template<class T>
class ArrayList : public LinearList<T> , public Comparable<T>{
protected:
	T *elem;
	int top;
	int capacity;
	int listSize;
	void checkIndex(int theIndex) const;

public:
	ArrayList(int capacity = 20);
	ArrayList(const ArrayList<T>&);
	~ArrayList() {delete [] elem;}

	bool empty() const {return listSize == 0;}
	int size() const {return listSize;}
	T& get(int theIndex) const;
	int indexOf(const T& theElem) const;
	void erase(int theIndex);
	void insert(int theIndex , const T& theElem);
	void pushBack(const T &theElem);
	T popBack();
	void show(std::ostream& out) const;
	bool compareTo(T a , T b , bool (*less)(T,T)) const;
	void exch(int i , int j);
	bool isSorted(int lo , int hi , bool (*less)(T,T));
	void sort(bool (*less)(T,T));
	void sort(void (*_sort)(T a[] , int len , bool(*less)(T,T)) , bool(*less)(T,T));
	void sort(void (*_sort)(T a[] , int lo , int hi , bool(*less)(T,T)) , bool(*less)(T,T) , int lo , int hi);
};

template<class T>
class ArrayStack : public ArrayList<T> {
public:
	ArrayStack(int capacity = 20) : ArrayList<T>::ArrayList(capacity) {}
	ArrayStack(const ArrayStack<T> &theStack) : ArrayList<T>::ArrayList(theStack) {}

};	//ArrayStack

template<class T>
ArrayList<T>::ArrayList(int capacity)
{
	if(capacity < 1)
	{
		std::cerr << "initial Capacity = " << capacity << "Must be > 0";
	}

	this->capacity = capacity;
	this->elem = new T[capacity];
	this->listSize = 0;
	this->top = -1;
}

template<class T>
ArrayList<T>::ArrayList(const ArrayList<T> &theList)
{
	this->capacity = theList.capacity;
	this->listSize = theList.listSize;
	this->elem = new T[this->capacity];

	for(int i=0 ; i<this->capacity ; i++)
	{
		this->elem[i] = theList.elem[i];
	}
	this->top = theList.top;
}

template<class T>
T& ArrayList<T>::get(int theIndex) const
{
	checkIndex(theIndex);
	return this->elem[theIndex];
}

template<class T>
int ArrayList<T>::indexOf(const T& theElem) const
{
	int index = 0;
	while(index<listSize || elem[index]!=theElem)
	{
		index++;
	}
	if(index == listSize)
	{
		std::cerr << "Failed to find " << theElem << std::endl;
		return FALSE;
	}
	else
	{
		return index;
	}
}

template<class T>
void ArrayList<T>::erase(int theIndex)
{
	checkIndex(theIndex);
	for(int i=theIndex ; i<listSize-1 ; i++)
	{
		elem[i] = elem[i+1];
	}
	this->listSize--;
	this->top--;
}

template<class T>
void ArrayList<T>::insert(int theIndex , const T& theElem)
{
	if(theIndex<0 || theIndex>listSize || listSize==capacity)
	{
		std::ostringstream os;
		os << "index = " << theIndex << " size = " << listSize;
		std::cerr << os.str();
		return;
	}

	for(int i=theIndex ; i<listSize-1 ; i++)
	{
		elem[i+1] = elem[i];
	}
	elem[theIndex] = theElem;
	this->listSize++;
	this->top++;
}

template<class T>
void ArrayList<T>::pushBack(const T& theElem)
{
	if(listSize != capacity)
	{
		insert(listSize , theElem);
	}
	else
	{
		std::cerr << "the container is full!" << std::endl;
	}
}

template<class T>
T ArrayList<T>::popBack()
{
	T target = this->elem[top];
	erase(top);
	return target;
}

template<class T>
void ArrayList<T>::checkIndex(int theIndex) const
{
	if(theIndex<0 || theIndex>listSize-1)
	{
		std::ostringstream os;
		os << "index = " << theIndex << " size = " << listSize;
		std::cerr << os.str();
	}
}

template<class T>
void ArrayList<T>::show(std::ostream &out) const
{
	if(empty())
	{
		std::cerr << "The container is empty!" << std::endl;
		return;
	}
	else
	{
		for(int i=0 ; i<listSize ; i++)
		{
			out << elem[i] << " ";
		}
	}
}

template<class T>
std::ostream& operator<<(std::ostream &out , const ArrayList<T> &x)
{
	x.show(out);
	return out;
}

template<class T>
bool ArrayList<T>::compareTo(T a , T b , bool (*less)(T,T)) const
{
	return less(a,b);
}

template<class T>
void ArrayList<T>::exch(int i , int j)
{
	T temp = elem[i];
	elem[i] = elem[j];
	elem[j] = temp;
}

template<class T>
bool ArrayList<T>::isSorted(int lo , int hi , bool (*less)(T,T))
{
	bool flag = TRUE;
	for(int i=lo ; i<hi ; i++)
	{
		if( less(elem[i+1],elem[i]) )
			flag = FALSE;
	}
	return flag;
}

template<class T>
void ArrayList<T>::sort(bool (*less)(T,T))
{
	for(int i=0 ; i<listSize ; i++)
	{
		for(int j=i ; j<listSize ; j++)
		{
			if( compareTo(elem[j],elem[i],less) )
			{
				exch(i,j);
			}
		}
	}
}

template<class T>
void ArrayList<T>::sort(void (*_sort)(T a[] , int len , bool(*less)(T,T)) , bool(*less)(T,T))
{
	if(!isSorted(0,listSize-1,less))
		_sort(elem , listSize , less);
}


template<class T>
void ArrayList<T>::sort(void (*_sort)(T a[] , int lo , int hi , bool(*less)(T,T)) , bool(*less)(T,T) , int lo , int hi)
{
	if(!isSorted(lo,hi,less))
		_sort(elem , lo , hi , less);
}




template<class T>
class BinaryHeap : public ArrayList<T>{
public:
	BinaryHeap(int capacity = 20);
	BinaryHeap(const BinaryHeap<T> &theHeap);
	~BinaryHeap();

	T delMax();
	void insert(const T theElem);
	void swim(int k);
	void sink(int k);
	void show(std::ostream &out) const;

};


template<class T>
BinaryHeap<T>::BinaryHeap(int capacity)
	:ArrayList(capacity)
{
	pushBack(-1);		//start from index 1
}

template<class T>
BinaryHeap<T>::BinaryHeap(const BinaryHeap<T> &theHeap)
	:ArrayList<T>::ArrayList(theHeap)
{

}

template<class T>
BinaryHeap<T>::~BinaryHeap()
{
	ArrayList<T>::~ArrayList();
}

template<class T>
T BinaryHeap<T>::delMax()
{
	T max = this->elem[1];
	exch(1 , top);
	popBack();
	sink(1);
	return max;
}

template<class T>
void BinaryHeap<T>::insert(const T theElem)
{
	pushBack(theElem);
	swim(top);
}

template<class T>
void BinaryHeap<T>::swim(int k)
{
	while( less(elem[k/2],elem[k]) && k > 1 )
	{
		exch(k/2,k);
		k = k / 2;
	}
}

template<class T>
void BinaryHeap<T>::sink(int k)
{
	while(2*k <= top)
	{
		int j = 2 * k;
		if( j<top && less(elem[j],elem[j+1]) )	j++;
		if( !less(elem[k],elem[j]) )	break;
		exch(k,j);
		k = j;
	}
}

template<class T>
void BinaryHeap<T>::show(std::ostream &out) const
{
	if(top == 0)
	{
		std::cerr << "The container is empty!" << std::endl;
		return;
	}
	else
	{
		for(int i=1 ; i<listSize ; i++)
		{
			out << elem[i] << " ";
		}
	}
}


template<class T>
std::ostream& operator<<(std::ostream &out , const BinaryHeap<T> &x)
{
	x.show(out);
	return out;
}


template<class T>
class PriorityQueue : public BinaryHeap<T>{
protected:

public:
	PriorityQueue(int capacity = 20) : BinaryHeap<T>::BinaryHeap(capacity) {}
	PriorityQueue(const PriorityQueue<T> &theQueue) : BinaryHeap<T>::BinaryHeap(theQueue) {}



};


#endif
