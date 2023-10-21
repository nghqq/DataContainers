#include <iostream>
#include <ctime>
#include <chrono>

#define tab "\t"

class BinaryTree 
{
protected:
	class Element 
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) :Data(Data), pLeft(pLeft), pRight(pRight) 
		{
#ifdef DEBUG
			std::cout << "Econstructor:\t" << this << std::endl;
#endif // DEBUG

		}
		~Element() 
		{
#ifdef DEBUG
			std::cout << "Edestructor:\t" << this << std::endl;
#endif // DEBUG

		}
		friend class BinaryTree;
		friend class UniqueTree;
	}*Root;
public:
	 Element* get_root()
	{
		return Root;
	}
	BinaryTree() 
	{
		Root = nullptr;
#ifdef DEBUG
		std::cout << "BTConstructor:\t" << this << std::endl;
#endif // DEBUG
	}
	BinaryTree(const std::initializer_list<int>& il) :BinaryTree() 
	{
		for (int const* it = il.begin(); it != il.end(); ++it) 
		{
			insert(*it, Root);
		}
	}
	~BinaryTree()
	{
		clear(Root);
#ifdef DEBUG
		std::cout << "BTDestructor:\t" << this << std::endl;
#endif // DEBUG

	}
	void insert(int Data) 
	{
		insert(Data, Root);
	}
	void depth_print(int depth)const
	{
		return depth_print(Root,depth);
	}
	void tree_print()const 
	{
		return tree_print(0,this->depth()*4);
	}
	void print() const
	{
		print(Root);
		std::cout << std::endl;
	}
	int minValue() const
	{
		return minValue(Root);
	}
	int maxValue()const 
	{
		return maxValue(Root);
	}
	int sum()const 
	{
		return sum(Root);
	}
	int count()const 
	{
		return count(Root);
	}
	double avg() const
	{
		return(double)sum(Root) / count(Root);
	}
	int depth() const
	{
		return depth(Root);
	}
	void clear() 
	{
		clear(Root);
		Root = nullptr;
	}
	void erase(int Data) 
	{
		erase(Data, Root);
		erase(Data, Root);
	}
private:
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
	  void erase(int Data, Element*& Root) 
	  {
		  if (Root == nullptr)return;
		  //erase(Data, Root->pLeft);
		  //erase(Data, Root->pRight);
		  if (Data == Root->Data)
		  {
			  if (Root->pLeft == Root->pRight) 
			  {
				  delete Root;
				  Root = nullptr;
			  }
			  else 
			  {
				  if (count(Root->pLeft) > count(Root->pRight)) 
				  {
					  Root->Data = maxValue(Root->pLeft);
					  erase(maxValue(Root->pLeft), Root->pLeft);
				  }
				  else 
				  {
					  Root->Data = minValue(Root->pRight);
					  erase(minValue(Root->pRight), Root->pRight);
				  }

			  }
		  }
		  if (Root)
		  {
			  //erase(Data, Root->pLeft);
			  //erase(Data, Root->pRight);
		  }
	  }
	  int depth(Element* Root) const
	  {
		  /*if (Root == nullptr)return 0;
		  if (depth(Root->pLeft) + 1 > depth(Root->pRight)+1) return depth(Root->pLeft) + 1;
		  else return depth(Root->pRight) + 1;*/

		  if (Root == nullptr)return 0;
		  //else return
			  //depth(Root->pLeft) + 1 > depth(Root->pRight) + 1 ?
			  //depth(Root->pLeft) + 1 :
			  //depth(Root->pRight) + 1;
		  int l_depth = depth(Root->pLeft) + 1;
		  int r_depth = depth(Root->pRight) + 1;
		  return l_depth > r_depth ? l_depth : r_depth;
	  }
	  void depth_print(Element* Root,int depth,int width = 4)const
	  {
		  if (Root == nullptr)return;
		  if (depth == 0) 
		  {
			  std::cout.width(width);
			  std::cout << Root-> Data << tab;
			  return;
		  } 
		  depth_print(Root->pLeft, depth - 1,width);
		  std::cout.width(width); std::cout << "";
		  depth_print(Root->pRight, depth - 1,width);

	  }
	  void tree_print(int depth,int width) const
	  {
		  if (depth == this->depth())return;
		  depth_print(this->Root,depth,width);
		  std::cout << std::endl;
		  std::cout << std::endl;
		  std::cout << std::endl;
		  tree_print(depth + 1,width/2);
	  }

	void clear(Element* Root) 
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
	}
	void print(Element* Root) const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		std::cout << Root->Data << tab;
		print(Root->pRight);
	}
	int minValue(Element* Root) const
	{
		//if (Root->pLeft == nullptr)return Root->Data;
		//else return minValue(Root->pLeft);
		return Root == nullptr ? 0 : Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue(Element* Root) const
	{
		//if (Root->pRight == nullptr)return Root->Data;
		//else return maxValue(Root->pRight);
		return Root == nullptr ? 0 : Root->pRight == nullptr ? Root->Data : maxValue(Root->pRight);
	}
	
	int sum(Element*Root) const
	{
		if (Root == nullptr)return 0;
		return Root->Data + sum(Root->pLeft) + sum(Root->pRight);

	}
	int count(Element* Root)const
	{
		if (Root == nullptr)return 0;
		else return count(Root->pLeft) + count(Root->pRight) + 1;
	}
}; 
class UniqueTree : public BinaryTree 
{
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data>Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data) 
	{
		insert(Data,Root);
	}
};
template<typename T>
void measure(const char msg[], T(BinaryTree::* function)()const, const BinaryTree& tree)
{
	std::cout << msg;
	clock_t start = clock();
	T value = (tree.*function)();
	clock_t end = clock();
	std::cout << value << " вычислено за " << double(end - start) / CLOCKS_PER_SEC << " секунд\n";
}
template<typename T>
void measure_chrono(const char msg[], T(BinaryTree::* function)()const, const BinaryTree& tree)
{
	std::cout << msg;
	auto start = std::chrono::high_resolution_clock::now();
	T value = (tree.*function)();
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> duration = end - start;
	std::cout << "Время выполнения: " << duration.count() << std::endl;

}
//#define BASE_CHECK
//#define UNIQUE_TREE_CHECK
//#define ERASE_CHECK
//#define DEPTH_CHECK
//#define DEPTH_PRINT_CHECK
#define CHRONO_CHECK
void main() 
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	std::cout << "Введите размер дерева: "; std::cin >> n;
	BinaryTree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	//tree.clear();
	//tree.print();

	measure("Минимальное значение в дереве: ", &BinaryTree::minValue, tree);
	measure("Максимальное значение в дереве: ", &BinaryTree::maxValue, tree);
	measure("Среднее-арифметическое: ", &BinaryTree::avg, tree);
	measure("Количество эллеметов: ", &BinaryTree::count, tree);
	measure("Сумма: ", &BinaryTree::sum, tree);
	measure("Глубина: ", &BinaryTree::depth, tree);
#ifdef PREFORMANCE_CHECK
	std::cout << std::endl;
	clock_t start = clock();   // Функция clock возвращает количестов тактов процессора
	clock_t end = clock();
	start = clock();
	std::cout << "Максимальное значение в дереве: " << tree.maxValue() << " вычислено за ";
	end = clock();
	std::cout << double(end - start) / CLOCKS_PER_SEC << " секунд\n";

	start = clock();
	std::cout << "Минимальное значение в дереве: " << tree.minValue() << " вычислено за ";
	end = clock();
	std::cout << double(end - start) / CLOCKS_PER_SEC << " секунд\n";

	start = clock();
	std::cout << "Сумма элеметов в дереве : " << tree.sum() << " вычислено за ";
	end = clock();
	std::cout << double(end - start) / CLOCKS_PER_SEC << " секунд\n";

	start = clock();
	std::cout << "Количество элеметов в дереве: " << tree.count() << " вычислено за ";
	end = clock();
	std::cout << double(end - start) / CLOCKS_PER_SEC << " секунд\n";

	start = clock();
	std::cout << "Среднее-арифметическое дерева: " << tree.avg() << " вычислено за ";
	end = clock();
	std::cout << double(end - start) / CLOCKS_PER_SEC << " секунд\n";

	start = clock();
	std::cout << "Глубина дерева: " << tree.depth() << " вычислено за ";
	end = clock();
	std::cout << double(end - start) / CLOCKS_PER_SEC << " секунд\n";
#endif // PREFORMANCE_CHECK



#ifdef UNIQUE_TREE_CHECK
	UniqueTree utree;
	for (int i = 0; i < n; i++)
	{
		utree.insert(rand() % 100);
	}
	utree.print();
	std::cout << std::endl;
	std::cout << "Максимальное значение в дереве: " << utree.maxValue() << std::endl;
	std::cout << "Минимальное значение в дереве: " << utree.minValue() << std::endl;
	std::cout << "Сумма элеметов в дереве : " << utree.sum() << std::endl;
	std::cout << "Количество элеметов в дереве: " << utree.count() << std::endl;
	std::cout << "Среднее-арифметическое дерева: " << utree.avg() << std::endl;
#endif // UNIQUE_TREE_CHECK

#endif // BASE_CHECK

	//BinaryTree tree = { 50,25,75,16,32,64,90 };
#ifdef ERASE_CHECK
	BinaryTree tree = { 5,8,2,6,7,9,10,1,3,4 };
	tree.print();
	int value;
	std::cout << "Введите удаляемое значение: "; std::cin >> value;
	tree.erase(value);
	tree.print();
	std::cout << "Количество элеметов в дереве: " << tree.count() << std::endl;
#endif // ERASE_CHECK

#ifdef DEPTH_CHECK
	//BinaryTree tree = { 5,8,2,6,7,9,10,1,3,4 };
	BinaryTree tree = { 50, 25, 75, 16, 32, 64, 90, 15 };
	tree.print();
	std::cout << "Глубина дерева: " << tree.depth() << std::endl;
#endif // DEPTH_CHECK
#ifdef DEPTH_PRINT_CHECK
	BinaryTree tree = { 5,8,2,6,7,9,10,1,3,4 };
	tree.print();
	tree.tree_print();
	int depth;
	std::cout << "Введите глубину: "; std::cin >> depth;
	tree.depth_print(depth);
#endif // 

#ifdef CHRONO_CHECK

	int n;
	std::cout << "Введите размер дерева: "; std::cin >> n;
	BinaryTree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	//tree.clear();
	//tree.print();

	measure_chrono("Минимальное значение в дереве: ", &BinaryTree::minValue, tree);
	measure_chrono("Максимальное значение в дереве: ", &BinaryTree::maxValue, tree);
	measure_chrono("Среднее-арифметическое: ", &BinaryTree::avg, tree);
	measure_chrono("Количество эллеметов: ", &BinaryTree::count, tree);
	measure_chrono("Сумма: ", &BinaryTree::sum, tree);
	measure_chrono("Глубина: ", &BinaryTree::depth, tree);
	std::cout << std::endl;

	measure("Минимальное значение в дереве: ", &BinaryTree::minValue, tree);
	measure("Максимальное значение в дереве: ", &BinaryTree::maxValue, tree);
	measure("Среднее-арифметическое: ", &BinaryTree::avg, tree);
	measure("Количество эллеметов: ", &BinaryTree::count, tree);
	measure("Сумма: ", &BinaryTree::sum, tree);
	measure("Глубина: ", &BinaryTree::depth, tree);
#endif // CHRONO_CHECK

	
}
