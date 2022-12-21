#pragma once
#include "Car.h" 
#include <vector>
#include <string>
#include <memory> 
#include <iostream> 
#include <functional> 
#include <algorithm> 

using info_t = std::shared_ptr<Car>;
using car_ptr = std::vector<info_t>;
class Park
{
	car_ptr List;
	std::string name;
public:
	Park(std::string name = "");
	std::string get_name() const;
	void set_name(std::string value);
	void add_by_order(info_t car);
	void add_to_begin(info_t car);
	void add_to_back(info_t car);
	void remove(const Car& car);
	void erase_if(std::function<bool(const info_t&)> lambda);
	void sort();
	friend std::ostream& operator<<(std::ostream& out, const Park& object);
};

