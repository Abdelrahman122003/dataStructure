#include <bits/stdc++.h>
using namespace std;

template <typename T>
class arrayList
{
private:
    int size;
    int maxSize;
    T *list;

public:
    arrayList(int n)
    {
        size = 0;
        maxSize = n;
        list = new T[maxSize];
    }
    int listSize()
    {
        return size;
    }
    int listMaxSize()
    {
        return maxSize;
    }
    void insert(T ele)
    {
        if (maxSize <= size)
        {
            throw std::out_of_range("\n\t\t\t*** This List is Full ***\n");
        }
        list[size] = ele;
        size++;
    }
    void insertAt(T ele, int index)
    {

        if (maxSize <= size)
        {
            throw std::out_of_range("\n\t\t\t*** This List is Full ***\n");
        }
        if (index >= size || index < 0)
        {
            throw std::out_of_range("\n\t\t\t*** Out Of bounds ***\n");
        }
        else
        {
            size++;
            for (int i = size - 1; i > index; i--)
            {
                list[i] = list[i - 1];
            }
            list[index] = ele;
        }
    }
    T retrieveAt(int index)
    {
        if (index >= size || index < 0)
        {

            throw std::out_of_range("\n\t\t\t*** Out Of bounds ***\n");
        }
        return list[index--];
    }
    void removeAt(int index)
    {

        if (index >= size || index < 0)
        {
            throw std::out_of_range("\n\t\t\t*** Out Of bounds ***\n");
        }
        else
        {
            for (int i = index; i < size; i++)
            {
                list[i] = list[i + 1];
            }
            size--;
        }
    }
    void replaceAt(T newEle, int index)
    {

        if (index >= size || index < 0)
        {
            throw std::out_of_range("\n\t\t\t*** Out Of bounds ***\n");
        }
        else
        {
            list[index] = newEle;
        }
    }
    bool isItemAtEqual(T element, int index)
    {
        if (index >= size || index < 0)
        {
            throw std::out_of_range("\n\t\t\t*** Out Of bounds ***\n");
        }
        return (list[index] == element);
    }
    bool isFull()
    {
        return (size == maxSize);
    }
    bool isEmpty()
    {
        return (size == 0);
    }
    void clear()
    {
        size = 0;
    }
    void print()
    {
        for (int i = 0; i < size; i++)
        {
            cout << list[i] << " ";
        }
        cout << endl;
    }
    ~arrayList()
    {
        delete[] list;
    }
};
int main()
{
    arrayList<int>arr(10);
    arr.insert(4);
    arr.insert(489);
    arr.print();
    system("pause");
    arr.retrieveAt(2);
    arr.print();
    system("pause");

    arr.print();
    // arr.insertAt(45, 1);
    // arr.insertAt(50, 3);
    // arr.insertAt(300, 2);
    // arr.insertAt(300, 2);
    // arr.insertAt(300, 2);
    // arr.removeAt(5);
    // arr.replaceAt(50000, 5);
    // arr.print();
    // system("pause");
    // cout << "check element : " << arr.isItemAtEqual(300, 2) << endl;
    // system("pause"); 
    // cout << "check element : " << arr.isItemAtEqual(300, 12) << endl;
    // cout << arr.isEmpty() << endl;
    // cout << arr.listSize() << endl;
    // cout << arr.isFull() << endl;

    // cout << arr.retrieveAt(9) << endl;
    // arr.print();

    
}
