#ifndef QUEUE_HPP
#define QUEUE_HPP

struct Node {
    int vertex;
    int level;
};

class MyQueue {
public:
    MyQueue(int maxSize);
    ~MyQueue();

    void push(Node node);
    Node pop();
    bool isEmpty() const;

private:
    Node* arr;
    int size;
    int head;
    int tail;
};
#endif