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
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) :Data(Data), pLeft(pLeft), pRight(pRight) 
		{
			std::cout << "Econstructor:\t" << this << std::endl;
		}
		~Element() 
		{
			std::cout << "Edestructor:\t" << this << std::endl;
		}
		friend class BinaryTree;
	}*Root;
public:
	 Element* get_root()
	{
		return Root;
	}
	BinaryTree() 
	{
		Root = nullptr;
		std::cout << "BTConstructor:\t" << this << std::endl;
	}
	~BinaryTree()
	{
		std::cout << "BTDestructor:\t" << this << std::endl;
	}

	void insert(int Data, Element* Root) 
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data) 
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else 
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	void print(Element* Root) 
	{
		if (Root == nullptr)return;
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
		else return maxValue(Root->pRight);
	}
	
	int sum(Element*Root) 
	{
		if (Root == nullptr)return 0;
		return Root->Data + sum(Root->pLeft) + sum(Root->pRight);

	}
	int count(Element* Root)
	{
		if (Root == nullptr)return 0;
		else return count(Root->pLeft) + count(Root->pRight) + 1;
	}
	double avg() 
	{
		return(double) sum(Root) / count(Root);
	}
}; 

void main() 
{
	setlocale(LC_ALL, "");
	int n;
	std::cout << "Введите размер дерева: "; std::cin >> n;
	BinaryTree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand()%100, tree.get_root());
	}
	tree.print(tree.get_root());
	std::cout << std::endl;
	std::cout << "Максимальное значение в дереве: " << tree.maxValue(tree.get_root()) << std::endl;
	std::cout << "Минимальное значение в дереве: " << tree.minValue(tree.get_root()) << std::endl;
	std::cout << "Сумма элеметов в дереве : " << tree.sum(tree.get_root()) << std::endl;
	std::cout << "Колличество элеметов в дереве: " << tree.count(tree.get_root()) << std::endl;
	std::cout << "Среднее-арифметическое дерева: " << tree.avg() << std::endl;
}
