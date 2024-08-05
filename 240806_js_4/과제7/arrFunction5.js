let bucketLists = [
  { id: 3, text: "여행가기", done: false },
  { id: 2, text: "코딩 먹기", done: true },
  { id: 1, text: "치킨 하기", done: false },
];

function toggle(id) {
  bucketLists = bucketLists.map((item) => {
    if (item.id == id) return { ...item, done: !item.done };
    else return item;
  });
}

toggle(2);

console.log(bucketLists);
