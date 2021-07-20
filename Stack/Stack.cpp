#include <iostream>
#include<vector>

using namespace std;

class Stack
{
public:
    void push(const int& value)
    {
        stack.push_back(value);
        index++;
        size++;
    }

    void pop()
    {
        stack.pop_back();
        index--;
        size--;
    }

    int top()
    {
        return stack[index];
    }

    int Size()
    {
        return size;
    }

    void isEmpty()
    {
        if (size == 0)
        {
            cout<<"Empty"<<endl;
        }
        else
        {
            cout<<"Not Empty"<<endl;
        }
    }
private:
    int index{ -1 }, size{ 0 };
    vector<int> stack;
};
int main()
{
    Stack s;
    s.push(1);
    s.push(2);
    s.push(3);
    cout<<s.top()<<endl;
    cout << s.Size() << endl;
    s.pop();
    cout<<s.top()<<endl;
    s.isEmpty();
}