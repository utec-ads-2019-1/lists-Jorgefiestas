#ifndef FORWARD_ITERATOR_H
#define FORWARD_ITERATOR_H

#include "../iterator.h"

template <typename T> 
class ForwardIterator : public Iterator<T> {
    public:
        ForwardIterator() : Iterator<T>() {};
        ForwardIterator(Node<T> *current) : Iterator<T>(current) {};

        ForwardIterator<T> operator=(ForwardIterator<T> other) {
			Iterator<T>::current = other.current;
			return *this;
        }

        bool operator!=(ForwardIterator<T> other) {
			return Iterator<T>::current != other.current;
        }

        ForwardIterator<T> operator++() {
			Iterator<T>::current = Iterator<T>::current->next;
			return Iterator<T>::current;
        }

        T operator*() {
			return Iterator<T>::current->data;
        }
};

#endif
