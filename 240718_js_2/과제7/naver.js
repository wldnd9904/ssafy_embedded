const darkToggleBtn = document.querySelector("#darkToggleBtn");
const darkSwitch = document.querySelector("#darkSwitch");
const mask = document.querySelector("#mask");
const body = document.querySelector("body");
const header = document.querySelector("header");

darkToggleBtn.addEventListener("click", () => {
  darkSwitch.classList.toggle("translate-x-8");
  darkSwitch.classList.toggle("bg-yellow-300");
  mask.classList.toggle("opacity-0");
  body.classList.toggle("bg-gray-900");
  body.classList.toggle("text-white");
  header.classList.toggle("invert");
});
