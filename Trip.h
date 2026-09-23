#ifndef TRIP_H
#define TRIP_H

#include <string>

class Trip
{
private:
    std::string from;
    std::string to;

    int stations;

    std::string type;

    double price;

public:
    Trip();

    Trip(
        const std::string& from,
        const std::string& to,
        int stations,
        const std::string& type,
        double price
    );

    std::string getFrom() const;
    std::string getTo() const;
    int getStations() const;
    std::string getType() const;
    double getPrice() const;

    bool operator<(const Trip& other) const;
};

#endif
