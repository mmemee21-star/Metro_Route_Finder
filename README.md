# Metro_Route_Finder 
A C++ console-based Metro Route Finder application developed using Object-Oriented Programming (OOP), custom data structures, and graph algorithms.

The project models a metro network as a graph and allows passengers to find the shortest route between stations, calculate ticket prices, manage their balance, and keep track of their trips.

---

## Project Overview

**Metro Route Finder** is a console application designed to simulate a simple metro transportation system.

The metro network is represented as a **graph**, where:

* Each station is represented as a vertex.
* Each connection between two stations is represented as an edge.
* **BFS (Breadth-First Search)** is used to find the route with the minimum number of stations.

The application also includes a ticket system, passenger wallet, trip history, station usage reports, and basic admin operations.

---

## Project Type

* **Language:** C++
* **Application Type:** Console Application
* **Programming Paradigm:** Object-Oriented Programming
* **Main Algorithm:** Breadth-First Search (BFS)
* **Main Data Structure:** Graph using Adjacency Lists
* **Custom Data Structure:** Linked Queue

---

## Team Member

This is an individual project developed by:

| Name    | Responsibility                                                                     |
| ------- | ---------------------------------------------------------------------------------- |
| Nermeen | Full project development, implementation, testing, documentation, and presentation |

---

## Main Features

### 1. View All Stations

Displays all stations available in the metro network.

### 2. View Connections

Displays the connections between metro stations.

### 3. Find Shortest Route

The passenger enters:

* Starting station
* Destination station

The program uses **BFS** to find a route containing the minimum number of stations.

The route is then reconstructed and displayed to the user.

### 4. Buy Ticket

The passenger can purchase a ticket after selecting a route.

The ticket price depends on the number of stations travelled.

The system supports:

* Regular Ticket
* Student Ticket

### 5. Wallet / Balance

The passenger has a wallet balance.

The user can:

* View current balance
* Add money
* Pay for a ticket

The program checks whether the passenger has enough balance before completing the purchase.

### 6. Trip History

The application stores previous trips and displays information such as:

* Starting station
* Destination station
* Number of stations
* Ticket type
* Ticket price

### 7. Station Usage Report

The system tracks how many times stations are used.

The usage report sorts stations according to their usage using a manually implemented **Bubble Sort** algorithm.

The number of comparisons is also displayed.

### 8. Admin Features

The admin section allows:

* Adding a new station
* Connecting two stations

These operations update the metro graph.

---

# Object-Oriented Programming

The project applies the main OOP concepts required for the application.

## Encapsulation

Data members are kept private inside classes and accessed through public methods.

For example, `Station`, `Passenger`, and `Trip` use private data members with public functions to control access.

---

## Abstraction

The `Ticket` class is an abstract base class.

It defines a common interface for different ticket types:

```cpp
virtual double calculatePrice(int stations) const = 0;
virtual std::string getType() const = 0;
```

The user does not need to know how every ticket type calculates its price.

---

## Inheritance

Two classes inherit from the abstract `Ticket` class:

```text
Ticket
├── RegularTicket
└── StudentTicket
```

Each derived class provides its own implementation of the ticket functions.

---

## Polymorphism

Polymorphism is implemented using a base-class pointer:

```cpp
Ticket* ticket;
```

The program can point to either a `RegularTicket` or a `StudentTicket`.

When:

```cpp
ticket->calculatePrice(stations);
```

is called, the appropriate derived-class implementation is executed at runtime.

This demonstrates **runtime polymorphism**.

---

## Constructors and Destructors

Constructors are used to initialize objects.

Destructors are implemented where dynamic memory needs to be released, especially in classes that manage linked structures.

---

## Operator Overloading

The `Trip` class overloads the `<` operator.

It compares trips according to the number of stations.

Example:

```cpp
trip1 < trip2
```

can be used to compare two trips based on their station count.

---

# Data Structures

## 1. Graph

The metro network is represented using a graph with an **Adjacency List**.

Each station stores a linked list of the stations directly connected to it.

Conceptually:

```text
Station A
   |
   ├── Station B
   ├── Station C
   └── Station D
```

An adjacency list is suitable because the metro network contains specific connections between stations rather than connections between every possible pair of stations.

---

## 2. Custom Linked Queue

A custom queue was implemented from scratch instead of using:

```cpp
std::queue
```

The queue follows the **FIFO** principle:

```text
First In → First Out
```

It is mainly used by BFS.

The queue supports:

* `enqueue()`
* `dequeue()`
* `isEmpty()`

---

## 3. Linked Nodes

The project uses linked nodes to build the adjacency lists and custom queue.

Each node stores information about the connected station and a pointer to the next node.

---

# Algorithms

## Breadth-First Search — BFS

BFS is used to find the shortest route between two stations in terms of the number of stations.

### Why BFS?

Every metro connection is considered to have equal cost.

Therefore, BFS guarantees that the first route found to the destination uses the minimum number of edges/stations.

### General Process

```text
Start Station
      ↓
Add to Queue
      ↓
Visit Neighbors
      ↓
Add Unvisited Stations
      ↓
Continue BFS
      ↓
Reach Destination
      ↓
Reconstruct Route
```

---

## Recursive Route Reconstruction

After BFS finishes, a `parent` array is used to remember how each station was reached.

The route is reconstructed recursively from the destination back to the starting station.

This is implemented through:

```cpp
rebuildRouteRecursive()
```

---

## Linear Search

The program uses linear search to find a station by its name.

The search checks stations one by one until the required station is found.

---

## Bubble Sort

The station usage report uses a manually implemented Bubble Sort.

Stations are sorted according to their usage count.

The algorithm also counts the number of comparisons performed during sorting.

---

# Time Complexity

| Operation             | Complexity |
| --------------------- | ---------- |
| Linear Station Search | O(V)       |
| BFS                   | O(V + E)   |
| Route Reconstruction  | O(V)       |
| Bubble Sort           | O(V²)      |

Where:

* `V` = number of stations
* `E` = number of connections

---

# Ticket System

Ticket prices are calculated according to the number of stations travelled.

| Number of Stations | Regular Ticket | Student Ticket |
| ------------------ | -------------: | -------------: |
| 1–9                |          8 EGP |          4 EGP |
| 10–16              |         12 EGP |          6 EGP |
| 17+                |         15 EGP |        7.5 EGP |

Students receive a **50% discount** on the regular ticket price.

For example:

```text
7 stations
Regular = 8 EGP
Student = 4 EGP
```

The ticket prices can be modified in:

```text
src/Ticket.cpp
```

---

# Error Handling

The program handles several possible errors.

### Station Not Found

If the user enters a station that does not exist, the program displays an appropriate error message.

### No Route Exists

If there is no connection between the starting station and destination, the program informs the user that no route exists.

### Insufficient Balance

If the passenger does not have enough money to buy a ticket, the purchase is rejected.

The user can add money to the wallet and try again.

---

# Project Structure

```text
MetroRouteFinder/
│
├── README.md
│
├── docs/
│   ├── UML-class-diagram.png
│   └── Presentation
├── include/
│   ├── Node.h
│   ├── Station.h
│   ├── RouteQueue.h
│   ├── MetroGraph.h
│   ├── Ticket.h
│   ├── Trip.h
│   └── Passenger.h
│
└── src/
    ├── Node.cpp
    ├── Station.cpp
    ├── RouteQueue.cpp
    ├── MetroGraph.cpp
    ├── Ticket.cpp
    ├── Trip.cpp
    ├── Passenger.cpp
    └── main.cpp
```

---

# Class Responsibilities

| Class           | Responsibility                                             |
| --------------- | ---------------------------------------------------------- |
| `Node`          | Represents a linked node used by the graph and queue       |
| `Station`       | Stores station information and usage count                 |
| `RouteQueue`    | Implements the custom FIFO queue                           |
| `MetroGraph`    | Manages stations, connections, BFS, and station usage      |
| `Ticket`        | Abstract base class for tickets                            |
| `RegularTicket` | Calculates regular ticket prices                           |
| `StudentTicket` | Calculates discounted student prices                       |
| `Trip`          | Stores trip information and overloads `<`                  |
| `Passenger`     | Manages balance, ticket purchase, and trip history         |
| `main`          | Handles the console menu and connects all project features |

---

# UML Class Diagram

The UML class diagram illustrates the relationships between the main classes in the project.

The diagram is available in:

```text
docs/uml-class-diagram.png
```

Main relationships include:

```text
              Ticket
             /      \
            /        \
RegularTicket      StudentTicket


Passenger ──────── Trip

MetroGraph ─────── Station
    |
    └──── Node

MetroGraph ───── RouteQueue
```

---

# Compilation

The project can be compiled using **GNU GCC Compiler** with C++17.

From the project directory:

```bash
g++ -std=c++17 src/*.cpp -Iinclude -o metro
```

On Windows:

```bash
g++ -std=c++17 src/*.cpp -Iinclude -o metro.exe
```

---

# Running the Program

After compilation, run:

### Linux / macOS

```bash
./metro
```

### Windows

```bash
metro.exe
```

---

# Main Menu

The application provides the following main menu:

```text
1. View all stations
2. View connections
3. Find route
4. Buy ticket
5. Wallet
6. Trip history
7. Station usage report
8. Admin
0. Exit
```

---

# Testing

The project was tested using different scenarios, including:

* Viewing all stations
* Viewing station connections
* Finding a valid shortest route
* Searching for a station that does not exist
* Testing a route where no connection exists
* Buying a regular ticket
* Buying a student ticket
* Testing insufficient balance
* Adding balance to the wallet
* Viewing trip history
* Viewing station usage statistics
* Sorting station usage
* Adding a station through the admin menu
* Connecting stations through the admin menu

The application also includes a disconnected station scenario that can be used to demonstrate the **No Route Exists** case.

---

# Technologies Used

* C++
* C++17
* Object-Oriented Programming
* Graph Data Structure
* Adjacency Lists
* Linked Lists
* Custom Queue
* Breadth-First Search
* Recursion
* Bubble Sort
* GNU GCC Compiler
* Code::Blocks / C++ Development Environment

---

# Conclusion

The **Metro Route Finder** project demonstrates how Object-Oriented Programming and fundamental data structures and algorithms can be combined to build a practical console-based application.

The project applies:

* Encapsulation
* Abstraction
* Inheritance
* Polymorphism
* Operator Overloading
* Graphs
* Linked Lists
* Custom Queues
* BFS
* Recursion
* Bubble Sort

The application provides a complete basic simulation of a metro route system, including route finding, ticket management, passenger balance, trip history, station usage reports, and administrative operations.
