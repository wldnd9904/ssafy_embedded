<script setup>
import { ref } from "vue";
const todos = ref([
  { id: 1, name: "밥먹기" },
  { id: 2, name: "잠자기" },
  { id: 3, name: "코딩하기" },
]);
const name = ref("");

const appendTodo = () => {
  if (!name.value) return;
  const id = todos.value.reduce((prev, curMenu) => Math.max(prev, curMenu.id), 0);
  const newItem = { id, name: name.value };
  todos.value = [...todos.value, newItem];
  name.value = "";
};
const deleteTodo = (id) => {
  todos.value = todos.value.filter((todo) => todo.id != id);
};
</script>

<template>
  <h1>과제7 - Todo List</h1>
  <ul v-if="todos.length">
    <li v-for="todo in todos" :key="todo.id">
      {{ todo.name }} <button @click="() => deleteTodo(todo.id)">X</button>
    </li>
  </ul>
  <span v-else>할 일이 없습니다.</span>
  <form onsubmit="return false">
    <input type="text" v-model="name" />
    <button @click="appendTodo">할 일 추가</button>
  </form>
</template>
