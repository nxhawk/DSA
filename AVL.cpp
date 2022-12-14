//{}[]
#include<iostream>
#include<math.h>
#include<queue>
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
	void zigzagSearch(link root)
	{
		if (root == nullptr) return;
		cout << "\nZig zag level order traversal:\n";
		vector<vector<int>> ans;
		queue<link> q;
		q.push(root);
		bool lefttoright = true;
		while(!q.empty())
		{
			int size = q.size();
			vector<int> row(size);
			for (int i = 0; i < size; i++)
			{
				link node = q.front();
				q.pop();

				int index = lefttoright ? i : (size - i - 1);
				row[index] = node->key;
				if (node->left) q.push(node->left);
				if (node->right) q.push(node->right);
			}
			lefttoright = !lefttoright;
			ans.push_back(row);
		}
		for (vector<int> row : ans)
		{
			for (int key : row) cout << key << " ";
			cout << endl;
		} 
		cout << "END\n\n";
	}
	int Diameter(link root, int &diameter)
	{
		if (root == nullptr) return 0;

		int left_height = Diameter(root->left, diameter);
		int right_height = Diameter(root->right, diameter);

		diameter = max(diameter, left_height + right_height + 1);

		return max(left_height, right_height) + 1;
	}
	//left view traveral
	void leftView(link root, vector<int>& ans, int level) {
		if (root == nullptr) return;
		
		//we entered into a new level    
		if (level == ans.size())
			ans.push_back(root->key);

		leftView(root->left, ans, level + 1);//chang index two line => right view
		leftView(root->right, ans, level + 1);
	}
	//max sum of long root to leaf path
	void maxSumOfLongRootToLeafPath(link root, int sum, int len, int &maxSum, int &maxLen)
	{
		if (root == nullptr) {
			if (len > maxLen) {
				maxLen = len;
				maxSum = sum;
			}
			else if (len == maxLen) maxSum = max(maxSum, sum);
			return;
		}
		sum += root->key, len += 1;
		maxSumOfLongRootToLeafPath(root->left, sum, len, maxSum, maxLen);
		maxSumOfLongRootToLeafPath(root->right, sum, len, maxSum, maxLen);
	}
	// find kth Ancestor of node has value (val)
	link solve(link root, int& k, int val) {
		if (root == nullptr) return root;
		if (root->key == val) return root;
		
		link leftAns = solve(root->left, k, val);
		link rightAns = solve(root->right, k, val);
		
		//wapas
		if (leftAns != nullptr && rightAns == nullptr){
			k--;
			if (k <= 0) {
				//answer lock
				k = INT_MAX;
				return root;
			}
			return leftAns;
		}

		if (leftAns == nullptr && rightAns != nullptr) {
			k--;
			if (k <= 0) {
				//answer lock
				k = INT_MAX;
				return root;
			}
			return rightAns;
		}
		return nullptr;
	}
	//kth ancestor
	int kthAncestor(link root, int k, int val)
	{
		link ans = solve(root, k, val);
		if (!ans || ans->key == val || k == 0) return -1;
		return ans->key;
	}
	//Function to return the maximum sum of non-adjacent nodes
	pair<int,int> maxSumNonAdj(link root)
	{
		if (root == nullptr) return make_pair(0, 0);

		pair<int, int> left = maxSumNonAdj(root->left);
		pair<int, int> right = maxSumNonAdj(root->right);
		pair<int, int> res;
		
		res.first = root->key + left.second + right.second;
		res.second = max(left.first, left.second) + max(right.first, right.second);

		return res;
	}
public:
	AVL(){ root = nullptr; }
	void addNode(int key){ root = addNode(root, key); }
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
	void delItem(int key){ root = delItem(root, key); }
	void pathRTL()
	{
		vector<int> vt;
		pathRTL(root, 0, vt);
	}
	//xoay cay 180 do (lat cay)
	void invert_Tree(){ invert_Tree(root); }
	void zigzagSearch(){ zigzagSearch(root); }
	//tinh duong kinh cua cay (duong kinh la so node nhieu nhat tren duong di tu la nay den la khac) 
	void Diameter()
	{
		int diameter = 0;
		Diameter(root, diameter);
		cout << "Diameter: " << diameter << endl;
	}
	//Left View
	void leftView() {
		vector<int> ans;
		leftView(root, ans, 0);
		cout << "LEFT VIEW: ";
		for (auto x : ans) cout << x << " ";
		cout << endl;
	}
	//max sum of long root to leaf path
	void maxSumOfLongRootToLeafPath()
	{
		int len = 0, sum = 0;
		maxSumOfLongRootToLeafPath(root, 0, 0, sum, len);
		cout << "Max Sum of long Root to Leaf Path: " << sum << " With length = " << len << endl;
	}
	//find kth Ancestor of node has value = val
	void kthAncestor(int k, int val)
	{
		int res = kthAncestor(root, k, val);
		if (res == -1) cout << "Error!\n";
		else cout << "Ancestor index " << k << " of node has key="<<val<<" is " << res << endl;
	}
	//void print the maximum sum of non-adjacent nodes
	void maxSumNonAdj() 
	{
		pair<int, int> ans = maxSumNonAdj(root);
		int res = max(ans.first, ans.second);
		cout << "Max sum of non-adjacent nodes: " << res << endl;
	}
};

int main()
{
	AVL tree;
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
	tree.addNode(31);
	//tree.printTree();
	tree.BFS();
	tree.zigzagSearch();
	tree.Diameter();
	//cout << endl;
	//tree.invert_Tree();
	//tree.BFS();
	//tree.pathRTL();
	tree.leftView();
	tree.maxSumOfLongRootToLeafPath();
	tree.kthAncestor(2, 98);
	tree.maxSumNonAdj();
	return 0;
}
