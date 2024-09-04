<script setup>
import { RouterLink, RouterView } from "vue-router";
import { useCommonStore } from "@/stores/common.js";
const common = useCommonStore();
</script>

<template>
  <div id="app">
    <header class="app-header">
      <h2>{{ common.title }}</h2>
    </header>
    <main class="app-main">
      <RouterView />
    </main>
    <footer class="app-footer">
      <div class="footer-text">All right reserved</div>
      <RouterLink :to="{ name: 'menus-home' }">관리자페이지(메뉴)</RouterLink>
      <span> | </span>
      <RouterLink :to="{ name: 'home' }">메인페이지(주문)</RouterLink>
    </footer>
  </div>
</template>

<style scoped>
.app-header,
.app-footer {
  border-top: 2px solid grey;
  border-bottom: 2px solid grey;
}
#app {
  display: flex;
  flex-direction: column;
  min-height: 100vh;
}
.app-header,
.app-footer {
  text-align: center;
}
.app-main {
  /* header 와 footer 를 제외하고 늘어남 */
  flex: 1;
}
</style>
