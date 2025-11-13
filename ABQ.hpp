#pragma once

#include <cstddef>
#include <stdexcept>
#include <iostream>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
    ABQ(): capacity_(1), curr_size_(0), array_(new T[capacity_]){}
    explicit ABQ(const size_t capacity): capacity_(capacity), curr_size_(0), array_(new T[capacity]){}
    ABQ(const ABQ& other) {
        array_ = new T[other.capacity_];
        for (size_t i = 0; i < other.curr_size_; i++){
            array_[i] = other.array_[i];
        }
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;

    }
    ABQ& operator=(const ABQ& rhs){
        if (this == &rhs) return *this;
        delete[] array_;
        array_ = new T[rhs.capacity_];
        for (size_t i = 0; i < rhs.curr_size_; i++){
            array_[i] = rhs.array_[i];
        }
        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        return *this;
    }
    ABQ(ABQ&& other) noexcept{
        array_ = other.array_;
        curr_size_ = other.curr_size_;
        capacity_ = other.capacity_;
        other.array_ = nullptr;
        other.curr_size_ = 0;
        other.capacity_ = 0;

    }
    ABQ& operator=(ABQ&& rhs) noexcept{
        if (this == &rhs) return *this;
        delete[] array_;
        array_ = rhs.array_;
        curr_size_ = rhs.curr_size_;
        capacity_ = rhs.capacity_;
        rhs.array_ = nullptr;
        rhs.curr_size_ = 0;
        rhs.capacity_ = 0;
        return *this;
    }
    ~ABQ() noexcept override{
        delete[] array_;
        curr_size_ = 0;
        capacity_ = 0;

    }

    // Getters
    [[nodiscard]] size_t getSize() const noexcept override{
        return curr_size_;
    }
    [[nodiscard]] size_t getMaxCapacity() const noexcept{
        return capacity_;
    }
    [[nodiscard]] T* getData() const noexcept{
        return array_;
    }
    void resize(){
        T* temp = new T[capacity_ * scale_factor_];
        for (size_t i = 0; i < capacity_; i++){
            temp[i] = array_[i];
        }
        delete[] array_;
        array_ = temp;
        capacity_ *= 2;
    }
    void shrink(){
        size_t newCap = capacity_ / scale_factor_;
        T* temp = new T[newCap];
        for (size_t i = 0; i < curr_size_; i++){
            temp[i] = array_[i];
        }
        delete[] array_;
        array_ = temp;
        capacity_ = newCap;
    }
    // Insertion
    void enqueue(const T& data) override{
        if (curr_size_ == capacity_) resize();
        array_[curr_size_] = data;
        curr_size_++;
    }

    // Access
    T peek() const override{
        if (curr_size_ == 0) throw std::runtime_error("Empty Array");
        return array_[0];
    }

    // Deletion
    T dequeue() override{
        if (curr_size_ == 0) throw std::runtime_error("Empty Array");
        if (curr_size_ == capacity_ / 2) shrink();
        //T val = array_[0];
        T* temp = new T[capacity_];
        for (size_t i = 0; i < curr_size_ - 1; i++){
            temp[i] = array_[i + 1];
        }
        delete[] array_;
        array_ = temp;
        curr_size_--;
        return array_[0];
        
    }
    void printForward(){
        for (size_t i = 0; i < curr_size_; i++){
            std::cout << array_[i] << std::endl;
        }
    }
    void printReverse(){
        for (size_t i = curr_size_; i >= 1; i--){
            std::cout << array_[i-1] << std::endl;
        }
    }

};
