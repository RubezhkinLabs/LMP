#pragma once
#include <string>
#include <fstream>
#include <iostream>

using TExpirationDate = int[2];

struct Goods
{
private:
	long code;
	std::string name;
	std::string unit;
	int cost;
	TExpirationDate date;
	std::string shop;
public:
	Goods() {}
	Goods(std::ifstream& file);
	void print();
	long getcode();
	int compare(const Goods& good);
	std::string getname();
	std::string getshop();
	int getcost();
};