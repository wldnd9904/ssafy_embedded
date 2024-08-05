let bucketLists = [
  { id: 3, text: "여행가기", done: false },
  { id: 2, text: "치킨 먹기", done: true },
  { id: 1, text: "코딩 하기", done: false },
];

function addList(list) {
  bucketLists = [list, ...bucketLists];
}

addList({ id: 4, content: "요리하기", completed: true });

console.log(bucketLists);
