#include "../include/Passenger.h"

#include <iostream>
#include <iomanip>

using namespace std;

Passenger::Passenger()
{
    balance = 20.0;

    tripCount = 0;
}

double Passenger::getBalance() const
{
    return balance;
}

void Passenger::addBalance(double amount)
{
    if (amount > 0)
    {
        balance += amount;
    }
}

bool Passenger::buyTicket(
    Ticket* ticket,
    int stationCount
)
{
    if (ticket == nullptr)
    {
        return false;
    }

    double price =
        ticket->calculatePrice(stationCount);

    if (balance < price)
    {
        return false;
    }

    balance -= price;

    return true;
}

void Passenger::addTrip(const Trip& trip)
{
    if (tripCount >= MAX_TRIPS)
    {
        return;
    }

    trips[tripCount] = trip;

    tripCount++;
}

void Passenger::showTripHistory() const
{
    cout << "\n=========================================\n";
    cout << "TRIP HISTORY\n";
    cout << "=========================================\n";

    if (tripCount == 0)
    {
        cout << "No trips taken yet.\n";
        return;
    }

    cout << left
         << setw(5) << "#"
         << setw(18) << "FROM"
         << setw(18) << "TO"
         << setw(10) << "STATIONS"
         << setw(12) << "TYPE"
         << "PRICE\n";

    for (int i = 0; i < tripCount; i++)
    {
        cout << left
             << setw(5) << i + 1
             << setw(18) << trips[i].getFrom()
             << setw(18) << trips[i].getTo()
             << setw(10) << trips[i].getStations()
             << setw(12) << trips[i].getType()
             << fixed
             << setprecision(0)
             << trips[i].getPrice()
             << " EGP\n";
    }

    cout << tripCount
         << " trips.\n";
}
