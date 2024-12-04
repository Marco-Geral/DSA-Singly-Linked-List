#ifndef SINGLY_SinglyList_CPP
#define SINGLY_SinglyList_CPP

#include "SinglyLinked.h"

template <class T>
std::ostream &operator<<(std::ostream &os, const SinglyList<T> *sl)
{
    if (sl->head == NULL)
    {
        os << "NULL";
        return os;
    }
    Node<T> *curr = sl->head;
    while (curr != NULL)
    {
        os << curr;
        curr = curr->next;
    }
    return os;
}

template<class T>
SinglyList<T>::SinglyList()
{

}

template<class T>
SinglyList<T>::SinglyList(T* arr, int size)
{
    if (arr == NULL || size <= 0)
    {
        // Handle invalid input by ensuring the list remains empty
        List<T>::head = NULL;
        return;
    }

    // Create the first node with the data from the array
    List<T>::head = new Node<T>(arr[0]);
    Node<T>* current = List<T>::head;

    for (int i = 1; i < size; i++)
    {
        // Create a new node for each element in the array and link it to the previous node
        current->next = new Node<T>(arr[i]);
        current = current->next;
    }
}

template<class T>
SinglyList<T>::~SinglyList()
{
    Node<T>* current = List<T>::head;
    while (current != NULL) {
        Node<T>* next = current->next;
        delete current;
        current = next;
    }
    List<T>::head = NULL; // Set head to NULL to indicate an empty list
}

template<class T>
Node<T>* SinglyList<T>::insert(T data, int pos)
{
    // Create a new node with the provided data
    Node<T>* newNode = new Node<T>(data);

    if (pos <= 0)
    {
        // Prepend the node to the list
        newNode->next = List<T>::head;
        List<T>::head = newNode;
    }
    else
    {
        // Insert the node at the specified position
        Node<T>* current = List<T>::head;
        int currentIndex = 0;

        while (current != NULL && currentIndex < pos - 1)
        {
            current = current->next;
            currentIndex++;
        }

        if (current != NULL)
        {
            newNode->next = current->next;
            current->next = newNode;
        }
        else
        {
            // Append the node to the end of the list
            if (List<T>::head == NULL)
            {
                List<T>::head = newNode;
            }
            else
            {
                current = List<T>::head;
                while (current->next != NULL)
                {
                    current = current->next;
                }
                current->next = newNode;
            }
        }
    }

    return newNode;
}

template<class T>
int SinglyList<T>::remove(T data)
{
    Node<T>* current = List<T>::head;
    Node<T>* prev = NULL;
    int index = 0;

    while (current != NULL)
    {
        if (current->getData() == data)
        {
            if (prev == NULL)
            {
                // If data is found at the head, update the head
                List<T>::head = current->next;
            }
            else
            {
                prev->next = current->next;
            }

            // Deallocate memory for the removed node
            delete current;
            return index;
        }

        prev = current;
        current = current->next;
        index++;
    }

    // Data was not found in the list
    return -1;
}

template<class T>
Node<T>* SinglyList<T>::operator[](int index) const {
    if (index < 0)
    {
        // Handle negative index by counting from the rear
        int newIndex = this->size() + index;  // Map to a positive index
        if (newIndex < 0 || newIndex >= this->size())
        {
            return NULL;
        }
        else
        {
            int currentIndex = 0;
            Node<T>* current = List<T>::head;

            while (current != NULL)
            {
                if (currentIndex == newIndex)
                {
                    return current;
                }

                current = current->next;
                currentIndex++;
            }
        }
    }
    else 
    {
        // Handle positive index by counting from the front
        int currentIndex = 0;
        Node<T>* current = List<T>::head;

        while (current != NULL)
        {
            if (currentIndex == index)
            {
                return current;
            }

            current = current->next;
            currentIndex++;
        }
    }

    // Index is out of bounds
    return NULL;
}


template<class T>
Node<T>* SinglyList<T>::operator()(T* dataPtr) const
{
    Node<T>* current = List<T>::head;

    while (current != NULL) {
        // Compare the data using dereferenced dataPtr
        if (*dataPtr == current->getData()) {
            return current; // Found a node with the specified data
        }

        current = current->next;
    }

    // Data was not found in the list
    return NULL;
}

template<class T>
int SinglyList<T>::getIndexFromFront(T data) const
{
    Node<T>* current = List<T>::head;
    int index = 0;

    while (current != NULL) {
        if (current->getData() == data) {
            return index; // Found a node with the specified data, return its index
        }

        current = current->next;
        index++;
    }

    // Data was not found in the list
    return -1;
}

template<class T>
int SinglyList<T>::getIndexFromRear(T data) const
{
    Node<T>* current = List<T>::head;
    int index = -1; // Initialize to -1 for the last element

    int currentIndex = 0;
    int targetIndex = -1;

    while (current != NULL) {
        if (current->getData() == data) {
            targetIndex = currentIndex;
        }

        current = current->next;
        currentIndex++;
    }

    if (targetIndex != -1) {
        return currentIndex - targetIndex - 1;
    } else {
        // Data was not found in the list
        return -1;
    }
}

template<class T>
List<T>* SinglyList<T>::sort(bool order) const
{
    SinglyList<T>* sortedList = new SinglyList<T>();

    // Copy the elements from the original list to the new list
    Node<T>* current = List<T>::head;
    while (current != NULL) {
        if (sortedList->head == NULL) {
            // If the new list is empty, simply add the first node
            sortedList->head = new Node<T>(current->getData());
        } else {
            // Perform insertion sort to add the current node
            Node<T>* newCurrent = sortedList->head;
            Node<T>* previous = NULL;
            Node<T>* newNode = new Node<T>(current->getData());

            while (newCurrent != NULL)
            {
                bool shouldInsertBefore =
                    (order && newNode->getData() <= newCurrent->getData()) || (!order && newNode->getData() >= newCurrent->getData());

                if (shouldInsertBefore)
                {
                    // Insert the newNode before newCurrent
                    newNode->next = newCurrent;
                    if (previous != NULL)
                    {
                        previous->next = newNode;
                    }
                    else
                    {
                        // Update the head if newNode is inserted at the beginning
                        sortedList->head = newNode;
                    }
                    break;
                }
                previous = newCurrent;
                newCurrent = newCurrent->next;
            }
            if (newCurrent == NULL) {
                // If newNode should be the last node, insert it at the end
                previous->next = newNode;
            }
        }
        current = current->next;
    }

    return sortedList;
}

template<class T>
Node<T>* SinglyList<T>::findSmallest() const
{
    if (List<T>::head == NULL) {
        return NULL; // The list is empty, return null
    }

    Node<T>* smallestNode = List<T>::head;
    Node<T>* current = List<T>::head->next;

    while (current != NULL) {
        if (current->getData() < smallestNode->getData()) {
            // Found a smaller value, update smallestNode
            smallestNode = current;
        }
        current = current->next;
    }

    return smallestNode;
}

template<class T>
Node<T>* SinglyList<T>::findBiggest() const
{
    if (List<T>::head == NULL) {
        return NULL; // The list is empty, return null
    }

    Node<T>* biggestNode = List<T>::head;
    Node<T>* current = List<T>::head->next;

    while (current != NULL) {
        if (current->getData() > biggestNode->getData()) {
            // Found a bigger value, update biggestNode
            biggestNode = current;
        }
        current = current->next;
    }

    return biggestNode;
}

template<class T>
List<T>* SinglyList<T>::clone() const
{
    SinglyList<T>* clonedList = new SinglyList<T>();

    // Iterate through the original list and copy each element
    Node<T>* current = List<T>::head;
    while (current != NULL) {
        clonedList->insert(current->getData(), -1); // Append elements to the cloned list
        current = current->next;
    }

    return clonedList;
}


#endif /*SinglyList_CPP*/
