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
        if (list.getHead() == nullptr) throw std::runtime_error("Empty Array");
        T data = list.getHead()->data;
        list.removeHead();
        return data;
    }

    // Access
    T peek() const override{
        if (list.getTail() == nullptr) throw std::runtime_error("Empty Array");
        return list.getTail()->data;
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