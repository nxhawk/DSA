//{}[]
#include<iostream>
#include<string>
#include<vector>
#include<queue>
#include<stack>
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
	void NLR(link root)
	{
		if (root == nullptr) return;
		root->printNode();
		NLR(root->left);
		NLR(root->right);
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
	int floorT(link root, int key)
	{
		if (root == nullptr) return -1;
		if (root->key > key) return floorT(root->left, key);
		else if (key == root->key) return key;
		else {
			int res = floorT(root->right, key);
			if (res != -1) return res;
			return root->key;
		}
	}
	int ceilT(link root, int key)
	{
		if (root == nullptr) return -1;
		if (root->key == key) return key;
		if (root->key < key) return ceilT(root->right, key);
		int res = ceilT(root->left, key);
		if (res != -1) return res;
		return root->key;
	}
	//find max weight path from root to leaf
	int maxPath(link root, int sum)
	{
		if (root == nullptr) return sum;
		return max(maxPath(root->left, sum + root->key), maxPath(root->right, sum + root->key));
	}
	//find max sum path from leaf to leaf
	int maxPath2(link root, int &sum)
	{
		if (root == nullptr) return 0;
		int left_sum = maxPath2(root->left, sum);
		int right_sum = maxPath2(root->right, sum);

		sum = max(sum, left_sum + right_sum + root->key);
		return max(left_sum, right_sum) + root->key;
	}
	//find max sum key of level
	void maxLevel(link root, int& level, int &sum)
	{
		level = 0;
		sum = root->key;
		int sumLevel[1000];//sum of level
		memset(sumLevel, 0, 1000);
		queue<pair<link, int>> q;// manager root and level of it
		q.push({root, 0});
		while(!q.empty())
		{
			pair<link, int> t = q.front();
			q.pop();

			sumLevel[t.second] += t.first->key;
			if (sumLevel[t.second] > sum) {
				sum = sumLevel[t.second];
				level = t.second;
			}

			if (t.first->left) q.push({t.first->left, t.second + 1});
			if (t.first->right) q.push({ t.first->right, t.second + 1 });
		} 
	}
	//find max sum level use DFS
	void maxLevel_DFS(link root, int &res, int &resLevel, int level, int sum[])
	//res is result (sum max), resLevel is level result (level has max sum), level is now level, sum[] save sum value of level now   
	{
		if (root == nullptr) return;
		sum[level] += root->key;

		if (sum[level] > res) {
			res = sum[level];
			resLevel = level;
		}
		maxLevel_DFS(root->left, res, resLevel, level + 1, sum);
		maxLevel_DFS(root->right, res, resLevel, level + 1, sum);
	}
	void LNR_non(link root)
	{
		if (root == nullptr) return;
		stack<link> s;
		link curr = root;
		while(curr || !s.empty())
		{
			while(curr)
			{
				s.push(curr);
				curr = curr->left;
			}

			curr = s.top();
			s.pop();

			cout << curr->key << " ";

			curr = curr->right;
		} 
	}
	void LRN_non(link root)
	{
		if (root == nullptr) return;
		
		vector<int> res;
		stack<link> s;
		link prev = nullptr;
		s.push(root);
		while(!s.empty())
		{
			link curr = s.top();
			if (!curr) break;
			
			if(prev==nullptr || prev->left == curr || prev->right == curr)
			{
				if (curr->left) s.push(curr->left);
				else if (curr->right) s.push(curr->right);
				else {
					s.pop();
					res.push_back(curr->key);
				}
			}
			else if (curr->left == prev) {
				if (curr->right) s.push(curr->right);
				else {
					s.pop();
					res.push_back(curr->key);
				}
			}
			else if(curr->right == prev)
			{
				s.pop();
				res.push_back(curr->key);
			}
			prev = curr;
		} 

		for (int d : res) cout << d << " ";
	}
	void NLR_non(link root)
	{
		if (root == nullptr) return;
		stack<link> s;
		s.push(root);
		while(!s.empty())
		{
			link t = s.top();
			s.pop();
			cout << t->key << " ";

			if (t->right) s.push(t->right);
			if (t->left) s.push(t->left);
		} 
	}
	bool isExist(link root, int key)
	{
		if (root == nullptr) return false;
		if (root->key == key) return true;
		if (root->key > key) return isExist(root->left, key);
		return isExist(root->right, key);
	}
	//tim to tien chung gan nhat cua key a va b
	int find_LCA(link root, int a, int b)
	{
		if (root == nullptr) return -1;
		if (root->key > a && root->key > b) return find_LCA(root->left, a, b);
		if (root->key < a && root->key < b) return find_LCA(root->right, a, b);
		return root->key;
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
	void NLR()
	{
		NLR(root);
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
	//find floor(key)
	void floorT(int key)
	{
		cout << "Floor " <<key<<": "<<floorT(root, key) << endl;
	}
	//find ceil(key)
	void ceilT(int key)
	{
		cout << "Ceil " << key << ": " << ceilT(root, key) << endl;
	}
	//find max weight path from root to leaf
	void maxPath()
	{
		cout << "Max path from root to leaf: " << maxPath(root, 0) << endl;
		//sum weight path leaf-left -> root ->leaf-right
		cout << "Max path from leaf-left->root->leadf-right: " << maxPath(root->left, 0) + root->key + maxPath(root->right, 0) << endl;
	}
	//find max weight path from leaf to leaf
	void maxPath2()
	{
		int sum = 0;
		maxPath2(root, sum);
		cout << "Max path from leaf to other leaf: " <<sum << endl;
	}
	//find max wieght level of tree
	void maxLevel()
	{
		int level, sum;
		maxLevel(root, level, sum);
		cout << "Max sum key Level is "<<level<<" with value: "<<sum << endl;
	}
	//find max wright level of tree use DFS
	void maxLevel_DFS()
	{
		int sum[1000], res = root->key, level = 0;
		memset(sum, 0, 1000);
		maxLevel_DFS(root, res, level, 0, sum);
		cout << "With DFS Max sum key Level is " << level << " with value: " << res << endl;
	}
	//LNR non recursive
	void LNR_non()
	{
		cout << "LNR non recursive: ";
		LNR_non(root);
		cout << endl;
	}
	void LRN_non()
	{
		cout << "LRN non recursive: ";
		LRN_non(root);
		cout << endl;
	}
	void NLR_non()
	{
		cout << "NLR non recursive: ";
		NLR_non(root);
		cout << endl;
	}
	void find_LCA(int a, int b)
	{
		if (!isExist(root, a) || !isExist(root, b)) cout << "Any one of them or both doesn't exists\n";
		else cout << find_LCA(root, a, b);
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
	tree.insertItem(5);
	tree.insertItem(4);

	//tree.delItem(16);
	//tree.delItem(22);
	//{}[]
	//tree.BFS();
	tree.find_LCA(13, 15);
	//tree.hashPathSum(69);
	//tree.findNotBalance();
	//tree.height();
	//cout << endl;
	//tree.floorT(17);
	//tree.ceilT(17);
	//tree.maxPath();
	//tree.maxLevel();
	//tree.maxLevel_DFS();
	//tree.LRN();
	//tree.LRN_non();
	//tree.LNR_non();
	//tree.NLR();
	//tree.NLR_non();
	return 0;
}
