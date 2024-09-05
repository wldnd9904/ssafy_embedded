<script setup>
import { useCommonStore } from "@/stores/common";
import { api } from "@/utils/firebase_api";
import { ref } from "vue";
import { useRouter } from "vue-router";

const common = useCommonStore();
const router = useRouter();

const menus = ref([]);

async function getMenus() {
  const result = await api.menus.findAll();
  console.log(result);
  menus.value = result;
}
getMenus();
function moveDetail(id) {
  router.push({ name: "menu-detail", params: { id: id } });
}
common.setTitle("메뉴 목록");
</script>

<template>
  <RouterLink :to="{ name: 'menu-register' }">
    <button class="w-full">메뉴 추가하기</button>
  </RouterLink>
  <ul>
    <li
      v-for="menu in menus"
      :key="menu.id"
      @click="moveDetail(menu.id)"
      class="cursor-pointer transition-all hover:bg-gray-100"
    >
      <div class="flex border-black border-b-2">
        <div
          class="flex-shrink-0 bg-cover bg-center w-32 min-h-32"
          :style="`background-image:url(${menu.image_src})`"
        ></div>
        <div
          class="flex-grow flex flex-col items-center justify-center gap-2 text-center p-2"
        >
          <span class="text-2xl font-bold">{{ menu.name }}</span>
          <span class="text-balance break-keep">{{ menu.description }}</span>
        </div>
      </div>
    </li>
  </ul>
</template>

<style scoped></style>
