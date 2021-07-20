#include <iostream>

using namespace std;

struct LLNode
{
	int data;
	LLNode* next;
};

class LinkedList
{
public:

	LinkedList()
	{
		head = tail = nullptr;
	}

	void insertIfEmpty(LLNode* newNode)
	{
		newNode->next = nullptr;
		head = tail = newNode;
	}

	void insertFront(const int& value)
	{
		auto newNode = new LLNode;
		newNode->data = value;
		if (isEmpty())
		{
			insertIfEmpty(newNode);
			return;
		}
		newNode->next = head;
		head = newNode;
		size++;
	}

	void insertRear(const int& value)
	{
		auto newNode = new LLNode;
		newNode->data = value;
		if (isEmpty())
		{
			insertIfEmpty(newNode);
			return;
		}
		newNode->next = nullptr;
		tail->next = newNode;
		tail = newNode;
		size++;
	}

	void insertAt(const int& position,const int& value)
	{
		if (size < position)
		{
			cout << "Linked List is smaller than position given." << endl;
			return;
		}
		auto newNode = new LLNode;
		newNode->data = value;
		if (head == nullptr)
		{
			insertIfEmpty(newNode);
			return;
		}
		if (position == 0)
		{
			insertFront(value);
			return;
		}
		auto cur = head;
		int pos{ 0 };
		while (pos != position - 1)
		{
			cur = cur->next;
			pos++;
		}
		newNode->next = cur->next;
		cur->next = newNode;
		size++;
	}

	void deleteFront()
	{
		head = head->next;
		size--;
	}
	
	void deleteRear()
	{
		auto cur = head;
		while (cur->next != tail)
		{
			cur = cur->next;
		}
		tail = cur;
		cur->next = nullptr;
		size--;
	}

	void deleteAt(const int& position)
	{
		if (size < position)
		{
			cout << "Linked List is smaller than position given." << endl;
			return;
		}
		if (size == 1 && position == 1)
		{
			head = tail = nullptr;
			return;
		}
		auto cur = head;
		int pos{ 0 };
		while (pos != position - 1)
		{
			cur = cur->next;
			pos++;
		}
		cur->next = cur->next->next;
		size--;
	}

	void printLinkedList()
	{
		if (head == nullptr)
		{
			cout << "Linked List is empty";
		}
		else
		{
			auto cur = head;
			while (cur != nullptr)
			{
				cout << cur->data << " ";
				cur = cur->next;
			}
		}
		cout << endl;
	}

	bool isEmpty()
	{
		if (head == nullptr)
		{
			return true;
		}
		return false;
	}

private:
	LLNode* head;
	LLNode* tail;
	int size{ 0 };
};

int main()
{
	LinkedList ll;
	ll.insertFront(1);
	ll.insertFront(2);
	ll.insertRear(3);
	ll.printLinkedList();
	ll.insertAt(0, 4);
	ll.printLinkedList();
	ll.insertAt(2, 5);
	ll.printLinkedList();
	ll.deleteFront();
	ll.deleteRear();
	ll.printLinkedList();
	ll.deleteAt(2);
	ll.printLinkedList();
}