#include"List.h"
template<typename T>
typename List<T>::ConstIterator  List<T>::begin() const
{
	return Head;
}
template<typename T>
typename List<T>::ConstIterator  List<T>::end() const
{
	return nullptr;
}
template<typename T>
typename List<T>::ConstReverseIterator  List<T>::rbegin() const
{
	return Tail;
}
template<typename T>
typename List<T>::ConstReverseIterator  List<T>::rend() const
{
	return nullptr;
}
template<typename T>
typename List<T>::Iterator  List<T>::begin()
{
	return Head;
}
template<typename T>
typename List<T>::Iterator  List<T>::end()
{
	return nullptr;
}
template<typename T>
typename List<T>::ReverseIterator  List<T>::rbegin()
{
	return Tail;
}
template<typename T>
typename List<T>::ReverseIterator  List<T>::rend()
{
	return nullptr;
}

// Constuctors

template<typename T>
List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
	std::cout << "LConstructor:\t" << this << std::endl;

}
template<typename T>
List<T>::List(const std::initializer_list<T>& il) : List()
{
	for (const T* it = il.begin(); it != il.end(); it++)   // it это ИТЕРАТОР !!!!!!!!!
		push_back(*it);
}
template<typename T>
List<T>::List(const List<T>& other) :List()
{
	//for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
	*this = other;
	std::cout << "LCopyConstuctor: " << this << std::endl;
}
template<typename T>
List<T>::~List()
{
	while (Head)pop_back();
	std::cout << "LDestuctor:\t" << this << std::endl;
}
// Operators
template<typename T>
List<T>& List<T>::operator=(const List<T>& other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
	std::cout << "LCopyAssignment: " << this << std::endl;
	return *this;
}
template<typename T>
void List<T>::insert(T Data, int index)
{
	if (index == 0)return push_front(Data);
	if (index >= size) return push_back(Data);
	Element* Temp;
	if (index < size / 2)
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
template<typename T>
void List<T>::push_front(T Data)
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
template<typename T>
void List<T>::push_back(T Data)
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
		Tail = Tail->pNext = new Element(Data, nullptr, Tail);
	}
	size++;
}


//Removing elements
template<typename T>
void List<T>::pop_front()
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
template<typename T>
void List<T>::pop_back()
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
template<typename T>
void List<T>::erase(int index)
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

template<typename T>
void List<T>::print()const
{
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
	{
		std::cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << std::endl;
	}
	std::cout << "Колличество элементов списка: " << size << std::endl;
}
template<typename T>
void List<T>::reverse_print()const
{
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
	{
		std::cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << std::endl;
	}
	std::cout << "Колличество элементов списка: " << size << std::endl;
}


/////////////////////////             LIST MEMBER-FUNCTIONS                 ////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


template<typename T>
List<T> operator+ (const List<T>& left, const List<T>& right)
{
	List<T> cat = left;
	for (typename List<T>::ConstIterator it = right.begin(); it != right.end(); it++)
	{
		//*it *= 10;
		cat.push_back(*it);
	}
	return cat;

}
template<typename T>
void reverse_print(const List<T>& list)
{
	for (typename List<T>::ConstReverseIterator it = list.rbegin(); it != list.rend(); it++)
	{
		std::cout << *it << tab;
	}
	std::cout << std::endl;
}