#include<iostream>

#define tab "\t"

void FillRand(int arr[], const int n);

void main()
{
	setlocale(LC_ALL, "");

	int n;
	std::cout << "¬ведите размер: "; std::cin >> n;

	int* arr = new int[n];
	FillRand(arr, n);
	Print(arr, n);
	
	int value;

	std::cout << "¬ведите значение: "; std::cin >> n;
	int* buffer = new int[n + 1] {};
	for (int i = 0; i < n; i++)buffer[i] = arr[i];
	delete[] arr;
	arr = buffer;

	arr[n] = value;
	n++;
	Print(arr, n);
	delete[] arr;
}

void FillRand(int arr[], const int n) 
{
	for (int i = 0; i < n; i++)
	{
		arr[i] = rand() % 100;
	}
}

void Print(int arr[], const int n)
{
	for (int i = 0; i < n; i++)
	{
		std::cout << arr[i] << tab;
	}
	std::cout << std::endl;
}