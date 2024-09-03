<script setup>
const props = defineProps({ titleProp: String, saltProp: Number });
const emit = defineEmits(["emitSalt"]);
function setSalt(newSalt) {
  emit("emitSalt", newSalt);
}
</script>

<template>
  <h3>ChickenChild</h3>
  <div>title: {{ titleProp }}</div>
  <div>salt: {{ saltProp }}</div>
  <button @click="setSalt(10)">싱겁게</button>
</template>

<style scoped></style>
