<script setup>
import { ref } from "vue";
import { useCommonStore } from "@/stores/common.js";
import { api } from "@/utils/firebase_api";
import { useRoute, useRouter } from "vue-router";
const route = useRoute();
const router = useRouter();
const common = useCommonStore();

const name = ref("");
const description = ref("");
const file = ref(null);

const foundMenu = ref({});

function onFileChange(e) {
  console.log(e.target.files);
  file.value = e.target.files[0];
}

async function createMenu() {
  console.log(name.value);
  console.log(description.value);
  console.log(file.value);

  if (!name.value || !description.value || !file.value) {
    alert("빈 값이 있습니다.");
    return;
  }
  await api.menus.create(name.value, description.value, file.value);
  alert("메뉴 추가 성공");
  router.push({ name: "menus" });
}

async function updateMenu() {
  await api.menus.update(route.params.id, name.value, description.value);
  alert("메뉴 수정 성공");
  router.push({ name: "menu-detail", params: { id: route.params.id } });
}
async function updateImage() {
  if (!file) return;
  await api.menus.updateImage(foundMenu.value, file.value);
  alert("이미지 수정 성공");
}

function setURL(file) {
  console.log(file);
  const imageURL = URL.createObjectURL(file);
  console.log(imageURL);
  return imageURL;
}
async function getMenu() {
  const result = await api.menus.findOne(route.params.id);
  foundMenu.value = result;
  name.value = result.name;
  description.value = result.description;
  console.log(result);
}
if (route.params.id) {
  common.setTitle("메뉴 수정하기");
  getMenu();
} else {
  common.setTitle("메뉴 추가하기");
}
</script>

<template>
  <div class="flex flex-col border border-black p-4 gap-2 mx-2 my-4">
    <div class="flex gap-1">
      <span>메뉴 이름: </span>
      <input
        class="border border-gray-400 flex-grow rounded-md px-2"
        type="text"
        v-model="name"
      />
    </div>
    <div class="flex gap-1">
      <span>메뉴 설명: </span>
      <input
        class="border border-gray-400 flex-grow rounded-md px-2"
        type="text"
        v-model="description"
      />
    </div>
    <input type="file" @change="onFileChange" />
    <div class="flex mx-auto font-bold">
      <button onclick="history.back();">취소</button>
      <div v-if="route.params.id">
        <button @click="updateMenu">메뉴 수정하기</button>
        <button @click="updateImage">이미지 수정하기</button>
      </div>
      <div v-else>
        <button @click="createMenu">메뉴 추가하기</button>
      </div>
    </div>
  </div>
  <div
    class="w-64 h-64 rounded-xl overflow-hidden mx-auto shadowed"
    v-if="!file && route.params.id"
  >
    <img :src="foundMenu.image_src" />
  </div>
  <div
    class="w-64 h-64 rounded-xl overflow-hidden mx-auto shadowed"
    v-if="file"
  >
    <img :src="setURL(file)" />
  </div>
</template>

<style scoped></style>
