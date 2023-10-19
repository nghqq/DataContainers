#include <iostream>

const char* Hello() 
{
	return "Hello";
}
int sum(int a,int b)
{
	return a + b;
}

void main()
{
	setlocale(LC_ALL, "");
	std::cout << Hello() << std::endl;
	const char* (*p_hello)() = Hello; // ќбъ€вл€ем указатель на функцию 
	// type (*name)(parameters);
	// type (*name)(parameters); ExistingFunctionName
	p_hello = Hello;
	std::cout << p_hello() << std::endl;


	int (*p_sum)(int a, int b) = sum;
	std::cout << p_sum(2, 3) << std::endl;
}