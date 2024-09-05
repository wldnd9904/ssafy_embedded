// import { initializeApp } from "https://www.gstatic.com/firebasejs/10.12.2/firebase-app.js";
// import {
//   getFirestore,
//   collection,
//   getDocs,
//   getDoc,
//   doc,
//   addDoc,
//   updateDoc,
//   deleteDoc,
// } from "https://www.gstatic.com/firebasejs/10.12.2/firebase-firestore.js";
// import {
//   getStorage,
//   ref,
//   getDownloadURL,
//   uploadBytes,
//   deleteObject,
// } from "https://www.gstatic.com/firebasejs/10.12.2/firebase-storage.js";

// npm i firebase
import { initializeApp } from "firebase/app";
import {
  getFirestore,
  collection,
  getDocs,
  getDoc,
  doc,
  addDoc,
  updateDoc,
  deleteDoc,
} from "firebase/firestore";
import {
  getStorage,
  ref,
  getDownloadURL,
  uploadBytes,
  deleteObject,
} from "firebase/storage";

// 아래를 개인 설정으로 치환하시오
const firebaseConfig = {
  apiKey: "AIzaSyC2vPT5hrDLJc3YgYS_CAotQZMj1BSHa8w",
  authDomain: "ssafy-cafe-2378c.firebaseapp.com",
  projectId: "ssafy-cafe-2378c",
  storageBucket: "ssafy-cafe-2378c.appspot.com",
  messagingSenderId: "440126552696",
  appId: "1:440126552696:web:de8701161a3cd2863fcb8d",
};

const app = initializeApp(firebaseConfig);
const db = getFirestore(app);
const storage = getStorage();

export const api = {
  menus: {
    findAll: async () => {
      try {
        const querySnapshot = await getDocs(collection(db, "menus"));
        const menus = querySnapshot.docs.map((doc) => {
          return { id: doc.id, ...doc.data() };
        });
        const newMenusPending = menus.map(async (menu) => {
          const url = await getDownloadURL(
            ref(storage, `images/${menu.image_file_name}`)
          );
          return {
            ...menu,
            image_src: url,
          };
        });
        const newMenus = await Promise.all(newMenusPending);
        return newMenus;
      } catch (error) {
        return error.code;
      }
    },
    findOne: async (id) => {
      try {
        const docSnapshot = await getDoc(doc(db, "menus", id));
        if (docSnapshot.exists()) {
          const menu = {
            id: docSnapshot.id,
            ...docSnapshot.data(),
          };
          const url = await getDownloadURL(
            ref(storage, `images/${menu.image_file_name}`)
          );
          return {
            ...menu,
            image_src: url,
          };
        } else {
          return 404;
        }
      } catch (error) {
        return error.code;
      }
    },
    create: async (name, description, file) => {
      const timestamp = Date.now();
      const newFileName = `${timestamp}_${file.name}`;

      const newMenu = {
        name: name,
        description: description,
        image_file_name: newFileName,
      };

      try {
        await addDoc(collection(db, "menus"), newMenu);
        await uploadBytes(ref(storage, `images/${newFileName}`), file);
      } catch (error) {
        return error.code;
      }
    },
    update: async (id, newName, newDescription) => {
      const newMenu = {
        name: newName,
        description: newDescription,
      };
      try {
        await updateDoc(doc(db, "menus", id), newMenu);
      } catch (error) {
        return error.code;
      }
    },
    updateImage: async (originalMenu, newFile) => {
      const timestamp = Date.now();
      const newFileName = `${timestamp}_${newFile.name}`;

      const newMenu = {
        name: originalMenu.name,
        description: originalMenu.description,
        image_file_name: newFileName,
      };
      try {
        await updateDoc(doc(db, "menus", originalMenu.id), newMenu);
        await deleteObject(
          ref(storage, `images/${originalMenu.image_file_name}`)
        );
        await uploadBytes(ref(storage, `images/${newFileName}`), newFile);
      } catch (error) {
        return error.code;
      }
    },
    delete: async (originalMenu) => {
      try {
        await deleteObject(
          ref(storage, `images/${originalMenu.image_file_name}`)
        );
        await deleteDoc(doc(db, "menus", originalMenu.id));
      } catch (error) {
        return error.code;
      }
    },
  },
  orders: {
    findAll: async () => {
      try {
        const querySnapshot = await getDocs(collection(db, "orders"));
        const ordersPending = querySnapshot.docs.map(async (doc) => {
          const menuRef = doc.data().menu_id;
          const menuDoc = await getDoc(menuRef);
          const menuData = menuDoc.data();
          const imageSrc = await getDownloadURL(
            ref(storage, `images/${menuData.image_file_name}`)
          );
          return {
            id: doc.id,
            ...doc.data(),
            menu: menuData,
            image_src: imageSrc,
          };
        });
        const orders = await Promise.all(ordersPending);
        return orders;
      } catch (error) {
        return error.code;
      }
    },
    findOne: async (id) => {
      try {
        const docSnapshot = await getDoc(doc(db, "orders", id));
        if (docSnapshot.exists()) {
          const menuRef = docSnapshot.data().menu_id;
          const menuDoc = await getDoc(menuRef);
          const menuData = menuDoc.data();
          const imageSrc = await getDownloadURL(
            ref(storage, `images/${menuData.image_file_name}`)
          );
          const order = {
            id: docSnapshot.id,
            ...docSnapshot.data(),
            image_src: imageSrc,
            menu: { id: menuRef.id, ...menuData },
          };
          return order;
        } else {
          return 404;
        }
      } catch (error) {
        return error.code;
      }
    },
    create: async (quantity, request_detail, menu_id) => {
      const newOrder = {
        quantity: quantity,
        request_detail: request_detail,
        menu_id: doc(db, "menus", menu_id),
      };

      try {
        await addDoc(collection(db, "orders"), newOrder);
      } catch (error) {
        return error.code;
      }
    },
    update: async (id, menu_id, quantity, request_detail) => {
      const newOrder = {
        menu_id: doc(db, "menus", menu_id),
        quantity: quantity,
        request_detail: request_detail,
      };
      try {
        await updateDoc(doc(db, "orders", id), newOrder);
      } catch (error) {
        return error.code;
      }
    },
    delete: async (id) => {
      try {
        await deleteDoc(doc(db, "orders", id));
      } catch (error) {
        return error.code;
      }
    },
  },
};
