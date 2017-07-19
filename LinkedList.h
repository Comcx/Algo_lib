
#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "LinearList.h"

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
	LinkedList(int initialCapacity = 20);	//construction
	LinkedList(const LinkedList<T>&);	//copy to struct
	~LinkedList();	//delete

	bool empty() const {return listSize==0;}
	int size() const {return listSize;}
	T& get(int theIndex) const;
	int indexOf(const T& theElem) const;
	void erase(int theIndex);
	void insert(int theIndex , T& theElem);
	void show(ostream& out) const;

};

template<class T>
LinkedList<T>::LinkedList(int initialCapacity)
{
	if(initialCapacity < 1)
    {
    	ostringstream s;
    	s << "initialCapacity = " << initialCapacity << "Must be > 0";
    	throw illegalParameterValue(s.str());
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
		currentNode = currentNode->next;

	return currentNode->elem;
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

	ChainNode<T> *priorNode = this->firstNode;
	ChainNode<T> *targetNode;

	if(theIndex == 0)
	{
		targetNode = this->firstNode;
		this->firstNode = this->firstNode->next;
	}
	else
	{
		for(int i=0 ; i<theIndex-1 ; i++)
			priorNode = priorNode->next;

		targetNode = priorNode->next;
		priorNode->next = priorNode->next->next;
	}
	
	delete targetNode;
	this->listSize--;
}

template<class T>
void LinkedList<T>::insert(int theIndex , T& theElem)
{
	checkIndex(theIndex);

	if(theIndex == 0)
		this->firstNode->elem = theElem;

	ChainNode<T> *priorNode = this->firstNode;
	for(int i=0 ; i<theIndex-1 ; i++)	//find the prior node of the node we try to insert
		priorNode = priorNode->next;

	ChainNode<T> *targetNode = new ChainNode<T>(theElem , priorNode->next);
	priorNode->next = targetNode;

	listSize++;
}

template<class T>
void LinkedList<T>::show(ostream &out) const
{
	ChainNode<T> *currentNode = this->firstNode;
	while(currentNode != NULL)
	{
		out << currentNode << " ";
		currentNode = currentNode->next;
	}
}

template<class T>
void LinkedList<T>::checkIndex(int theIndex) const
{
	if(theIndex<0 || theIndex>listSize)
	{
		ostringstream os;
		os << "index = " << theIndex << " size = " << listSize;
		throw illegalIndex(os.str());
	}
}



#endif