/*
* Copyright (c) 2017 , LAIN
* All rights reserved
*
* name : Stack.h
* contents : TOP SECRET
*
* developed by Comcx
* created time : 
* Guide:
		���ø�ջ�ĸ�ʽ��Stack<dataType> [name]( int maxSize=20 )
*		��������
*
*/


#ifndef STACK_H
#define STACK_H

#include <iostream>

template <class T> 
class Stack{
private:
	int maxSize;									   //ջ�������
	T *content;								  //ջ��ָ��
	int top;										 //ջ�����
	static const int CAPACITY = 20;                                                 
public:
	//Stack();
	Stack( int maxSize=CAPACITY );                                       //��ʼ����Ĭ��ջ��СΪ20
	~Stack(){}                                                   //��������
																 //
	int getTop(){return top;}									//		
	int Size(){return (this->maxSize);}					   //��ȡ��С	
	bool isEmpty(){return ( this->top == -1 );}              //�Ƿ�Ϊ��
	bool isFull(){return (this->top == Size() );}           //�Ƿ�����
	void Push( T Elem );                             //ѹջ
	T Pop();                                        //��ջ
	void Show();                                          //��ʾ

};




template <class T> 
void Stack<T>::Show()
{
	if( !isEmpty() )
	{
		int flag = top;
		for ( ; flag>-1 ; flag-- )
			std::cout << content[flag] << std::endl;
	}
	else
		std::cerr << "Stack is empty!" << std::endl;
}


template <class T> 
Stack<T>::Stack( int maxSize )
{
	this->maxSize = maxSize;
	this->content = new T [maxSize];
	this->top = -1;
}


template <class T> 
void Stack<T>::Push( T Elem )
{
	if( !isFull() )
		content[++top] = Elem;
	else
		std::cerr << "Stack is full!" << std::endl;

}

template <class T> 
T Stack<T>::Pop()
{
	T Elem;
	if( !isEmpty() )
		Elem = content[top--];
	else
		std::cerr << "Stack is empty!" << std::endl;

	return Elem;
}





#endif//STACK_H
