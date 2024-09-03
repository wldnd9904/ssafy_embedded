<script setup>
import { RouterLink } from "vue-router";
</script>

<template>
  <h1>Board</h1>
  <nav>
    <RouterLink :to="{ name: 'assignment-2' }">과제2로 돌아가기</RouterLink>
  </nav>
</template>
