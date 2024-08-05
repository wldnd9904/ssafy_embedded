const arr = [1, 2, 3, 4, 5];
const squares = arr.map((el) => el * el);
console.log(squares); // [ 1, 4, 9, 16, 25 ]

const arr2 = ["a", "bcd", "ef", "g"];
const lengths = arr2.map((el) => el.length);
console.log(lengths); // [ 1, 3, 2, 1 ]
