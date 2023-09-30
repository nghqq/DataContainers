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
		std::cout << "EConstructor:\t " << this << std::endl;
	}
	~Element() 
	{
		count--;
		std::cout << "EDestructor:\t " << this << std::endl;
	}
	friend class ForwardList;
};
int Element::count = 0; //определение статической переменной 
class ForwardList 
{
	//Forward - односвязанный, однонаправленный 
	Element* Head;

public:
	   //Constuctors
	ForwardList()
	{
		//Конструктор  по умолчанию  создает пустой список
		this->Head = nullptr; // Если список пуст, его Голова указывает на 0
		std::cout << "LConstructor:\t" << this << std::endl;
	}
	~ForwardList()
	{
		while (Head)pop_front();
		std::cout << "LDestructor:\t" << this << std::endl;
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
		
		Head = new Element(Data,Head);
		

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
	}
	void insert(int Data,int index) 
	{
		if (index == 0)return push_front(Data);
		//1) Создаем новый элемент:
		//Element* New = new Element(Data);
		//2) Доходим до нужного элемента:
		Element* Temp = Head;
		for (int i = 0; i < index-1; i++)
		{
			if (Temp->pNext == nullptr)return push_back(Data);
			Temp = Temp->pNext;
		} 
		//3)Вставляем новый элемент по указанному индексу:
		//New->pNext = Temp->pNext;
		//Temp=Temp->pNext

		Temp->pNext = new Element(Data, Temp->pNext);
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
	}
	void erase(int del_index) 
	{
		Element* Temp = Head;
		for (int i = 0; i < del_index-1; i++)
		{
			Temp = Temp->pNext;
		}
		delete Temp->pNext;
		Temp->pNext = nullptr;
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
		for (Element* Temp = Head; Temp; Temp=Temp->pNext)
		std::cout << Temp << tab << Temp->Data << tab << Temp->pNext << std::endl;
		//std::cout << "Колл-во элементов в списке: " << Head->count << std::endl;
		std::cout << "Колл-во элементов в списке: " << Element::count << std::endl; // к статическим полям принято обращаться через имя класса и оператор разрешения видимости (::)
	}
};

//#define BASE_CHECK
//#define INSERT_CHECK

void main() 
{
#ifdef BASE_CHECK
	setlocale(LC_ALL, "");
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

	int arr[] = { 3,5,8,13,21 };
	for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++)
	{
		std::cout << arr[i] << tab;
	}
	std::cout << std::endl;
	for (int i : arr) 
	{
		std::cout << i << tab;
	}
	std::cout << std::endl;
}