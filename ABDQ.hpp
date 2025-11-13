#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>
#include <iostream>

template <typename T>
class ABDQ : public DequeInterface<T> {
private:                 
    T* data_;// underlying dynamic data_
    std::size_t capacity_;     // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

public:
    // Big 5
    ABDQ():  data_(new T[4]), capacity_(4), size_(0), front_(0), back_(0){}
    explicit ABDQ(std::size_t capacity): data_(new T[capacity]), capacity_(capacity), size_(0), front_(0), back_(0){}
    ABDQ(const ABDQ& other) {
        data_ = new T[other.capacity_];
        for (std::size_t i = other.front_; i < other.front_ + other.size_ ; i++){
            data_[i % other.capacity_] = other.data_[i % other.capacity_];
        }
        front_ = other.front_;
        back_ = other.back_;
        capacity_ = other.capacity_;
        size_ = other.size_;

    }
    ABDQ& operator=(const ABDQ& other){
        if (this == &other) return *this;
        delete[] data_;
        data_ = new T[other.capacity_];
        for (std::size_t i = other.front_; i < other.front_ + other.size_ ; i++){
            data_[i % other.capacity_] = other.data_[i % other.capacity_];
        }
        front_ = other.front_;
        back_ = other.back_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        return *this;
    }
    ABDQ(ABDQ&& other) noexcept{
        data_ = other.data_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        other.front_ = 0;
        other.back_ = 0;


    }
    ABDQ& operator=(ABDQ&& other) noexcept{
        if (this == &other) return *this;
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        front_ = other.front_;
        back_ = other.back_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        other.front_ = 0;
        other.back_ = 0;
        return *this;
    }
    ~ABDQ() noexcept override{
        delete[] data_;
        size_ = 0;
        capacity_ = 0;
        front_ = 0;
        back_ = 0;

    }

    // Insertion
    void ensureCapacity(){
        std::size_t newCap = capacity_ * SCALE_FACTOR;
        T* temp = new T[newCap];
        for (std::size_t i = front_; i < front_ + size_ ; i++){
            temp[i % newCap] = data_[i % capacity_];
        }
        delete[] data_;
        data_ = temp;
        capacity_ = newCap;
        back_ = (front_ + size_) % capacity_;
    }
    void shrinkIfNeeded(){
        std::size_t newCap = capacity_ / SCALE_FACTOR;
        T* temp = new T[newCap];
        for (std::size_t i = front_; i < front_ + size_; i++){
            temp[i % newCap] = data_[i % capacity_];
        }
        delete[] data_;
        data_ = temp;
        capacity_ = newCap;
        front_  %= capacity_;
        back_ = (front_ + size_) % capacity_;
    }
    void pushFront(const T& item) override{
        if (size_ == capacity_) ensureCapacity();
        front_ = (front_ - 1 + capacity_) % capacity_;
        data_[front_] = item;
        size_++;
    }
    void pushBack(const T& item) override{
        if (size_ == capacity_) ensureCapacity();
        data_[back_] = item;
        back_ = (back_ + 1) % capacity_;
        size_++;
    }

    // Deletion
    T popFront() override{
        if (size_ == 0){
            throw std::runtime_error("Empty Array");
        }
        T val = data_[front_];
        front_ = (front_ + 1) % capacity_;
        size_--;
        if (size_ == (capacity_ / 2) - 1) shrinkIfNeeded();
        return val;
        
    }
    T popBack() override{
        if (size_ == 0){
            throw std::runtime_error("Empty Array");
        }
        T val = data_[back_ - 1];
        back_ = (back_ - 1 + capacity_) % capacity_;
        size_--;
        if (size_ == (capacity_ / 2) - 1) shrinkIfNeeded();
        return val;

    }

    // Access
    const T& front() const override{
        if (size_ == 0){
            throw std::runtime_error("Empty Array");
        }
        return data_[front_];
    }
    const T& back() const override{
        if (size_ == 0){
            throw std::runtime_error("Empty Array");
        }
        return data_[back_ - 1];
    }

    // Getters
    std::size_t getSize() const noexcept override{
        return size_;
    }
    void printForward(){
        for (std::size_t i = front_; i < size_ + front_; i++){
            std::cout << data_[i % capacity_] << std::endl;
        }
    }
    void printReverse(){
        std::size_t i = back_ - 1;
        std::size_t count = 0;
        while(i != front_){
            std::cout << data_[(i + capacity_) % capacity_] << std::endl;
            i = (i - 1) % capacity_;
            count++;
        }
        std::cout << data_[front_] << std::endl;

    }

};
