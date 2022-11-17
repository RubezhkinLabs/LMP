#include "My_List.h"
#include <Windows.h>

int task(ptrNODE& ptr,std::string shop)
{
	while (ptr && ptr->info.getshop() != shop)
		ptr = ptr->next;
	int cnt = 0;
	if (ptr)
	{
		cnt++;
		std::string name = ptr->info.getshop();
		int price = ptr->info.getcost();
		ptr = ptr->next;
		while (ptr && ptr->info.getshop() == name && ptr->info.getcost() == price)
		{
			cnt++;
			ptr = ptr->next;
		}
	}
	return cnt;
}


void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	bool flag = 1;
	while (flag)
	{
		std::ifstream file("goods.txt");
		if (file)
		{
			DLIST DL("goods.txt");
			file.close();
			DL.print();
			std::cout << "Введите имя магазина: ";
			std::string shop;
			std::cin >> shop;
			ptrNODE ptr = DL.get_begin();
			int res = task(ptr, shop);
			if (res == 1)
				std::cout << ptr->prev->info.getname() << '\n';
			else if (res > 1)
				std::cout << res << '\n';
			else
				std::cout << "Нет такого магазина \n";
			std::cout << "Продолжить? (1 - Да, 0 - Нет): ";
			std::cin >> flag;
		}
	} 
	std::cin.get();
}



