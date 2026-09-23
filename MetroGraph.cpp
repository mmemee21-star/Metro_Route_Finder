#include "../include/MetroGraph.h"

#include <iostream>
#include <string>

using namespace std;

MetroGraph::MetroGraph()
{
    stationCount = 0;

    for (int i = 0; i < MAX_STATIONS; i++)
    {
        adjacency[i] = nullptr;
    }
}

MetroGraph::~MetroGraph()
{
    for (int i = 0; i < MAX_STATIONS; i++)
    {
        clearList(i);
    }
}

void MetroGraph::clearList(int index)
{
    Node* current = adjacency[index];

    while (current != nullptr)
    {
        Node* temp = current;

        current = current->getNext();

        delete temp;
    }

    adjacency[index] = nullptr;
}

int MetroGraph::findStationIndex(const string& name) const
{
    // Linear Search
    for (int i = 0; i < stationCount; i++)
    {
        if (stations[i].getName() == name)
        {
            return i;
        }
    }

    return -1;
}

bool MetroGraph::stationExists(const string& name) const
{
    return findStationIndex(name) != -1;
}

int MetroGraph::getStationCount() const
{
    return stationCount;
}

string MetroGraph::getStationName(int index) const
{
    if (index < 0 || index >= stationCount)
    {
        return "";
    }

    return stations[index].getName();
}

int MetroGraph::getUsageCount(int index) const
{
    if (index < 0 || index >= stationCount)
    {
        return 0;
    }

    return stations[index].getUsageCount();
}

void MetroGraph::increaseUsage(int index)
{
    if (index >= 0 && index < stationCount)
    {
        stations[index].increaseUsage();
    }
}

bool MetroGraph::addStation(const string& name)
{
    if (name.empty())
    {
        return false;
    }

    if (stationCount >= MAX_STATIONS)
    {
        return false;
    }

    if (stationExists(name))
    {
        return false;
    }

    stations[stationCount] = Station(
        stationCount + 1,
        name
    );

    adjacency[stationCount] = nullptr;

    stationCount++;

    return true;
}

bool MetroGraph::connectionExists(int a, int b) const
{
    Node* current = adjacency[a];

    while (current != nullptr)
    {
        if (current->getStationIndex() == b)
        {
            return true;
        }

        current = current->getNext();
    }

    return false;
}

bool MetroGraph::connectStations(
    const string& stationA,
    const string& stationB
)
{
    int a = findStationIndex(stationA);
    int b = findStationIndex(stationB);

    if (a == -1 || b == -1)
    {
        return false;
    }

    if (a == b)
    {
        return false;
    }

    if (connectionExists(a, b))
    {
        return false;
    }

    Node* nodeA = new Node(b);

    nodeA->setNext(adjacency[a]);

    adjacency[a] = nodeA;


    // Undirected graph
    Node* nodeB = new Node(a);

    nodeB->setNext(adjacency[b]);

    adjacency[b] = nodeB;

    return true;
}

void MetroGraph::viewAllStations() const
{
    cout << "\n=========================================\n";
    cout << "ALL STATIONS\n";
    cout << "=========================================\n";

    for (int i = 0; i < stationCount; i++)
    {
        cout << (i + 1) << ". "
             << stations[i].getName()
             << "\n";
    }

    cout << "\n"
         << stationCount
         << " stations.\n";
}

void MetroGraph::viewConnections(const string& name) const
{
    int index = findStationIndex(name);

    if (index == -1)
    {
        cout << "[X] Station \"" << name
             << "\" is not in the network.\n";

        return;
    }

    cout << "\n"
         << name
         << " connects directly to:\n";

    Node* current = adjacency[index];

    if (current == nullptr)
    {
        cout << "- No direct connections.\n";
        return;
    }

    while (current != nullptr)
    {
        int neighbor = current->getStationIndex();

        cout << "- "
             << stations[neighbor].getName()
             << "\n";

        current = current->getNext();
    }
}

void MetroGraph::rebuildRouteRecursive(
    int current,
    int start,
    int parent[],
    int route[],
    int& routeLength
) const
{
    // Base case
    if (current == start)
    {
        route[routeLength++] = current;
        return;
    }

    // Recursive call
    rebuildRouteRecursive(
        parent[current],
        start,
        parent,
        route,
        routeLength
    );

    route[routeLength++] = current;
}

bool MetroGraph::findShortestRoute(
    const string& startName,
    const string& destinationName,
    int route[],
    int& routeLength,
    int& visitedCount
) const
{
    routeLength = 0;
    visitedCount = 0;

    int start = findStationIndex(startName);
    int destination = findStationIndex(destinationName);

    if (start == -1 || destination == -1)
    {
        return false;
    }

    bool visited[MAX_STATIONS];

    int parent[MAX_STATIONS];

    for (int i = 0; i < MAX_STATIONS; i++)
    {
        visited[i] = false;
        parent[i] = -1;
    }

    RouteQueue queue;

    visited[start] = true;

    queue.enqueue(start);

    bool found = false;

    while (!queue.isEmpty())
    {
        int current = queue.dequeue();

        visitedCount++;

        if (current == destination)
        {
            found = true;
            break;
        }

        Node* neighbor = adjacency[current];

        while (neighbor != nullptr)
        {
            int nextStation =
                neighbor->getStationIndex();

            if (!visited[nextStation])
            {
                visited[nextStation] = true;

                parent[nextStation] = current;

                queue.enqueue(nextStation);
            }

            neighbor = neighbor->getNext();
        }
    }

    if (!found)
    {
        return false;
    }

    rebuildRouteRecursive(
        destination,
        start,
        parent,
        route,
        routeLength
    );

    return true;
}
