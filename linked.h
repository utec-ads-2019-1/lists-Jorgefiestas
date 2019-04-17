#ifndef LINKED_H
#define LINKED_H

#include "list.h"
#include "iterators/bidirectional_iterator.h"

template <typename T>
class LinkedList : public List<T> {
    public:
		LinkedList() : List<T>() {} 
		T front(); 
		T back(); 
		void push_front(T); 
		void push_back(T);  
		void pop_front();  
		void pop_back(); 
		T operator[](int index); 
		bool empty(); 
		int size(); 
		void clear(); 

		void sort(); 
		void mergeSort(Node<T>*&); 
		Node<T>* mergeSortSplit(Node<T>*); 
		Node<T>* sortedMerge(Node<T>*, Node<T>*); 

		void reverse(); 

        string name() {
            return "Linked List";
        }

        BidirectionalIterator<T> begin() {
			return BidirectionalIterator<T>(List<T>::head, List<T>::tail);
        }

	    BidirectionalIterator<T> end() {
			return BidirectionalIterator<T>(nullptr, List<T>::tail);
        }

        void merge(LinkedList<T>);

		~LinkedList(){
			clear();
		}
};

template <typename T>
T LinkedList<T>::front(){
	if(List<T>::head == nullptr) throw(out_of_range("Segmentation Fault"));
	return List<T>::head->data;
}

template <typename T>
T LinkedList<T>::back(){
	if(List<T>::tail == nullptr) throw(out_of_range("Segmentation Fault"));
	return List<T>::tail->data;
}

template <typename T>
void LinkedList<T>::push_front(T value){
	List<T>::nodes++;
	List<T>::head = new Node<T>(value, List<T>::head);
	if(List<T>::head->next == nullptr) List<T>::tail = List<T>::head;
	else List<T>::head->next->prev = List<T>::head;
}

template <typename T>
void LinkedList<T>::push_back(T value){
	List<T>::nodes++;
	List<T>::tail = new Node<T>(value, nullptr, List<T>::tail);
	if(List<T>::tail->prev == nullptr) List<T>::head = List<T>::tail;
	else List<T>::tail->prev->next = List<T>::tail;
}

template <typename T>
void LinkedList<T>::pop_front(){
	if(List<T>::head == nullptr) throw(out_of_range("Segmentation Fault"));
	List<T>::nodes--;
	if(List<T>::head->next == nullptr){
		List<T>::head->killSelf();
		List<T>::head = nullptr;
		List<T>::tail = nullptr;
		return;
	}
	List<T>::head = List<T>::head->next;
	List<T>::head->prev->killSelf();
	List<T>::head->prev = nullptr;
}

template <typename T>
void LinkedList<T>::pop_back(){
	if(List<T>::head == nullptr) throw(out_of_range("Segmentation Fault"));
	List<T>::nodes--;
	if(List<T>::head->next == nullptr){
		List<T>::head->killSelf();
		List<T>::head = nullptr;
		List<T>::tail = nullptr;
		return;
	}
	List<T>::tail = List<T>::tail->prev;
	List<T>::tail->next->killSelf();
	List<T>::tail->next = nullptr;
}

template <typename T>
T LinkedList<T>::operator[](int idx){
	Node<T>* temp = List<T>::head;
	while(idx--){
		if(temp == nullptr) throw(out_of_range("Segmentation Fault"));
		temp = temp->next;
	}
	return temp->data;
}

template <typename T>
bool LinkedList<T>::empty(){
	return List<T>::nodes == 0;
}

template <typename T>
int LinkedList<T>::size(){
	return List<T>::nodes;
}

template <typename T>
void LinkedList<T>::clear(){
	while(List<T>::head != nullptr){
		pop_front();
	}
}

template <typename T>
void LinkedList<T>::sort(){
	mergeSort(List<T>::head);
	Node<T>* temp = List<T>::head;
	while(temp->next != nullptr){
		temp->next->prev = temp;
		temp = temp->next;
	}
	List<T>::tail = temp;
}

template <typename T>
void LinkedList<T>::mergeSort(Node<T>* &root){
	if(root == nullptr || root->next == nullptr) return;

	Node<T>* half = mergeSortSplit(root);
	mergeSort(root);
	mergeSort(half);
	root = sortedMerge(root, half);
}
	
template <typename T>
Node<T>* LinkedList<T>::mergeSortSplit(Node<T>* root){
	Node<T>* slow = root, *fast = root->next;

	while(fast != nullptr){
		fast = fast->next;
		if(fast == nullptr) continue;
		slow = slow->next;
		fast = fast->next;
	}

	Node<T>* half = slow->next;
	slow->next = nullptr;
	return  half;
}

template <typename T>
Node<T>* LinkedList<T>::sortedMerge(Node<T>* a, Node<T>* b){
	if(a == nullptr) return b;
	if(b == nullptr) return a;
	
	Node<T>* result = nullptr;

	if(a->data <= b->data){
		result = a;
		result->next = sortedMerge(a->next, b);
	}
	else{
		result = b;
		result->next = sortedMerge(a, b->next);
	}
	return result;
}

template <typename T>
void LinkedList<T>::reverse(){
	Node<T>* temp = List<T>::head;
	while(temp != nullptr){
		Node<T>* tempPrev = temp->next;
		temp->next = temp->prev;
		temp->prev = tempPrev;
		temp = temp->prev;
	}
	temp = List<T>::head;
	List<T>::head = List<T>::tail;
	List<T>::tail = temp;
}

template <typename T>
void LinkedList<T>::merge(LinkedList<T> list){
	while(!list.empty()){
		push_back(list.front());
		list.pop_front();
	}
}

#endif
