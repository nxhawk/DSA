//{}[]
#include<iostream>
#include<string>
#include<math.h>
#include<vector>

using namespace std;

class Node
{
public:
	int id;
	string name;
	float gpa;
	Node* left;
	Node* right;

	Node() {
		this->gpa = -1;
		this->name = "";
		this->id = -1;
		this->left = this->right = nullptr;
	}
	Node(int id, string name, float gpa) {
		this->gpa = gpa;
		this->id = id;
		this->name = name;
		this->left = this->right = nullptr;
	}
	void printNode() {
		cout << id << " " << name << " " << gpa << endl;
	}
};

class BST : Node
{
	typedef Node* link;
private:
	link root;


	void addNode(link& root, Node t)
	{
		if (root == nullptr) {
			root = new Node(t);
			return;
		}
		if (root->id == t.id) return;
		if (root->id > t.id) addNode(root->left, t);
		else addNode(root->right, t);
	}

	void printTree(link tree) {
		if (tree == nullptr) return;
		printTree(tree->left);
		tree->printNode();
		printTree(tree->right);
	}
	int height(link root)
	{
		if (root == nullptr) return 0;
		return max(height(root->left), height(root->right)) + 1;
	}
	Node findMin(link root)
	{
		if (root == nullptr) return Node();
		link p = root;
		while (p->left) p = p->left;
		return Node(p->id, p->name, p->gpa);
	}
	Node findMax(link root)
	{
		if (root == nullptr) return Node();
		link p = root;
		while (p->right) p = p->right;
		return Node(p->id, p->name, p->gpa);
	}
	int countNode(link root)
	{
		if (root == nullptr) return 0;
		return countNode(root->left) + countNode(root->right) + 1;
	}
	void searchStandFor(link&p, link&q)
	{
		if (q->left) searchStandFor(p, q->left);
		else {
			p->gpa = q->gpa;
			p->name = q->name;
			p->id = q->id;
			p = q;
		}
	}
	void delNode(link& root, int id)
	{
		if (root == nullptr) return;
		if (root->id > id) delNode(root->left, id);
		else if (root->id < id) delNode(root->right, id);
		else {
			link p = root;
			if (root->left == nullptr) root = root->right;
			else if (root->right == nullptr) root = root->left;
			else {
				link q = root->right;
				searchStandFor(p, q);
				delNode(root->right, p->id);
				return;
			}
			delete p;
		}
	}
	void LRN(link root) {
		if (root == nullptr) return;
		LRN(root->left);
		LRN(root->right);
		root->printNode();
	}
	void BFS(link root)
	{
		if (root == nullptr) return;
		vector<link> queue;
		queue.push_back(root);
		int i = 0;
		while(i < queue.size()) {
			link r = queue[i++];
			r->printNode();
			if (r->left) queue.push_back(r->left);
			if (r->right) queue.push_back(r->right);
		}
	}
public:
	BST() {
		root = nullptr;
	}

	void addNode(Node t)
	{
		addNode(root, t);
	}
	void printTree()
	{
		printTree(root);
	}
	int height()
	{
		return height(root);
	}
	Node findMin()
	{
		return findMin(root);
	}
	Node findMax()
	{
		return findMax(root);
	}
	int countNode()
	{
		return countNode(root);
	}
	void delNode(int id)
	{
		delNode(root, id);
	}
	void LRN() {
		LRN(root);
	}
	void BFS()
	{
		BFS(root);
	}
};

int main()
{
	BST tree;
	tree.addNode({ 10, "Nguyen Van A", 8.6 });
	tree.addNode({ 8, "Tran Thi B", 5.5 });
	tree.addNode({ 16, "Vo Van C", 9.9 });
	tree.addNode({ 14, "Truong Ngoc D", 7.2 });
	tree.addNode({ 22, "Phan Dinh G", 7.9 });
	tree.addNode({ 20, "Nguyen Ngoc E", 10.0 });
	tree.addNode({ 18, "To Ngoc Y", 5.4 });
	tree.addNode({ 19, "Bui Thien K", 6.8 });
	tree.addNode({ 21, "Vo Thanh L", 8.4 });
	tree.addNode({ 13, "Le Hoai O", 9.4 });
	tree.addNode({ 15, "Truong Hoai J", 4.4 });
	/*
	tree.printTree();
	cout << "Height: " << tree.height() << endl;

	Node res = tree.findMin();
	cout << "Min tree: ";
	res.printNode();

	res = tree.findMax();
	cout << "Max tree: ";
	res.printNode();

	cout << "Count of Node: " << tree.countNode() << endl;
	*/
	tree.delNode(16);
	tree.delNode(22);
	//tree.LRN();
	tree.BFS();
	return 0;
}