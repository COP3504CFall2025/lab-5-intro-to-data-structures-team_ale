#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>

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
    ABDQ(): data_(new T), capacity_(4), size_(0), front_(0), back(0){}
    explicit ABDQ(std::size_t capacity): data_(new T), capacity_(capacity), size_(0), front_(0), back(0){}
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
        if (this = &other) return *this;
        delete[] data_;
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }
    ~ABDQ() noexcept override{
        delete[] data_;
        size_ = 0;
        capacity_ = 0;

    }

    // Insertion
    void ensureCapacity(){
        T* temp = new T[capacity_ * 2];
        for (size_t i = 0; i < capacity_; i++){
            temp[i] = data_[i];
        }
        delete[] data_;
        data_ = temp;
        capacity_ *= 2;
    }
    void shrinkIfNeeded(){
        T* temp = new T[capacity_ / 2];
        for (size_t i = 0; i < capacity_; i++){
            temp[i] = data_[i];
        }
        delete[] data_;
        data_ = temp;
        capacity_ /= 2;
    }
    void pushFront(const T& item) override;
    void pushBack(const T& item) override{
        size_++;
        if (size_ > capacity_) resize();
        data_[size_ - 1] = data;
    }

    // Deletion
    T popFront() override{

    }
    T popBack() override{
        size_--;
        T* temp = new T[capacity_];
        for (size_t i = 0; i < size_ - 1; i++){
            temp[i] = data_[i + 1];
        }
        delete[] data_;
        data_ = temp;
    }

    // Access
    const T& front() const override;
    const T& back() const override;

    // Getters
    std::size_t getSize() const noexcept override{
        return size_;
    }

};
