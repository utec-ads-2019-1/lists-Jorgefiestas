#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
    T data;
    Node<T>* next;
    Node<T>* prev;
	Node(T data){
		this->data = data;
		this->next = nullptr;
		this->prev = nullptr;
	}
	Node(T data, Node<T>* next){
		this->data = data;
		this->next = next;
		this->prev = nullptr;
	}
	Node(T data, Node<T>* next, Node<T>* prev){
		this->data = data;
		this->next = next;
		this->prev = prev;
	}
    void killSelf() {
		delete this;
    }
};

#endif
