class Node:
    def __init__(self, key):
        self.key = key
        self.next = None

    def printNode(self):
        print(self.key, end=" ")


class LinkedList:
    def __init__(self):
        self.head = None
        self.tail = None

    # push to top linked list
    def push(self, key):
        new_node = Node(key)
        new_node.next = self.head
        self.head = new_node
        if self.tail is None:
            self.tail = self.head

    # print list
    def printList(self):
        curr = self.head
        while curr:
            curr.printNode()
            curr = curr.next
        print()

    # add new item at tail
    def append(self, key):
        new_node = Node(key)
        if self.head is None:
            self.head = self.tail = new_node
            return

        self.tail.next = new_node
        self.tail = new_node

    # insert after index
    def insertAfter(self, index, key):
        curr = self.head
        for _ in range(index):
            curr = curr.next
        new_node = Node(key)
        new_node.next = curr.next
        if new_node.next is None:
            self.tail = new_node
        curr.next = new_node

    # Delete Node
    def deleteNode(self, key):
        # delete top element
        while self.head.key == key:
            self.head = self.head.next
        # check None
        if self.head is None:
            self.tail = self.head

        curr = self.head
        prev = curr
        while curr:
            if curr.key == key:
                if curr.next is None:
                    self.tail = prev
                prev.next = curr.next
            prev = curr
            curr = curr.next

    # count node
    def countNode(self):
        count = 0
        curr = self.head

        while curr:
            count += 1
            curr = curr.next

        return count

    # count node recursive
    def countNodeRec(self, node):
        if node is None:
            return 0
        return 1 + self.countNodeRec(node.next)

    def countNodeRec1(self):
        return self.countNodeRec(self.head)

    # bubble sort linked list

    def bubbleSort(self):
        p = self.head
        while p:
            curr = p.next
            if curr is None:
                break
            while curr:
                if p.key > curr.key:
                    p.key, curr.key = curr.key, p.key
                curr = curr.next
            p = p.next


if __name__ == '__main__':
    llist = LinkedList()
    llist.append(1)
    llist.append(3)
    llist.push(2)
    llist.append(13)
    llist.push(12)
    llist.append(123)
    llist.insertAfter(4, 5)
    llist.insertAfter(2, 123)
    llist.deleteNode(123)
    llist.printList()
    # llist.bubbleSort()
    print("Node:", llist.countNodeRec1())
