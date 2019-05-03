#ifndef BIDIRECTIONAL_ITERATOR_H
#define BIDIRECTIONAL_ITERATOR_H

#include "../iterator.h"

template <typename T> 
class BidirectionalIterator : public Iterator<T> {
	private:
		Node<T>* last;
    public:
        BidirectionalIterator() : Iterator<T>() {};
        BidirectionalIterator(Node<T> *node) : Iterator<T>(node) {};
        BidirectionalIterator(Node<T> *node, Node<T>*last) : Iterator<T>(node) {
			this->last = last;
		};

        BidirectionalIterator<T> operator=(BidirectionalIterator<T> other) {
            Iterator<T>::current = other.current;
			return *this;
        }

        bool operator!=(BidirectionalIterator<T> other) {
			return Iterator<T>::current != other.current;
        }

        BidirectionalIterator<T> operator++() {
            Iterator<T>::current = Iterator<T>::current->next;
			return *this;
        }

        BidirectionalIterator<T> operator--() {
			if(Iterator<T>::current == nullptr) Iterator<T>::current = last;
			else Iterator<T>::current = Iterator<T>::current->prev;
			return *this;
        }

        T operator*() {
            // Si la lista está vacía?
			return Iterator<T>::current->data;
        }
};

#endif
