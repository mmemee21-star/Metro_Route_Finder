#ifndef PASSENGER_H
#define PASSENGER_H

#include "Trip.h"
#include "Ticket.h"

const int MAX_TRIPS = 100;

class Passenger
{
private:
    double balance;

    Trip trips[MAX_TRIPS];

    int tripCount;

public:
    Passenger();

    double getBalance() const;

    void addBalance(double amount);

    bool buyTicket(
        Ticket* ticket,
        int stationCount
    );

    void addTrip(const Trip& trip);

    void showTripHistory() const;
};

#endif
