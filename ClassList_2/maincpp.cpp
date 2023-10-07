#include<iostream>

#define tab "\t"
class List 
{
	class Element 
	{
		int Data;
		Element* pNext;
		Element* pPrev;

	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :Data(Data), pNext(pNext), pPrev(pPrev)
		{
			std::cout << "EConstructor:\t" << this << std::endl;
		}
		~Element() 
		{
			std::cout << "EDestructor:\t" << this << std::endl;
		}
		friend class List;

	} *Head, * Tail;
	size_t size; // size_t это unsigned int
	//Директива typedef даёт существующему типу данных новое имя:
	//typedef существующий_тип_данных новоем_имя_этого_типа;
public:
	List() 
	{
		Head = Tail = nullptr;
		size = 0;
		std::cout << "LConstructor:\t" << this << std::endl;

	}
	~List() 
	{
		while (Head)pop_front();
		std::cout << "LDestuctor:\t" << this << std::endl;
	}

	void push_front(int Data) 
	{
		if (Head == nullptr && Tail == nullptr) 
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			/*Element* New = new Element(Data);
			New->pNext = Head;
			Head->pPrev = New;
			Head = New;*/
			Head = Head->pPrev = new Element(Data, Head);
		}
		size++;

	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr) 
		{
			Head = Tail = new Element(Data);
		}
		else 
		{
			/*Element* New = new Element(Data);
			New->pPrev = Tail;
			Tail->pNext = New;
			Tail=New;*/
			Tail = Tail->pNext = new Element(Data, nullptr,Tail);
		}
		size++;
	}
	

					//Removing elements

	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			return;
		}
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
	}

	void pop_back() 
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail) 
		{
			delete Head;
			Head = Tail = nullptr;
			return;
		}
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
	}

	// Methods


	void print()
	{
		for (Element* Temp = Head; Temp; Temp=Temp->pNext) 
		{
			std::cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << std::endl;
		}
			std::cout << "Колличество элементов списка: " << size << std::endl;
	}
	void reverse_print() 
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		{
			std::cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << std::endl;
		}
			std::cout << "Колличество элементов списка: " << size << std::endl;
	}
	
};

void main() 
{
	setlocale(LC_ALL, "");

	int n;
	std::cout << "Введите размер списка: "; std::cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();
}