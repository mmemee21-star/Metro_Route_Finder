#include "../include/Station.h"

Station::Station()
{
    id = -1;
    name = "";
    usageCount = 0;
}

Station::Station(int id, const std::string& name)
{
    this->id = id;
    this->name = name;
    usageCount = 0;
}

int Station::getId() const
{
    return id;
}

std::string Station::getName() const
{
    return name;
}

int Station::getUsageCount() const
{
    return usageCount;
}

void Station::setName(const std::string& newName)
{
    name = newName;
}

void Station::increaseUsage()
{
    usageCount++;
}
