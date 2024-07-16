const QUERY_PERCENT = ".percent > span";
const QUERY_DATE = ".txt-info > strong";
const chartFirstLine = document.querySelector(
  "#contents > div.wrap-movie-chart > div.sect-movie-chart > ol:nth-child(2)"
);

// 1. 인기순위 1등 영화 정보 출력하기
const firstMovie = chartFirstLine.children[0];

const firstMovieTitle = firstMovie.querySelector(".title").textContent;

const firstMovieBookRate = firstMovie.querySelector(QUERY_PERCENT).textContent;

const firstMovieReleaseDate = firstMovie
  .querySelector(QUERY_DATE)
  .textContent.trim()
  .slice(0, 10);

console.log("제목: " + firstMovieTitle);
console.log("예매율: " + firstMovieBookRate);
console.log("개봉일자: " + firstMovieReleaseDate);

// 2. 인기순위 2등 영화 정보 변경하기
const secondMovie = chartFirstLine.children[1];

secondMovie.querySelector(".title").textContent = "삼겹살과 그대라면";

secondMovie.querySelector(QUERY_PERCENT).textContent =
  +firstMovieBookRate.slice(0, 4) - 5 + "%";

secondMovie.querySelector(QUERY_DATE).textContent = "1985.07.07 개봉";

// 3. 인기순위 3등과 1등 정보 변경하기
chartFirstLine.insertBefore(
  chartFirstLine.children[2],
  chartFirstLine.children[0]
);
chartFirstLine.insertBefore(
  chartFirstLine.children[2],
  chartFirstLine.children[1]
);
chartFirstLine.children[0].querySelector(".rank").textContent = "No.1";
chartFirstLine.children[2].querySelector(".rank").textContent = "No.3";
