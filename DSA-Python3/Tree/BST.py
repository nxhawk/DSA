class Node:
    key = 0
    left = right = None

    def __init__(self, key):
        self.key = key


class BST:
    root = None

    def insert(self, key):
        def insertItem(root, key):
            if root is None:
                return Node(key)
            if root.key == key:
                return self.root
            if root.key < key:
                root.right = insertItem(root.right, key)
            else:
                root.left = insertItem(root.left, key)
            return root
        self.root = insertItem(self.root, key)

    def inorder(self):
        def inorderT(root):
            if root is None:
                return
            inorderT(root.left)
            print(root.key, end=" ")
            inorderT(root.right)

        inorderT(self.root)
        print()

    def deleteNode(self, key):
        def deleteT(root, key):
            if root is None:
                return root
            if key < root.key:
                root.left = deleteT(root.left, key)
            elif key > root.key:
                root.right = deleteT(root.right, key)
            else:
                l = root.left
                r = root.right
                if l is None:
                    root = None
                    return r
                if r is None:
                    root = None
                    return l
                while r.left:
                    r = r.left
                root.key = r.key
                root.right = deleteT(root.right, r.key)
            return root

        self.root = deleteT(self.root, key)

    def BFS(self):
        if self.root is None:
            return
        queue = []
        queue.append(self.root)
        while queue:
            size = len(queue)
            for _ in range(size):
                curr = queue.pop(0)
                print(curr.key, end=" ")
                if curr.left:
                    queue.append(curr.left)
                if curr.right:
                    queue.append(curr.right)
            print()


if __name__ == '__main__':
    tree = BST()
    tree.insert(5)
    tree.insert(13)
    tree.insert(2)
    tree.insert(47)
    tree.insert(15)
    tree.insert(12)
    tree.insert(4)
    tree.deleteNode(5)
    tree.deleteNode(47)
    tree.BFS()
