#ifndef STATION_H
#define STATION_H

#include <string>

class Station
{
private:
    int id;
    std::string name;
    int usageCount;

public:
    Station();
    Station(int id, const std::string& name);

    int getId() const;
    std::string getName() const;
    int getUsageCount() const;

    void setName(const std::string& newName);
    void increaseUsage();
};

#endif
