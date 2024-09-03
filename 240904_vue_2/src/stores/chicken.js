import { ref } from "vue";
import { defineStore } from "pinia";

export const useChickenStore = defineStore("chicken", () => {
  const title = ref("치킨은 맛있다");
  const salt = ref(30);

  const setSalt = (newSalt) => {
    salt.value = newSalt;
  };

  return { title, salt, setSalt };
});
