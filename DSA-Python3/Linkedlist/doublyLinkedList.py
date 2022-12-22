class Node:
    def __init__(self, data=None, next=None, prev=None):
        self.data = data
        self.next = next
        self.prev = prev


class DoublyLinkedList:
    def __init__(self):
        self.head = None
        self.tail = None

    def get_length(self):
        count = 0
        curr = self.head
        while curr:
            count += 1
            curr = curr.next
        return count

    def print_forward(self):
        if self.head is None:
            print("Linked list is empty")
            return

        print("S->", end="")
        curr = self.head
        while curr:
            print(f"{curr.data}->", end="")
            curr = curr.next
        print("E")

    def print_backward(self):
        if self.head is None:
            print("Linked list is empty")
            return

        print("E<-", end="")
        curr = self.tail
        while curr:
            print(f"{curr.data}<-", end="")
            curr = curr.prev
        print("S")

    def addHead(self, data):
        newNode = Node(data)

        if self.head is None:
            self.head = self.tail = newNode
        else:
            newNode.next = self.head
            self.head.prev = newNode
            self.head = newNode

    def addTail(self, data):
        newNode = Node(data)

        if self.head is None:
            self.head = self.tail = newNode
        else:
            newNode.prev = self.tail
            self.tail.next = newNode
            self.tail = newNode

    def addAt(self, index, data):
        length = self.get_length()
        if index < 0 or index > length:
            raise Exception("Invalid Index")
        if index == 0:
            self.addHead(data)
        elif index == length:
            self.addTail(data)
        else:
            curr = self.head
            for _ in range(index):
                curr = curr.next
            newNode = Node(data)
            newNode.prev = curr.prev
            curr.prev.next = newNode
            newNode.next = curr
            curr.prev = newNode

    def delHead(self):
        if self.head is None:
            return
        if self.head == self.tail:
            self.head = self.tail = None
        else:
            self.head = self.head.next
            self.head.prev = None

    def delTail(self):
        if self.head is None:
            return
        if self.head == self.tail:
            self.head = self.tail = None
        else:
            self.tail = self.tail.prev
            self.tail.next = None

    def delAt(self, index):
        length = self.get_length() - 1
        if index < 0 or index > length:
            raise Exception("Invalid Index")

        if index == 0:
            self.delHead()
        elif index == length:
            self.delTail()
        else:
            curr = self.head
            for _ in range(index):
                curr = curr.next
            curr.next.prev = curr.prev
            curr.prev.next = curr.next
            del curr

    def delVal(self, val):
        while self.head and self.head.data == val:
            self.delHead()
        while self.head and self.tail.data == val:
            self.delTail()
        if self.head is None:
            return
        curr = self.head
        while curr:
            if curr.data == val:
                curr.next.prev = curr.prev
                curr.prev.next = curr.next
                curr = curr.prev
            curr = curr.next


if __name__ == '__main__':
    l = DoublyLinkedList()
    l.addHead("hao")
    l.addTail("nhat")
    l.addAt(2, "hao")
    l.delVal("hao")
    l.print_forward()
    l.print_backward()
