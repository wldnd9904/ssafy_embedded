function getWeather() {
  const WEATHER_API_KEY = "595789b0d99f838e9694d37e10370493";
  const city = "Seoul,kr";
  const url = `https://api.openweathermap.org/data/2.5/forecast?q=${city}&appid=${WEATHER_API_KEY}&units=metric&lang=kr`;
  axios
    .get(url)
    .then((response) => {
      const data = response.data;
      const weatherForecastDiv = document.querySelector("#weather-forecast");
      const title = document.querySelector("#title");
      title.textContent = `${city} (${new Date().toLocaleString()} 기준)`;
      weatherForecastDiv.innerHTML = ""; // Clear any existing content
      // Extract weather data for the next 5 days
      const forecastList = data.list
        .filter((item, index) => index % 8 === 0)
        .slice(0, 5);
      forecastList.forEach((item) => {
        const date = new Date(item.dt_txt);
        const options = { weekday: "long", month: "long", day: "numeric" };
        const weatherInfo = `
  <div class="weather-info">
  <h2>${
    date.getDate() == new Date().getDate()
      ? "오늘"
      : date.toLocaleDateString("ko-KR", options)
  }</h2>
  <img src="http://openweathermap.org/img/wn/${
    item.weather[0].icon
  }.png" alt="${item.weather[0].description}">
  <p>${item.weather[0].description}</p>
  <p>온도: ${item.main.temp_max.toFixed(1)}°C</p>
  <p>습도: ${item.main.humidity}%</p>
  <p>바람: ${item.wind.speed} m/s</p>
  </div>
  `;
        weatherForecastDiv.innerHTML += weatherInfo;
      });
    })
    .catch((error) => {
      console.error("날씨 정보를 가져오는 중 오류 발생:", error);
      const weatherForecastDiv = document.querySelector("#weather-forecast");
      weatherForecastDiv.innerHTML = "날씨 정보를 가져오는 중 오류 발생";
    });
}
getWeather();
