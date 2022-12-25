#include<iostream>

using namespace std;

class Node
{
public:
	int key;
	Node* next;
	Node(int key) : key(key), next(nullptr) {}
};

class LinkedList {
	typedef Node* link;
private:
	link head;
public:
	LinkedList() : head(nullptr) {}
	void addHead(int key) {
		if (head == nullptr) return head = new Node (key), void();

		link node = new Node(key);
		node->next = head;
		head = node;
	}
	void display()
	{
		link curr = head;
		while (curr) {
			cout << curr->key << "->";
			curr = curr->next;
		}
		cout << "NULL\n";
	}
	link nodeMid() 
	{
		link slow = head;
		link fast = head;

		while (fast && fast->next)
			slow = slow->next,	fast = fast->next->next;
		
		return slow;
	}
};

int main()
{
	LinkedList ll;
	ll.addHead(10); ll.addHead(12); ll.addHead(13); ll.addHead(1); ll.addHead(2); ll.addHead(55);
	ll.display();
	Node* res = ll.nodeMid();
	cout << "Node middle: " << res->key << endl;
	return 0;
}