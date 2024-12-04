#include "List.h"
#include "Node.h"
#include "SinglyLinked.h"

#include <iostream>
#include <string>

using namespace std;

template <class T>
void testNodeClass()
{
    std::cout << "Testing Node class:" << std::endl;
    
    // Create some nodes
    Node<T>* node1 = new Node<T>(1);
    Node<T>* node2 = new Node<T>(2);
    Node<T>* node3 = new Node<T>(3);

    // Print the nodes
    std::cout << "Node 1: " << node1 << std::endl;
    std::cout << "Node 2: " << node2 << std::endl;
    std::cout << "Node 3: " << node3 << std::endl;

    // Test the getData function
    std::cout << "Node 1 data: " << node1->getData() << std::endl;

    // Test the equality operator
    std::cout << "Node 2 == 2: " << (*node2 == 2) << std::endl;

    // Clean up
    delete node1;
    delete node2;
    delete node3;
}

template <class T>
void testSinglyListClass()
{
    std::cout << "Testing SinglyList class:" << std::endl;

    // Create a list and populate it
    SinglyList<T> list;
    list.insert(1, -1); // Append
    list.insert(2, -1);
    list.insert(3, -1);

    // Print the list
    std::cout << "Original List: " << &list << std::endl;

    // Test findSmallest and findBiggest functions
    Node<T>* smallest = list.findSmallest();
    Node<T>* biggest = list.findBiggest();
    std::cout << "Smallest Node: " << smallest << std::endl;
    std::cout << "Biggest Node: " << biggest << std::endl;

    // Test the clone function
    //SinglyList<T>* clonedList = list.clone();
    //std::cout << "Cloned List: " << clonedList << std::endl;

    // Clean up
    //delete clonedList;
}

template<class T>
void testSinglyListOperators(const SinglyList<T>& list) {
    // Test the operator[] function
    std::cout << "Testing operator[]:" << std::endl;

    // Test positive indices
    std::cout << "Test positive indices : " << std::endl;
    for (int i = 0; i < list.size(); i++) {
        Node<T>* node = list[i];
        if (node) {
            std::cout << "Index " << i << ": " << node->getData() << std::endl;
        } else {
            std::cout << "Index " << i << ": Out of bounds" << std::endl;
        }
    }

    std::cout << "Test negative indices : " << std::endl;
    // Test negative indices
    for (int i = -1; i >= -list.size(); i--) {
        Node<T>* node = list[i];
        if (node) {
            std::cout << "Index " << i << ": " << node->getData() << std::endl;
        } else {
            std::cout << "Index " << i << ": Out of bounds" << std::endl;
        }
    }

    std::cout << "Test out of bounds indices : " << std::endl;
    // Test out-of-bounds indices
    int invalidIndex = list.size();
    Node<T>* invalidNode = list[invalidIndex];
    if (!invalidNode) {
        std::cout << "Index " << invalidIndex << ": Out of bounds" << std::endl;
    }

    // Test the operator() function
    std::cout << "Testing operator():" << std::endl;

    // Define a value to search for in the list
    T valueToFind;

    // Search for a value that is present in the list
    Node<T>* foundNode = list(&valueToFind);
    if (foundNode) {
        std::cout << "Found value " << valueToFind << " in the list." << std::endl;
    } else {
        std::cout << "Value " << valueToFind << " not found in the list." << std::endl;
    }

    // Search for a value that is not present in the list
    T valueNotInList;
    foundNode = list(&valueNotInList);
    if (!foundNode) {
        std::cout << "Value " << valueNotInList << " not found in the list." << std::endl;
    } else {
        std::cout << "Found value " << valueNotInList << " in the list." << std::endl;
    }
}



int main(int argc, char const *argv[])
{
    testNodeClass<int>();
    testSinglyListClass<int>();

    int data[] = {1, 2, 3, 4, 5};
    SinglyList<int> myList(data, 5);
    testSinglyListOperators(myList);

    return 0;
}