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


if __name__ == '__main__':
    llist = LinkedList()
    llist.append(1)
    llist.append(3)
    llist.push(2)
    llist.append(13)
    llist.push(12)
    llist.append(123)
    llist.printList()
    llist.insertAfter(4, 5)
    llist.insertAfter(2, 123)
    llist.printList()
