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

    // Core Removal Operations
    T popFront() override{
        T front = list.getHead()->val;
        list.removeHead();
        return front;
    }
    T popBack() override{
        T back = list.getTail()->val;
        list.removeTail();
        return back;
    }

    // Element Accessors
    const T& front() const override{
        return list.getHead()->val;
    }
    const T& back() const override{
        return list.getTail()->val;
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






