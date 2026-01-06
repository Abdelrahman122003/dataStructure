#include <iostream>
#include <stack>
using namespace std;

template<typename type>

class queueLinkedList{
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
    queueLinkedList(){
        head = tail = NULL;
        size = 0;
    }
    void enqueue(type ele){
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
    type first(){
        
        // cout << "first : " << head->element << endl;
        // cout << "inside : " << endl;
        // print();
        if(head == NULL){
            cout << "\n\t\t\t*** This queue is empty ***\n" << endl;
            return head->element;
        }else{
            return head->element;
        }
    }
    type dequeue(){
        // cout << "enter 1" << endl;
        if(head == NULL || size == 0){
            cout << "\n\t\t\t*** This queue is empty ***\n";
            return head->element;
        }else{
            // Node* current = first;
			// first = first->next;
			// first->prev = NULL;
			// delete current;
            type e = head->element;   
            node* ptr = head;
            head = head->next;
            head->prev = NULL;
            delete ptr;
            size--;
            cout << "inside : " << endl;
            print();
            return e;
        }
        
    }
    bool isEmpty(){
        return (size == 0 || head == NULL);
    }
    int queueSize(){
        return size;
    }
    void clear(){
        size = 0;
        head = NULL;
        tail = NULL;
    }
    void print(){
        if(head == NULL){
            cout << "\n\t\t\t*** This queue is empty ***\n" << endl;
            return;
        }
        node* p = tail;
        while(p->prev != NULL){
            cout << p->element << " -> ";
            p = p->prev;
        }
        cout << p->element << endl;
    }
};

int main(){
    queueLinkedList<string>q;
    // cout << q.dequeue() << endl;
    q.enqueue("dfdf");
    q.enqueue("er");
    q.enqueue("ryty");
    q.enqueue("adsgg");
    q.print();
    // system("pause");
    // cout << "size : " << q.queueSize() << endl;
    system("pause");
    cout << q.dequeue() << endl;
    // cout << "size : " << q.queueSize() << endl;
    // system("pause");
    // cout << q.first() << endl;
    // system("pause");
    // cout << "size : " << q.queueSize() << endl;
    // system("pause");
    // system("pause");
    // q.print();
    
}
