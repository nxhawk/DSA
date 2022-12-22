// Terminal run code: node stackArray.js

class Stack {
  #arr; //private value
  constructor() {
    this.#arr = [];
  }

  push(x) {
    this.#arr.push(x);
  }

  pop(x) {
    this.#arr.pop();
  }

  top(x) {
    return this.#arr[this.#arr.length - 1];
  }

  isEmpty() {
    return this.#arr.length === 0;
  }
}

///run main
let st = new Stack();

st.push(10);
st.pop();
st.pop();
st.push(5);
console.log(st.top());
