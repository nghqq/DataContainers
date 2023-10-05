#include<iostream>

class Element 
{
public:
	double data;
	Element* pPrev;
	Element* pNext;


		//Constuctor
	Element(double data) 
	{
		this->data = data;
		this->pNext = nullptr;
		this->pPrev = nullptr;
		std::cout << "EConstuctor:\t" << this << std::endl;
	}
	~Element() 
	{
		std::cout << "EDestuctor:\t" << this << std::endl;
	}
	friend class LinkedList;
};
class LinkedList 
{
	Element* Head;
	Element* Tail;
	int size;

public:
			//Constuctor

	LinkedList()
	{
		this->Head = nullptr;
		this->Tail = nullptr;
		this->size = 0;
		std::cout << "LLConstuctor:\t" << this << std::endl;
	}
	~LinkedList() 
	{
		std::cout << "LLDestuctor:\t" << this << std::endl;
	}
};



void main() 
{
	setlocale(LC_ALL, "");


}