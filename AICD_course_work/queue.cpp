#include "queue.hpp"

MyQueue::MyQueue(int maxSize) {
    size = maxSize;
    arr = new Node[size];
    head = 0;
    tail = 0;
}

MyQueue::~MyQueue() {
    delete[] arr;
}

void MyQueue::push(Node node) {
    arr[tail++] = node;
}

Node MyQueue::pop() {
    return arr[head++];
}

bool MyQueue::isEmpty() const {
    return head == tail;
}
