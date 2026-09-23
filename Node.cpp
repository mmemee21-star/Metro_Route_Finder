#include "../include/Node.h"

Node::Node(int index)
    : stationIndex(index), next(nullptr) {}

int Node::getStationIndex() const
{
    return stationIndex;
}

Node* Node::getNext() const
{
    return next;
}

void Node::setNext(Node* nextNode)
{
    next = nextNode;
}
