<script setup>
import { useChickenStore } from "@/stores/chicken";

const chicken = useChickenStore();
</script>

<template>
  <h3>ChickenChild</h3>
  <div>title: {{ chicken.title }}</div>
  <div>salt: {{ chicken.salt }}</div>
  <button @click="chicken.setSalt(10)">싱겁게</button>
</template>

<style scoped></style>
