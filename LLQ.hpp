#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLQ : public QueueInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLQ(): list(){}

    // Insertion
    void enqueue(const T& item) override{
        list.addTail(item);
    }

    // Deletion
    T dequeue() override{
        T val = list.getTail()->val;
        list.removeTail();
        return val;
    }

    // Access
    T peek() const override{
        return list.getTail()->val;
    }

    // Getter
    std::size_t getSize() const noexcept override{
        return static_cast<std::size_t>(list.getCount());
    }
    void* getHead(){
        return list.getHead();
    }

    void printForward(){
        list.printForward();
    }
    void printReverse(){
        list.printReverse();
    }

};