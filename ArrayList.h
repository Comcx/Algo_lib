#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include "LinearList.h"

//ArrayList(Stack)
template<class T>
class ArrayList : public LinearList<T>{
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

};

template<class T>
class ArrayStack : public ArrayList<T> {};

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


#endif
