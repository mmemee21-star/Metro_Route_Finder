#ifndef METRO_GRAPH_H
#define METRO_GRAPH_H

#include "Station.h"
#include "Node.h"
#include "RouteQueue.h"

const int MAX_STATIONS = 50;

class MetroGraph
{
private:
    Station stations[MAX_STATIONS];

    Node* adjacency[MAX_STATIONS];

    int stationCount;

    int findStationIndex(const std::string& name) const;

    bool connectionExists(int a, int b) const;

    void clearList(int index);

    void rebuildRouteRecursive(
        int current,
        int start,
        int parent[],
        int route[],
        int& routeLength
    ) const;

public:
    MetroGraph();
    ~MetroGraph();

    bool addStation(const std::string& name);

    bool connectStations(
        const std::string& stationA,
        const std::string& stationB
    );

    void viewAllStations() const;

    void viewConnections(const std::string& name) const;

    bool stationExists(const std::string& name) const;

    int getStationCount() const;

    std::string getStationName(int index) const;

    int getUsageCount(int index) const;

    void increaseUsage(int index);

    bool findShortestRoute(
        const std::string& startName,
        const std::string& destinationName,
        int route[],
        int& routeLength,
        int& visitedCount
    ) const;
};

#endif
