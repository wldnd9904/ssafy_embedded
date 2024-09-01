import { initializeApp } from "./firebaseImports.js";
import { getFirestore } from "./firebaseImports.js";
import { getStorage } from "./firebaseImports.js";

const firebaseConfig = {
  apiKey: "AIzaSyC2vPT5hrDLJc3YgYS_CAotQZMj1BSHa8w",
  authDomain: "ssafy-cafe-2378c.firebaseapp.com",
  projectId: "ssafy-cafe-2378c",
  storageBucket: "ssafy-cafe-2378c.appspot.com",
  messagingSenderId: "440126552696",
  appId: "1:440126552696:web:de8701161a3cd2863fcb8d",
};

// Initialize Firebase
const app = initializeApp(firebaseConfig);
const db = getFirestore(app);
const storage = getStorage();

export { storage, db };
