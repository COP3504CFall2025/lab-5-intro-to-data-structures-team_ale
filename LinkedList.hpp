#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;



template <typename T>
class LinkedList {
private:
// Stores pointers to first and last nodes and count
	struct Node{
		Node* prev;
		Node* next;
		T data;
	};
	Node* head;
	Node* tail;
	unsigned int count;
public:
	// Behaviors
	void printForward() const{
		Node* temp_ptr = head;
		while (temp_ptr != nullptr){
			std::cout << temp_ptr->data << std::endl;
			temp_ptr = temp_ptr->next;
		}
	}
	void printReverse() const{
		Node* temp_ptr = tail;
		while (temp_ptr != nullptr){
			std::cout << temp_ptr->data << std::endl;
			temp_ptr = temp_ptr->prev;
		}
	}

	// Accessors
	[[nodiscard]] unsigned int getCount() const{
		return count;
	}
	Node* getHead(){
		return head;
	}
	const Node* getHead() const{
		return head;
	}
	Node* getTail(){
		return tail;
	}
	const Node* getTail() const{
		return tail;
	}

	// Insertion
	void addHead(const T& data){
		Node* tmp_ptr = new Node();
		tmp_ptr->data = data;
		tmp_ptr->next = head;
		tmp_ptr->prev = nullptr;
		if (head != nullptr) head->prev = tmp_ptr;
		else tail = tmp_ptr;
		head = tmp_ptr;
		count++;
	}
	void addTail(const T& data){
		Node* tmp_ptr = new Node();
		tmp_ptr->data = data;
		tmp_ptr->prev = tail;
		tmp_ptr->next = nullptr;
		if (tail != nullptr) tail->next = tmp_ptr;
		else head = tmp_ptr;
		tail = tmp_ptr;
		count++;
	}

	// Remodata
	bool removeHead(){
		if (head == nullptr) return false;
		Node* tmp_ptr = head;
		head = head->next;
		if (head != nullptr) head->prev = nullptr;
		else tail = nullptr;
		delete tmp_ptr;
		tmp_ptr = nullptr;
		count--;
		return true;
	}
	bool removeTail(){
		if (tail == nullptr) return false;
		Node* tmp_ptr = tail;
		tail = tail->prev;
		if (tail != nullptr) tail->next = nullptr;
		else head = nullptr;
		delete tmp_ptr;
		tmp_ptr = nullptr;
		count--;
		return true;
	}
	void clear(){
		Node* temp_ptr = head;
		while (temp_ptr != nullptr){
			Node* tempy = temp_ptr->next;
			delete temp_ptr;
			temp_ptr = tempy;
		}
        head = nullptr;
        tail = nullptr;
        count = 0;
	
	}

	// Operators
	LinkedList<T>& operator=(LinkedList<T>&& other) noexcept{
		if (this == &other || other.head == nullptr){
			return *this;
		}
        this->clear();
        head = other.head;
        tail = other.tail;
        count = other.count;
        other.head = nullptr;
        other.tail = nullptr;
        other.count = 0;
		return *this;
	}
	LinkedList<T>& operator=(const LinkedList<T>& rhs){
		if (this == &rhs || rhs.head == nullptr){
			return *this;
		}
        this->clear();
        Node* ptr = rhs.head;
		while (ptr != nullptr){
			addTail(ptr->data);
			ptr = ptr->next;
		}
		return *this;

	}

	// Construction/Destruction
	LinkedList(){
		head = nullptr;
		tail = nullptr;
		count = 0;
		Node();
	}
	LinkedList(const LinkedList<T>& list): head(nullptr), tail(nullptr), count(0){
		Node* ptr = list.head;
		while (ptr != nullptr){
			addTail(ptr->data);
			ptr = ptr->next;
		}

	}
	LinkedList(LinkedList<T>&& other) noexcept{
        head = other.head;
        tail = other.tail;
        count = other.count;
        other.head = nullptr;
        other.tail = nullptr;
        other.count = 0;
	}
	T& operator[](int index){
		int pos = 0;
		Node* ptr = head;
		while (pos < index){
			ptr = ptr->next;
			pos++;
		}
		return ptr->data;
	}

	~LinkedList(){
		clear();
	}

};

