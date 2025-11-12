#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;



template <typename T>
class LinkedList {
private:
// Stores pointers to first and last nodes and count
	struct Node{
		Node* previous;
		Node* next;
		T val;
	};
	Node* head;
	Node* tail;
	unsigned int count;
public:
	// Behaviors
	void printForward() const{
		Node* temp_ptr = head;
		while (temp_ptr != nullptr){
			std::cout << temp_ptr->val << std::endl;
			temp_ptr = temp_ptr->next;
		}
	}
	void printReverse() const{
		Node* temp_ptr = tail;
		while (temp_ptr != nullptr){
			std::cout << temp_ptr->val << std::endl;
			temp_ptr = temp_ptr->previous;
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
		tmp_ptr->val = data;
		if (head == nullptr){
			head = tmp_ptr;
			tail = tmp_ptr;
		}else{
			head->previous = tmp_ptr;
			tmp_ptr->next = head;
			tmp_ptr->previous = nullptr;
			head = tmp_ptr;
		}
		count++;
	}
	void addTail(const T& data){
		Node* tmp_ptr = new Node();
		tmp_ptr->val = data;
		if (tail == nullptr){
			head = tmp_ptr;
			tail = tmp_ptr;
		}else{
			tail->next = tmp_ptr;
			tmp_ptr->previous = tail;
			tmp_ptr->next = nullptr;
			tail = tmp_ptr;
		}
		count++;
	}

	// Removal
	void removeHead(){
		try{
            if (list.getHead() == list.getTail()) throw std::runtime_error("Empty Array");
        }catch(std::runtime_error& error){}
		if (count == 1){
			delete head;
			head = nullptr;
			tail = nullptr;
		}
		Node* tmp_ptr = head;
		head = head->next;
		head->previous = nullptr;
		delete tmp_ptr;
		tmp_ptr = nullptr;
		count--;
	}
	void removeTail(){
		try{
            if (list.getHead() == list.getTail()) throw std::runtime_error("Empty Array");
        }catch(std::runtime_error& error){}
		if (count == 1){
			delete tail;
			head = nullptr;
			tail = nullptr;
		}
		Node* tmp_ptr = tail;
		tail = tail->previous;
		tail->next = nullptr;
		delete tmp_ptr;
		tmp_ptr = nullptr;
		count--;
	}
	void Clear(){
		if (head == nullptr){
			return;
		}
		Node* temp_ptr = head->next;
		while (temp_ptr != nullptr){
			delete temp_ptr->previous;
			if (temp_ptr->next == nullptr){
				delete temp_ptr;
				temp_ptr = nullptr;
			}
			else temp_ptr = temp_ptr->next;
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
        this->Clear();
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
        this->Clear();
        Node* ptr = rhs.head;
		while (ptr != nullptr){
			addTail(ptr->val);
			ptr = ptr->next;
		}
		return *this;

	}

	// Construction/Destruction
	LinkedList(){
		head = nullptr;
		tail = nullptr;
		count = 0;
	}
	LinkedList(const LinkedList<T>& list): head(nullptr), tail(nullptr), count(0){
		Node* ptr = list.head;
		while (ptr != nullptr){
			addTail(ptr->val);
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
		return ptr->val;
	}

	~LinkedList(){
		Clear();
	}

};

