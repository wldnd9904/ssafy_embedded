import { db } from "../app.js";
import {
  collection,
  getDocs,
  orderBy,
  query,
  doc,
  getDoc,
  Timestamp,
  addDoc,
  updateDoc,
  deleteDoc,
} from "https://www.gstatic.com/firebasejs/10.13.0/firebase-firestore.js";

async function getArticles() {
  try {
    const collectionRef = await collection(db, "articles");
    const q = await query(collectionRef, orderBy("createdAt", "desc"));
    const querySnapshot = await getDocs(q);
    console.log(querySnapshot);
    const articles = querySnapshot.docs.map((doc) => ({
      id: doc.id,
      ...doc.data(),
    }));
    return articles;
  } catch (error) {
    return error.code;
  }
}

async function getArticle(id) {
  try {
    const docRef = await doc(db, "articles", id);
    const docSnapshot = await getDoc(docRef);
    if (docSnapshot.exists()) {
      const article = { id: docSnapshot.id, ...docSnapshot.data() };
      return article;
    } else {
      return 404;
    }
  } catch (error) {
    return error.code;
  }
}

export { getArticles, getArticle };
