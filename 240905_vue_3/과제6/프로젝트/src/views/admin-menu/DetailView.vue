<script setup>
import { api } from "@/utils/firebase_api";
import { ref } from "vue";
import { useRoute, useRouter } from "vue-router";

const route = useRoute();
const router = useRouter();
console.log(route.params);
const data = ref({});

async function getMenu() {
  const result = await api.menus.findOne(route.params.id);
  console.log(result);
  data.value = result;
}
getMenu();
function moveRegister() {
  router.push({ name: "menu-update", params: { id: route.params.id } });
}
async function deleteMenu() {
  const confirmResult = confirm("삭제하시겠습니까?");
  if (!confirmResult) return;
  await api.menus.delete(data.value);
  router.push({ name: "menus" });
}
function moveList() {
  router.push({ name: "menus" });
}
</script>

<template>
  <div class="flex flex-col rounded-2xl" v-if="data">
    <div class="flex flex-col h-48 items-center overflow-hidden relative">
      <img class="h-48 w-48 absolute z-10" :src="data.image_src" />
      <img
        class="w-full blur-md absolute z-0 -translate-y-1/3 scale-110"
        :src="data.image_src"
      />
    </div>
    <div class="flex flex-col gap-2 p-2">
      <span class="text-xl font-bold">{{ data.name }}</span>
      <span class="break-keep">{{ data.description }}</span>
      <div class="flex gap-1 justify-end">
        <button
          class="border-none hover:opacity-50 text-blue-500"
          @click="moveRegister"
        >
          수정
        </button>
        <button
          class="border-none hover:opacity-50 text-red-500"
          @click="deleteMenu"
        >
          삭제
        </button>
        <button class="border-none hover:opacity-50" @click="moveList">
          목록
        </button>
      </div>
    </div>
  </div>
</template>

<style scoped></style>
