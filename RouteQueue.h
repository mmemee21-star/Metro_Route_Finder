#ifndef ROUTE_QUEUE_H
#define ROUTE_QUEUE_H

class QueueNode
{
private:
    int value;
    QueueNode* next;

public:
    QueueNode(int value);

    int getValue() const;
    QueueNode* getNext() const;

    void setNext(QueueNode* nextNode);
};


class RouteQueue
{
private:
    QueueNode* front;
    QueueNode* rear;

public:
    RouteQueue();
    ~RouteQueue();

    bool isEmpty() const;

    void enqueue(int value);
    int dequeue();
};

#endif
