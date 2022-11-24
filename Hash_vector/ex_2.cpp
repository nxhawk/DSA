#include<iostream>
#include<string>
#include<vector>

//{}[]
using namespace std;

struct Student
{
	int student_id;
	string name;
	float gpa;
};

struct Hash
{
	int mod;
	vector<Student>* table;
};

void createHash(Hash& h, int mod)
{
	h.mod = mod;
	h.table = new vector<Student>[mod];
}

int funcHash(int key, int mod)
{
	return key % mod;
}

void insertItem(Hash& h, Student key)
{
	int index = funcHash(key.student_id, h.mod);
	h.table[index].push_back(key);
}

bool findIdHash(Hash h, int id)
{
	int index = funcHash(id, h.mod);
	for (int i = 0; i < h.table[index].size(); i++)
		if (h.table[index][i].student_id == id) return true;
	return false;
}

int main()
{
	Hash h;
	createHash(h, 100);
	insertItem(h, { 123, "Nguyen Van A", 9.5 });
	insertItem(h, { 124, "Pham Minh B", 8.5 });
	insertItem(h, { 125, "Vo Van C", 7.0 });
	insertItem(h, { 223, "Phan Van E", 5.0 });

	int id;
	cin >> id;
	if (findIdHash(h, id)) cout << "exist\n";
	else cout << "non-exist\n";
	return 0;
}