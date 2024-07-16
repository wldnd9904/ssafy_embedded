// 1. 1이 몇개인지 세기
let a1 = 0;
for (const i of [1, 2, 3, 1, 2, 3, 1, 2, 3]) {
  if (i === 1) a1++;
}
console.log(a1);

// 2. 'A' 존재 여부 출력
let a2 = false;
for (const c of ["A", "E", "W", "Q", "A"]) {
  if (c === "A") {
    a2 = true;
    break;
  }
}
console.log(a2 ? "O" : "X");
