<script setup>
import { ref } from "vue";
const idInput = ref("");
const pwInput = ref("");
const checkInput = ref(false);
const colorInput = ref("red");
const jobInput = ref("student");
</script>

<template>
  <h1>과제1 - 회원가입</h1>
  <form>
    <input type="text" v-model="idInput" placeholder="아이디" />
    <span> {{ idInput }}</span>
    <br />
    <input type="password" v-model="pwInput" placeholder="비밀번호" />
    <span> {{ pwInput }}</span>
    <br />
    <input type="checkbox" v-model="checkInput" />
    <span> {{ checkInput }}</span>
    <br />
    <br />
    <label> <input type="radio" value="red" v-model="colorInput" /> 빨강 </label>
    <label> <input type="radio" value="blue" v-model="colorInput" /> 파랑 </label>
    <br />
    <span> {{ colorInput }}</span>
    <br />
    <br />
    <label>
      직업
      <select v-model="jobInput">
        <option value="student">학생</option>
        <option value="teacher">강사</option>
        <option value="homeProtector">무직</option>
      </select>
    </label>
    <br />
    <span>{{ jobInput }}</span>
  </form>
</template>
