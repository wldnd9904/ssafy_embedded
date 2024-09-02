<script setup>
import { ref } from "vue";
const num = ref(null);
const answer = Math.ceil(Math.random() * 100);
</script>

<template>
  <h1>과제4 - 1 to 100</h1>
  <input type="number" v-model="num" />
  <br />
  <span v-if="!num">1부터 100 사이의 숫자를 입력하세요.</span>
  <span v-else-if="num < 1 || num > 100">1부터 100 사이의 수가 아닙니다.</span>
  <span v-else-if="num > answer">DOWN</span>
  <span v-else-if="num < answer">UP</span>
  <span v-else="num < answer">정답</span>

  <br />
  <br />
  <br />
  <span>정답: {{ answer }}</span>
</template>
