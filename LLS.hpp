#pragma once

#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <stdlib.h>
#include <stdexcept>

template <typename T>
class LLS : public StackInterface<T> {
private:
    LinkedList<T> list;
public:
    // Constructor
    LLS(): list(){} //calls default constructor of LinkedList<T>

    // Insertion
    void push(const T& item) override{
        list.addHead(item);
    }
    // Deletion
    T pop() override{
        try{
            if (list.getHead() == list.getTail()) throw std::runtime_error("Empty Array");
        }catch(std::runtime_error& error){}
        T val = list.getHead()->val;
        list.removeHead();
        return val;
    }

    // Access
    T peek() const override{
        return list.getHead()->val;
    }

    //Getters
    std::size_t getSize() const noexcept override{
        return static_cast<std::size_t>(list.getCount());
    }
    void printForward(){
        list.printForward();
    }
    void printReverse(){
        list.printReverse();
    }
};