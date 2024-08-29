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

const saveLogToFirestore = async (log) => {
  try {
    const docRef = collection(db, "kernel_logs");
    const doc = await addDoc(docRef, log);
    console.log("Log entry added with ID: ", doc.id);
  } catch (error) {
    console.error(error.code);
  }
};

const demoLevels = ["FATAL", "ERROR", "WARNING", "INFO", "DEBUG"];

const demoMessages = [
  "System initialized successfully",
  "Failed to load kernel module",
  "Disk space running low",
  "Network interface up",
  "Kernel panic - not syncing",
  "Process started with PID 1234",
  "Unable to open device",
  "High memory usage detected",
  "USB device connected",
  "System shut down",
  "File system corruption",
  "Network packet loss",
  "CPU usage statistics",
  "Overheating detected",
  "Backup completed successfully",
  "Authentication failure",
  "Service timeout",
  "File access permissions changed",
  "Disk failure",
  "System update applied",
  "System halted",
  "Service unavailable",
  "Disk check completed",
  "Out of memory",
  "Connection timeout",
  "Module not found",
  "Network error",
  "Hardware malfunction",
  "System rebooted",
  "Memory leak detected",
  "System maintenance completed",
  "File not found",
  "Service crash",
  "Backup scheduled",
  "Application crash",
  "File system check complete",
  "Battery level low",
  "Network instability",
  "Configuration updated",
  "Unexpected shutdown",
  "System overload",
  "Log file rotation",
  "Security breach",
  "Process terminated",
  "Service restored",
  "Invalid configuration",
  "Resource allocation",
  "High disk usage",
  "System diagnostics completed",
  "Disk space cleared",
];

const randomLog = () => {
  const level = demoLevels[Math.floor(Math.random() * demoLevels.length)];
  const message = demoMessages[Math.floor(Math.random() * demoMessages.length)];
  return {
    filename: "logger.js",
    timestamp: getFormattedDate(),
    hostname: `host${Math.ceil(Math.random() * 10)}`,
    log_level: level,
    message: message,
  };
};

// 현재 시간을 "Aug 03 03:00:40" 형식으로 출력하는 함수
function getFormattedDate() {
  const now = new Date();

  // 월, 날짜, 시간, 분, 초를 포맷합니다.
  const months = [
    "Jan",
    "Feb",
    "Mar",
    "Apr",
    "May",
    "Jun",
    "Jul",
    "Aug",
    "Sep",
    "Oct",
    "Nov",
    "Dec",
  ];
  const month = months[now.getMonth()]; // 현재 월
  const date = String(now.getDate()).padStart(2, "0"); // 현재 날짜 (2자리로 포맷)
  const hours = String(now.getHours()).padStart(2, "0"); // 현재 시간 (24시간제, 2자리로 포맷)
  const minutes = String(now.getMinutes()).padStart(2, "0"); // 현재 분 (2자리로 포맷)
  const seconds = String(now.getSeconds()).padStart(2, "0"); // 현재 초 (2자리로 포맷)

  return `${month} ${date} ${hours}:${minutes}:${seconds}`;
}

let logger;

const loggerCheckBox = document.querySelector("#logger");
loggerCheckBox.addEventListener("change", (e) => {
  if (e.currentTarget.checked) {
    logger = setInterval(() => {
      saveLogToFirestore(randomLog());
    }, 1200);
  } else {
    clearInterval(logger);
  }
});
