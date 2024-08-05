const bucketLists = [
  { id: 3, text: "여행가기", done: false },
  { id: 2, text: "치킨 먹기", done: true },
  { id: 1, text: "코딩 하기", done: false },
];

function getValues(list, key) {
  return list.map((item) => item[key]);
}

console.log(getValues(bucketLists, "id"));
console.log(getValues(bucketLists, "text"));
console.log(getValues(bucketLists, "done"));
