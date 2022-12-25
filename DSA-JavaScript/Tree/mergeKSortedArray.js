/// Terminal run code: node mergeKSortedArray.js

/**
 *
 * @param {Array} arr
 * @param {Int} a
 * @param {Int} b
 * @returns {boolean}
 */
function cmp(arr, a, b) {
  return arr[a[0]][a[1]] > arr[b[0]][b[1]];
}

class MinHeap {
  #arr;
  constructor(cmp, g) {
    this.#arr = [];
    this.grid = g;
    this.comparator = cmp;
  }

  upheapify(idx) {
    if (idx === 0) return;
    let parentIdx = Math.floor((idx - 1) / 2);
    if (this.comparator(this.grid, this.#arr[parentIdx], this.#arr[idx])) {
      [this.#arr[parentIdx], this.#arr[idx]] = [
        this.#arr[idx],
        this.#arr[parentIdx],
      ];
      this.upheapify(parentIdx);
    }
  }

  downheapify(idx) {
    let l = idx * 2 + 1,
      r = idx * 2 + 2,
      sm = idx;
    if (
      l < this.#arr.length &&
      this.comparator(this.grid, this.#arr[sm], this.#arr[l])
    )
      sm = l;
    if (
      r < this.#arr.length &&
      this.comparator(this.grid, this.#arr[sm], this.#arr[r])
    )
      sm = r;
    if (sm !== idx) {
      [this.#arr[sm], this.#arr[idx]] = [this.#arr[idx], this.#arr[sm]];
      this.downheapify(sm);
    }
  }

  insert(x) {
    this.#arr.push(x);
    this.upheapify(this.#arr.length - 1);
  }

  removeRoot() {
    [this.#arr[0], this.#arr[this.#arr.length - 1]] = [
      this.#arr[this.#arr.length - 1],
      this.#arr[0],
    ];
    this.#arr.pop();
    this.downheapify(0);
  }

  display() {
    console.log(this.#arr);
  }

  getRoot() {
    return this.#arr[0];
  }

  isEmpty() {
    return this.#arr.length === 0;
  }
}

/**
 *
 * @param {number[]} grid
 * @returns {number[]}
 */
function mergeKSortedArray(grid) {
  let k = grid.length;
  let heap = new MinHeap(cmp, grid);
  for (let i = 0; i < k; i++) heap.insert([i, 0]);
  let res = [];
  while (!heap.isEmpty()) {
    let root = heap.getRoot();
    res.push(grid[root[0]][root[1]]);
    heap.removeRoot();
    let currArr = root[0];
    let currIdx = root[1];
    if (currIdx + 1 < grid[currArr].length) heap.insert([currArr, currIdx + 1]);
  }
  return res;
}

//data
let grid = [
  [2, 13, 78, 231],
  [1, 5, 9, 12, 33],
  [89, 111, 234],
  [1, 2],
  [3, 4, 5, 6, 7, 8, 9, 10, 11],
  [99, 232, 2245],
];
//// run main
//test code
let x = mergeKSortedArray(grid);
console.log(x);
