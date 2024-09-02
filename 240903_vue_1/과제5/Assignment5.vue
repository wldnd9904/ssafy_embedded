<script setup>
import { ref } from "vue";
const menus = ref([
  { id: 1, name: "짜장면", price: 6000, isPossible: true },
  { id: 2, name: "짬뽕", price: 7000, isPossible: true },
  { id: 3, name: "탕수육", price: 18000, isPossible: false },
  { id: 4, name: "군만두", price: 5000, isPossible: true },
]);
const filteredMenus = () => menus.value.filter((menu) => menu.isPossible);
const name = ref("");
const price = ref(0);

const appendMenu = () => {
  if (!name.value) return;
  if (!price.value || price.value < 0) return;
  const id = menus.value.reduce((prev, curMenu) => Math.max(prev, curMenu.id), 0);
  const newItem = { id, name: name.value, price: price.value, isPossible: true };
  menus.value = [...menus.value, newItem];
  name.value = "";
  price.value = 0;
  const firstInput = document.querySelector("input");
  firstInput.focus();
};
</script>

<template>
  <h1>과제5 - 북경반점</h1>
  <ul>
    <li v-for="menu in filteredMenus()" :key="menu.id">{{ menu.name }} - {{ menu.price }}</li>
  </ul>
  <form onsubmit="return false;">
    <label>
      <input type="text" v-model="name" placeholder="메뉴 이름" />
      메뉴 이름
    </label>
    <br />
    <label>
      <input type="number" v-model="price" placeholder="가격" />
      가격
    </label>
    <br />
    <button @click="appendMenu">추가</button>
  </form>
</template>
