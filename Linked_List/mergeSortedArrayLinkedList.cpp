#include<iostream>

using namespace std;

class Node {
public:
	int key;
	Node* next;
	Node(int key = 0) {
		this->key = key;
		this->next = nullptr;
	}
};

class LinkedList {
	typedef Node* link;
private:
	void addTail(link& head, int key)
	{
		if (head == nullptr) return head = new Node(key), void();

		link curr = head;
		while (curr->next) curr = curr->next;
		curr->next = new Node(key);
		
	}
public:
	link head;
	LinkedList() {	head = nullptr;	}
	void addTail(int key) {	addTail(head, key);	}	
	void display() 
	{
		link curr = head;
		while (curr) {
			cout << curr->key << "->";
			curr = curr->next;
		}
		cout << "NULL\n";
	}
	void sort() 
	{
		link p = head;
		while (p->next)
		{
			link q = p->next;
			while (q) {
				if (q->key < p->key) {
					int tmp = q->key;
					q->key = p->key;
					p->key = tmp;
				}
				q = q->next;
			}
			p = p->next;
		}
	}
};

Node* merge(Node* h1, Node* h2)
{
	if (h1 == nullptr) return h2;
	if (h2 == nullptr) return h1;

	Node* result;
	if (h1->key < h2->key) {
		result = h1;
		result->next = merge(h1->next, h2);
	}
	else {
		result = h2;
		result->next = merge(h1, h2->next);
	}
	return result;
}

void display (Node* res) 
{
	Node* curr = res;
	while (curr) {
		cout << curr->key << "->";
		curr = curr->next;
	}
	cout << "NULL\n";
}

int main()
{
	int a1[] = {3, 13, 75, 2, 32, 54, 12, 3, 4, 3, 2};
	int a2[] = {8, 7, 34, 1, 2, 54, 23, 1};
	LinkedList h1, h2;
	for (int x : a1) h1.addTail(x);
	for (int x : a2) h2.addTail(x);
	h1.sort();
	h2.sort();
	Node* res = merge(h1.head, h2.head);
	display(res);
	return 0;
}
