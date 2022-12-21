#pragma once
#include "Car.h"
#include <string> 

class PassengerCar : public Car
{
private:
	std::string type;
	std::string model;
	std::string color;
public:
	PassengerCar(std::string brand = "", std::string model = "", std::string type = "", std::string color = "", std::string number = "", std::string dName = "", std::string dSurname = "");

	std::string get_type() const;
	std::string get_model() const;
	std::string get_color() const;
	void set_color(std::string Color);
	std::string toString() const override;
};

