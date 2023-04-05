#include"HashTable.h"
#include<Windows.h>
#include<fstream>

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	std::ifstream file("list.txt");
	HashTable Table(file);
	Table.print();
	Table.remove(1433);
	Table.print();
	std::ifstream file1("list1.txt");
	Goods ptr(file1);
	Table.add(ptr);
	Table.print();
}