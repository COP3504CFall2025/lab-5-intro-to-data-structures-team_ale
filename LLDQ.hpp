#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ(): list(){}

    // Core Insertion Operations
    void pushFront(const T& item) override{
        list.addHead(item);
    }
    void pushBack(const T& item) override{
        list.addTail(item);
    }

    // Core Remodata Operations
    T popFront() override{
        if (list.getHead() == nullptr) throw std::runtime_error("Empty Array");
        T front = list.getHead()->data;
        list.removeHead();
        return front;
    }
    T popBack() override{
        if (list.getTail() == nullptr) throw std::runtime_error("Empty Array");
        T back = list.getTail()->data;
        list.removeTail();
        return back;
    }

    // Element Accessors
    const T& front() const override{
        if (list.getHead() == nullptr) throw std::runtime_error("Empty Array");
        return list.getHead()->data;
    }
    const T& back() const override{
        if (list.getTail() == nullptr) throw std::runtime_error("Empty Array");
        return list.getTail()->data;
    }

    // Getter
    std::size_t getSize() const noexcept override{
        return list.getCount();
    }

    void printForward(){
        list.printForward();
    }
    void printReverse(){
        list.printReverse();
    }
};






