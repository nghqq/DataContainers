#include<iostream>

#define tab "\t"

template<typename T>
class List 
{
	class Element 
	{
		T Data;
		Element* pNext;
		Element* pPrev;

	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr) :Data(Data), pNext(pNext), pPrev(pPrev)
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
	class ConstBaseIterator 
	{
	protected:
		Element* Temp;


	public: 
		ConstBaseIterator(Element*Temp=nullptr):Temp(Temp){}
		~ConstBaseIterator() {}
		  

		bool operator==(const ConstBaseIterator& other) const
	{
		return this->Temp == other.Temp;
	}
		  bool operator!=(const ConstBaseIterator& other)const
		  {
			  return this->Temp != other.Temp;
		  }
		 
		  const T& operator *()const
		  {
			  return  Temp->Data;
		  }
	};
	
public:
	  class ConstIterator: public ConstBaseIterator
	{
	protected:
		//Element* Temp;

	public: 
		ConstIterator(Element*Temp=nullptr):ConstBaseIterator(Temp){}
		~ConstIterator(){}

		 ConstIterator& operator++()
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return *this;
		}
		 ConstIterator& operator++(int) 
		{
			ConstIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return old;
		}
		 ConstIterator& operator--()
		{
			 ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return *this;
		}
		 ConstIterator& operator--(int)
		{
			ConstIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return old;
		}
	};
	  class ConstReverseIterator:public ConstBaseIterator
	{
		
	public:
		ConstReverseIterator(Element* Temp = nullptr): ConstBaseIterator(Temp){}
		~ConstReverseIterator(){}

		ConstReverseIterator operator++() 
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return *this;
		}
		ConstReverseIterator operator++(int) 
		{
			ConstReverseIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
			return old;
		}
		ConstReverseIterator operator--() 
		{
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return *this;
		}
		ConstReverseIterator operator--(int)
		{
			ConstReverseIterator old = *this;
			ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
			return old;
		}
		
	};
	  class Iterator :public ConstIterator
	  {
	  public:
		  Iterator(Element* Temp = nullptr):ConstIterator(Temp){}
		  ~Iterator(){}
		  T& operator*() 
		  {
			  return ConstBaseIterator::Temp->Data;
		  }
	  };
	  class ReverseIterator :public ConstReverseIterator 
	  {
	  public:
		  ReverseIterator(Element* Temp = nullptr) :ConstReverseIterator(Temp){}
		  ~ReverseIterator(){}
		  T& operator*() 
		  {
			  return ConstBaseIterator::Temp->Data;
		  }
	  };

	ConstIterator begin() const
	{
		return Head;
	}
	ConstIterator end() const
	{
		return nullptr;
	}
	ConstReverseIterator rbegin() const
	{
		return Tail;
	}
	ConstReverseIterator rend() const
	{
		return nullptr;
	}

	Iterator begin()
	{
		return Head;
	}
	Iterator end() 
	{
		return nullptr;
	}
	ReverseIterator rbegin() 
	{
		return Tail;
	}
	ReverseIterator rend() 
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
	List(const std::initializer_list<T>& il) : List() 
	{
		for (const T* it = il.begin(); it != il.end(); it++)   // it это ИТЕРАТОР !!!!!!!!!
			push_back(*it);
	}
	List(const List<T>& other):List()
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

	List<T>& operator=(const List<T>& other) 
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		std::cout << "LCopyAssignment: " << this << std::endl;
		return *this;
	}

	void insert(T Data, int index)
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
	
	void push_front(T Data) 
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
	void push_back(T Data)
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
		if (Head == Tail)return pop_front();
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
template<typename T>
List<T> operator+ (const List<T>& left, const List<T>& right)
{
	List<T> cat = left;
	for ( typename List<T>::ConstIterator it = right.begin(); it != right.end(); it++)
	{
		//*it *= 10;
		cat.push_back(*it);
	}
	return cat;
	
}
template<typename T>
void reverse_print(const List<T>& list) 
{
	for (typename List<T>::ConstReverseIterator it = list.rbegin(); it != list.rend();it++) 
	{
		std::cout << *it << tab;
	}
	std::cout << std::endl;
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

	List<int> list_1 = { 3,5,8,13,21 };
	List<int> list_2 = { 32,55,89 };
	List<int> list_3 = list_1 + list_2;
	List<std::string> list_s = {"No","Money","No","Funny"};
	List<double> list_d = { 1.3, 2.3, 3.4, 2.6 };
	for (int i : list_1)std::cout << i << tab;
	std::cout << std::endl;
	for (int i : list_2)std::cout << i << tab;
	std::cout << std::endl;
	for (int i : list_3)std::cout << i << tab;
	std::cout << std::endl;

	reverse_print(list_3);
	for (List<int>::Iterator it = list_3.begin(); it != list_3.end(); it++) 
	{
		*it *= 10;
	}
	for (int i : list_3)std::cout << i << tab;
	std::cout << std::endl;
	
	for (double i : list_d)std::cout << i << tab; std::cout << std::endl;

	for (std::string i : list_s)std::cout << i << tab; std::cout << std::endl;
}