#include <iostream>
#include <string>
#include <list>
using namespace std;


template <typename type>
struct node
{
    type element;
    node<type> *next;
    node(type element) : element(element) {}
};
// Circular Linked List
template <typename type>
class circularSLL
{
private:
    int length;
    node<type> *head, *tail;

public:

    circularSLL()
    {
        clear();
    }
    int linkedListSize();
    bool isEmpty();
    void clear();
    void insertAtHead(type ele);
    void insertAtTail(type ele);
    void insertInMiddle(type ele, int index);
    void removeHead();
    void removeTail();
    void removeAt(int index);
    type retrieveAt(int index);
    void replaceAt(type ele, int index);
    bool isExit(type ele);
    bool isItemAtEqual(type ele, int index);
    void print();
};
template <typename type>
int circularSLL<type>::linkedListSize()
{
    return length;
}
template <typename type>
bool circularSLL<type>::isEmpty()
{
    return (length == 0);
}
template <typename type>
void circularSLL<type>::clear()
{
    tail = head = nullptr;
    length = 0;
}
template <typename type>
void circularSLL<type>::insertAtHead(type ele)
{
    node<type> *newNode = new node<type>(ele);
    if (head == nullptr)
    {
        head = tail = newNode;
        // tail = newNode;
        newNode->next = head;
    }
    else
    {
        newNode->next = head;
        head = newNode;
        tail->next = head;
    }
    length++;
}
template <typename type>
void circularSLL<type>::insertAtTail(type ele)
{
    node<type> *newNode = new node<type>(ele);
    if (head == nullptr)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        newNode->next = head;
        tail = newNode;
    }
    length++;
}
template <typename type>
void circularSLL<type>::insertInMiddle(type ele, int index)
{
    if (index > length || index < 0)
    {
        throw std::out_of_range("\n\t\t\tOut of bounds\n");
    }
    else
    {
        node<type> *newNode = new node<type>(ele);
        if (index == 0)
        {
            insertAtHead(ele);
        }
        else if (index == length)
        {
            insertAtTail(ele);
        }
        else
        {
            node<type> *ptr = head;
            for (int i = 1; i < index; i++)
            {
                ptr = ptr->next;
            }
            newNode->next = ptr->next;
            ptr->next = newNode;
            length++;
        }
    }
}
template <typename type>
void circularSLL<type>::removeHead()
{
    if (length == 0)
    {
        throw std::out_of_range("\n\t\t\t*** Empty linked list ***\n");
    }
    else if (length == 1)
    {
        delete head;
        head = tail = NULL;
    }
    else
    {
        node<type> *ptr = head;
        head = ptr->next;
        tail->next = head;
        delete ptr;
    }
    length--;
}
template <typename type>
void circularSLL<type>::removeTail()
{
    if (length == 0)
    {
        throw std::out_of_range("\n\t\t\t*** Empty linked list ***\n");
    }
    else if (length == 1)
    {
        delete head;
        head = tail = NULL;
    }
    else
    {
        node<type> *cur = head->next;
        node<type> *pre = head;
        int counter = length;
        while (counter > 1)
        {
            pre = cur;
            cur = cur->next;
            counter--;
        }
        delete cur;
        pre->next = head;
        tail = pre;
        delete pre;
    }
    length--;
}
template <typename type>
void circularSLL<type>::removeAt(int index)
{
    if (length == 0)
    {
        throw std::out_of_range("\n\t\t\t*** Empty linked list ***\n");
    }
    if (index >= length)
    {
        throw std::out_of_range("\n\t\t\t*** Out Of bounds ***\n");
    }
    if (index == 0)
    {
        removeHead();
        return;
    }
    else if (index == length - 1)
    {
        removeTail();
        return;
    }
    else
    {
        node<type> *cur = head->next;
        node<type> *pre = head;
        for (int i = 1; i < index; i++)
        {
            pre = cur;
            cur = cur->next;
        }
        if (cur == tail)
        {
            tail = cur;
            tail->next = head;
        }
        else
            pre->next = cur->next;
        // cout << tail->next->element << " " << head->element << endl;
    }
    length--;
}
template <typename type>
type circularSLL<type>::retrieveAt(int index)
{
    // zero based
    type e;
    if (length <= index)
    {
        throw std::out_of_range("\n\t\t\t*** Out of bound ***\n");
    }
    node<type> *ptr = head;
    int counter = 0;
    int count = length;
    while (count)
    {
        if (counter == index)
        {
            e = ptr->element;
            break;
        }
        counter++;
        count--;
        ptr = ptr->next;
    }
    return e;
}
template <typename type>
void circularSLL<type>::replaceAt(type ele, int index)
{
    // zero based
    if (length <= index)
    {
        throw std::out_of_range("\n\t\t\t*** Out of bound ***\n");
    }
    node<type> *ptr = head;
    int counter = 0;
    int count = length;
    while (count)
    {
        if (counter == index)
        {
            ptr->element = ele;
            break;
        }
        counter++;
        count--;
        ptr = ptr->next;
    }
}
template <typename type>
bool circularSLL<type>::isExit(type ele)
{
    // zero based
    node<type> *ptr = head;
    int counter = length;
    while (counter)
    {
        if (ptr->element == ele)
        {
            return true;
        }
        counter--;
        ptr = ptr->next;
    }
    return false;
}
template <typename type>
bool circularSLL<type>::isItemAtEqual(type ele, int index)
{
    if (index >= length)
    {
        throw std::out_of_range("\n\t\t\t*** Out of bound ***\n");
    }
    node<type> *ptr = head;
    int counter = 0, size = length;
    while (size)
    {
        if (counter == index)
        {
            if (ptr->element == ele)
                return true;
        }
        counter++;
        size--;
        ptr = ptr->next;
    }
    return false;
}
template <typename type>
void circularSLL<type>::print()
{
    node<type> *ptr = head;
    int counter = length;
    while (counter)
    {
        if (counter == 1)
        {
            cout << ptr->element << endl;
            ;
            break;
        }
        cout << ptr->element << "->";
        ptr = ptr->next;
        counter--;
    }
}

int main(){
    circularSLL<int>s;
    // sLL s;
    s.insertAtHead(3);
    s.print();
    system("pause");
    s.insertAtHead(4);
    s.print();
    system("pause");
    s.insertAtTail(67);
    s.print();
    system("pause");
    s.insertInMiddle(56776, 2);
    s.print();
    system("pause");
    s.removeTail();
    s.print();
    // system("pause");
    // system("pause");
    // s.insertInMiddle(34, 3);
    // s.print();
    // system("pause");
    // s.insertAtTail(456);
    // s.print();
    system("pause");
    s.removeAt(1);
    s.print();
   
    s.insertAtHead(758);
    s.print();
    system("pause");
    cout << "retrive : " << s.retrieveAt(1) << endl;
    // cout << "retrive : " << s.retrieveAt(10) << endl;

    s.insertAtHead(23);
    s.insertAtHead(1);
    s.insertAtHead(4578);

    s.print();
    system("pause");

    s.replaceAt(90000000, 1);
    system("pause");
    s.print();

    // cout << "is exit : " << s.isExit(67) << endl;
    // cout << "is exit : " << s.isExit(125) << endl;

    // system("pause");

    // cout << "is ele are equal : " << s.isItemAtEqual(90000000, 0) << endl;
    // cout << "is ele are equal : " << s.isItemAtEqual(56776, 56) << endl;




}