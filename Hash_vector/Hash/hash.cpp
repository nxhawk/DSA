//{}[]
#include<iostream>
#include<string>

using namespace std;

struct Student
{
	int student_id;
	string name;
	float gpa;
	Student(int a = 0, string b = "", float c = 0) {
		student_id = a;
		name = b;
		gpa = c;
	}
};

struct Node
{
	Student key;
	Node* next;
	Node(Student val) {
		key = val;
		next = nullptr;
	}
};

struct Hash
{
	int mod;
	Node** table;
};


void initHashTable(Hash& h, int mod)
{
	h.mod = mod;
	h.table = new Node*[mod];
	for (int i = 0; i < mod; i++) h.table[i] = nullptr;
}

int hashFunc(int val, int mod)
{
	return val % mod;
}

void insertItem(Hash& h, Student value)
{
	int index = hashFunc(value.student_id, h.mod);
	if (h.table[index] == nullptr) {
		Node* p = new Node(value);
		h.table[index] = p;
	}
	else {
		Node* p = h.table[index];
		Node* q = nullptr;
		while(p) {
			if (p->key.student_id == value.student_id) return;
			if (p->key.student_id > value.student_id) break;
			q = p;
			p = p->next;
		}
		Node* newnode = new Node(value);
		if (!newnode) return;
		if (p == nullptr) {
			q->next = newnode;
		}
		else if (q == nullptr) {
			h.table[index] = newnode;
			h.table[index]->next = p;
		}
		else {
			newnode->next = p;
			q->next = newnode;
		}
	}
}

bool findId(Hash h, int id)
{
	int index = hashFunc(id, h.mod);
	if (!h.table[index]) return false;
	Node* p = h.table[index];
	while(p) {
		if (p->key.student_id == id) return true;
		p = p->next;
	}
	return false;
}

void printHash(Hash h)
{
	for (int i = 0; i < h.mod; i++)
		if (h.table[i]) {
			Node* p = h.table[i];
			while(p) {
				cout << p->key.name << endl;
				p = p->next;
			}
		}
}

bool deleteItem(Hash&h, int id)
{
	int index = hashFunc(id, h.mod);
	if (!h.table[index]) return false;
	Node* p = h.table[index];
	Node* q = nullptr;
	while(p) {
		if (p->key.student_id == id) break;
		if (p->key.student_id > id) return false;
		q = p;
		p = p->next;
	}
	if (p == nullptr) return false;
	if (p->next == nullptr) {
		if (q == nullptr) {
			delete h.table[index];
			h.table[index] = nullptr;
		}
		else {
			delete p;
			q->next = nullptr;
		}
	}else {
		if (q == nullptr){
			Node* tmp = h.table[index];
			h.table[index] = h.table[index]->next;
			delete tmp;
		}
		else {
			q->next = p->next;
			delete p;
		}
	}
	return true;
}

int main()
{
	Hash h;
	initHashTable(h, 100);
	insertItem(h, { 423,"Nguyen Van A", 9.5 });
	insertItem(h, { 23, "Pham Minh B", 8.5 });
	insertItem(h, { 123, "Vo Van C", 7.0 });
	insertItem(h, { 323, "Phan Van E", 5.0 });
	cout << deleteItem(h, 123) << endl;
	printHash(h);
	return 0;
}