<script setup>
import { usePersonStore } from "@/stores/person";
import GrandChild from "./GrandChild.vue";

const person = usePersonStore();

const toggleName = () => {
  if (person.name === "david") person.setName("데이비드");
  else person.setName("david");
};
</script>

<template>
  <h1>Child</h1>
  <div>{{ person.name }}</div>
  <div>{{ person.age }}</div>
  <button @click="toggleName">이름 변경</button>
  <GrandChild />
</template>

<style scoped></style>
