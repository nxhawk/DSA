#include<iostream>
#include<math.h>
#include<vector>
#include<queue>

using namespace std;

enum Color {RED, BLACK, DOUBLE_BLACK};

struct Node
{
	int data;
	int color;
	Node* left, * right, * parent;
	explicit Node(int);
};
Node::Node(int data = 0) {
	this->data = data;
	color = RED;
	left = right = parent = nullptr;
}

typedef Node* link;

class RBTree 
{
private:
	link root;
protected:
	int getColor(link);
	void setColor(link, int);
	void rotateLeft(link);
	void rotateRight(link);
	void fixInsertRBTree(link);
	void fixDeleteRBTree(link);
	link insertBST(link, link);
	link deleteBST(link, int);
public:
	RBTree();
	void insertValue(int);
	void deleteValue(int);
	void printTree();
};

//init tree
RBTree::RBTree() { root = nullptr; }

int RBTree::getColor(link root) {if (root == nullptr) return BLACK;	return root->color;}
void RBTree::setColor(link root, int color) { if (root == nullptr) return; root->color = color;}

//insert BST code
link RBTree::insertBST(link root, link ptr)
{
	if (root == nullptr) return ptr;

	if (root->data > ptr->data) {
		root->left = insertBST(root->left, ptr);
		root->left->parent = root;
	}else if (root->data < ptr->data) {
		root->right = insertBST(root->right, ptr);
		root->right->parent = root;
	} 

	return root;
}

//insert new node Red black tree
void RBTree::insertValue(int data)
{
	link node = new Node(data);
	root = insertBST(root, node);
	fixInsertRBTree(node);
}

//Rotate
void RBTree::rotateLeft(link ptr)
{
	link right_child = ptr->right;
	ptr->right = right_child->left;

	if (ptr->right != nullptr)
		ptr->right->parent = ptr;

	right_child->parent = ptr->parent;

	if (ptr->parent == nullptr)
		root = right_child;
	else if (ptr == ptr->parent->left)
		ptr->parent->left = right_child;
	else
		ptr->parent->right = right_child;

	right_child->left = ptr;
	ptr->parent = right_child;
}
void RBTree::rotateRight(link ptr)
{
	link left_child = ptr->left;
	ptr->left = left_child->right;

	if (ptr->left != nullptr)
		ptr->left->parent = ptr;

	left_child->parent = ptr->parent;

	if (ptr->parent == nullptr)
		root = left_child;
	else if (ptr == ptr->parent->left)
		ptr->parent->left = left_child;
	else
		ptr->parent->right = left_child;

	left_child->right = ptr;
	ptr->parent = left_child;
}

//fix after insert 
void RBTree::fixInsertRBTree(link ptr)
{
	link parent = nullptr;
	link grandparent = nullptr;
	while(ptr!=root && getColor(ptr) == RED && getColor(ptr->parent) == RED) {
		parent = ptr->parent;
		grandparent = parent->parent;
		if (parent == grandparent->left) {
			link uncle = grandparent->right;
			if (getColor(uncle) == RED) {
				setColor(uncle, BLACK);
				setColor(parent, BLACK);
				setColor(grandparent, RED);
				ptr = grandparent;
			}else {
				if (ptr == parent->right) {
					rotateLeft(parent);
					ptr = parent;
					parent = ptr->parent;
				}
				rotateRight(grandparent);
				swap(parent->color, grandparent->color);
				ptr = parent;
			}
		}
		else {
			link uncle = grandparent->left;
			if (getColor(uncle) == RED) {
				setColor(uncle, BLACK);
				setColor(parent, BLACK);
				setColor(grandparent, RED);
				ptr = grandparent;
			}
			else {
				if (ptr == parent->left) {
					rotateRight(parent);
					ptr = parent;
					parent = ptr->parent;					
				}
				rotateLeft(grandparent);
				swap(parent->color, grandparent->color);
				ptr = parent;
			}
		}
	}
	setColor(root, BLACK);
}

void RBTree::printTree() 
{
	if (root == nullptr) {
		cout << "Tree is null\n";
		return;
	}
	queue<link> q;
	q.push(root);
	while(!q.empty()) {
		int sz = q.size();
		while (sz--) {
			link curr = q.front();
			q.pop();
			
			cout << curr->data;
			if (getColor(curr) == BLACK) cout << "B   ";
			else cout << "R   ";

			if (curr->left) q.push(curr->left);
			if (curr->right) q.push(curr->right);
		}
		cout << endl;
	}
}

//find node need delete 
link RBTree::deleteBST(link root, int data)
{
	if (root == nullptr) return root;
	if (data < root->data) return deleteBST(root->left, data);
	if (data > root->data) return deleteBST(root->right, data);
	
	if (root->left == nullptr && root->right == nullptr) return root;

	link temp = root->right;
	while (temp->left) temp = temp->left;
	root->data = temp->data;
	return deleteBST(root->right, temp->data);
}

void RBTree::deleteValue(int data)
{
	link node = deleteBST(root, data);
	fixDeleteRBTree(node);
}


//Damn!!! What is it
void RBTree::fixDeleteRBTree(link node) {
	if (node == nullptr) return;

	if (node == root) {
		root = nullptr;
		return;
	}

	if (getColor(node) == RED || getColor(node->left) == RED || getColor(node->right) == RED) {
		link child = node->left != nullptr ? node->left : node->right;

		if (node == node->parent->left) node->parent->left = child;
		else node->parent->right = child;
		
		if (child != nullptr) child->parent = node->parent;
		setColor(child, BLACK);
		delete (node);		
	}
	else {
		link sibling = nullptr;
		link parent = nullptr;
		link ptr = node;
		setColor(ptr, DOUBLE_BLACK);
		while (ptr != root && getColor(ptr) == DOUBLE_BLACK) {
			parent = ptr->parent;
			if (ptr == parent->left) {
				sibling = parent->right;
				if (getColor(sibling) == RED) {
					setColor(sibling, BLACK);
					setColor(parent, RED);
					rotateLeft(parent);
				}
				else {
					if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
						setColor(sibling, RED);
						if (getColor(parent) == RED) setColor(parent, BLACK);
						else setColor(parent, DOUBLE_BLACK);
						ptr = parent;
					}
					else {
						if (getColor(sibling->right) == BLACK) {
							setColor(sibling->left, BLACK);
							setColor(sibling, RED);
							rotateRight(sibling);
							sibling = parent->right;
						}
						setColor(sibling, parent->color);
						setColor(parent, BLACK);
						setColor(sibling->right, BLACK);
						rotateLeft(parent);
						break;
					}
				}
			}
			else {
				sibling = parent->left;
				if (getColor(sibling) == RED) {
					setColor(sibling, BLACK);
					setColor(parent, RED);
					rotateRight(parent);
				}
				else {
					if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
						setColor(sibling, RED);
						if (getColor(parent) == RED) setColor(parent, BLACK);
						else setColor(parent, DOUBLE_BLACK);
						ptr = parent;
					}
					else {
						if (getColor(sibling->left) == BLACK) {
							setColor(sibling->right, BLACK);
							setColor(sibling, RED);
							rotateLeft(sibling);
							sibling = parent->left;
						}
						setColor(sibling, parent->color);
						setColor(parent, BLACK);
						setColor(sibling->left, BLACK);
						rotateRight(parent);
						break;
					}
				}
			}
		}
		if (node == node->parent->left) node->parent->left = nullptr;
		else node->parent->right = nullptr;
		delete(node);
		setColor(root, BLACK);
	}
}

int main()
{	
	RBTree tree;
	tree.insertValue(5);
	tree.insertValue(1);
	tree.insertValue(4);
	tree.insertValue(3);
	tree.insertValue(2);
	tree.insertValue(8);
	tree.insertValue(9);
	tree.insertValue(7);
	tree.insertValue(16);
	tree.insertValue(11);
	tree.insertValue(12);
	tree.insertValue(15);
	tree.deleteValue(8);
	tree.printTree();
	return 0;
}