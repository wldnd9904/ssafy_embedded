const bucketList = [
  { id: 1, text: "B형 합격하기", done: true },
  { id: 2, text: "서류 합격하기", done: false },
  { id: 3, text: "면접 합격하기", done: false },
  { id: 4, text: "검강검진 통과하기", done: false },
  { id: 5, text: "삼성 입사하기", done: false },
];

const todoList = bucketList.filter((bucket) => bucket.done == false);

console.log(todoList);
// [
//   { id: 2, text: "서류 합격하기  ", done: false },
//   { id: 3, text: "면접 합격하기  ", done: false },
//   { id: 4, text: "검강검진 통과  하기", done: false },
//   { id: 5, text: "삼성 입사하기  ", done: false },
// ];
