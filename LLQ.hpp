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
        try{
            if (list.getHead() == list.getTail()) throw std::runtime_error("Empty Array");
        }catch(std::runtime_error& error){}
        T data = list.getTail()->data;
        list.removeTail();
        return data;
    }

    // Access
    T peek() const override{
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