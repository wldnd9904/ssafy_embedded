import { ref } from "vue";
import { defineStore } from "pinia";

export const usePersonStore = defineStore("person", () => {
  const name = ref("david");
  const age = ref(10);
  const decrementAge = () => {
    age.value--;
  };
  const setName = (newName) => {
    name.value = newName;
  };
  const setAge = (newAge) => {
    age.value = newAge;
  };

  return { name, age, decrementAge, setName, setAge };
});
