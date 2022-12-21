#include "Park.h"

Park::Park(std::string name) : name(name) {}

std::string Park::get_name() const
{
	return name;
}

void Park::set_name(std::string Name)
{
	name = Name;
}

void Park::add_by_order(info_t car)
{
	auto i = List.begin();
	while (i != List.end() && (*i)->cmp(*car) == -1)
		++i;
	List.insert(i, std::move(car));
}

void Park::add_to_begin(info_t car)
{
	List.insert(List.begin(),std::move(car));
}

void Park::add_to_back(info_t car)
{
	List.push_back(std::move(car));
}

void Park::remove(const Car& car)
{
	for (auto i = List.begin(); i != List.end();)
		if ((*i)->cmp(car) == 0)
			i = List.erase(i);
		else ++i;
}

void Park::erase_if(std::function<bool(const info_t&)> lambda)
{
	auto i = std::remove_if(List.begin(), List.end(), lambda);
	List.erase(i, List.end());
}

void Park::sort()
{ 
	std::sort(List.begin(), List.end(), [](const info_t& pCar1, const info_t& pCar2) {return pCar1->cmp(*pCar2) == -1; });
}

std::ostream& operator<<(std::ostream& out, const Park& object)
{
	for (const info_t& pCar : object.List)
		out << pCar->toString() << '\n';
	return out;
}
