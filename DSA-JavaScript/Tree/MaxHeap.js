//// Terminal run code: node MaxHeap.js

class MaxHeap {
  #arr;
  constructor() {
    this.#arr = [];
  }
  upheapify(idx) {
    if (idx === 0) return;
    let parentIdx = Math.floor((idx - 1) / 2);
    if (this.#arr[parentIdx] < this.#arr[idx]) {
      [this.#arr[parentIdx], this.#arr[idx]] = [
        this.#arr[idx],
        this.#arr[parentIdx],
      ];
      this.upheapify(parentIdx);
    }
  }

  heapify(idx) {
    let l = idx * 2 + 1,
      r = idx * 2 + 2,
      mx = idx;
    if (l < this.#arr.length && this.#arr[l] > this.#arr[mx]) mx = l;
    if (r < this.#arr.length && this.#arr[r] > this.#arr[mx]) mx = r;
    if (mx !== idx) {
      [this.#arr[mx], this.#arr[idx]] = [this.#arr[idx], this.#arr[mx]];
      this.heapify(mx);
    }
  }

  insert(x) {
    this.#arr.push(x);
    this.upheapify(this.#arr.length - 1);
  }

  /**
   *
   * @return {MaxInt}
   */
  get() {
    if (!this.#arr) return undefined;
    let res = this.#arr[0];
    [this.#arr[0], this.#arr[this.#arr.length - 1]] = [
      this.#arr[this.#arr.length - 1],
      this.#arr[0],
    ];
    this.#arr.pop();
    this.heapify(0);
    return res;
  }

  display() {
    console.log(this.#arr);
  }
}

////run main
heap = new MaxHeap();
heap.insert(12);
heap.insert(4);
heap.insert(15);
heap.insert(5);
heap.insert(20);
heap.insert(3);
heap.insert(14);
heap.insert(30);
console.log(heap.get());
heap.display();
heap.insert(50);
heap.display();
