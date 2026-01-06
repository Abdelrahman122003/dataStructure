#include <iostream>
#include <stack>
using namespace std;

template <typename type>
class Queue
{
private:
    int size;
    int maxSize;
    type *arr;

public:
    Queue() : size(0), maxSize(10)
    {
        arr = new type[maxSize];
    }

    Queue(int maxSize) : maxSize(maxSize), size(0)
    {
        arr = new type[maxSize];
    }
    void enqueue(type ele)
    {
        if (size == maxSize)
        {
            maxSize *= 2;
            type *new_arr = new type[maxSize];
            for (int i = 0; i < size; i++)
            {
                new_arr[i] = arr[i];
            }
            delete[] arr;
            arr = new_arr;
        }
        arr[size] = ele;
        size++;
    }
    type first()
    {
        if (size == 0)
        {
            throw std::out_of_range("\n\t\t\t*** This queue is empty ***\n");
        }
        return arr[0];
    }
    type dequeue()
    {
        type e = arr[0];
        if (size == 0)
        {
            throw std::out_of_range("\n\t\t\t*** This queue is empty ***\n");
        }
        else
        {
            for (size_t i = 0; i < size - 1; i++)
            {
                arr[i] = arr[i + 1];
            }
            size--;
            if (size < (maxSize / 4)) // Shrink the array when it's only 25% full
            {
                maxSize /= 2;
                type *new_arr = new type[maxSize];
                for (int i = 0; i < size; i++)
                {
                    new_arr[i] = arr[i];
                }
                delete[] arr;
                arr = new_arr;
            }
        }
        return e;
    }
    bool isEmpty()
    {
        return (size == 0);
    }
    int queueSize()
    {
        return size;
    }
    void clear()
    {
        size = 0;
    }
    void print()
    {
        if (size == 0)
        {
            cout << "\n\t\t\t*** This queue is empty ***\n";
        }
        else
        {
            for (int i = 0; i < size; i++)
            {
                if (i == size - 1)
                {
                    cout << arr[i] << endl;
                }
                else
                {
                    cout << arr[i] << " <- ";
                }
            }
        }
    }
};

int main(){
    Queue<string>q;
    q.enqueue("sdsdsd");
    q.print();
    q.enqueue("abde");
    q.print();
    q.enqueue("sdfgfgfg");
    q.print();
    q.enqueue("sdfd");
    q.print();
    q.enqueue("sFgfgfgd");
    q.print();


}