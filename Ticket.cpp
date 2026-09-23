#include "../include/Ticket.h"

Ticket::~Ticket()
{
}


// ======================================
// Regular Ticket
// ======================================

double RegularTicket::calculatePrice(int stations) const
{
    if (stations <= 9)
    {
        return 8.0;
    }
    else if (stations <= 16)
    {
        return 12.0;
    }

    return 15.0;
}

std::string RegularTicket::getType() const
{
    return "Regular";
}


// ======================================
// Student Ticket
// ======================================

double StudentTicket::calculatePrice(int stations) const
{
    RegularTicket regular;

    return regular.calculatePrice(stations) / 2.0;
}

std::string StudentTicket::getType() const
{
    return "Student";
}
