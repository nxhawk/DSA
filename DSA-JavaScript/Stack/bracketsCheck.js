/**
 * @param {string} s
 * @return {boolean}
 */

// Terminal run code: node ./bracketsCheck.js

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

//check correct brackets (no check word)
var isValid = (s) => {
  let st = new Stack();
  for (let e of s) {
    if (e === "(" || e === "{" || e === "[") st.push(e);
    else {
      if (st.isEmpty()) return false;
      else {
        if (e === ")") {
          if (st.top() !== "(") return false;
          st.pop();
        } else if (e === "}") {
          if (st.top() !== "{") return false;
          st.pop();
        } else {
          if (st.top() !== "[") return false;
          st.pop();
        }
      }
    }
  }
  return st.isEmpty();
};

//test function
console.log(isValid("({}[]{()()}[])({}[])"));
