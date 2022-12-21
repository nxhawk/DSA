class Node:
    height = key = 0
    left = right = None

    def __init__(self, key):
        self.key = key
        self.height = 1


class AVL:
    root = None

    def height(self, root):
        if root is None:
            return 0
        return root.height

    def rightRotation(self, root):
        newroot = root.left
        root.left = newroot.right
        newroot.right = root
        root.height = max(self.height(root.left), self.height(root.right)) + 1
        newroot.height = max(self.height(newroot.left),
                             self.height(newroot.right)) + 1
        return newroot

    def leftRotation(self, root):
        newroot = root.right
        root.right = newroot.left
        newroot.left = root
        root.height = max(self.height(root.left), self.height(root.right)) + 1
        newroot.height = max(self.height(newroot.left),
                             self.height(newroot.right)) + 1
        return newroot

    def _balance(self, root):
        if root is None:
            return root
        bal = self.height(root.left) - self.height(root.right)
        if bal > 1:
            if self.height(root.left.left) < self.height(root.left.right):
                root.left = self.leftRotation(root.left)
            return self.rightRotation(root)
        elif bal < -1:
            if self.height(root.right.right) < self.height(root.right.left):
                root.right = self.rightRotation(root.right)
            return self.leftRotation(root)
        return root

    def insert(self, key):

        def addNode(root, key):
            if root is None:
                return Node(key)
            if root.key == key:
                return root
            elif root.key > key:
                root.left = addNode(root.left, key)
            else:
                root.right = addNode(root.right, key)
            # update height
            root.height = 1 + max(self.height(root.left),
                                  self.height(root.right))
            # balance
            return self._balance(root)
        self.root = addNode(self.root, key)

    def deleteNode(self, key):
        def deleteItem(root, key):
            if root is None:
                return root
            if root.key > key:
                root.left = deleteItem(root.left, key)
            elif root.key < key:
                root.right = deleteItem(root.right, key)
            else:
                l = root.left
                r = root.right
                if l is None:
                    root = r
                elif r is None:
                    root = l
                else:
                    while r.left:
                        r = r.left
                    root.key = r.key
                    root.right = deleteItem(root.right, r.key)
            if root is None:
                return root
            # update
            root.height = 1 + max(self.height(root.left),
                                  self.height(root.right))
            # balance
            return self._balance(root)
        self.root = deleteItem(self.root, key)

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
    tree = AVL()
    tree.insert(80)
    tree.insert(1000)
    tree.insert(50)
    tree.insert(75)
    tree.insert(57)
    tree.insert(1111)
    tree.insert(1112)
    tree.deleteNode(57)
    tree.BFS()
