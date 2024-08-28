// Import the functions you need from the SDKs you need
import { initializeApp } from "https://www.gstatic.com/firebasejs/10.13.0/firebase-app.js";
import { getFirestore } from "https://www.gstatic.com/firebasejs/10.13.0/firebase-firestore.js";
import { getAuth } from "https://www.gstatic.com/firebasejs/10.13.0/firebase-auth.js";
// TODO: Add SDKs for Firebase products that you want to use
// https://firebase.google.com/docs/web/setup#available-libraries

// Your web app's Firebase configuration
const firebaseConfig = {
  apiKey: "AIzaSyDyXahOAj1XNPLMCd-sFmaiO43SQ8QkmaM",
  authDomain: "ssafy-practice-40ff4.firebaseapp.com",
  projectId: "ssafy-practice-40ff4",
  storageBucket: "ssafy-practice-40ff4.appspot.com",
  messagingSenderId: "1097846263876",
  appId: "1:1097846263876:web:cbb33e263742d26e92ec11",
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
const db = getFirestore(app);
const auth = getAuth(app);

export { db, auth };
