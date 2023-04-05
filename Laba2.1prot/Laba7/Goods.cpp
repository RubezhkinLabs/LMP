#include "Goods.h"

Goods::Goods(std::ifstream& file)
{
	file >> code;
	file.ignore();
	std::getline(file, name);
	std::getline(file, unit);
	file >> cost;
	file >> date[0] >> date[1];
	file.ignore();
	std::getline(file, shop);
	std::string dline;
	std::getline(file, dline);
}

void Goods::print()
{
	std::cout << code << "\n";
	std::cout << name << "\n";
	std::cout << unit << "\n";
	std::cout << cost << "\n";
	std::cout << date[0] << ' ' << date[1] << "\n";
	std::cout << shop << "\n";
	std::cout << "---" << "\n";
}

long Goods::getcode()
{
	return code;
}

int Goods::compare(const Goods& good)
{
	int result = 1;
	if (shop < good.shop ||
		shop == good.shop && cost > good.cost ||
		shop == good.shop && cost == good.cost && code < good.code)
		result = -1;
	else if (shop == good.shop && cost == good.cost && code == good.code)
		result = 0;
	return result;
}

std::string Goods::getname()
{
	return name;
}

std::string Goods::getshop()
{
	return shop;
}

int Goods::getcost()
{
	return cost;
}
