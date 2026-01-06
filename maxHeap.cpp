#include <iostream>
// #include <poir> 

using namespace std;

/*
parent for node => (i-1)/2
left for node   => (2i+1)
right for node  => (2i+2)
*/
template<typename type>
class maxHeap{
    private:
    int size;
    int capacity = 10;
    type *heap;
    public:
    maxHeap(){
        size = 0;
        heap = new type[capacity];
    }
    // this function to get child in the left of node
    int left(int node){
        int in = node*2+1;
        return(size <= in?-1:in);
    }
    // this function to get child in the right of node
    int right(int node){
        int in = node*2+2;
        return(size <= in?-1:in);
    }
    // this function to get parent of this node
    int parent(int node){
        int in = (node-1)/2;
        return(size <= in?-1:in);
    }
    void heapifyUp(int childPos){
        int parentPos = parent(childPos);
        if(childPos == 0||heap[parentPos] > heap[childPos])return;
        swap(heap[childPos],heap[parentPos]);
        heapifyUp(parentPos);
    }
    // insert in heap
    void push(type ele){
        // to recapacity heap to protect memory
         if(capacity == size){
            capacity *= 2;
            type *newHeap = new type[capacity];
            for (int i = 0; i < size; i++)newHeap[i] = heap[i];
            delete[] heap;
            heap = newHeap;
        }
        heap[size++] = ele;
        heapifyUp(size-1);
    }
    void heapifyDown(int parentPos){
        int childPos = left(parentPos);
        int rightChild = right(parentPos);

        // no children
        if(childPos == -1)return;
        
        // to minimize between left and right child 
        if(rightChild != -1 && heap[childPos] < heap[rightChild])
        childPos = rightChild;

        // swap between parent and least child
        if(heap[childPos] > heap[parentPos]){
            swap(heap[parentPos], heap[childPos]);
            heapifyDown(childPos);
        }
    }
    // delete element
    void pop()
    {
        if(size < (capacity/4)){
            capacity = capacity/2;
            type* newHeap = new type[capacity];
            for (int i = 0; i < size; i++)newHeap[i] = heap[i];
            delete [] heap;
            heap = newHeap;
        }
        if(isEmpty())return;
        // delete parent then parent -> last child
        heap[0] = heap[--size]; 
        heapifyDown(0);
    }
    bool isEmpty(){
        return(size == 0);
    }
    int sizeHeap(){
        return(size);
    }
    void print(){
        for (int i = 0; i < size; i++)
        {
            cout << heap[i] << " ";
        }cout << endl;
    }
    ~maxHeap(){
        delete[] heap;
    }

};

int main(){
    maxHeap<int>h;
    h.push(23);
    h.push(10);
    h.push(4);
    h.push(1);
    h.push(2);
    h.push(70);
    h.push(12);
    h.print();
    system("pause");
    h.pop();
    h.print();
    system("pause");
    h.pop();
    h.print();
    system("pause");
    h.pop();
    h.print();
    system("pause");
    h.pop();
    h.print();
    system("pause");
    h.pop();
    h.print();
}