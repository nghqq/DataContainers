#include <iostream>

#define tab "\t"

class Element 
{
	int Data;
	Element* pNext;

public:
		//Constuctors

	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		std::cout << "EConstructor:\t " << std::endl;
	}
	~Element() 
	{
		std::cout << "EDestructor:\t " << std::endl;
	}
	friend class ForwardList;
};
class ForwardList 
{
	//Forward - односвязанный, однонаправленный 
	Element* Head;

public:
	   //Constuctors
	ForwardList()
	{
		this->Head = nullptr;
		std::cout << "LConstructor:\t" << this << std::endl;
	}
	~ForwardList()
	{
		std::cout << "LDestructor:\t" << this << std::endl;
	}
					//Adding element

	void push_front(int Data)
	{
		//1) Создаем элемент для добавляемого значения:
		Element* New = new Element(Data);
		//2) Пристыковываем элемент к списку:
		New->pNext = Head;
		//3) Теперь новый элемент является начальным элементом списка:
		Head = New;
	}
	void push_back(int Data,int n) 
	{
		Element* New = new Element(Data);
		 //2) Доходим до конца списка
		Element *Temp
		while (Temp->pNext) 
		{

		}
	}

			//  Methods

	void print()const 
	{
		Element* Temp = Head;

		while (Temp) 
		{
			std::cout << Temp << tab << Temp->Data << tab << Temp->pNext << std::endl;
			Temp = Temp->pNext;
		}
	}
};

void main() 
{
	setlocale(LC_ALL, "");
	int n;
	std::cout << "Введите размер списка: "; std::cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	std::cout << std::endl;
	list.print();
}