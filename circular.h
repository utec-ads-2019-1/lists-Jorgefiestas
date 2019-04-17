#ifndef CIRCULAR_H
#define CIRCULAR_H

#include "list.h"

template <typename T>
class CircularLinkedList : public List<T> {
    public:
        CircularLinkedList() : List<T>() {}
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
            return "Circular Linked List";
        }

        BidirectionalIterator<T> begin() {
            return BidirectionalIterator<T>(List<T>::head);
        }

	    BidirectionalIterator<T> end() {
			return BidirectionalIterator<T>(List<T>::head);
        }

        void merge(CircularLinkedList<T>);

		~CircularLinkedList(){
			clear();
		}
};

 template <typename T>
 T CircularLinkedList<T>::front(){
     if(List<T>::head == nullptr) throw(out_of_range("Segmentation Fault"));
     return List<T>::head->data;
 }
 
 template <typename T>
 T CircularLinkedList<T>::back(){
     if(List<T>::tail == nullptr) throw(out_of_range("Segmentation Fault"));
     return List<T>::tail->data;
 }

template <typename T>
void CircularLinkedList<T>::push_front(T value){
	List<T>::nodes++;
	List<T>::head = new Node<T>(value, List<T>::head, List<T>::tail);
	if(List<T>::head->next == nullptr){
		List<T>::head->next = List<T>::head;
		List<T>::head->prev = List<T>::head;
		List<T>::tail = List<T>::head;
		return;
	}
	List<T>::head->next->prev = List<T>::head;
	List<T>::tail->next = List<T>::head;
}

template <typename T>
void CircularLinkedList<T>::push_back(T value){
	List<T>::nodes++;
	List<T>::tail = new Node<T>(value, List<T>::head, List<T>::tail);
	if(List<T>::tail->next == nullptr){
		List<T>::tail->next = List<T>::tail;
		List<T>::tail->prev = List<T>::tail;
		List<T>::head = List<T>::tail;
		return;
	}
	List<T>::tail->prev->next = List<T>::tail;
	List<T>::head->prev = List<T>::tail;
}

template <typename T>
void CircularLinkedList<T>::pop_front(){
	if(List<T>::head == nullptr) throw(out_of_range("Segmentation fault!"));
	List<T>::nodes--;
	if(List<T>::head->next == List<T>::head){
		List<T>::head->killSelf();
		List<T>::head = nullptr;
		List<T>::tail = nullptr;
		return;
	}
	List<T>::head = List<T>::head->next;
	List<T>::head->prev->killSelf();
	List<T>::tail->next = List<T>::head;
	List<T>::head->prev = List<T>::tail;
}

template <typename T>
void CircularLinkedList<T>::pop_back(){
	if(List<T>::head == nullptr) throw(out_of_range("Segmentation fault!"));
	List<T>::nodes--;
	if(List<T>::head->next == List<T>::head){
		List<T>::head->killSelf();
		List<T>::head = nullptr;
		List<T>::tail = nullptr;
		return;
	}
	List<T>::tail = List<T>::tail->prev;
	List<T>::head->prev->killSelf();
	List<T>::tail->next = List<T>::head;
	List<T>::head->prev = List<T>::tail;
}

template <typename T>
T CircularLinkedList<T>::operator [](int idx){
	if(List<T>::head == nullptr) throw(out_of_range("Segmentation fault!"));
	idx = idx%List<T>::nodes;
	Node<T>* temp = List<T>::head;
	while(idx--)
		temp = temp->next;
	return temp->data;
}

template <typename T>
bool CircularLinkedList<T>::empty(){
	return List<T>::nodes == 0;
}

template <typename T>
int CircularLinkedList<T>::size(){
	return List<T>::nodes;
}

template <typename T>
void CircularLinkedList<T>::clear(){
	while(List<T>::head != nullptr){
		pop_front();
	}
}

template <typename T>
void CircularLinkedList<T>::sort(){
	if(List<T>::head == nullptr) return;
	List<T>::head->prev = nullptr;
	List<T>::tail->next = nullptr;

    mergeSort(List<T>::head);
    Node<T>* temp = List<T>::head;

    while(temp->next != nullptr){
        temp->next->prev = temp;
        temp = temp->next;
    }
	
	List<T>::tail = temp;
	List<T>::head->prev = List<T>::tail;
	List<T>::tail->next = List<T>::head;
}

template <typename T>
void CircularLinkedList<T>::mergeSort(Node<T>* &root){
    if(root == nullptr || root->next == nullptr) return;

    Node<T>* half = mergeSortSplit(root);
    mergeSort(root);
    mergeSort(half);
    root = sortedMerge(root, half);
}

template <typename T>
Node<T>* CircularLinkedList<T>::mergeSortSplit(Node<T>* root){
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
Node<T>* CircularLinkedList<T>::sortedMerge(Node<T>* a, Node<T>* b){
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
void CircularLinkedList<T>::reverse(){
	List<T>::head->prev = nullptr;
	List<T>::tail->next = nullptr;
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
	List<T>::head->prev = List<T>::tail;
	List<T>::tail->next = List<T>::head;
}
	
template <typename T>
void CircularLinkedList<T>::merge(CircularLinkedList<T> list){
	while(!list.empty()){
		push_back(list.front());
		list.pop_front();
	}
}

#endif
