<script setup>
import { ref } from "vue";
const hello = ref("Hello World!");
const reverseMessage = () => (hello.value = hello.value.split("").reverse().join(""));
const appendExclame = () => (hello.value += "!");
</script>

<template>
  <h1>과제6 - !dlroW olleH</h1>
  <h1>{{ hello }}</h1>
  <button @click="reverseMessage">Reverse Message</button>
  <br />
  <button @click="appendExclame">Append "!"</button>
</template>
