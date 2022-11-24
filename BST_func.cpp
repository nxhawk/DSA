//{}[]
#include<iostream>
#include<string>
#include<vector>
#include<math.h>

#define oo -1000000

using namespace std;

class Node
{
public:
	int key;
	Node* left;
	Node* right;
	Node(int key = oo)
	{
		this->key = key;
		this->left = this->right = nullptr;
	}
	void printNode()
	{
		cout << key << " ";
	}
};

int a[1000000];

class BST : public Node
{
	typedef Node* link;
private:
	link root;
	link insertItem(link &root, int t)
	{
		if (root == nullptr) {
			link p = new Node(t);
			return p;
		}
		if (root->key > t) root->left = insertItem(root->left, t);
		else if (root->key < t) root->right = insertItem(root->right, t);
		return root;
	}
	void LRN(link root)
	{
		if (root == nullptr) return;
		LRN(root->left);
		LRN(root->right);
		root->printNode();
	}
	link findMin(link r)
	{
		while (r->left) r = r->left;
		return r;
	}
	link delItem(link& root, int t)
	{
		if (root == nullptr) return root;
		if (root->key > t) root->left = delItem(root->left, t);
		else if (root->key < t) root->right = delItem(root->right, t);
		else
		{
			link p = root;
			if (root->left == nullptr) root = root->right;
			else if (root->right == nullptr) root = root->left;
			else {
				link temp = findMin(root->right);
				root->key = temp->key;
				root->right = delItem(root->right, temp->key);
			}
		} 
		return root;
	}
	void BFS(link root)
	{
		if (root == nullptr) return;
		vector<link> t;
		t.push_back(root);
		int i = 0;
		while(i < t.size())
		{
			link r = t[i++];
			r->printNode();
			if (r->left) t.push_back(r->left);
			if (r->right) t.push_back(r->right);
		} 
	}
	//check has path from root to leaf with sum each key == sum ?
	bool hashPathSum(link root, int sum, int vt)
	{
		if (root == nullptr) {
			if (sum == 0) {
				for (int i = 0; i < vt - 1; i++) cout << a[i] << "->";
				cout << a[vt-1] << endl;
				return true;
			}
			return false;
		} 
		a[vt] = root->key;
		return hashPathSum(root->left, sum - root->key, vt + 1) || hashPathSum(root->right, sum - root->key, vt + 1);
	}
	int height(link root)
	{
		if (root == nullptr) return 0;
		return max(height(root->left), height(root->right)) + 1;
	}
	//find node is not balance
	void findNotBalance(link root) {
		if (root == nullptr) return;
		if (abs(height(root->left) - height(root->right)) > 1) cout << root->key << " ";
		findNotBalance(root->left);
		findNotBalance(root->right);
	}
public:
	BST() {
		root = nullptr;
	}
	void insertItem(int t)
	{
		root = insertItem(root, t);
	}
	void LRN() {
		LRN(root);
		cout << endl;
	}
	void delItem(int t)
	{
		root = delItem(root, t);
	}
	void BFS()
	{
		BFS(root);
		cout << endl;
	}
	void hashPathSum(int sum)
	{
		if (hashPathSum(root, sum, 0)) cout << "Yes\n";
		else cout << "No\n";
	}
	void findNotBalance()
	{
		findNotBalance(root);
		cout << endl;
	}
	void height()
	{
		cout << "Height: " << height(root) << endl;
	}
};

int main()
{
	BST tree;
	tree.insertItem(10);
	tree.insertItem(8);
	tree.insertItem(16);
	tree.insertItem(14);
	tree.insertItem(22);
	tree.insertItem(15);
	tree.insertItem(13);
	tree.insertItem(20);
	tree.insertItem(21);
	tree.insertItem(18);
	tree.insertItem(19);
	//tree.delItem(16);
	//tree.delItem(22);
	//{}[]
	tree.BFS();
	tree.hashPathSum(69);
	tree.findNotBalance();
	tree.height();
	return 0;
}