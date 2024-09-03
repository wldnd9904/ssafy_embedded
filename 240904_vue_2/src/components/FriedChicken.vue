<script setup>
import ChickenChild from "./ChickenChild.vue";
const props = defineProps({ titleProp: String, saltProp: Number });
const emit = defineEmits(["emitSalt"]);
function changeSalt(newSalt) {
  emit("emitSalt", newSalt);
}
</script>

<template>
  <h2>FriedChicken</h2>
  <div>title: {{ titleProp }}</div>
  <div>salt: {{ saltProp }}</div>
  <ChickenChild :title-prop="titleProp" :salt-prop="saltProp" @emit-salt="changeSalt" />
</template>

<style scoped></style>
