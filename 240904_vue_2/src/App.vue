<script setup>
import { RouterLink, RouterView } from "vue-router";
</script>

<template>
  <header>
    <nav>
      <RouterLink to="/">Home</RouterLink>
      <RouterLink to="/about">About</RouterLink>
      <br />
      <RouterLink
        v-for="i in Array.from({ length: 7 }, (_, i) => i + 1)"
        :to="{ name: `assignment-${i}` }"
        :key="i"
        >과제{{ i }}
      </RouterLink>
    </nav>
  </header>

  <RouterView />
</template>
