// Terminal run code: node stackLinkedList.js

class Node {
  constructor(data) {
    this.data = data;
    this.next = null;
  }
}

class LinkedList {
  //singly
  constructor() {
    this.head = null;
  }

  addHead(data) {
    let node = new Node(data);
    node.next = this.head;
    this.head = node;
  }

  removeHead() {
    if (this.head === null) return;
    let temp = this.head;
    this.head = this.head.next;
    temp = null;
  }

  getHead() {
    if (this.head == null) return undefined;
    return this.head.data;
  }

  isEmpty() {
    if (this.head === null) return true;
    return false;
  }
}

class Stack {
  constructor() {
    this.ll = new LinkedList();
  }

  push(x) {
    this.ll.addHead(x);
  }

  pop() {
    this.ll.removeHead();
  }

  top() {
    return this.ll.getHead();
  }

  isEmpty() {
    return this.ll.isEmpty();
  }
}

////run main
let st = new Stack();
st.push(1);
console.log(st.isEmpty());
st.push(2);
st.push(3);
console.log(st.top());
st.pop();
st.pop();
st.pop();
st.push(2);
console.log(st.isEmpty());
console.log(st.top());
