#ifndef LIST_CPP
#define LIST_CPP

#include "List.h"

template<class T>
List<T>::List()
{
    head = NULL;
}

template<class T>
List<T>::~List()
{
    // The destructor is empty
}

template<class T>
int List<T>::size() const
{
    int count = 0;
    Node<T>* current = head;
    
    while (current != NULL) {
        count++;
        current = current->next;
    }

    return count;
}

template<class T>
bool List<T>::contains(T data) const
{
    Node<T>* current = head;
    
    while (current != NULL) {
        if (current->getData() == data)
        {
            return true; // Found the data in the list
        }
        current = current->next;
    }

    return false; // Data not found in the list
}

#endif /*LIST_CPP*/