#include <iostream>
#include<vector>
#include<algorithm>

using namespace std;

class Queue
{
public:
    void Insert(const int& value)
    {
        queue.push_back(value);
        front++;
        if (rear == -1)
        {
            rear = 0;
        }
        size++;
    }

    void Delete()
    {
        queue.erase(queue.begin());
        rear++;
        size--;
    }

    void printQueue()
    {
        for (int i : queue)
        {
            cout << i << " ";
        }
        cout << endl;
    }

    int Size()
    {
        return size;
    }

    void isEmpty()
    {
        if (size == 0)
        {
            cout << "Queue is empty" << endl;
        }
        else
        {
            cout << "Queue is not empty" << endl;
        }
    }

private:
    vector<int> queue;
    int front{ -1 }, rear{ -1 }, size{ 0 };
};

int main()
{
    Queue q;
    q.isEmpty();
    q.Insert(1);
    q.Insert(2);
    q.Insert(3);
    q.printQueue();
    q.Delete();
    q.printQueue();
    cout << q.Size()<<endl;
    q.isEmpty();
}