<script setup>
import { ref } from "vue";
import { useCommonStore } from "@/stores/common.js";
import { api } from "@/utils/firebase_api";
import { useRoute, useRouter } from "vue-router";
const route = useRoute();
const router = useRouter();
const common = useCommonStore();
const menus = ref([]);
const menuId = ref("");
const request_detail = ref("");
const quantity = ref(0);

const foundOrder = ref({});
async function getMenus() {
  const result = await api.menus.findAll();
  console.log(result);
  menus.value = result;
}
getMenus();

async function createOrder() {
  console.log(menuId.value);
  console.log(request_detail.value);

  if (!menuId.value || !quantity.value || quantity.value <= 0) {
    alert("빈 값이 있습니다.");
    return;
  }
  await api.orders.create(quantity.value, request_detail.value, menuId.value);
  alert("주문이 접수되었습니다.");
  router.push({ name: "orders" });
}

async function updateOrder() {
  await api.orders.update(
    route.params.id,
    menuId.value,
    quantity.value,
    request_detail.value
  );
  alert("주문 수정 성공");
  router.push({ name: "order-detail", params: { id: route.params.id } });
}

async function getOrder() {
  const result = await api.orders.findOne(route.params.id);
  foundOrder.value = result;
  menuId.value = result.menu.id;
  quantity.value = result.quantity;
  request_detail.value = result.request_detail;
  console.log(result);
}
if (route.params.id) {
  common.setTitle("주문 수정하기");
  getOrder();
} else {
  common.setTitle("주문하기");
}
</script>

<template>
  <div class="flex flex-col border border-black p-4 gap-2 mx-2 my-4">
    <div class="flex gap-1">
      <span>메뉴 선택: </span>
      <select v-model="menuId">
        <option value="" selected>메뉴 선택</option>
        <option v-for="menu in menus" :value="menu.id">{{ menu.name }}</option>
      </select>
    </div>
    <div class="flex gap-1">
      <span>수량: </span>
      <input type="number" v-model="quantity" value="0" />
    </div>
    <div class="flex gap-1">
      <span>요청 사항: </span>
      <input
        class="border border-gray-400 flex-grow rounded-md px-2"
        type="text"
        v-model="request_detail"
      />
    </div>
    <div class="flex mx-auto font-bold">
      <button onclick="history.back();">취소</button>
      <div v-if="route.params.id">
        <button @click="updateOrder">주문 수정하기</button>
      </div>
      <div v-else>
        <button @click="createOrder">주문하기</button>
      </div>
    </div>
  </div>
</template>

<style scoped></style>
