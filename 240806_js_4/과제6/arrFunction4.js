let bucketLists = [
  { id: 3, text: "여행가기", done: false },
  { id: 2, text: "치킨 먹기", done: true },
  { id: 1, text: "코딩 하기", done: false },
];

function removeList(id) {
  bucketLists = bucketLists.filter((item) => item.id != id);
}

removeList(2);

console.log(bucketLists);
