<script setup>
import LineChart from "@/components/Linechart.vue";
import UserForm from "@/components/UserForm.vue";
import dataLab from "../utils/api.js";
import { useChartStore } from "@/stores/chart.js";
const chartStore = useChartStore();

async function getData() {
  try {
    const response = await dataLab.get();
    chartStore.setChartData(response.data);
    console.log(response.data);
  } catch (error) {
    console.log(error);
  }
}
getData();
</script>

<template>
  <LineChart />
  <UserForm />
</template>
