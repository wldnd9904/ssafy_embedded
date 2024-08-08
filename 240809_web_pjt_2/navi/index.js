const timeSpan = document.getElementById("current-time");
let showColon = false;
const updateTime = () => {
  const now = new Date();
  const hour = now.getHours();
  const minuteString = String(now.getMinutes()).padStart(2, "0");

  const AMPM = hour > 12 ? "PM" : "AM";
  const hourString = String(hour % 12).padStart(2, "0");
  timeSpan.textContent = `${hourString}${
    showColon ? ":" : " "
  }${minuteString} ${AMPM}`;
  showColon = !showColon;
};

updateTime();
setInterval(() => {
  updateTime();
}, 500);
