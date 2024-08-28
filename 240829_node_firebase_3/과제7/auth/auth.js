import { auth } from "../app.js";
import {
  signInWithEmailAndPassword,
  createUserWithEmailAndPassword,
  signOut,
} from "https://www.gstatic.com/firebasejs/10.13.0/firebase-auth.js";

async function login(email, password) {
  try {
    const result = await signInWithEmailAndPassword(auth, email, password);
    return result;
  } catch (error) {
    return error.code;
  }
}
async function signup(email, password) {
  try {
    const result = await createUserWithEmailAndPassword(auth, email, password);
    return result;
  } catch (error) {
    return error.code;
  }
}
async function logout() {
  try {
    const result = await signOut(auth);
    return result;
  } catch (error) {
    return error.code;
  }
}

export { login, signup, logout };
