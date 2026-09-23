#include "../include/Trip.h"

Trip::Trip()
{
    from = "";
    to = "";
    stations = 0;
    type = "";
    price = 0;
}

Trip::Trip(
    const std::string& from,
    const std::string& to,
    int stations,
    const std::string& type,
    double price
)
{
    this->from = from;
    this->to = to;
    this->stations = stations;
    this->type = type;
    this->price = price;
}

std::string Trip::getFrom() const
{
    return from;
}

std::string Trip::getTo() const
{
    return to;
}

int Trip::getStations() const
{
    return stations;
}

std::string Trip::getType() const
{
    return type;
}

double Trip::getPrice() const
{
    return price;
}

bool Trip::operator<(const Trip& other) const
{
    return stations < other.stations;
}
