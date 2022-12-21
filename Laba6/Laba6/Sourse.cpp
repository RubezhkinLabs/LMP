 #include <iostream> 
#include <fstream> 
#include "Park.h"
#include "PassengerCar.h"
#include "Truck.h"

void init(Park& park, std::ifstream& file)
{
	char t;
	std::string brand, number, Name, Surname;
	std::string model, Type, color;
	int tonnage;
	while (file >> t)
	{
		file >> brand >> number >> Name >> Surname;
		if (t == 'P') {
			file >> model >> Type >> color;
			PassengerCar pCar = PassengerCar(brand, model, Type, color, number, Name, Surname);
			park.add_by_order(std::move(std::make_shared<PassengerCar>(pCar)));
		}
		else {
			file >> Type >> tonnage;
			Truck truck = Truck(brand, Truck::string_to_type(Type), tonnage, number, Name, Surname);
			park.add_by_order(std::move(std::make_shared<Truck>(truck)));
		}
	}
	file.close();
}

void task(Park& park)
{
	auto is_van = [](const info_t& Car)->bool {
		Truck* t = dynamic_cast<Truck*>(Car.get());
		bool result = false;
		if (t && t->get_type() == van)
			result = true;
		return result;
	};
	park.erase_if(is_van);
}

int main() { 
	{
		std::ifstream file("data.txt");
		Park park("My Car Park");
		init(park, file);
		std::cout << park << "\n----------------------\n";
		task(park);
		std::cout << park;
	}
	std::cin.get();
}
