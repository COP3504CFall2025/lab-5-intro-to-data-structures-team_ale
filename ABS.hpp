#pragma once

#include <cstddef>
#include <stdexcept>
#include <iostream>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABS : public StackInterface<T> {
public:
    // Big 5 + Parameterized Constructor
    ABS(): capacity_(1), curr_size_(0), array_(new T[capacity_]){}
    explicit ABS(const size_t capacity): capacity_(capacity), curr_size_(0), array_(new T[capacity]){}
    ABS(const ABS& other) {
        array_ = new T[other.capacity_];
        for (size_t i = 0; i < other.curr_size_; i++){
            array_[i] = other.array_[i];
        }
        capacity_ = other.capacity_;
        curr_size_ = other.curr_size_;

    }
    ABS& operator=(const ABS& rhs){
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
    ABS(ABS&& other) noexcept{
        array_ = other.array_;
        curr_size_ = other.curr_size_;
        capacity_ = other.capacity_;
        other.array_ = nullptr;
        other.curr_size_ = 0;
        other.capacity_ = 0;

    }
    ABS& operator=(ABS&& rhs) noexcept{
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
    ~ABS() noexcept override{
        delete[] array_;
        curr_size_ = 0;
        capacity_ = 0;

    }

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override{
        return curr_size_;
    }

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept{
        return capacity_;
    }

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept{
        return array_;
    }

    // Push item onto the stack
    void resize(){
        T* temp = new T[capacity_ * scale_factor_];
        for (size_t i = 0; i < capacity_; i++){
            temp[i] = array_[i];
        }
        delete[] array_;
        array_ = temp;
        capacity_ *= 2;
    }
    void push(const T& data) override{
        curr_size_++;
        if (curr_size_ > capacity_) resize();
        T* temp = new T[capacity_];
        temp[0] = data;
        for (size_t i = 0; i < curr_size_; i++){
            temp[i + 1] = array_[i];
        }
        delete[] array_;
        array_ = temp;
    }

    T peek() const override{
        return array_[0];
    }

    T pop() override{
        if (curr_size_ == 0) throw std::runtime_error("Empty Array");
        curr_size_--;
        T val = array_[curr_size_ - 1];
        T* temp = new T[capacity_];
        for (size_t i = 0; i < curr_size_ - 1; i++){
            temp[i] = array_[i + 1];
        }
        delete[] array_;
        array_ = temp;
        return val;
    }
    void printForward(){
        for (size_t i = 0; i < curr_size_; i++){
            std::cout << array_[i] << std::endl;
        }
    }
    void printReverse(){
        for (size_t i = curr_size_; i >= 1; i--){
            std::cout << array_[i - 1] << std::endl;
        }
    }
private:
    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;
};
