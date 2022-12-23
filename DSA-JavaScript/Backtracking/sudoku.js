let grid = [
  [3, ".", 6, 5, ".", 8, 4, ".", "."],
  [5, 2, ".", ".", ".", ".", ".", ".", "."],
  [".", 8, 7, ".", ".", ".", ".", 3, 1],
  [".", ".", 3, ".", "1", ".", ".", 8, "."],
  [9, ".", ".", 8, 6, 3, ".", ".", 5],
  [".", 5, ".", ".", 9, ".", 6, ".", "."],
  [1, 3, ".", ".", ".", ".", 2, 5, "."],
  [".", ".", ".", ".", ".", ".", ".", 7, 4],
  [".", ".", 5, 2, ".", 6, 3, ".", "."],
];

function canWePlace(r, c, num) {
  for (let i = 0; i < 9; i++)
    if (grid[i][c] === num || grid[r][i] === num) return false;

  let R = Math.floor(r / 3);
  let C = Math.floor(c / 3);
  for (let i = R * 3; i < R * 3 + 3; i++)
    for (let j = C * 3; j < C * 3 + 3; j++)
      if (grid[i][j] === num) return false;
  return true;
}

function f(r, c) {
  if (c === 9) {
    f(r + 1, 0);
    return;
  }

  if (r === 9) {
    console.log(grid);
    return;
  }

  if (grid[r][c] !== ".") f(r, c + 1);
  else {
    for (let num = 1; num <= 9; num++)
      if (canWePlace(r, c, num)) {
        grid[r][c] = num;
        f(r, c + 1);
        grid[r][c] = ".";
      }
  }
}

f(0, 0);
