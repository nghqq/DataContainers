#include"List.h"
#include"list.cpp"
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////            LIST MEMBER-FUNCTIONS                  ////////////////////////////////////////

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