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
        try{
            if (list.getHead() == list.getTail()) throw std::runtime_error("Empty Array");
        }catch(std::runtime_error& error){}
        T front = list.getHead()->data;
        list.removeHead();
        return front;
    }
    T popBack() override{
        try{
            if (list.getHead() == list.getTail()) throw std::runtime_error("Empty Array");
        }catch(std::runtime_error& error){}
        T back = list.getTail()->data;
        list.removeTail();
        return back;
    }

    // Element Accessors
    const T& front() const override{
        try{
            if (list.getHead() == list.getTail()) throw std::runtime_error("Empty Array");
        }catch(std::runtime_error& error){}
        return list.getHead()->data;
    }
    const T& back() const override{
        try{
            if (list.getHead() == list.getTail()) throw std::runtime_error("Empty Array");
        }catch(std::runtime_error& error){}
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






