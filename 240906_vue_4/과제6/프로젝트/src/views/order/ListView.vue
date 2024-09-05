<script setup>
import { useCommonStore } from "@/stores/common";
import { api } from "@/utils/firebase_api";
import { ref } from "vue";
import { useRouter } from "vue-router";

const common = useCommonStore();
const router = useRouter();

const orders = ref([]);

async function getOrders() {
  const result = await api.orders.findAll();
  console.log(result);
  orders.value = result;
}
getOrders();
function moveDetail(id) {
  router.push({ name: "order-detail", params: { id: id } });
}
common.setTitle("주문 목록");
</script>

<template>
  <RouterLink :to="{ name: 'order-register' }">
    <button class="w-full">주문하기</button>
  </RouterLink>
  <ul>
    <li
      v-for="order in orders"
      :key="order.id"
      @click="moveDetail(order.id)"
      class="cursor-pointer transition-all hover:bg-gray-100"
    >
      <div class="flex border-black border-b-2">
        <div
          class="flex-shrink-0 bg-cover bg-center w-16 min-h-16"
          :style="`background-image:url(${order.image_src})`"
        ></div>
        <div class="flex-grow flex flex-col p-2 overflow-hidden">
          <span class="text-xl font-bold">
            {{ order.menu.name }}
            <span class="text-lg"> {{ order.quantity }}개 </span>
          </span>
          <span class="text-gray-500 text-nowrap text-ellipsis overflow-hidden">
            {{ order.request_detail }}
          </span>
        </div>
        <div>
          <button
            class="border-none hover:opacity-50 text-red-500"
            @click="deleteMenu"
          >
            삭제
          </button>
        </div>
      </div>
    </li>
  </ul>
</template>

<style scoped></style>
