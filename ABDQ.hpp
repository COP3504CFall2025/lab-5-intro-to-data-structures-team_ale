#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>
#include <iostream>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:
    T* data_;                 // underlying dynamic data_
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ(): data_(new T[capacity_]), capacity_(4), size_(0), front_(0), back_(0){}
    explicit ABDQ(std::size_t capacity): data_(new T[capacity_]), capacity_(capacity), size_(0), front_(0), back_(0){}
    ABDQ(const ABDQ& other) {
        data_ = new T[other.capacity_];
        for (size_t i = 0; i < other.size_; i++){
            data_[i] = other.data_[i];
        }
        capacity_ = other.capacity_;
        size_ = other.size_;

    }
    ABDQ& operator=(const ABDQ& other){
        if (this == &other) return *this;
        delete[] data_;
        data_ = new T[other.capacity_];
        for (size_t i = 0; i < other.size_; i++){
            data_[i] = other.data_[i];
        }
        capacity_ = other.capacity_;
        size_ = other.size_;
        return *this;
    }
    ABDQ(ABDQ&& other) noexcept{
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;

    }
    ABDQ& operator=(ABDQ&& other) noexcept{
        if (this == &other) return *this;
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        return *this;
    }
    ~ABDQ() noexcept override{
        delete[] data_;
        size_ = 0;
        capacity_ = 0;

    }

    // Insertion
    void ensureCapacity(){
        capacity_ *= SCALE_FACTOR;
        T* temp = new T[capacity_];
        for (size_t i = 0; i < size_; i++){
            temp[i] = data_[i];
        }
        delete[] data_;
        data_ = temp;
        front_ = 0;
        back_ = size_  - 1;
    }
    void shrinkIfNeeded(){
        capacity_ /= SCALE_FACTOR;
        T* temp = new T[capacity_];
        for (size_t i = 0; i < size_; i++){
            temp[i] = data_[i];
        }
        delete[] data_;
        data_ = temp;
        front_ = 0;
        back_ = size_ - 1;
    }
    void pushFront(const T& item) override{
        front_ = (front_ - 1 + capacity_) % capacity_;
        if (front_ == back_) ensureCapacity();
        data_[front_] = item;
        size_++;
    }
    void pushBack(const T& item) override{
        back_ = (back_ + 1) % capacity_;
        if (front_ == back_) ensureCapacity();
        data_[back_] = item;
        size_++;
    }

    // Deletion
    T popFront() override{
        try{
            if (back_ == front_) throw std::runtime_error("Empty Array");
        }catch(std::runtime_error& error){}
        T val = data_[front_];
        front_ = (front_ + 1) % capacity_;
        size_--;
        if (size_ == capacity_ / 2) shrinkIfNeeded();
        return val;
        
    }
    T popBack() override{
        try{
            if (back_ == front_) throw std::runtime_error("Empty Array");
        }catch(std::runtime_error& error){}
        T val = data_[back_];
        back_ = (back_ - 1 + capacity_) % capacity_;
        size_--;
        if (size_ == capacity_ / 2) shrinkIfNeeded();
        return val;

    }

    // Access
    const T& front() const override{
        try{
            if (back_ == front_) throw std::runtime_error("Empty Array");
        }catch(std::runtime_error& error){}
        return data_[front_];
    }
    const T& back() const override{
        try{
            if (back_ == front_) throw std::runtime_error("Empty Array");
        }catch(std::runtime_error& error){}
        return data_[back_];
    }

    // Getters
    std::size_t getSize() const noexcept override{
        return size_;
    }
    void printForward(){
        for (size_t i = front_; i < size_ + front_; i++){
            std::cout << data_[i % capacity_] << std::endl;
        }
    }
    void printReverse(){
        for (size_t i = back_; i >= front_; i--){
            std::cout << data_[(i + capacity_) % capacity_] << std::endl;
        }
    }

};
