import { ref } from "vue";
import { defineStore } from "pinia";

export const useCommonStore = defineStore("common", () => {
  const title = ref("싸피 카페");
  function setTitle(newTitle) {
    title.value = newTitle;
  }
  return { title, setTitle };
});
