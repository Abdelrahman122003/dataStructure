#include <iostream>
#include <stack>
using namespace std;

template<typename type>

class stackLinkedList{
    private:
    int size;
    class node{
    public:
    type element;
    node* next;
    node* prev;
   };
    node* head;
    node* tail;
    public:
    stackLinkedList(){
        head = tail = NULL;
        size = 0;
    }
    void push(type ele){
        node* newNode = new node();
        newNode->element = ele;
        if(head == NULL){
            head = tail = newNode;
            tail->next = NULL;
            head->prev = NULL;
        }else{
            tail->next = newNode;
            newNode->prev = tail;
            tail->next = NULL;
            tail = newNode;
        }
        size++;
    }
    type pop(){
        if(size == 0 || head == NULL){
            cout << "\n\t\t\t*** This stack is empty ***" << endl;
        }
        type e = tail->element;
        tail = tail->prev;
        tail->next = NULL;
        return e;
    }
    type top(){
        if(size == 0 || head == NULL){
            cout << "\n\t\t\t*** This stack is empty ***" << endl;
        }
        return tail->element;
    }
    bool isEmpty(){
        return (size == 0);
    }
    int stackSize(){
        return size;
    }
    void clear(){
        size = 0;
        head = NULL;
        tail = NULL;
    }
    void print(){
        if(head == NULL){
            cout << "\n\t\t\t*** This stack is empty ***\n" << endl;
            return;
        }
        node* p = tail;
        while(p->prev != NULL){
            cout << p->element << " <- ";
            p = p->prev;
        }
        cout << p->element << endl;
    }
};
int main(){
    stackLinkedList<int>s;
    // cout << s.pop() << endl;;
    // cout << "--------------------------------" << endl;
    s.push(34);
    s.print();
    // cout << endl;
    // system("pause");
    s.push(45);
    // s.print();
    // cout << endl;
    // system("pause");
    s.push(2);
    // s.print();
    // cout << endl;
    // system("pause");
    s.push(90);
    // s.print();
    // cout << endl;
    // system("pause");
    cout << s.pop() << endl;
    // cout << s.top() << endl;
    s.print();
    // cout << endl;
    // system("pause");

}