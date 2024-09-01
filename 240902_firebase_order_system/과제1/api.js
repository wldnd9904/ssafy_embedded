import { collection, getDocs, getDoc, addDoc } from "../firebaseImports.js";
import { doc, updateDoc, uploadBytes, deleteDoc } from "../firebaseImports.js";
import { getDownloadURL, ref, deleteObject } from "../firebaseImports.js";
import { db, storage } from "../app.js";

const findAllMenus = async () => {
  try {
    const querySnapshot = await getDocs(collection(db, "menus"));
    const menus = querySnapshot.docs.map((doc) => ({
      id: doc.id,
      ...doc.data(),
    }));
    const menusImageURLPending = menus.map(async (menu) => {
      const url = await getDownloadURL(
        ref(storage, `images/${menu.image_file_name}`)
      );
      return {
        ...menu,
        image_src: url,
      };
    });
    const menusWithImageURL = await Promise.all(menusImageURLPending);
    return menusWithImageURL;
  } catch (error) {
    return error.code;
  }
};

const findOneMenu = async (id) => {
  try {
    const docSnapshot = await getDoc(doc(db, "menus", id));
    if (!docSnapshot.exists()) return 404;
    const menu = {
      id: docSnapshot.id,
      ...docSnapshot.data(),
    };
    const url = await getDownloadURL(
      ref(storage, `images/${menu.image_file_name}`)
    );
    const menuWithImageURL = {
      ...menu,
      image_src: url,
    };
    return menuWithImageURL;
  } catch (error) {
    return error.code;
  }
};

const createMenu = async (name, description, file) => {
  const timestamp = Date.now();
  const newFileName = `${timestamp}_${file.name}`;
  const newMenu = {
    name,
    description,
    image_file_name: newFileName,
  };
  try {
    await addDoc(collection(db, "menus"), newMenu);
    return await uploadBytes(ref(storage, `images/${newFileName}`), file);
  } catch (error) {
    return error.code;
  }
};

const updateMenu = async (id, name, description) => {
  const newMenu = {
    name,
    description,
  };
  try {
    return await updateDoc(doc(db, "menus", id), newMenu);
  } catch (error) {
    return error.code;
  }
};

const updateMenuImage = async (menu, file) => {
  const timestamp = Date.now();
  const newFileName = `${timestamp}_${file.name}`;
  const newMenu = {
    name: menu.name,
    description: menu.description,
    image_file_name: newFileName,
  };
  try {
    await updateDoc(doc(db, "menus", menu.id), newMenu);
    await deleteObject(ref(storage, `images/${menu.image_file_name}`));
    return await uploadBytes(ref(storage, `images/${newFileName}`), file);
  } catch (error) {
    return error.code;
  }
};

const deleteMenu = async (menu) => {
  try {
    await deleteObject(ref(storage, `images/${menu.image_file_name}`));
    return await deleteDoc(doc(db, "menus", menu.id));
  } catch (error) {
    return error.code;
  }
};

const findAllOrders = async () => {
  try {
    const querySnapshot = await getDocs(collection(db, "orders"));
    const orders = querySnapshot.docs.map((doc) => ({
      id: doc.id,
      ...doc.data(),
    }));
    const ordersWithMenuPending = orders.map(async (order) => {
      const menuRef = await getDoc(order.menu_id);
      return {
        ...order,
        menu: menuRef.data(),
        menu_id: { id: menuRef.id },
      };
    });
    const ordersWithMenu = await Promise.all(ordersWithMenuPending);
    return ordersWithMenu;
  } catch (error) {
    return error.code;
  }
};
const findOneOrder = async () => {};
const createOrder = async () => {};
const updateOrder = async () => {};
const deleteOrder = async () => {};

export const api = {
  menus: {
    findAll: findAllMenus,
    findOne: findOneMenu,
    create: createMenu,
    update: updateMenu,
    updateImage: updateMenuImage,
    delete: deleteMenu,
  },
  orders: {
    findAll: findAllOrders,
    findOne: findOneOrder,
    create: createOrder,
    update: updateOrder,
    delete: deleteOrder,
  },
};

export default api;
