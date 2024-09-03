<script setup>
import PiniaFriedChicken from "@/components/PiniaFriedChicken.vue";
import { useChickenStore } from "@/stores/chicken";
const chicken = useChickenStore();
</script>

<template>
  <h1>과제6 - Pinia 치킨</h1>
  <div>title: {{ chicken.title }}</div>
  <div>salt: {{ chicken.salt }}</div>
  <PiniaFriedChicken />
</template>
