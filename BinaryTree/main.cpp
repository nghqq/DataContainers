#include <iostream>

#define tab "\t"

class BinaryTree 
{
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) : Data(Data), pLeft(pLeft), pRight(pRight)
		{
			std::cout << "EConstructor: \t" << this << std::endl;
		}
		~Element()
		{
			std:: cout<<"EDestructor: \t" << this << std::endl;
		}
		friend class BinaryTree;
	}*Root;
public:
	BinaryTree() 
	{
		Root = nullptr;
		std::cout << "BTConstructor:\t" << this << std::endl;
	}
	BinaryTree() 
	{
		std::cout << "BTDestructor:\t" << this << std::endl;
	}
	void Insert(int Data,Element* Root) 
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data) 
		{
			if (Root->pLeft = nullptr)Root = new Element(Data);
			else Insert(Data, Root->pLeft);
		}
		else 
		{
			if (Root->pRight = nullptr)Root = new Element(Data);
			else Insert(Data, Root->pRight);

		}
	}
	void print(Element* Root) 
	{
		if (Root = nullptr)return;
		print(Root->pLeft);
		std::cout << Root->Data << tab;
		print(Root->pRight);
	}

	int minValue(Element* Root) 
	{
		if (Root->pLeft == nullptr)return Root->Data;
		else return minValue(Root->pLeft);
	}
	int maxValue(Element* Root)
	{
		if (Root->pRight == nullptr)return Root->Data;
		else return maxValue(Root->pLeft);
	}
	int Sum(Element* Root) 
	{
		if (Root == nullptr)return 0;
		else return Root->Data + Sum(Root->pLeft) + Sum(Root->pRight);
	}
	int Count(Element* Root)
	{
		if (Root == nullptr)return 0;
		else return Count(Root->pLeft) + Count(Root->pRight)+1;
	}
	double AVG() 
	{
		return (double)Sum(Root) / Count(Root);
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	BinaryTree tree;
	std::cout << "Введите размер дерева: "; std::cin >> n;
	for (size_t i = 0; i < n; i++)
	{
		tree.Insert(rand() % 100, tree.get_Root());
	}
	tree.print(tree.get_Root());
	std::cout << std::endl;

	std::cout << "Минимальное значение в дереве: " << tree.minValue(tree.getRoot()) << std::endl;
	std::cout << "Максимальное значение в дереве: " << tree.maxValue(tree.getRoot()) << std::endl;
	std::cout << "Сумма элементов в дереве: " << tree.Sum(tree.getRoot()) << std::endl;
	std::cout << "Кол-во элементов в дереве:" << tree.Count(tree.getRoot()) << std::endl;
	std::cout << "Среднее арифметическое :" << tree.AVG(tree.getRoot()) << std::endl;

}
