<script setup>
import { usePersonStore } from "@/stores/person";

const person = usePersonStore();
</script>

<template>
  <h2>GrandChild</h2>
  <div>{{ person.name }}</div>
  <button @click="person.setAge(1)">한살로 돌아가자</button>
</template>

<style scoped></style>
