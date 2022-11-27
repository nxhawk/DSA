//{}[]

#include<iostream>
#include<math.h>

using namespace std;

class Node
{
	typedef Node* link;
public:
	int key;
	link next;
	link prev;

	Node(int key = 0)
	{
		this->key = key;
		this->next = this->prev = nullptr;
	}
};

class DBList
{
	typedef Node* link;
private:
	link head;
	link tail;
	int length;
public:
	DBList()
	{
		head = tail = nullptr;
		length = 0;
	}
	//check empty list
	bool isEmpty()
	{
		return length == 0;
	}
	//add data end of list
	void append(int data)
	{
		if (head == nullptr)
		{
			link newNode = new Node(data);
			head = tail = newNode;
			length++;
		}
		else
		{
			link newNode = new Node(data);
			tail->next = newNode;
			newNode->prev = tail;

			tail = newNode;

			length++;
		} 
	}
	//add data first of list
	void prepend(int data)
	{
		if (head == nullptr) 
		{
			link newNode = new Node(data);
			head = tail = newNode;
			length++;
			return;
		} 
		link newNode = new Node(data);
		newNode->next = head;

		head->prev = newNode;
		head = newNode;

		length++;
	}
	//insert at after index (0->length -1)
	void insertAfter(int index, int data)
	{
		if (index >= length || index < 0) cout << "Out of list\n";
		else {
			link curr = head;
			while (index--) curr = curr->next;
			link newNode = new Node(data);
			newNode->next = curr->next;
			newNode->prev = curr;

			curr->next->prev = newNode;
			curr->next = newNode;
			length++;
		}
	}
	//insert at before index (0->length - 1)
	void insertBefore(int index, int data)
	{
		if (index < 0 || index >= length) cout << "Out of list\n";
		else {
			index = length - index - 1;
			link curr = tail;
			while (index--) curr = curr->prev;
			link newNode = new Node(data);
			newNode->next = curr;
			newNode->prev = curr->prev;

			curr->prev->next = newNode;
			curr->prev = newNode;
			length++;
		}
	}
	//print list
	void print()
	{
		if (head == nullptr) {
			cout << "List is empty\n";
			return;
		}
		link curr = head;
		while (curr)
		{
			cout << curr->key << "->";
			curr = curr->next;
		}
		cout << "NULL" <<endl << endl;
	}
	//delete node at head
	void deleteHead()
	{
		if (head == nullptr) return;
		head = head->next;
		delete(head->prev);
		head->prev = nullptr;
		length--;
	}
	//delete node at tail
	void deleteTail()
	{
		if (tail == nullptr) return;
		tail = tail->prev;
		delete(tail->next);
		tail->next = nullptr;
		length--;
	}
	//delete index	
	void deleteIndex(int index)
	{
		if (index < 0 || index > length - 1) return;
		if (index == 0) deleteHead();
		else if (index == length - 1) deleteTail();
		else {
			link curr = head;
			while (index--) curr = curr->next;
			link temp = curr;
			curr->prev->next = curr->next;
			curr->next->prev = curr->prev;
			delete(temp);
			length--;
		}
	}
};

int main()
{
	DBList l;
	l.append(10);
	l.append(12);
	l.prepend(17);
	l.append(15);
	l.prepend(13);
	l.insertAfter(0, 3);
	l.insertBefore(4, 2);
	l.print();
	//l.deleteHead();
	//l.deleteTail();
	//l.insertBefore(2, 123);
	l.deleteIndex(2);
	l.print();
	return 0;
}