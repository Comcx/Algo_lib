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
		调用该栈的格式：Stack<dataType> [name]( int maxSize=20 )
*		基本操作
*
*/


#ifndef STACK_H
#define STACK_H

#include <iostream>

template <class T> 
class Stack{
private:
	int maxSize;									   //栈最大容量
	T *content;								  //栈底指针
	int top;										 //栈顶序号
	static const int CAPACITY = 20;                                                 
public:
	//Stack();
	Stack( int maxSize=CAPACITY );                                       //初始化，默认栈大小为20
	~Stack(){}                                                   //析构函数
																 //
	int getTop(){return top;}									//		
	int Size(){return (this->maxSize);}					   //获取大小	
	bool isEmpty(){return ( this->top == -1 );}              //是否为空
	bool isFull(){return (this->top == Size() );}           //是否填满
	void Push( T Elem );                             //压栈
	T Pop();                                        //出栈
	void Show();                                          //显示

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
