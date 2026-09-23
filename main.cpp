#include <iostream>
#include <string>
#include <iomanip>

#include "../include/MetroGraph.h"
#include "../include/Passenger.h"
#include "../include/Ticket.h"
#include "../include/Trip.h"

using namespace std;


// ==========================================
// Function Prototypes
// ==========================================

void buildInitialNetwork(MetroGraph& metro);

void showMainMenu();

void findRoute(
    MetroGraph& metro,
    Passenger& passenger
);

void buyTicket(
    MetroGraph& metro,
    Passenger& passenger
);

void walletMenu(
    Passenger& passenger
);

void usageReport(
    MetroGraph& metro
);

void adminMenu(
    MetroGraph& metro
);

void addStation(
    MetroGraph& metro
);

void connectStations(
    MetroGraph& metro
);

int getIntegerInput();


// ==========================================
// MAIN
// ==========================================

int main()
{
    MetroGraph metro;

    Passenger passenger;

    buildInitialNetwork(metro);

    int choice;

    do
    {
        showMainMenu();

        cout << "Choose: ";

        choice = getIntegerInput();

        switch (choice)
        {
        case 1:
            metro.viewAllStations();
            break;

        case 2:
        {
            string name;

            cout << "Station name: ";
            getline(cin, name);

            metro.viewConnections(name);

            break;
        }

        case 3:
            findRoute(
                metro,
                passenger
            );
            break;

        case 4:
            buyTicket(
                metro,
                passenger
            );
            break;

        case 5:
            walletMenu(passenger);
            break;

        case 6:
            passenger.showTripHistory();
            break;

        case 7:
            usageReport(metro);
            break;

        case 8:
            adminMenu(metro);
            break;

        case 0:
            cout << "\nGoodbye!\n";
            break;

        default:
            cout << "\n[X] Invalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}


// ==========================================
// INITIAL NETWORK
// ==========================================

void buildInitialNetwork(MetroGraph& metro)
{
    metro.addStation("Helwan");
    metro.addStation("Maadi");
    metro.addStation("Dar El-Salam");
    metro.addStation("El-Zahraa");
    metro.addStation("Mar Girgis");
    metro.addStation("Saad Zaghloul");
    metro.addStation("Sadat");
    metro.addStation("Attaba");
    metro.addStation("Shubra");
    metro.addStation("Ghamra");
    metro.addStation("Naguib");
    metro.addStation("Giza");
    metro.addStation("Dokki");
    metro.addStation("Bohooth");
    metro.addStation("Opera");
    metro.addStation("Kit Kat");

    // Main line

    metro.connectStations(
        "Helwan",
        "Maadi"
    );

    metro.connectStations(
        "Maadi",
        "Dar El-Salam"
    );

    metro.connectStations(
        "Dar El-Salam",
        "El-Zahraa"
    );

    metro.connectStations(
        "El-Zahraa",
        "Mar Girgis"
    );

    metro.connectStations(
        "Mar Girgis",
        "Saad Zaghloul"
    );

    metro.connectStations(
        "Saad Zaghloul",
        "Sadat"
    );

    metro.connectStations(
        "Sadat",
        "Naguib"
    );

    metro.connectStations(
        "Naguib",
        "Attaba"
    );

    metro.connectStations(
        "Attaba",
        "Ghamra"
    );

    metro.connectStations(
        "Ghamra",
        "Shubra"
    );


    // Second branch

    metro.connectStations(
        "Sadat",
        "Opera"
    );

    metro.connectStations(
        "Opera",
        "Dokki"
    );

    metro.connectStations(
        "Dokki",
        "Bohooth"
    );

    metro.connectStations(
        "Bohooth",
        "Giza"
    );


    // Kit Kat intentionally disconnected
    // so the "No route" error can be demonstrated.
}


// ==========================================
// MAIN MENU
// ==========================================

void showMainMenu()
{
    cout << "\n\n";
    cout << "=========================================\n";
    cout << "           METRO ROUTE FINDER\n";
    cout << "=========================================\n";

    cout << "1. View all stations\n";
    cout << "2. View connections of a station\n";
    cout << "3. Find a route\n";
    cout << "4. Buy a ticket\n";
    cout << "5. My wallet\n";
    cout << "6. Trip history\n";
    cout << "7. Station usage report\n";
    cout << "8. Admin\n";
    cout << "0. Exit\n";

    cout << "-----------------------------------------\n";
}


// ==========================================
// INTEGER INPUT
// ==========================================

int getIntegerInput()
{
    int value;

    while (!(cin >> value))
    {
        cin.clear();

        cin.ignore(
            10000,
            '\n'
        );

        cout << "[X] Please enter a number: ";
    }

    cin.ignore(
        10000,
        '\n'
    );

    return value;
}


// ==========================================
// FIND ROUTE
// ==========================================

void findRoute(
    MetroGraph& metro,
    Passenger& passenger
)
{
    string from;
    string to;

    cout << "\n=========================================\n";
    cout << "FIND A ROUTE\n";
    cout << "=========================================\n";

    cout << "From : ";
    getline(cin, from);

    if (!metro.stationExists(from))
    {
        cout << "[X] Station \""
             << from
             << "\" is not in the network.\n";

        return;
    }

    cout << "To : ";
    getline(cin, to);

    if (!metro.stationExists(to))
    {
        cout << "[X] Station \""
             << to
             << "\" is not in the network.\n";

        return;
    }

    int route[MAX_STATIONS];

    int routeLength = 0;

    int visitedCount = 0;

    bool found =
        metro.findShortestRoute(
            from,
            to,
            route,
            routeLength,
            visitedCount
        );

    if (!found)
    {
        cout << "[X] No route exists between "
             << from
             << " and "
             << to
             << ".\n";

        return;
    }

    cout << "\nROUTE FOUND [BFS, "
         << visitedCount
         << " nodes visited]\n";

    cout << "---------------------------------------------------\n";

    for (int i = 0; i < routeLength; i++)
    {
        cout << i + 1
             << ". "
             << metro.getStationName(
                    route[i]
                )
             << "\n";

        // Increase usage
        metro.increaseUsage(route[i]);
    }

    cout << "---------------------------------------------------\n";

    cout << "Stations : "
         << routeLength
         << "\n";

    if (routeLength <= 9)
    {
        cout << "Zone : 1-9\n";
    }
    else if (routeLength <= 16)
    {
        cout << "Zone : 10-16\n";
    }
    else
    {
        cout << "Zone : 17+\n";
    }
}


// ==========================================
// BUY TICKET
// ==========================================

void buyTicket(
    MetroGraph& metro,
    Passenger& passenger
)
{
    string from;
    string to;

    cout << "\n=========================================\n";
    cout << "BUY A TICKET\n";
    cout << "=========================================\n";

    cout << "From : ";
    getline(cin, from);

    cout << "To : ";
    getline(cin, to);

    if (!metro.stationExists(from))
    {
        cout << "[X] Station \""
             << from
             << "\" is not in the network.\n";

        return;
    }

    if (!metro.stationExists(to))
    {
        cout << "[X] Station \""
             << to
             << "\" is not in the network.\n";

        return;
    }

    int route[MAX_STATIONS];

    int routeLength = 0;

    int visitedCount = 0;

    bool found =
        metro.findShortestRoute(
            from,
            to,
            route,
            routeLength,
            visitedCount
        );

    if (!found)
    {
        cout << "[X] No route exists between "
             << from
             << " and "
             << to
             << ".\n";

        return;
    }

    cout << "\nTicket type:\n";
    cout << "(1) Regular\n";
    cout << "(2) Student\n";

    cout << "Choose: ";

    int typeChoice =
        getIntegerInput();

    Ticket* ticket = nullptr;

    if (typeChoice == 1)
    {
        ticket = new RegularTicket();
    }
    else if (typeChoice == 2)
    {
        ticket = new StudentTicket();
    }
    else
    {
        cout << "[X] Invalid ticket type.\n";
        return;
    }

    double price =
        ticket->calculatePrice(
            routeLength
        );

    cout << "\nTrip is "
         << routeLength
         << " stations";

    if (routeLength <= 9)
    {
        cout << " > Zone 1-9\n";
    }
    else if (routeLength <= 16)
    {
        cout << " > Zone 10-16\n";
    }
    else
    {
        cout << " > Zone 17+\n";
    }

    // Demonstrate polymorphism
    RegularTicket regular;

    StudentTicket student;

    cout << "Regular : "
         << regular.calculatePrice(routeLength)
         << " EGP\n";

    cout << "Student : "
         << student.calculatePrice(routeLength)
         << " EGP\n";

    cout << "Balance : "
         << passenger.getBalance()
         << " EGP\n";


    if (passenger.getBalance() < price)
    {
        cout << "[X] Balance is "
             << passenger.getBalance()
             << " EGP, ticket costs "
             << price
             << " EGP.\n";

        cout << "Purchase rejected.\n";

        delete ticket;

        return;
    }


    bool purchased =
        passenger.buyTicket(
            ticket,
            routeLength
        );

    if (purchased)
    {
        Trip trip(
            from,
            to,
            routeLength,
            ticket->getType(),
            price
        );

        passenger.addTrip(trip);

        cout << "[OK] Ticket bought. "
             << "New balance: "
             << passenger.getBalance()
             << " EGP\n";
    }
    else
    {
        cout << "Purchase rejected.\n";
    }

    delete ticket;
}


// ==========================================
// WALLET
// ==========================================

void walletMenu(
    Passenger& passenger
)
{
    cout << "\n=========================================\n";
    cout << "MY WALLET\n";
    cout << "=========================================\n";

    cout << "Balance: "
         << passenger.getBalance()
         << " EGP\n";

    cout << "Add how much? ";

    double amount;

    while (!(cin >> amount))
    {
        cin.clear();

        cin.ignore(
            10000,
            '\n'
        );

        cout << "[X] Enter a valid amount: ";
    }

    cin.ignore(
        10000,
        '\n'
    );

    if (amount <= 0)
    {
        cout << "[X] Amount must be greater than 0.\n";
        return;
    }

    passenger.addBalance(amount);

    cout << "[OK] New balance: "
         << passenger.getBalance()
         << " EGP\n";
}


// ==========================================
// USAGE REPORT
// ==========================================

void usageReport(
    MetroGraph& metro
)
{
    int count =
        metro.getStationCount();

    if (count == 0)
    {
        cout << "No stations.\n";
        return;
    }

    int indices[MAX_STATIONS];

    for (int i = 0; i < count; i++)
    {
        indices[i] = i;
    }

    long long comparisons = 0;


    // Bubble Sort
    for (int i = 0; i < count - 1; i++)
    {
        bool swapped = false;

        for (int j = 0; j < count - i - 1; j++)
        {
            comparisons++;

            if (
                metro.getUsageCount(
                    indices[j]
                )
                <
                metro.getUsageCount(
                    indices[j + 1]
                )
            )
            {
                int temp = indices[j];

                indices[j] =
                    indices[j + 1];

                indices[j + 1] = temp;

                swapped = true;
            }
        }

        if (!swapped)
        {
            break;
        }
    }


    cout << "\n=========================================\n";
    cout << "STATION USAGE\n";
    cout << "=========================================\n";

    for (int i = 0; i < count; i++)
    {
        int index = indices[i];

        int usage =
            metro.getUsageCount(index);

        if (usage > 0)
        {
            cout << metro.getStationName(index)
                 << " "
                 << usage
                 << "\n";
        }
    }

    cout << "\nSorted in "
         << comparisons
         << " comparisons [bubble sort]\n";
}


// ==========================================
// ADMIN
// ==========================================

void adminMenu(
    MetroGraph& metro
)
{
    cout << "\n=========================================\n";
    cout << "ADMIN\n";
    cout << "=========================================\n";

    cout << "1. Add station\n";
    cout << "2. Connect two stations\n";
    cout << "0. Back\n";

    cout << "Choose: ";

    int choice =
        getIntegerInput();

    switch (choice)
    {
    case 1:
        addStation(metro);
        break;

    case 2:
        connectStations(metro);
        break;

    case 0:
        return;

    default:
        cout << "[X] Invalid choice.\n";
    }
}


// ==========================================
// ADD STATION
// ==========================================

void addStation(
    MetroGraph& metro
)
{
    string name;

    cout << "Station name: ";

    getline(cin, name);

    if (metro.addStation(name))
    {
        cout << "[OK] Station "
             << name
             << " added.\n";
    }
    else
    {
        cout << "[X] Could not add station.\n";
        cout << "The station may already exist "
             << "or the network is full.\n";
    }
}


// ==========================================
// CONNECT STATIONS
// ==========================================

void connectStations(
    MetroGraph& metro
)
{
    string stationA;
    string stationB;

    cout << "Station A: ";
    getline(cin, stationA);

    cout << "Station B: ";
    getline(cin, stationB);

    if (!metro.stationExists(stationA))
    {
        cout << "[X] Station \""
             << stationA
             << "\" is not in the network.\n";

        return;
    }

    if (!metro.stationExists(stationB))
    {
        cout << "[X] Station \""
             << stationB
             << "\" is not in the network.\n";

        return;
    }

    if (
        metro.connectStations(
            stationA,
            stationB
        )
    )
    {
        cout << "[OK] "
             << stationA
             << " and "
             << stationB
             << " are now connected.\n";
    }
    else
    {
        cout << "[X] Could not create connection.\n";
    }
}
