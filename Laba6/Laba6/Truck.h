#pragma once
#include "Car.h"
#include <string> 
enum Type {
	tanker, 
	van,
	flatbed,
};

class Truck : public Car
{
private:
	size_t tonnage;
	Type type;
public:
	Truck(std::string brand = "", Type type = tanker, size_t tonnage = 0, std::string number = "", std::string dName = "", std::string dSurname = "");
	size_t get_tonnage();
	Type get_type();
	std::string get_type_string() const;
	static Type string_to_type(std::string str);
	std::string toString() const override;
};

