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

async function createArticle(title, content) {
  try {
    const timestamp = Timestamp.fromDate(new Date());
    const newArticle = {
      title: title,
      content: content,
      createdAt: timestamp,
      updatedAt: timestamp,
    };
    const docRef = await addDoc(collection(db, "articles"), newArticle);
    return docRef.id;
  } catch (error) {
    return error.code;
  }
}

async function updateArticle(id, title, content) {
  try {
    const timestamp = Timestamp.fromDate(new Date());
    const newArticle = {
      title: title,
      content: content,
      updatedAt: timestamp,
    };
    await updateDoc(doc(db, "articles", id), newArticle);
    return id;
  } catch (error) {
    return error.code;
  }
}
async function deleteArticle(id) {
  try {
    await deleteDoc(doc(db, "articles", id));
    return id;
  } catch (error) {
    return error.code;
  }
}

export { getArticles, getArticle, createArticle, updateArticle, deleteArticle };
