//{}[]

#include<iostream>
#include<math.h>
#include<string>
#include<vector>

using namespace std;

class Node {
public:
	int key;
	int height;
	Node* left;
	Node* right;
	Node(int key = 0) {
		this->height = 1;
		this->key = key;
		this->left = this->right = nullptr;
	}
};


class AVL : public Node
{
	typedef Node* link;
private:
	link root;
	int height(link root)
	{
		if (root == nullptr) return 0;
		return root->height;
	}
	link rightRotation(link root)
	{
		link newroot = root->left;
		root->left = newroot->right;
		newroot->right = root;
		root->height = 1 + max(height(root->left), height(root->right));
		newroot->height = 1 + max(height(newroot->left), height(newroot->right));
		return newroot;
	}
	link leftRotation(link root)
	{
		link newroot = root->right;
		root->right = newroot->left;
		newroot->left = root;
		root->height = 1 + max(height(root->left), height(root->right));
		newroot->height = 1 + max(height(newroot->left), height(newroot->right));
		return newroot;
	}	
	link _balance(link root)
	{
		if (root == nullptr) return root;
		int bal = height(root->left) - height(root->right);
		if (bal > 1)
		{
			if (height(root->left->left) < height(root->left->right)) root->left = leftRotation(root->left);
			return rightRotation(root);
		} 
		else if (bal < -1) {
			if (height(root->right->right) < height(root->right->left))	root->right = rightRotation(root->right);
			return leftRotation(root);
		}
		return root;
	}
	link addNode(link root, int key)
	{
		if (root == nullptr)
		{
			link p = new Node(key);
			return p;
		}
		if (root->key == key) return root;
		if (key < root->key) root->left = addNode(root->left, key);
		else if (key > root->key) root->right = addNode(root->right, key);
		//update height
		root->height = 1 + max(height(root->left), height(root->right));
		//balance tree
		return _balance(root);
	}
	void printTree(link root)
	{
		if (root == nullptr) return;
		printTree(root->left);
		printTree(root->right);
		cout << root->key << " ";
	}
	void BFS(link root)
	{
		if (root == nullptr) return;
		vector<link> t;
		vector<int> tt;
		t.push_back(root);
		tt.push_back(0);
		int i = 0;
		while(i < t.size())
		{
			link p = t[i++];
			if (p->left) t.push_back(p->left), tt.push_back(tt[i-1] + 1);
			if (p->right) t.push_back(p->right), tt.push_back(tt[i-1] + 1);
			cout << p->key << " ";
			if (i == 1) cout << endl;
			else if (i >= t.size()) continue;
			else if (tt[i - 1] != tt[i]) cout << endl;
		} 
	}
	link delItem(link root, int key)
	{
		if (root == nullptr) return root;
		if (root->key > key) root->left = delItem(root->left, key);
		else if (root->key < key) root->right = delItem(root->right, key);
		else {
			link r = root->right;
			link l = root->left;
			if (r == nullptr) {
				delete(root);
				root = l;
			}else if (l == nullptr) {
				delete root;
				root = r;
			}else {
				while (r->left) r = r->left;
				root->key = r->key;
				root->right = delItem(root->right, r->key);
			}
		}
		if (root == nullptr) return root;
		//update height
		root->height = 1 + max(height(root->left), height(root->right));
		//blance tree
		return _balance(root);
	}
	//print all key in path from root to leaf
	void pathRTL(link root, int n, vector<int> vt)
	{
		if (root == nullptr) return;
		if (root->left == nullptr && root->right == nullptr) {
			for (int i = 0; i < n; i++) cout << vt[i] << " ";
			cout << root->key << endl;
			return;
		}
		vt.push_back(root->key);
		pathRTL(root->left, n + 1, vt);
		pathRTL(root->right, n + 1, vt);
	}
	//xoay cay 180 (lat cay)
	void invert_Tree(link root)
	{
		if (root == nullptr) return;
		invert_Tree(root->left);
		invert_Tree(root->right);

		//rotate (swap)
		link temp = root->left;
		root->left = root->right;
		root->right = temp;
	}
public:
	AVL()
	{
		root = nullptr;
	}
	void addNode(int key)
	{
		root = addNode(root, key);
	}
	void printTree()
	{
		printTree(root);
		cout << endl;
	}
	void BFS()
	{
		BFS(root);
		cout << endl;
	}
	void delItem(int key)
	{
		root = delItem(root, key);
	}
	void pathRTL()
	{
		vector<int> vt;
		pathRTL(root, 0, vt);
	}
	//xoay cay 180 do (lat cay)
	void invert_Tree()
	{
		invert_Tree(root);
	}
};

int main()
{
	AVL tree;
	//{}[]
	tree.addNode(45);
	tree.addNode(36);
	tree.addNode(15);
	tree.addNode(29);
	tree.addNode(57);
	tree.addNode(78);
	tree.addNode(60);
	tree.addNode(83);
	tree.addNode(79);
	tree.addNode(96);
	tree.addNode(20);
	tree.addNode(99);
	tree.addNode(97);

	tree.delItem(36);
	tree.delItem(15);
	tree.delItem(78);

	//tree.printTree();
	tree.BFS();

	cout << endl;
	tree.invert_Tree();
	tree.BFS();
	//tree.pathRTL();
	return 0;
}