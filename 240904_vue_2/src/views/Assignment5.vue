<script setup>
import FriedChicken from "@/components/FriedChicken.vue";
import { ref } from "vue";
const title = ref("치킨은 맛있다");
const salt = ref(30);

function changeSalt(newSalt) {
  salt.value = newSalt;
}
</script>

<template>
  <h1>과제5 - Props/Emit 치킨</h1>
  <div>title: {{ title }}</div>
  <div>salt: {{ salt }}</div>
  <FriedChicken :title-prop="title" :salt-prop="salt" @emit-salt="changeSalt" />
</template>
