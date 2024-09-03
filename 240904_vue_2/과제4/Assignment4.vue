<script setup>
import HomeChild from "@/components/HomeChild.vue";
import { usePersonStore } from "@/stores/person";

const person = usePersonStore();
</script>

<template>
  <h1>과제4 - Person Store</h1>
  <div>{{ person.name }}</div>
  <div>{{ person.age }}</div>
  <button @click="person.decrementAge">나이를 줄이자</button>
  <HomeChild />
</template>
