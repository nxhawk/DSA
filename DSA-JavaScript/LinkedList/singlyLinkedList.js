class Node {
  constructor(data) {
    this.data = data;
    this.next = null;
  }
}

class LinkedList {
  constructor() {
    this.head = null;
  }

  display() {
    if (this.head == null) {
      console.log("Linked list is empty\n");
      return;
    }
    let A = Array();
    let curr = this.head;
    while (curr) {
      A.push(curr.data);
      curr = curr.next;
    }
    console.log(A);
  }

  addHead(data) {
    if (this.head === null) {
      this.head = new Node(data);
      return;
    }
    let node = new Node(data);
    node.next = this.head;
    this.head = node;
  }

  removeHead() {
    if (this.head === null) return;
    else {
      let temp = this.head.next;
      this.head.next = this.head = null;
      this.head = temp;
    }
  }

  addTail(data) {
    if (this.head === null) {
      this.head = new Node(data);
      return;
    }
    let node = new Node(data);
    let temp = this.head;
    while (temp.next) temp = temp.next;
    temp.next = node;
  }

  removeTail() {
    if (this.head === null) return;
    else {
      let node = this.head;
      while (node.next.next !== null) node = node.next;
      node.next = null;
    }
  }

  addAt(pos, data) {
    if (this.head === null || pos == 0) this.addHead(data);
    else {
      let temp = this.head;
      pos--;
      while (pos-- && temp.next != null) temp = temp.next;

      let node = new Node(data);
      node.next = temp.next;
      temp.next = node;
    }
  }

  removeAt(pos) {
    if (this.head == null) return;
    if (this.head.next == null || pos == 0) this.removeHead();
    else {
      let temp = this.head;
      pos--;
      while (pos-- && temp.next) temp = temp.next;
      let node = temp.next;
      temp.next = temp.next.next;
      node.next = node = null;
    }
  }

  reverseLLPointers() {
    if (this.head == null) return;
    let prev = null;
    let curr = this.head;
    while (curr) {
      let temp = curr.next;
      curr.next = prev;
      prev = curr;
      curr = temp;
    }
    this.head = prev;
  }

  reverseLLValues() {
    if (this.head === null) return;
    //get length
    let len = 0;
    let temp = this.head;
    while (temp) len++, (temp = temp.next);
    //swap
    let curr = this.head;
    for (let i = 0; i < len / 2; i++) {
      let temp = this.head;
      for (let j = 0; j < len - i - 1; j++) temp = temp.next;
      let v = curr.data;
      curr.data = temp.data;
      temp.data = v;
      curr = curr.next;
    }
  }
}

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//
////  Terminal run code: node <nameFile.js>
//
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

///run main
///----->
let ll = new LinkedList();
//init data
ll.addHead(12);
ll.addTail(14);
ll.addHead(13);
ll.addTail(4);
ll.addHead(15);
ll.removeTail();
ll.removeTail();
ll.addTail(11);
ll.addAt(3, 2);
ll.removeAt(3);
ll.display();
ll.reverseLLValues();
ll.addHead(1);
ll.addTail(2);
ll.reverseLLPointers();
//print
ll.display();
///<-----
