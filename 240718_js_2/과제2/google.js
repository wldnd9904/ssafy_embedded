const darkModeButton = document.querySelector(".darkModeButton");
const body = document.querySelector("body");
darkModeButton.addEventListener("click", () => {
  body.classList.toggle("dark");
  darkModeButton.textContent = body.classList.contains("dark")
    ? "일반 모드"
    : "다크 모드";
});
