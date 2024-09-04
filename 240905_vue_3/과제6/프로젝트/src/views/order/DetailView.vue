<script setup>
import { api } from "@/utils/firebase_api";
import { ref } from "vue";
import { useRoute, useRouter } from "vue-router";

const route = useRoute();
const router = useRouter();
console.log(route.params);
const data = ref({});

async function getOrder() {
  const result = await api.orders.findOne(route.params.id);
  console.log(result);
  data.value = result;
}
getOrder();
function moveRegister() {
  router.push({ name: "order-update", params: { id: route.params.id } });
}
async function deleteOrder() {
  const confirmResult = confirm("삭제하시겠습니까?");
  if (!confirmResult) return;
  await api.orders.delete(data.value.id);
  router.push({ name: "orders" });
}
function moveList() {
  router.push({ name: "orders" });
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
    <div class="flex flex-col p-2">
      <span class="text-xl font-bold">{{ data.menu?.name }}</span>
      <span class="break-keep">수량: {{ data.quantity }}개</span>
      <span class="break-keep text-gray-500">{{
        data.request_detail ? `"${data.request_detail}"` : "요청사항 없음"
      }}</span>
      <div class="flex gap-1 justify-end">
        <button
          class="border-none hover:opacity-50 text-blue-500"
          @click="moveRegister"
        >
          수정
        </button>
        <button
          class="border-none hover:opacity-50 text-red-500"
          @click="deleteOrder"
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
