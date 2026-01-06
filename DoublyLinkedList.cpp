#include <iostream>
#include <string>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <math.h>
#include <set>
#include <vector>
#include <map>
#include <stack>
#include <sstream>
#include <queue>
#include <iomanip>
#include <windows.h>
#include <cstdio>
#include <list>
#include <fstream>
using namespace std;

template <typename type>
struct D_node
{
    type element;
    D_node<type> *next;
    D_node<type> *prev;
    D_node(type element) : element(element) {}
};

// Double Linked List
template <typename type>
class DLL
{
private:
    int size;
    D_node<type> *head, *tail;

public:
    DLL()
    {
        clear();
    }
    void insertAtHead(type ele);
    void insertAtTail(type ele);
    void insertAt(type ele, int index);
    void insertAfter(D_node<type> *prev_node, int data);
    int doubleLinkedListSize();
    void removeAtHead();
    void removeAtTail();
    bool isEmpty();
    void clear();
    void removeAt(int index);
    type retrieveAt(int index);
    void replaceAt(type ele, int index);
    bool isExist(type ele);
    bool isItemAtEqual(type ele, int index);
    void reverse();
    void forwardTraversal();
    void backwardTraversal();
    void swap(int firstItemIdx, int secondItemIdx);
};
template <typename type>
void DLL<type>::insertAfter(D_node<type> *prev_node, int data)
{
    if (prev_node == nullptr)
    {
        throw std::invalid_argument("Previous node can't be null");
    }
    D_node<type> *new_node = new D_node<type>(data);
    new_node->next = prev_node->next;
    if (prev_node->next != nullptr) // the nullptr doesn't have a previous ptr
        prev_node->next->prev = new_node;
    prev_node->next = new_node;
    new_node->prev = prev_node;
    size++;
}

template <typename type>
int DLL<type>::doubleLinkedListSize()
{
    return size;
}
template <typename type>
bool DLL<type>::isEmpty()
{
    return (size == 0);
}
template <typename type>
void DLL<type>::clear()
{
    tail = head = nullptr;
    size = 0;
}
template <typename type>
void DLL<type>::insertAtHead(type ele)
{
    D_node<type> *newNode = new D_node<type>(ele);
    if (head == nullptr)
    {
        head = tail = newNode;
        head->prev = NULL;
        tail->next = NULL;
    }
    else
    {
        newNode->next = head;
        newNode->prev = NULL;
        head->prev = newNode;
        head = newNode;
    }
    // cout << "done" << endl;
    size++;
}
template <typename type>
void DLL<type>::insertAtTail(type ele)
{
    D_node<type> *newNode = new D_node<type>(ele);
    if (head == nullptr)
    {
        newNode->next = newNode->prev = NULL;
        head = tail = newNode;
    }
    else
    {
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = NULL;
        tail = newNode;
    }

    size++;
}
template <typename type>
void DLL<type>::insertAt(type ele, int index)
{
    if (index > size)
    {
        throw std::out_of_range("\n\t\t\t*** Out Of bounds ***\n");
    }
    else if (index == 0)
    {
        insertAtHead(ele);
        return;
    }
    else if (index == size)
    {
        insertAtTail(ele);
        return;
    }
    else
    {
        D_node<type> *ptr = head;
        for (int i = 1; i < index; i++)
        {
            ptr = ptr->next;
        }
        insertAfter(ptr, ele);
    }
    size++;
}
template <typename type>
void DLL<type>::removeAtHead()
{
    if (head == NULL)
    {
        throw std::out_of_range("\n\t\t\t*** This list is empty ***\n");
    }
    else if (size == 0)
    {
        delete head;
        head = tail = NULL;
    }
    else
    {
        head = head->next;
        head->prev = NULL;
    }
    size--;
}
template <typename type>
void DLL<type>::removeAtTail()
{
    if (head == NULL)
    {
        throw std::out_of_range("\n\t\t\t*** This list is empty ***\n");
    }
    else if (size == 0)
    {
        delete head;
        head = tail = NULL;
    }
    else
    {
        tail = tail->prev;
        tail->next = NULL;
    }
    size--;
}
template <typename type>
void DLL<type>::removeAt(int index)
{
    if (index >= size)
    {
        throw std::out_of_range("\n\t\t\t*** out of bounds ***\n");
    }
    else if (index == 0)
    {
        removeAtHead();
    }
    else if (index == size - 1)
    {
        removeAtTail();
    }
    else
    {
        D_node<type> *ptr = head;
        for (int i = 0; i < index; i++)
        {
            ptr = ptr->next;
        }
        ptr->prev->next = ptr->next;
        ptr->next->prev = ptr->prev;
        delete ptr;
    }
    size--;
}
template <typename type>
type DLL<type>::retrieveAt(int index)
{
    // zero based
    if (size <= index)
    {
        throw std::out_of_range("\n\t\t\t*** Out Of bounds ***\n");
    }
    D_node<type> *ptr = head;
    int counter = 0;
    while (ptr->next != nullptr)
    {
        if (counter == index)
        {
            break;
        }
        counter++;
        ptr = ptr->next;
    }
    return ptr->element;
}

template <typename type>
void DLL<type>::replaceAt(type ele, int index)
{
    // zero based
    if (size <= index)
    {
        throw std::out_of_range("\n\t\t\t*** out of bounds ***\n");
    }
    D_node<type> *ptr = head;
    int counter = 0;
    while (ptr->next != NULL)
    {
        if (counter == index)
        {
            break;
        }
        counter++;
        ptr = ptr->next;
    }
    ptr->element = ele;
}
template <typename type>
bool DLL<type>::isExist(type ele)
{
    // zero based
    D_node<type> *ptr = head;
    while (ptr != nullptr)
    {
        if (ptr->element == ele)
        {
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}
template <typename type>
bool DLL<type>::isItemAtEqual(type ele, int index)
{
    // zero based
    if (size <= index)
    {
        throw std::out_of_range("\n\t\t\t*** Out Of bounds ***\n");
    }

    D_node<type> *ptr = head;
    int counter = 0;
    while (ptr != nullptr)
    {
        if (counter == index)
        {
            if (ptr->element == ele)
                return true;
        }
        counter++;
        ptr = ptr->next;
    }
    return false;
}

template <typename type>
void DLL<type>::reverse()
{
    D_node<type> *current = head;
    while (current != nullptr)
    {
        swap(current->next, current->prev);
        current = current->prev;
    }
    swap(head, tail);
}
template <typename type>
void DLL<type>::forwardTraversal()
{
    D_node<type> *ptr = head;
    while (ptr->next != NULL)
    {
        cout << ptr->element << "->";
        ptr = ptr->next;
    }
    cout << tail->element << endl;
}
template <typename type>
void DLL<type>::backwardTraversal()
{
    D_node<type> *ptr = tail;
    while (ptr->prev != NULL)
    {
        cout << ptr->element << "->";
        ptr = ptr->prev;
    }
    cout << head->element << endl;
}
template <typename type>
void DLL<type>::swap(int firstItemIdx, int secondItemIdx)
{
    
    if (firstItemIdx < 0 || secondItemIdx < 0 || firstItemIdx >= size || secondItemIdx >= size)
        throw std::out_of_range("\n\t\t\t*** Out Of bounds ***\n");
    if (firstItemIdx == secondItemIdx)
    {
        throw std::invalid_argument("Can't swap the same node with itself");
    }

    if (firstItemIdx > secondItemIdx)
    {
        std::swap(firstItemIdx, secondItemIdx);
    }

    D_node<type> *firstNode = head;
    for (int i = 0; i < firstItemIdx; i++)
    {
        firstNode = firstNode->next;
    }

    D_node<type> *secondNode = head;
    for (int i = 0; i < secondItemIdx; i++)
    {
        secondNode = secondNode->next;
    }

    if (abs(firstItemIdx - secondItemIdx) != 1)
    {

        // Update prev pointers of adjacent nodes
        if (firstNode->prev != nullptr)
            firstNode->prev->next = secondNode;

        if (secondNode->prev != nullptr)
            secondNode->prev->next = firstNode;

        // Update prev pointers of adjacent nodes
        if (firstNode->next != nullptr)
            firstNode->next->prev = secondNode;

        if (secondNode->next != nullptr)
            secondNode->next->prev = firstNode;

        // Swap previous and next pointers
        std::swap(firstNode->prev, secondNode->prev);
        std::swap(firstNode->next, secondNode->next);
    }
    else
    {
        // Update prev pointers of adjacent nodes
        if (firstNode->prev != nullptr)
            firstNode->prev->next = secondNode;

        if (secondNode->next != nullptr)
            secondNode->next->prev = firstNode;

        firstNode->next = secondNode->next;
        secondNode->next = firstNode;
        

        secondNode->prev = firstNode->prev;
        firstNode->prev = secondNode;
    }

    // if it's the head pointer
    if (firstNode == head)
        head = secondNode; // now head is the second node

    else if (secondNode == head) // using else if here to prevent the previous condition
                                 // as the previous condition make this condition always true
        head = firstNode;

    // if it's the tail pointer
    if (tail == firstNode)
        tail = secondNode; // now tail is the second node

    else if (tail == secondNode) // using else if here to prevent the previous condition
                                 // as the previous condition make this condition always true
        tail = firstNode;
}

int main(){

    DLL<int> d;
    d.insertAtTail(23);
    d.insertAtTail(3);
    d.insertAtTail(34545);
    d.insertAtTail(121);
    d.insertAtTail(89);
    // system("pause");
    // d.forwardTraversal();
    // system("pause");
    // d.backwardTraversal();
    // // d.forwardTraversal();
    // // system("pause");
    // d.insertAtHead(2);
    // // // d.forwardTraversal
    // // // system("pause");
    // d.insertAtTail(234);
    // // // d.forwardTraversal();
    // // // system("pause");
    // d.forwardTraversal();
    // system("pause");

    // // // d.removeTail();
    // d.backwardTraversal();
    // // d.insertAt(567, 2);
    // // // d.forwardTraversal();

   d.insertAt(567, 2);

  
    // system("pause");
    // d.removeHead();
    // d.forwardTraversal();
    // system("pause");
    // d.backwardTraversal();


   d.insertAt(5667, 4);

  
    // system("pause");
    // d.removeHead();
    // d.forwardTraversal();
    // system("pause");
    // d.backwardTraversal();

    system("pause");
    cout << "reverse : " << endl;
    d.forwardTraversal();
    d.reverse();
    system("pause");
    d.forwardTraversal();
    // system("pause");
    d.backwardTraversal();


    // system("pause");
    // // cout << "retrive : " << d.retrieveAt(2) << endl;
    // d.forwardTraversal();

    // // system("pause");
    // // cout << "replace : " << endl;
    // //  d.replaceAt(10192, 3);
    // // d.forwardTraversal();


    // // system("pause");
    // // cout << "is exit : " << d.isExit(56) << endl;;


    // // system("pause");
    // // cout << "is exit : " << d.isExit(10192) << endl;;
    
    // // system("pause");
    // // cout << "is exit : " << d.isItemAtEqual(10192, 4) << endl;;
    
    // // system("pause");
    // // cout << "is exit : " << d.isItemAtEqual(10192, 4) << endl;;
}