<script setup>
import { ref } from "vue";
const abc = ref("");
</script>

<template>
  <h1>과제3 - ABC</h1>
  <input type="text" v-model="abc" />
  <br />
  <span v-if="['A', 'B', 'C'].includes(abc)">{{ abc }}</span>
  <span v-else>A B C가 아닙니다.</span>
</template>
