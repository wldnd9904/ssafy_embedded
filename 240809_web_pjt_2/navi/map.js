let container = document.getElementById("map"); //지도를 담을 영역의 DOM 레퍼런스
let mapOption = {
  center: new kakao.maps.LatLng(37.50136, 127.0396),
  level: 2,
  mapTypeId: kakao.maps.MapTypeId.ROADMAP,
};

const map = new kakao.maps.Map(container, mapOption); //지도 생성 및 객체 리턴

async function getData() {
  const REST_API_KEY = "d1e5ca49a30fbc01e74d32fd88a7c409";
  const url = "https://apis-navi.kakaomobility.com/v1/directions";
  const origin = `127.0396, 37.50136`;
  const destination = `127.0396, 36.50136`;
  const headers = {
    Authorization: `KakaoAK ${REST_API_KEY}`,
    "Content-Type": "application/json",
  };

  //필수값 (경도, 위도)
  const queryParams = new URLSearchParams({
    origin,
    destination,
  });

  const requestURL = `${url}?${queryParams}`;
  try {
    const response = await axios.get(requestURL, { headers });
    console.log(response);
  } catch (error) {}
}
getData();

let imageSrc = "./img/building.png";
let imageSize = new kakao.maps.Size(64, 69);
let imageOption = { offset: new kakao.maps.Point(32, 60) };

let initialMarkerImage = new kakao.maps.MarkerImage(
  imageSrc,
  imageSize,
  imageOption
);

let initialMarkerPosition = new kakao.maps.LatLng(37.50136, 127.0396);

let initialMarker = new kakao.maps.Marker({
  image: initialMarkerImage,
  position: initialMarkerPosition,
});

initialMarker.setMap(map);
let initialInfoWindow = new kakao.maps.InfoWindow({
  content: `<div style="width:150px; height:23px; color:gray; font-size: 12px; display:flex; justify-content:center; align-items:center;"><span>역삼 멀티캠퍼스에서 출발</span></div>`,
});
initialInfoWindow.open(map, initialMarker);

// map.js
// 장소 검색 객체를 생성합니다
let ps = new kakao.maps.services.Places();
// 마커 객체를 가지고 있을 배열입니다
let markers = [];
// 전역적으로 사용될 infowindow, ployline( 경로 표시 )
let infowindow = new kakao.maps.InfoWindow();
let polyline = new kakao.maps.Polyline();
// 검색

const searchFunction = function (event, save = true) {
  // Enter  키가 아닌 경우 또는 검색어가 없는 경우에는 함수 실행을 종료합니다 .
  if (event && event.type === "keyup" && event.key !== "Enter") return;
  infowindow.close();
  let keyword = document.querySelector("#search-input").value;
  if (!keyword.trim()) {
    alert("키워드를 입력해주세요!");
    return;
  }
  //   장소검색 객체를 통해 키워드로 장소검색을 요청합니다
  if (save) {
    recentSearchList = [keyword, ...recentSearchList];
    localStorage.setItem("recentSearch", JSON.stringify(recentSearchList));
  }
  ps.keywordSearch(keyword, placesSearchCB);
  infowindow.setMap(null);
  polyline.setMap(null);
};
const recentSearch = localStorage.getItem("recentSearch");
let recentSearchList = recentSearch ? JSON.parse(recentSearch) : [];
console.log(recentSearchList);
const renderSearch = () => {
  let listEl = document.querySelector(".search-results");
  listEl.textContent =
    recentSearchList.length > 0 ? "최근 검색" : "최근 검색 내역이 없습니다.";
  const ul = document.createElement("ul");
  recentSearchList.map((keyword, idx) => {
    const li = document.createElement("li");
    const a = document.createElement("a");
    const x = document.createElement("a");
    x.style.color = "white";
    x.textContent = " x";
    a.textContent = keyword;
    a.addEventListener("click", () => {
      document.querySelector("#search-input").value = keyword;
      searchFunction(null, false);
    });
    x.addEventListener("click", () => {
      recentSearchList = recentSearchList.filter((item, i) => i != idx);
      localStorage.setItem("recentSearch", JSON.stringify(recentSearchList));
      renderSearch();
    });

    li.append(a);
    li.append(x);
    ul.append(li);
  });
  listEl.append(ul);
};
renderSearch();

//   검색 버튼에 클릭 이벤트를 추가합니다
document
  .getElementById("search-button")
  .addEventListener("click", searchFunction);
//   검색 input 엘리먼트에 키보드 이벤트를 추가합니다
document
  .getElementById("search-input")
  .addEventListener("keyup", searchFunction);
//   장소검색이 완료됐을 때 호출되는 콜백함수 입니다
function placesSearchCB(data, status, pagination) {
  if (status === kakao.maps.services.Status.OK) {
    //   검색 결과 목록에 추가합니다
    displayPlaces(data);
  } else {
    alert("검색 결과가 없습니다.");
  }
}
//   검색 결과 목록을 화면에 표시하고, 마커를 추가하는 함수입니다
function displayPlaces(places) {
  let listEl = document.querySelector(".search-results");
  listEl.innerHTML = "";
  //   기존 마커들을 모두 제거합니다
  removeMarkers();
  for (let i = 0; i < places.length; i++) {
    let itemEl = document.createElement("div");
    itemEl.className = "item";
    itemEl.innerHTML = `
    <div class="info">
    <b>${places[i].place_name}</b>
    <br/><br/>
    <span>${places[i].road_address_name}</span>
    <span class="tel">${places[i].phone}</span>
    </div>
    `;
    itemEl.addEventListener("click", function () {
      infowindow.close();
      //   클릭된 장소의 좌표를 지도 중심으로 설정합니다
      let centerPosition = new kakao.maps.LatLng(places[i].y, places[i].x);
      map.setCenter(centerPosition);
      // startNavigation(places[i]);
      infowindow = new kakao.maps.InfoWindow({
        content: `<div style="padding:5px; color:gray;font-size:1.1vw;">${places[i].place_name}</div>`, //인포윈도우에 표시할 내용
      });
      infowindow.open(map, marker);
      getCarDirection(initialMarkerPosition, centerPosition);
    });
    listEl.appendChild(itemEl);
    //마커를 지도에 추가합니다
    // addMarker(new kakao.maps.LatLng(places[i].y, places[i].x));
    let marker = new kakao.maps.Marker({
      position: new kakao.maps.LatLng(places[i].y, places[i].x),
    });
    marker.setMap(map);
    markers.push(marker);
    kakao.maps.event.addListener(marker, "click", function () {
      infowindow.close();
      //클릭된 장소의 좌표를 지도 중심으로 설정합니다
      let centerPosition = new kakao.maps.LatLng(places[i].y, places[i].x);
      map.setCenter(centerPosition);
      infowindow = new kakao.maps.InfoWindow({
        content: `<div style="padding:5px; color:gray;font-size:1.1vw;">${places[i].place_name}</div>`, //인포윈도우에 표시할 내용
      });
      getCarDirection(initialMarkerPosition, centerPosition);
      infowindow.open(map, marker);
    });
  }
}
//지도 위에 표시되고 있는 마커를 모두 제거하는 함수입니다
function removeMarkers() {
  for (let i = 0; i < markers.length; i++) {
    markers[i].setMap(null);
  }
  markers = [];
}

async function getCarDirection(startPosition, destinationPosition) {
  const REST_API_KEY = "d1e5ca49a30fbc01e74d32fd88a7c409";
  // 호출방식의 URL을 입력합니다.
  const url = "https://apis-navi.kakaomobility.com/v1/directions";
  // 출발지(origin), 목적지(destination)의 좌표를 문자열로 변환합니다.
  const origin = `${startPosition.La},${startPosition.Ma}`;
  const destination = `${destinationPosition.La},${destinationPosition.Ma}`;
  // 요청 헤더를 추가합니다.
  const headers = {
    Authorization: `KakaoAK ${REST_API_KEY}`,
    "Content-Type": "application/json",
  };
  // 공식문서 표3의 요청 파라미터에 필수값을 적어줍니다.
  const queryParams = new URLSearchParams({
    origin: origin,
    destination: destination,
  });
  const requestUrl = `${url}?${queryParams}`; // 파라미터까지 포함된 전체 URL
  try {
    const response = await axios.get(requestUrl, { headers: headers });
    if (response.status !== 200) {
      throw new Error(`HTTP error! Status: ${response.status}`);
    }
    const data = response.data;
    console.log("data = ", data);

    const linePath = [];
    data.routes[0].sections[0].roads.forEach((router) => {
      router.vertexes.forEach((vertex, index) => {
        // 인덱스가 짝수일 때만 linePath에 추가하여야 정상적으로 그려짐
        if (index % 2 === 0) {
          linePath.push(
            new kakao.maps.LatLng(
              router.vertexes[index + 1],
              router.vertexes[index]
            )
          );
        }
      });
    });
    polyline.setMap(null);
    polyline = new kakao.maps.Polyline({
      path: linePath,
      strokeWeight: 5,
      strokeColor: "blue",
      strokeOpacity: 0.7,
      strokeStyle: "solid",
    });
    polyline.setMap(map);
    // 거리가 지도 범위보다 크면 자동으로 지도 bound 설정
    let initialInfowindowBounds = new kakao.maps.LatLng(37.50936, 127.0396);
    let bounds = new kakao.maps.LatLngBounds(
      initialInfowindowBounds,
      destinationPosition
    );
    bounds.extend(initialMarkerPosition);
    map.setBounds(bounds);
  } catch (error) {
    console.error("Error:", error);
  }
}
