<script setup>
import { useChickenStore } from "@/stores/chicken";
import PiniaChickenChild from "./PiniaChickenChild.vue";
const chicken = useChickenStore();
</script>

<template>
  <h2>FriedChicken</h2>
  <div>title: {{ chicken.title }}</div>
  <div>salt: {{ chicken.salt }}</div>
  <PiniaChickenChild />
</template>

<style scoped></style>
