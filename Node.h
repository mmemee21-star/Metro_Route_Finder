#ifndef NODE_H
#define NODE_H

class Node
{
private:
    int stationIndex;
    Node* next;

public:
    Node(int index);

    int getStationIndex() const;
    Node* getNext() const;

    void setNext(Node* nextNode);
};

#endif
