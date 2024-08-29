import { initializeApp } from "https://www.gstatic.com/firebasejs/10.13.1/firebase-app.js";
import {
  getFirestore,
  addDoc,
  collection,
  query,
  getDocs,
  orderBy,
  limit,
  onSnapshot,
} from "https://www.gstatic.com/firebasejs/10.13.1/firebase-firestore.js";

// Your web app's Firebase configuration
const firebaseConfig = {
  apiKey: "AIzaSyDRL7NYCt56rhCdm-pTTwBAlumOezzBo6g",
  authDomain: "ssafy-log.firebaseapp.com",
  projectId: "ssafy-log",
  storageBucket: "ssafy-log.appspot.com",
  messagingSenderId: "791053708266",
  appId: "1:791053708266:web:9a7e543d9c6bb491b62093",
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
const db = getFirestore(app);

const parseLogEntry = (fileName, line) => {
  const parts = line.split(" ");
  if (parts.length < 5) return null;
  return {
    filename: fileName,
    timestamp: `${parts[0]} ${parts[1]} ${parts[2]}`,
    hostname: parts[3],
    log_level: parts[5].split(":")[0],
    message: parts.slice(6).join(" ").replace("\r", ""),
  };
};

const saveLogToFirestore = async (log) => {
  try {
    const docRef = collection(db, "kernel_logs");
    const doc = await addDoc(docRef, log);
    console.log("Log entry added with ID: ", doc.id);
  } catch (error) {
    console.error(error.code);
  }
};

const saveButton = document.querySelector("#saveButton");
saveButton.addEventListener("change", async (e) => {
  console.log(e);
  console.log(e.target.files);
  const file = e.target.files[0];
  const text = await file.text();
  const lines = text.split("\n");
  const logs = lines
    .map((line) => parseLogEntry(file.name, line))
    .filter((log) => log != null);
  await Promise.all(logs.map((log) => saveLogToFirestore(log)));
  console.log("all logs done");
});

const subscribeRealTimeUpdates = () => {
  const collectionRef = collection(db, "kernel_logs");
  const qRecent = query(collectionRef, orderBy("timestamp", "desc"), limit(10));
  const qAll = query(collectionRef, orderBy("timestamp"));
  const kernelLogsContainer = document.querySelector(".kernelLogs");

  const logEntryHtml = (log) => {
    return `
    <div class="log-entry filename">
    ${log.filename}
    </div>
    <div class="log-entry log">
    [ ${log.timestamp} ] ${log.hostname} kernel:
    <span class="${log.log_level.toLowerCase()}">
      ${log.log_level}: ${log.message}
    </span>
    `;
  };
  let unsubscribe;

  const subscribeQuery = (q, pos = "beforeend", autoScroll = true) => {
    if (unsubscribe) unsubscribe();
    unsubscribe = onSnapshot(q, (snapshot) => {
      kernelLogsContainer.innerHTML = "";
      snapshot.forEach((doc) => {
        const logComponent = logEntryHtml(doc.data());
        kernelLogsContainer.insertAdjacentHTML(pos, logComponent);
      });
      if (autoScroll)
        kernelLogsContainer.scrollTo({
          top: kernelLogsContainer.scrollHeight,
          behavior: "smooth", // 부드러운 스크롤 효과를 원하면 이 줄을 포함하세요
        });
      console.log("update");
    });
  };

  subscribeQuery(qAll);

  const allLogsButton = document.querySelector("#allLogsButton");
  allLogsButton.addEventListener("click", () => {
    subscribeQuery(qAll);
    console.log("now subscribing ALL...");
  });
  const recentLogsButton = document.querySelector("#recentLogsButton");
  recentLogsButton.addEventListener("click", () => {
    subscribeQuery(qRecent, "afterbegin", false);
    console.log("now subscribing RECENT...");
  });
};
subscribeRealTimeUpdates();
