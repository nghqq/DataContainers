#include <iostream>

#define tab "\t"

class Element 
{
	int Data;
	Element* pNext;
	static int count; //���������� ����������� ���������� 

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
int Element::count = 0; //����������� ����������� ���������� 
class ForwardList 
{
	//Forward - �������������, ���������������� 
	Element* Head;

public:
	   //Constuctors
	ForwardList()
	{
		//�����������  �� ���������  ������� ������ ������
		this->Head = nullptr; // ���� ������ ����, ��� ������ ��������� �� 0
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
		/*//1) ������� ������� ��� ������������ ��������:
		Element* New = new Element(Data);
		//2) �������������� ������� � ������:
		New->pNext = Head;
		//3) ������ ����� ������� �������� ��������� ��������� ������:
		Head = New;*/
		
		Head = new Element(Data,Head);
		

	}
	void push_back(int Data) 
	{
		if (Head == nullptr) return push_front(Data);
		//1) ������� ����� �������
		//Element* New = new Element(Data);
		 //2) ������� �� ����� ������:
		Element* Temp = Head; // ��� �� ������ �� ������ ����� ������� �������� Temp
		while (Temp->pNext)  // ���� � pNext ����� �� 0 ��� 'true', ��� ������ � pNext ����� 0 ��� ����� 'false'
		{
			Temp = Temp->pNext;
		}
		// ������ 'Temp' ��������� �� ��������� �������
		//3) ��������� ����� ������� � ����� ������
		Temp->pNext = new Element(Data);
	}
	void insert(int Data,int index) 
	{
		if (index == 0)return push_front(Data);
		//1) ������� ����� �������:
		//Element* New = new Element(Data);
		//2) ������� �� ������� ��������:
		Element* Temp = Head;
		for (int i = 0; i < index-1; i++)
		{
			if (Temp->pNext == nullptr)return push_back(Data);
			Temp = Temp->pNext;
		} 
		//3)��������� ����� ������� �� ���������� �������:
		//New->pNext = Temp->pNext;
		//Temp=Temp->pNext

		Temp->pNext = new Element(Data, Temp->pNext);
	}
	void pop_front() 
	{
		Element* Erased = Head;	//1) ���������� ����� ���������� ��������
		Head = Head->pNext;		//2) ��������� ��������� ������� �� ������
		delete Erased;			//3) ������� �� ������ 
	}
	void pop_back() 
	{
		//1) ������� �� �������������� ��������:
		Element* Temp = Head;
		while (Temp->pNext->pNext) 
		{
			Temp = Temp->pNext;
		}
		//2) ������� ��������� ������� �� ������:
		delete Temp->pNext;
		//3) �������� ��������� �� ��������� �������:
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
		/*Element* Temp = Head; // Temp ��� ��������.
		//�������� ��� ���������, ��� ������ �������� ����� �������� ������ � ��������� ��������� ������.

		while (Temp) 
		{
			std::cout << Temp << tab << Temp->Data << tab << Temp->pNext << std::endl;
			Temp = Temp->pNext; // ������� �� ��������� �������
		}*/
		for (Element* Temp = Head; Temp; Temp=Temp->pNext)
		std::cout << Temp << tab << Temp->Data << tab << Temp->pNext << std::endl;
		//std::cout << "����-�� ��������� � ������: " << Head->count << std::endl;
		std::cout << "����-�� ��������� � ������: " << Element::count << std::endl; // � ����������� ����� ������� ���������� ����� ��� ������ � �������� ���������� ��������� (::)
	}
};

#define BASE_CHECK
#define INSERT_CHECK

void main() 
{
#ifdef BASE_CHECK
	setlocale(LC_ALL, "");
	int n;
	std::cout << "������� ������ ������: "; std::cin >> n;
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
	std::cout << "������� ������: "; std::cin >> index;
	int value;
	std::cout << "������� ����������� �������� : "; std::cin >> value;
	list.insert(value, index);
	list.print();
#endif INSERT_CHECK // INSERT_CHECK
	int del_index;
	std::cout << "������� ������: "; std::cin >> del_index;
	list.erase(del_index);
	list.print();


#endif // BASE_CHECK



}