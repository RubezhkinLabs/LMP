#pragma once
#include <string> 

class Car
{
private:
	std::string brand, number, Name, Surname;
public:
	Car(std::string brand = "", std::string number = "", std::string dName = "", std::string dSurname = "");
	virtual ~Car() {};
	std::string get_brand() const;
	std::string get_number() const;
	void set_number(std::string value);
	std::string get_name() const;
	void set_name(std::string value);
	std::string get_surname() const;
	void set_surname(std::string value);
	int cmp(const Car& other) const;
	virtual std::string toString() const;
};

