#include <iostream>
#include <stack>
using namespace std;

template <typename type>
class Stack
{
private:
    int size;
    int maxSize;
    type *arr;

public:
    Stack(int maxSize) : maxSize(maxSize), size(0)
    {
        arr = new type[maxSize];
    }
    Stack() : size(0), maxSize(10)
    {
        arr = new type[maxSize];
    }
    void push(type ele)
    {
        if (size == maxSize)
        {
            maxSize *= 2;
            type *new_array = new type[maxSize];
            for (int i = 0; i < size; i++)
            {
                new_array[i] = arr[i];
            }
            delete[] arr;
            arr = new_array;
        }
        arr[size++] = ele;
    }
    type pop()
    {
        if (size == 0)
        {
            throw std::out_of_range("\n\t\t\t*** This stack is empty ***");
        }
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
        return arr[--size];
    }
    type top()
    {
        if (size == 0)
        {
            throw std::out_of_range("\n\t\t\t*** This stack is empty ***");
        }
        return arr[size - 1];
    }
    bool isEmpty()
    {
        return size == 0;
    }
    void clear()
    {
        size = 0;
    }
    int sizeStack()
    {
        return size;
    }
    void print()
    {
        if (size == 0)
        {
            cout << "\n\t\t\t*** This stack is empty ***";
        }
        for (int i = size - 1; i >= 0; i--)
        {
            if (i == 0)
            {
                cout << arr[i] << endl;
                return;
            }
            cout << arr[i] << "<-";
        }
    }
};

int main(){
   
    Stack<int>s;
    s.push(23);
    s.push(24);
    s.push(25);
    s.push(26);
    s.print();
    cout << s.sizeStack() << endl;
    system("pause");
    cout << s.pop() << endl;
    cout << s.sizeStack() << endl;
}