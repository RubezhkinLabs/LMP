#include "Truck.h"

Truck::Truck(std::string brand, Type type, size_t tonnage, std::string number, std::string dName, std::string dSurname)
: Car(brand, number, dName, dSurname), type(type), tonnage(tonnage) {}

size_t Truck::get_tonnage() 
{
    return tonnage;
}

Type Truck::get_type() 
{
    return type;
}

std::string Truck::get_type_string() const
{
    switch (type)
    {
    case tanker:
        return "Tanker";
        break;
    case van:
        return "Van";
        break;
    case flatbed:
        return "Flatbed Truck";
        break;
    }
}

Type Truck::string_to_type(std::string str)
{
    if (str == "tanker")
        return tanker;
    else if (str == "van")
        return van;
    else if (str == "flatbed")
        return flatbed;
}

std::string Truck::toString() const
{
    return "Truck: " + Car::toString() + ' ' + get_type_string() + ' ' + std::to_string(tonnage) + " ton";
}
