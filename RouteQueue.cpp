#include "../include/RouteQueue.h"
#include <stdexcept>

QueueNode::QueueNode(int value)
{
    this->value = value;
    this->next = nullptr;
}

int QueueNode::getValue() const
{
    return value;
}

QueueNode* QueueNode::getNext() const
{
    return next;
}

void QueueNode::setNext(QueueNode* nextNode)
{
    next = nextNode;
}


// ==========================
// RouteQueue
// ==========================

RouteQueue::RouteQueue()
{
    front = nullptr;
    rear = nullptr;
}

RouteQueue::~RouteQueue()
{
    while (!isEmpty())
    {
        dequeue();
    }
}

bool RouteQueue::isEmpty() const
{
    return front == nullptr;
}

void RouteQueue::enqueue(int value)
{
    QueueNode* newNode = new QueueNode(value);

    if (rear == nullptr)
    {
        front = rear = newNode;
        return;
    }

    rear->setNext(newNode);
    rear = newNode;
}

int RouteQueue::dequeue()
{
    if (isEmpty())
    {
        throw std::runtime_error("Queue is empty.");
    }

    QueueNode* temp = front;

    int value = temp->getValue();

    front = front->getNext();

    if (front == nullptr)
    {
        rear = nullptr;
    }

    delete temp;

    return value;
}
