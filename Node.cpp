#ifndef NODE_CPP
#define NODE_CPP

#include "Node.h"

template<class T>
Node<T>::Node(T data)
{
    this->data = data;
    this->next = NULL; // Initialize 'next' to NULL as it's the end of the list.
}

template<class T>
T Node<T>::getData() const
{
    return data;
}

template<class T>
bool Node<T>::operator==(T other) const
{
    return this->data == other;
}


#endif /*NODE_CPP*/