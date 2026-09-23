#ifndef TICKET_H
#define TICKET_H

#include <string>

class Ticket
{
public:
    virtual ~Ticket();

    virtual double calculatePrice(
        int stations
    ) const = 0;

    virtual std::string getType() const = 0;
};


class RegularTicket : public Ticket
{
public:
    double calculatePrice(
        int stations
    ) const override;

    std::string getType() const override;
};


class StudentTicket : public Ticket
{
public:
    double calculatePrice(
        int stations
    ) const override;

    std::string getType() const override;
};

#endif
