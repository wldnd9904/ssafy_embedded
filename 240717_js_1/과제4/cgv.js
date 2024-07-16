// 1. 모든 영화 제목 저장하기
const titleNodes = document.querySelectorAll(".title");
const titles = Array.from(titleNodes).map((node) => node.textContent);
console.log(titles);

// 2. 모든 영화 제목들 모자이크 처리
titleNodes.forEach((node) => {
  node.textContent = node.textContent.replace(/[a-zA-Z가-힣0-9]/g, "*");
});

// 3. 모든 영화 예매율 30% 증가
const percentNodes = document.querySelectorAll(".percent > span");
percentNodes.forEach((node) => {
  node.textContent =
    Math.min(100, +node.textContent.split("%")[0] + 30).toFixed(1) + "%";
});
