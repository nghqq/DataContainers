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
	class Iterator 
	{
		Element* Temp;

	public: 
		Iterator(Element*Temp=nullptr):Temp(Temp){}
		~Iterator(){}

		Iterator& operator++()
		{
			Temp = Temp->pNext;
			return *this;
		}
		Iterator& operator++(int) 
		{
			Iterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		Iterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		Iterator& operator--(int)
		{
			Iterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		bool operator==(const Iterator& other)const 
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const Iterator& other)const 
		{
			return this->Temp != other.Temp;
		}
		 const int& operator*() const
		{
			return Temp->Data;
		}
		  int& operator*()
		 {
			 return Temp->Data;
		 }

	};
	class ReverseIterator 
	{
		Element* Temp;
	public:
		ReverseIterator(Element* Temp = nullptr): Temp(Temp){}
		~ReverseIterator(){}

		ReverseIterator operator++() 
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ReverseIterator operator++(int) 
		{
			ReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ReverseIterator operator--() 
		{
			Temp = Temp->pNext;
			return *this;
		}
		ReverseIterator operator--(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		bool operator==(const ReverseIterator& other) const 
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ReverseIterator& other)const 
		{
			return this->Temp != other.Temp;
		}
		int operator *() 
		{
			return  Temp->Data;
		}
	};

	Iterator begin() const
	{
		return Head;
	}
	Iterator end() const
	{
		return nullptr;
	}
	ReverseIterator rbegin() const
	{
		return Tail;
	}
	ReverseIterator rend() const
	{
		return nullptr;
	}

	// Constuctors


	List() 
	{
		Head = Tail = nullptr;
		size = 0;
		std::cout << "LConstructor:\t" << this << std::endl;

	}
	List(const std::initializer_list<int>& il) : List() 
	{
		for (const int* it = il.begin(); it != il.end(); it++)   // it это ИТЕРАТОР !!!!!!!!!
			push_back(*it);
	}
	List(const List& other):List()
	{
		//for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		*this = other;
		std::cout << "LCopyConstuctor: " << this << std::endl;
	}
	~List() 
	{
		while (Head)pop_back();
		std::cout << "LDestuctor:\t" << this << std::endl;
	}
					// Operators

	List& operator=(const List& other) 
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		std::cout << "LCopyAssignment: " << this << std::endl;
		return *this;
	}

	void insert(int Data, int index)
	{
		if (index == 0)return push_front(Data);
		if (index >= size) return push_back(Data);
		Element* Temp;
		if (index<size/2)
		{
			Temp = Head;
			for (int i = index; i < index; i++)Temp = Temp->pNext;

		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - index - 1; i++)Temp = Temp->pPrev;
		}
		Element* New = new Element(Data);
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;
		size++;
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
		size--;
	}

	void pop_back() 
	{
		/*if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Tail;
			Head = Tail = nullptr;
			return;
		}*/
		if (Head == Tail)return pop_back();
		Tail = Tail->pPrev;
		delete Tail->pNext;
		Tail->pNext = nullptr;
		size--;
	}
	
	void erase(int index) 
	{
		if (index == 0)return pop_front();
		if (index == size - 1)return pop_back();
		if (index >= size)return;

		Element* Temp;
		if (index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < index; i++)Temp = Temp->pNext;
			
		}
		if (index > size / 2)
		{
			Temp = Tail;
			for (int i = 0; i < index; i++)Temp = Temp->pPrev;

		}
		Temp->pPrev->pNext = Temp->pNext;
		Temp->pNext->pPrev = Temp->pPrev;
		delete Temp;
		size--;
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

List operator+ (const List& left, const List& right) 
{
	List cat = left;
	for (List::Iterator it = right.begin(); it != right.end(); it++)

		cat.push_back((*it)*=10);
	return cat;
	
}

//#define BASE_CHECK
//#define BASE_CHECK_2
//#define ITERATORS_CHECK
void main() 
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	std::cout << "Введите размер списка: "; std::cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();
	list.pop_back();
	list.print();
	
#endif // BASE_CHECK
#ifdef ITERATORS_CHECK
	List list = { 3,5,8,13,21 };
	list.print();
	for (int i : list)std::cout << i << tab;
	std::cout << std::endl;

	for (List::ReverseIterator it = list.rbegin(); it != list.rend(); it++)
	{
		std::cout << *it << tab;
	}
	std::cout << std::endl;
#endif // ITERATORS_CHECK

	
#ifdef BASE_CHECK_2

	int n;
	std::cout << "Введите размер списка: "; std::cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();
	int index;
	int value;
	std::cout << "Введите индекс добавляемого элемента: "; std::cin >> index;
	std::cout << "Введите добавляемое значение: "; std::cin >> value;
	list.insert(value, index);
	list.print();
	list.reverse_print();
#endif // BASE_CHECK_2

	List list_1 = { 3,5,8,13,21 };
	List list_2 = { 32,55,89 };
	List list_3 = list_1 + list_2;
	for (int i : list_1)std::cout << i << tab;
	std::cout << std::endl;
	for (int i : list_2)std::cout << i << tab;
	std::cout << std::endl;
	for (int i : list_3)std::cout << i << tab;
	std::cout << std::endl;
	

}