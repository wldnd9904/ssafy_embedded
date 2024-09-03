<script setup>
import { computed, ref } from "vue";
const todos = ref([
  { id: 1, title: "오늘 할 일 만들기", isDone: false },
  { id: 2, title: "내일 할 일 만들기", isDone: false },
  { id: 3, title: "모레 할 일 만들기", isDone: false },
]);
const showDone = ref(true);
const filteredTodos = computed(() =>
  showDone.value ? todos.value : todos.value.filter((todo) => !todo.isDone)
);

const title = ref("");
const appendTodo = () => {
  if (!title.value) return;
  const id =
    todos.value.reduce((prev, curMenu) => Math.max(prev, curMenu.id), 0) + 1;
  const newItem = { id, title: title.value, isDone: false };
  todos.value.push(newItem);
  title.value = "";
};
const toggleIsDone = (id) => {
  const todo = todos.value.find((todo) => todo.id == id);
  todo.isDone = !todo.isDone;
};
const deleteTodo = (id) => {
  todos.value = todos.value.filter((todo) => todo.id != id);
};
const toggleShowDone = () => {
  showDone.value = !showDone.value;
};
const isAllDone = computed(() =>
  todos.value.reduce((prev, cur) => prev & cur.isDone, true)
);
</script>

<template>
  <h1 class="fw-bold">과제7 - Todo List</h1>
  <form class="input-group mb-4" onsubmit="return false">
    <input
      type="text"
      class="form-control"
      v-model="title"
      placeholder="할 일을 입력하세요"
    />
    <button class="btn btn-outline-secondary" @click="appendTodo">추가</button>
  </form>

  <ul v-if="todos.length" class="list-group mb-4">
    <li
      v-for="todo in filteredTodos"
      class="d-flex p-2 gap-2 list-group-item"
      :key="todo.id"
    >
      <input
        type="checkbox"
        :checked="todo.isDone"
        @change="toggleIsDone(todo.id)"
      />
      <span class="flex-grow-1" :class="todo.isDone && 'done'">
        {{ todo.title }}
      </span>
      <button class="btn-close" @click="() => deleteTodo(todo.id)"></button>
    </li>
  </ul>

  <span v-else>할 일이 없습니다.</span>
  <button type="button" class="btn btn-primary mb-4" @click="toggleShowDone">
    {{ showDone ? "완료된 항목 숨기기" : "전체" }}
  </button>

  <p v-if="isAllDone">모든 일을 완료했습니다.</p>
</template>

<style scoped>
.done {
  text-decoration: line-through;
}
</style>
