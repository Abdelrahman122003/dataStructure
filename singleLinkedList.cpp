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
    node() : next(NULL), element(0) {}
};
// **Single Linked List

template <typename type>
class SLL
{
private:
    int size;
    // Swap first node with Idx's node
    void swap(int Idx);
    void adjacentSwap(int firstIdx, int secondIdx);

public:
    node<type> *head, *tail;
    SLL()
    {
        clear();
    }
    SLL<type> &operator=(const SLL<type> anotherSLL);
    // SLL(const SLL<type> anotherSLL);
    void insertAtHead(type ele);
    void insertAtTail(type ele);
    void insertAt(type ele, int index);
    void removeAtHead();
    void removeAtTail();
    void removeAt(int index);
    type retrieveAt(int index);
    void replaceAt(type ele, int index);
    bool isExist(type ele);
    bool isItemAtEqual(type ele, int index);
    bool isEmpty();
    int linkedListSize();
    void clear();
    void print();
    void swap(int firstIdx, int secondIdx);
};

template <typename type>
void SLL<type>::swap(int firstIdx, int secondIdx)
{
    if (firstIdx < 0 || secondIdx < 0 || firstIdx >= size || secondIdx >= size)
    {
        throw std::out_of_range("\n\t\t\t*** Out Of bounds ***\n");
        return;
    }
    if (firstIdx == secondIdx)
    {
        throw std::invalid_argument("Can't swap the same node with itself");
        return;
    }

    // If the two nodes are adjacent
    if (abs(firstIdx - secondIdx) == 1)
    {
        adjacentSwap(firstIdx, secondIdx);
        return;
    }
    // Swapping secondIdx node with the head node (first node)
    if (firstIdx == 0)
    {
        swap(secondIdx);
        return;
    }
    // Swapping firstIdx node with the head node (first node)
    else if (secondIdx == 0)
    {
        swap(firstIdx);
        return;
    }

    // Pointer to the Back node of firstIdx node
    node<type> *cursorB1 = this->head;
    // Pointer to the firstIdx node
    node<type> *cursor1 = nullptr;
    // Pointer to the next(After) node of firstIdx node
    node<type> *cursorAf1 = nullptr;

    // Pointer to the Back node of secondIdx node
    node<type> *cursorB2 = this->head;
    // Pointer to the secondIdx node
    node<type> *cursor2 = nullptr;
    // Pointer to the next(After) node of secondIdx node
    node<type> *cursorAf2 = nullptr;

    /*
        Making cursorB1 pointing at "firstIdx - 1" node by incrementing it by (firstIdx - 1),
        'cause the cursorB1 poiting at the head in the intial state
    */
    for (int i = 0; i < firstIdx - 1; i++)
    {
        cursorB1 = cursorB1->next;
    }
    // Inialize the cursors
    cursor1 = cursorB1->next;
    cursorAf1 = cursor1->next;

    // Same as above
    for (int i = 0; i < secondIdx - 1; i++)
    {
        cursorB2 = cursorB2->next;
    }
    cursor2 = cursorB2->next;
    cursorAf2 = cursor2->next;

    /*
    Swapping nodes by change the Back(previous) and After(next) nodes
    of the firstIdx node with the Back(previous) and After(next) nodes of secondIdx node
    */
    cursorB1->next = cursor2;
    cursor2->next = cursorAf1;
    cursorB2->next = cursor1;
    cursor1->next = cursorAf2;

    // If the cursor1 or cursor2 was the last node then make the tail pointing at it
    if (cursor1->next == NULL)
    {
        tail = cursor1;
    }
    else if (cursor2->next == NULL)
    {
        tail = cursor2;
    }
}

template <typename type>
void SLL<type>::adjacentSwap(int firstIdx, int secondIdx)
{
    /*
        If the first Index was higher than the second Index
        Then swapping the values to make it easy to swap nodes
    */
    if (firstIdx > secondIdx)
    {
        std::swap(firstIdx, secondIdx);
    }

    /*
    --  Here we need only cursor to the previous node of the firstIdx node
    --  And a cursor to the next node of secondIdx node, 'cause the two nodes are adjacent
    */
    node<type> *cursorB1 = this->head;
    node<type> *cursor1 = nullptr;

    node<type> *cursor2 = this->head;
    node<type> *cursorAf2 = nullptr;

    for (int i = 0; i < secondIdx; i++)
    {
        cursor2 = cursor2->next;
    }
    cursorAf2 = cursor2->next;

    // Checking if the firstIdx node (remember: firstIdxit is the lower index now) is first (head) node or not
    if (firstIdx == 0)
    {
        /*
        -- Swapping the head node with secondIdx node by making the head pointer points at the second node and first node poiting at the third node
        -- and the second node poiting at first node
        */
        cursor1 = this->head;
        this->head = cursor2;
        cursor2->next = cursor1;
        cursor1->next = cursorAf2;
        return;
    }
    // Else Intialize the previous node of secondIdx node
    for (int i = 0; i < firstIdx - 1; i++)
    {
        cursorB1 = cursorB1->next;
    }
    cursor1 = cursorB1->next;

    /*
    -- Swapping the two adjacent nodes
    -- By Making the previous of firstIdx node pointing at the secondIdx node
    -- and the secondIdx node points at the firstIdx node and the firstIdx node points at the nextnode of the secondIdx node
    */
    cursorB1->next = cursor2;
    cursor2->next = cursor1;
    cursor1->next = cursorAf2;

    // Checking if the cursor1 was the last node to make the tail points at it
    if (cursor1->next == NULL)
    {
        tail = cursor1;
    }
}

template <typename type>
// Swapping the head node with Idx node
void SLL<type>::swap(int Idx)
{
    node<type> *cursor1 = this->head;
    node<type> *cursorAf1 = cursor1->next;

    node<type> *cursorB2 = this->head;
    node<type> *cursor2 = nullptr;
    node<type> *cursorAf2 = nullptr;

    for (int i = 0; i < Idx - 1; i++)
    {
        cursorB2 = cursorB2->next;
    }
    cursor2 = cursorB2->next;
    cursorAf2 = cursor2->next;

    /*
    -- Swapping the head node with secondIdx node by making the head pointer points at the second node and first node poiting at the next node of the Idx node
    -- and the Idx node poiting at first node
    */
    this->head = cursor2;
    cursor2->next = cursorAf1;
    cursorB2->next = cursor1;
    cursor1->next = cursorAf2;

    // Checking if the cursor1 was the last node to make the tail points at it
    if (cursor1->next == NULL)
    {
        tail = cursor1;
    }
}

template <typename type>
SLL<type> &SLL<type>::operator=(const SLL<type> anotherSLL)
{
    if (this != &anotherSLL)
    {
        delete head;
        delete tail;
        head = new node<type>;
        tail = new node<type>;
        head = tail = nullptr;
        node<type> *current = anotherSLL.head;

        while (current != NULL)
        {
            this->insertAtTail(current->element);
            current = current->next;
        }
    }
    return *this;
}

// template <typename type>
// SLL<type>::SLL(const SLL<type> anotherSLL)
// {
//     node<type>* current = anotherSLL.head;
//     head = tail = nullptr;
//     while (current != NULL)
//     {
//         this->insertAtTail(current->element);
//         current = current->next;
//     }
// }

template <typename type>
int SLL<type>::linkedListSize()
{
    return size;
}
template <typename type>
bool SLL<type>::isEmpty()
{
    return (size == 0);
}
template <typename type>
void SLL<type>::clear()
{
    tail = head = nullptr;
    size = 0;
}
template <typename type>
void SLL<type>::insertAtHead(type ele)
{
    node<type> *newNode = new node<type>(ele);
    if (size == 0)
    {
        head = newNode;
        tail = newNode;
        newNode->next = NULL;
    }
    else
    {
        newNode->next = head;
        head = newNode;
    }
    size++;
}
template <typename type>
void SLL<type>::insertAtTail(type ele)
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
        newNode->next = nullptr;
        tail = newNode;
    }
    size++;
}
template <typename type>
void SLL<type>::insertAt(type ele, int index)
{
    if (index > size || index < 0)
    {
        throw std::out_of_range("\n\t\t\t*** Out Of bounds ***\n");
    }
    else
    {
        node<type> *newNode = new node<type>(ele);
        if (index == 0)
        {
            insertAtHead(ele);
        }
        else if (index == size)
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
            size++;
        }
    }
}
template <typename type>
void SLL<type>::removeAtHead()
{
    if (size == 0)
    {
        throw std::out_of_range("\n\t\t\t*** Empty linked list ***\n");
    }
    else if (size == 1)
    {
        delete head;
        head = tail = NULL;
    }
    else
    {
        node<type> *ptr = head;
        head = ptr->next;
        delete ptr;
    }
    size--;
}

template <typename type>
void SLL<type>::removeAtTail()
{
    if (size == 0)
    {
        throw std::out_of_range("\n\t\t\t*** Empty linked list ***\n");
    }
    else if (size == 1)
    {
        delete head;
        head = tail = NULL;
    }
    else
    {
        node<type> *cur = head->next;
        node<type> *pre = head;
        while (cur->next != NULL)
        {
            pre = cur;
            cur = cur->next;
        }
        delete cur;
        pre->next = NULL;
        tail = pre;
        delete pre;
    }
    size--;
}
template <typename type>
void SLL<type>::removeAt(int index)
{
    if (size == 0)
    {
        throw std::out_of_range("\n\t\t\t*** Empty linked list ***\n");
    }
    if (index >= size)
    {
        throw std::out_of_range("\n\t\t\t*** Out Of bounds ***\n");
    }
    if (index == 0)
    {
        removeAtHead();
        return;
    }
    if (index == (size - 1))
    {
        removeAtTail();
        return;
    }
    else
    {
        int counter = 0;
        node<type> *cur = head;
        while (counter < index - 1)
        {
            cur = cur->next;
            counter++;
        }
        node<type> *tmp = cur->next;
        cur->next = tmp->next;
        delete tmp;
    }
    size--;
}

template <typename type>
type SLL<type>::retrieveAt(int index)
{
    // zero based
    type e;
    if (size <= index)
    {
        throw std::out_of_range("\n\t\t\t*** Out of bound ***\n");
    }
    node<type> *ptr = head;
    int counter = 0;
    while (ptr->next != NULL)
    {
        if (counter == index)
        {
            e = ptr->element;
            break;
        }
        counter++;
        ptr = ptr->next;
    }
    return e;
}
template <typename type>
void SLL<type>::replaceAt(type ele, int index)
{
    // zero based
    if (size <= index)
    {
        throw std::out_of_range("\n\t\t\t*** Out Of bounds ***\n");
    }
    node<type> *ptr = head;
    int counter = 0;
    while (ptr->next != NULL)
    {
        if (counter == index)
        {
            ptr->element = ele;
            break;
        }
        counter++;
        ptr = ptr->next;
    }
}
template <typename type>
bool SLL<type>::isExist(type ele)
{
    // zero based
    node<type> *ptr = head;
    int counter = 0;
    while (ptr->next != NULL)
    {
        if (ptr->element == ele)
        {
            return true;
        }
        counter++;
        ptr = ptr->next;
    }
    return false;
}
template <typename type>
bool SLL<type>::isItemAtEqual(type ele, int index)
{
    node<type> *ptr = head;
    int counter = 0;
    while (ptr->next != NULL)
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
void SLL<type>::print()
{
    node<type> *ptr = this->head;
    while (ptr->next != nullptr)
    {
        cout << ptr->element << "->";
        ptr = ptr->next;
    }
    cout << tail->element << endl;
}
int main(){
    SLL<int>s;
    // sLL s;
    s.insertAtHead(3);
    
    s.print();
    system("pause");
    s.insertAtHead(4);
    s.print();
    system("pause");
    s.insertAtHead(67);
    s.print();
    system("pause");
    s.insertAt(23, 2);
    s.print();
    system("pause");
    s.insertAtTail(67676);
    s.print();
    // system("pause");
    // system("pause");
    // s.insertInMiddle(34, 3);
    // s.print();
    // system("pause");
    // s.insertAtTail(456);
    // s.print();
    // system("pause");
    // s.removeAt(456);
    // s.print();
    // system("pause");
    // s.removeAt(67);
    // s.print();
    // system("pause");
    // s.removeAt(23);
    // s.print();
    // system("pause");
    // cout << "retrive : " << s.retrieveAt(10) << endl;

    // s.insertAtHead(23);
    // s.insertAtHead(1);
    // s.insertAtHead(4578);

    // s.print();
    // system("pause");

    // s.replaceAt(90000000, 1);
    // system("pause");
    // s.print();

    // cout << "is exit : " << s.isExit(90000000) << endl;

    // system("pause");

    // cout << "is ele are equal : " << s.isItemAtEqual(90000000, 0) << endl;

    // list<int>l;
    // l.push_back(4);


}