<script setup>
import { RouterLink } from "vue-router";

const postings = [
  { id: 1, title: "즐거운 싸피" },
  { id: 2, title: "vue 할만함?" },
  { id: 500, title: "임베 화이팅" },
];
</script>

<template>
  <h1>과제3 - 게시판</h1>
  <ul>
    <li v-for="posting in postings" :key="posting.id">
      <RouterLink :to="{ name: 'detail', params: { id: posting.id } }">
        {{ posting.title }}
      </RouterLink>
    </li>
  </ul>
</template>
