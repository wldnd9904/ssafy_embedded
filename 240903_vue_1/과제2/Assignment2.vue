<script setup>
import { ref } from "vue";
const numbers = ref([]);
function generateNumbers() {
  const ret = [];
  const visited = Array.from({ length: 46 }, () => false);
  while (ret.length < 6) {
    const num = Math.ceil(Math.random() * 45);
    if (visited[num]) continue;
    visited[num] = true;
    ret.push(num);
  }
  ret.sort((a, b) => a - b);
  numbers.value = ret;
}
generateNumbers();
</script>

<template>
  <h1>과제2 - 로또 번호 생성기</h1>
  <button @click="generateNumbers">번호 생성</button>
  <br />
  <span> {{ numbers }}</span>
</template>
