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

	Node(int key = 0)
	{
		this->key = key;
		this->next = nullptr;
	}
};

class CCList
{
	typedef Node* link;
private:
	link head;
	link tail;
	int length;
public:
	CCList()
	{
		head = tail = nullptr;
		length = 0;
	}
	//check empty list
	bool isEmpty()
	{
		return length == 0;
	}
	//because circular linked list so => 
	int fixIndex(int index)
	{
		while (index < 0) index += length;
		return index % length;
	}
	//insert at tail
	void append(int data)
	{
		if (head == nullptr)
		{
			link newNode = new Node(data);
			head = tail = newNode;
			tail->next = head;
			length++;
			return;
		} 
		link newNode = new Node(data);
		tail->next = newNode;
		tail = tail->next;
		tail->next = head;
		length++;
	}
	//insert at head
	void prepend(int data)
	{
		if (head == nullptr) {
			link newNode = new Node(data);
			head = tail = newNode;
			tail->next = head;
			length++;
			return;
		}
		link newNode = new Node(data);
		tail->next = newNode;
		newNode->next = head;
		head = newNode;

		length++;
	}
	//insert at after index (0->lenght -1)
	void insertAfter(int index, int data)
	{
		index = fixIndex(index);
		link curr = head;
		while (index--) curr = curr->next;
		link newNode = new Node(data);
		newNode->next = curr->next;
		curr->next = newNode;
		
		length++;
	}
	//print list
	void print()
	{
		if (head == nullptr) return;
		link curr = head;
		do {
			cout << curr->key << "->";
			curr = curr->next;
		} while (curr != head);
		cout << "NULL\n";
	}
	//delete head
	void deleteHead()
	{
		if (head == nullptr) return;
		link p = head;
		tail->next = head->next;
		head = head->next;
		delete(p);
		length--;
	}
	//delete tail
	void deleteTail()
	{
		if (head == nullptr) return;
		link curr = head;
		link p = tail;
		while (curr->next != tail) curr = curr->next;
		tail = curr;
		tail->next = head;
		delete(p);
		length--;
	}
	//delete index
	void deleteIndex(int index)
	{
		index = fixIndex(index);
		if (index == 0) deleteHead();
		else if (index == length - 1) deleteTail();
		else {
			link curr = head;
			link prev = head;
			while(index--) {
				prev = curr;
				curr = curr->next;
			}
			prev->next = curr->next;
			delete(curr);
		}
	}
};

int main()
{
	CCList l;
	l.append(12);
	l.append(13);
	l.prepend(10);
	l.append(11);
	l.prepend(4);
	l.insertAfter(10, 1);
	l.deleteIndex(0);
	l.insertAfter(2, 19);
	l.append(134);
	l.prepend(122);
	l.insertAfter(4, 2);
	l.print();
	l.deleteTail();
	l.deleteIndex(4);
	l.deleteHead();
	l.print();
	return 0;
}