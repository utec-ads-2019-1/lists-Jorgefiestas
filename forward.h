#ifndef FORWARD_H
#define FORWARD_H

#include "list.h"
#include "iterators/forward_iterator.h"

template <typename T>
class ForwardList : public List<T> {
    public:
        ForwardList() : List<T>() {}
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
		void reverse_rec(Node<T>*);

        string name() {
            return "Forward List";
        }

        ForwardIterator<T> begin() {
			return ForwardIterator<T>(List<T>::head);
        }

	    ForwardIterator<T> end() {
			return nullptr;
        }

        void merge(ForwardList<T>);

		~ForwardList(){
			clear();
		}
};

template <typename T>
T ForwardList<T>::front(){
	if(List<T>::head == nullptr) throw out_of_range("Segmentation Fault");
	return List<T>::head->data;
}

template <typename T>
T ForwardList<T>::back(){
	if(List<T>::tail == nullptr) throw out_of_range("Segmentation Fault");
	return List<T>::tail->data;
}

template <typename T>
void ForwardList<T>::push_front(T value){
	List<T>::nodes++;
	List<T>::head = new Node<T>(value, List<T>::head);
	if(List<T>::head->next == nullptr)
		List<T>::tail = List<T>::head;
}

template <typename T>
void ForwardList<T>::push_back(T value){
	if(List<T>::head == nullptr)
		return push_front(value);
	List<T>::nodes++;
	List<T>::tail->next = new Node<T>(value);
	List<T>::tail = List<T>::tail->next;
}

template <typename T>
void ForwardList<T>::pop_front(){
	if(List<T>::head == nullptr) throw out_of_range("Segmentation Fault");
	List<T>::nodes--;
	if(List<T>::head->next == nullptr){
		List<T>::head->killSelf();
		List<T>::head = nullptr;
		List<T>::tail = nullptr;
		return;
	}
	Node<T>* temp = List<T>::head;
	List<T>::head = List<T>::head->next;
	temp->killSelf();
}

template <typename T>
void ForwardList<T>::pop_back(){
	if(List<T>::head == nullptr) throw out_of_range("Segmentation Fault");
	List<T>::nodes--;
	if(List<T>::head->next == nullptr){
		List<T>::head->killSelf();
		List<T>::head = nullptr;
		List<T>::tail = nullptr;
		return;
	}
	Node<T>* temp = List<T>::head;
	while(temp->next->next != nullptr)
		temp = temp->next;
	temp->next->killSelf();
	temp->next = nullptr;
	List<T>::tail = temp;
}

template <typename T>
T ForwardList<T>::operator[](int idx){
	Node<T>* temp = List<T>::head;
	while(idx--){
		if(temp == nullptr) throw out_of_range("Segmentation Fault");
		temp = temp->next;
	}
	return temp->data;
}

template <typename T>
bool ForwardList<T>::empty(){
	return List<T>::nodes == 0;
}

template <typename T>
int ForwardList<T>::size(){
	return List<T>::nodes;
}

template <typename T>
void ForwardList<T>::clear(){
	while(List<T>::head != nullptr){
		Node<T>* temp = List<T>::head->next;
		List<T>::head->killSelf();
		List<T>::head = temp;
	}
	List<T>::nodes = 0;
}

template <typename T>
void ForwardList<T>::sort(){
	mergeSort(List<T>::head);
}

template <typename T>
void ForwardList<T>::mergeSort(Node<T>* &root){
	if(root == nullptr) return;
	if(root->next == nullptr) return;

	Node<T>* half = mergeSortSplit(root);
	mergeSort(root);
	mergeSort(half);
	root = sortedMerge(root, half);
}
	
template <typename T>
Node<T>* ForwardList<T>::mergeSortSplit(Node<T>* root){
	Node<T> *slow = root, *fast = root->next;

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
Node<T>* ForwardList<T>::sortedMerge(Node<T>* a, Node<T>* b){
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
void ForwardList<T>::reverse(){
	if(List<T>::head == nullptr)
		return;
	if(List<T>::head->next == nullptr)
		return;
	reverse_rec(List<T>::head);
	List<T>::tail->next = nullptr;
}

template <typename T>
void ForwardList<T>::reverse_rec(Node<T>* node){
	if(node->next == nullptr){
		List<T>::head = node;
		return;
	}
	reverse_rec(node->next);
	List<T>::tail->next = node;
	List<T>::tail = node;
}

template <typename T>
void ForwardList<T>::merge(ForwardList<T> list){
	while(!list.empty()){
		push_back(list.front());
		list.pop_front();
	}
}

#endif
