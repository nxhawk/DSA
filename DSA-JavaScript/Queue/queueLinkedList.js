/**
 * @param {string} s
 * @return {Array}
 */

/// Terminal run code: node queueLinkedList.js

/*
  You will be given stream of characters. The moment we recieve a new
  character, we need to return the first non repeating character
  at that point of time (return -1 if haven't).  
*/

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
    this.tail = null;
  }

  addTail(data) {
    if (this.head == null) this.head = this.tail = new Node(data);
    else {
      let node = new Node(data);
      this.tail.next = node;
      this.tail = node;
    }
  }

  removeHead() {
    if (this.head === null) return;
    if (this.head === this.tail) this.head = this.tail = null;
    else {
      let temp = this.head.next;
      this.head.next = null;
      this.head = temp;
    }
  }

  getHead() {
    if (this.head === null) return undefined;
    return this.head.data;
  }
}

//no isEmpty, isFull
class Queue {
  constructor() {
    this.ll = new LinkedList();
  }
  enqueue(x) {
    this.ll.addTail(x);
  }

  dequeue() {
    this.ll.removeHead();
  }

  front() {
    return this.ll.getHead();
  }
}

function firstNonRepeatingChar(str) {
  let A = new Array();
  let q = new Queue();
  let mp = {};
  for (let curr of str) {
    if (!mp[curr]) {
      mp[curr] = 1;
      q.enqueue(curr);
    } else mp[curr]++;
    while (mp[q.front()] > 1) q.dequeue();
    if (q.front()) A.push(q.front());
    else A.push(-1);
  }
  return A;
}

///run main
//text function
console.log(firstNonRepeatingChar("abbcadcd"));
