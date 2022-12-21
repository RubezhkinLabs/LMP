#include "Car.h"

Car::Car(std::string brand, std::string number, std::string dName, std::string dSurname)
	: brand(brand), number(number), Name(dName), Surname(dSurname)
{}

std::string Car::get_brand() const
{
	return brand;
}

std::string Car::get_number() const
{
	return number;
}

void Car::set_number(std::string value)
{
	number = value;
}

std::string Car::get_name() const
{
	return Name;
}

void Car::set_name(std::string value)
{
	Name = value;
}

std::string Car::get_surname() const
{
	return Surname;
}

void Car::set_surname(std::string value)
{
	Surname = value;
}

int Car::cmp(const Car& other) const
{ 
	int result = 1;
	if (Surname < other.Surname ||
		Surname == other.Surname && Name < other.Name)
		result = -1;
	else if (number == other.number)
		result = 0;
	return result;
}

std::string Car::toString() const
{
	return Surname + ' ' + Name + ' ' + number + ' ' + brand;
}
