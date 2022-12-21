#include "PassengerCar.h"

PassengerCar::PassengerCar(std::string brand, std::string model, std::string type, std::string color, std::string number, std::string dName, std::string dSurname)
    : Car(brand, number, dName, dSurname), model(model), type(type), color(color) {}

std::string PassengerCar::get_type() const
{
    return type;
}


std::string PassengerCar::get_model() const
{
    return model;
}

std::string PassengerCar::get_color() const
{ 
    return color;
}

void PassengerCar::set_color(std::string Color)
{
    color = Color;
}

std::string PassengerCar::toString() const
{
    return "Passenger: " + Car::toString() + ' ' + model + ' ' + get_type() + ' ' + color;
}

