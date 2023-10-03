#include <iostream>

#define tab "\t"

class Element
{
	int Data;
	Element* pNext;
	static int count; //Объявление статической переменной 

public:
	//Constuctors

	Element(int Data, Element* pNext = nullptr) :Data(Data), pNext(pNext)
	{
		count++;

#ifdef DEBUG
		std::cout << "EConstructor:\t " << this << std::endl;
#endif // DEBUG

	}


	~Element()
	{
		count--;
#ifdef DEBUG

		std::cout << "EDestructor:\t " << this << std::endl;
#endif // DEBUG
	}
	friend class ForwardList;
	friend class Iterator;
};
int Element::count = 0; //определение статической переменной 

class Iterator
{
	Element* Temp;

public:
	Iterator(Element* Temp = nullptr) : Temp(Temp)
	{
#ifdef DEBUG
		std::cout << "ItConstuctor\t" << this << std::endl;
#endif // DEBUG

	}

	Iterator(const Iterator& other) 
	{
		this->Temp = other.Temp;
#ifdef DEBUG
		std::cout << "ItCopyConstuctor\t" << this << std::endl;
#endif // DEBUG

	}


	~Iterator()
	{
#ifdef DEBUG
		std::cout << "ItDestructor\t" << this << std::endl;
#endif // DEBUG
	}

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

	bool operator ==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator !=(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	int operator*()
	{
		return Temp->Data;
	}

};

class ForwardList
{
	//Forward - односвязанный, однонаправленный 
	Element* Head;
	unsigned int size;

public:
	const Iterator begin()const
	{
		return Head;
	}
	const Iterator end()const
	{
		return nullptr;
	}

	//Constuctors
	ForwardList()
	{
		//Конструктор  по умолчанию  создает пустой список
		this->Head = nullptr; // Если список пуст, его Голова указывает на 0
		this->size = 0;
		std::cout << "LConstructor:\t" << this << std::endl;
	}

	ForwardList( const std::initializer_list<int>&il) :ForwardList()
	{
		std::cout << typeid(il.begin()).name() << std::endl;
		for (int const* it = il.begin(); it != il.end(); ++it)
		{
			push_back(*it);
		}
	}

	//CopyConstuctors:

	ForwardList(const ForwardList& other):ForwardList()
	{
		/*for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
		push_back(Temp->Data);*/
		*this = other;  // Из конструктора копирования код повтороно используется код CopyAssignment
		std::cout << "LCopyConstrtuctor:\t" << this << std::endl;
	}
	ForwardList(const ForwardList&& other) :ForwardList()
	{
		/*this->Head = other.Head; // Не получается занулить 'other'
		this->size = other.size;*/

		//other.Head = nullptr;
		//other.size = 0;
		*this = std::move(other);
		std::cout << "MoveConstructor:" << this<<"<-"<<&other << std::endl;
	}


	~ForwardList()
	{
		while (Head)pop_front();
		std::cout << "LDestructor:\t" << this << std::endl;
	}

	//Assignment operators:

	
	ForwardList& operator = (ForwardList&& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		this->Head = other.Head;
		this->size = size;
		other.Head = nullptr;
		other.size = 0;
		std::cout << "MoveAssignment:" << this << std::endl;

	}

	//Operators

	ForwardList& operator=(const ForwardList& other) 
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp;Temp=Temp->pNext)
			push_back(Temp->Data);
		std::cout << "CopyAssignment:\t" << this << std::endl;
		return *this;
		
	}


	//Adding elements:

	void push_front(int Data)
	{
		/*//1) Создаем элемент для добавляемого значения:
		Element* New = new Element(Data);
		//2) Пристыковываем элемент к списку:
		New->pNext = Head;
		//3) Теперь новый элемент является начальным элементом списка:
		Head = New;*/

		Head = new Element(Data, Head);
		size++;


	}
	void push_back(int Data)
	{
		if (Head == nullptr) return push_front(Data);
		//1) Создаем новый элемент
		//Element* New = new Element(Data);
		 //2) Доходим до конца списка:
		Element* Temp = Head; // Что бы ходить по списку нужно создать итератор Temp
		while (Temp->pNext)  // пока в pNext будет не 0 это 'true', как только в pNext будет 0 это будет 'false'
		{
			Temp = Temp->pNext;
		}
		// Сейчас 'Temp' указывает на последний элемент
		//3) Добавляем новый элемент в конец списка
		Temp->pNext = new Element(Data);
		size++;
	}
	void insert(int Data, int index)
	{
		if (index == 0)return push_front(Data);
		//1) Создаем новый элемент:
		//Element* New = new Element(Data);
		//2) Доходим до нужного элемента:
		Element* Temp = Head;
		for (int i = 0; i < index - 1; i++)
		{
			if (Temp->pNext == nullptr)return push_back(Data);
			Temp = Temp->pNext;
		}
		//3)Вставляем новый элемент по указанному индексу:
		//New->pNext = Temp->pNext;
		//Temp=Temp->pNext

		Temp->pNext = new Element(Data, Temp->pNext);
		size++;
	}
	void pop_front()
	{
		Element* Erased = Head;	//1) Запоминаем адрес удаляемого элемента
		Head = Head->pNext;		//2) Исключаем удаляемый элемент из списка
		delete Erased;			//3) Удаляем из памяти 
	}
	void pop_back()
	{
		//1) Доходим до предпоследнего элемента:
		Element* Temp = Head;
		while (Temp->pNext->pNext)
		{
			Temp = Temp->pNext;
		}
		//2) Удаляем последний элемент из памяти:
		delete Temp->pNext;
		//3) Обнуляем указатель на последний элемент:
		Temp->pNext = nullptr;
		size--;
	}
	void erase(int del_index)
	{
		if (del_index == 0)return pop_front();
		Element* Temp = Head;
		for (int i = 0; i < del_index - 1; i++)
		{
			if (Temp == nullptr)return;
			Temp = Temp->pNext;
		}
		Element* Erased = Temp->pNext;
		Temp->pNext = Temp->pNext->pNext;
		delete Erased;
		size--;
	}

	//  Methods

	void print()const
	{
		/*Element* Temp = Head; // Temp это итератор.
		//Итератор это указатель, при помощи которого можно получить доступ к элементам структуры данных.

		while (Temp)
		{
			std::cout << Temp << tab << Temp->Data << tab << Temp->pNext << std::endl;
			Temp = Temp->pNext; // Переход на следующий элемент
		}*/
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			std::cout << Temp << tab << Temp->Data << tab << Temp->pNext << std::endl;
		std::cout << "Колл-во элементов в списке: " << this->size << std::endl;
		std::cout << "Общее колличество  элементов в списке: " << Element::count << std::endl; // к статическим полям принято обращаться через имя класса и оператор разрешения видимости (::)
	}


};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList result = left;
	for (Iterator it = right.begin(); it != right.end(); it++)
		result.push_back(*it);
	return result;
}

//#define BASE_CHECK
//#define INSERT_CHECK
//#define RANGE_BASED_FOR_ARRAYS
//#define RANGE_BASED_FOR_LIST
#define COPY_METHODS_CHECK
#define FORWARD_LIST_PREFORMANCE_LIST
void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	std::cout << "Введите размер списка: "; std::cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);
	}
	std::cout << std::endl;
	list.push_back(123);
	list.print();
	//list.insert(358);
	list.pop_front();
	list.print();
	std::cout << std::endl;

	list.pop_back();
	list.print();

	std::cout << std::endl;
#ifdef INSERT_CHECK
	int index;
	std::cout << "Введите индекс: "; std::cin >> index;
	int value;
	std::cout << "Введите добавляемое значение : "; std::cin >> value;
	list.insert(value, index);
	list.print();
#endif INSERT_CHECK // INSERT_CHECK
	int del_index;
	std::cout << "Введите индекс: "; std::cin >> del_index;
	list.erase(del_index);
	list.print();


#endif // BASE_CHECK

#ifdef RANGE_BASED_FOR_ARRAYS
	int arr[] = { 3,5,8,13,21 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		std::cout << arr[i] << tab;
	}
	std::cout << std::endl;
	for (int i : arr)
	{
		std::cout << i << tab;
	}
	std::cout << std::endl;
#endif // RANGE_BASED_FOR_ARRAYS

#ifdef  RANGE_BASED_FOR_LIST
	ForwardList list = { 3,5,8,13,21 };
	list.print();

	for (int i : list)
	{
		std::cout << i << tab;
	}
	std::cout << std::endl;
	for (Iterator it = list.begin(); it != list.end(); ++it)
	{
		std::cout << *it << tab;
	}
	std::cout << std::endl;
#endif //  RANGE_BASED_FOR_LIST

	ForwardList list_1 = { 3,5,8,13,21 };
	for (int i : list_1)std::cout << i << tab; std::cout << std::endl;

	ForwardList list_2 = list_1;
	for (int i : list_2)std::cout << i << tab; std::cout << std::endl;

	ForwardList list_3 = list_1 + list_2;
	for (int i : list_3)std::cout << i << tab; std::cout << std::endl;
	list_3.print();
}