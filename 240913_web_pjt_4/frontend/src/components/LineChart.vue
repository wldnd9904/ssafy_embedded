<script setup>
import {
  Chart as ChartJS,
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend,
} from "chart.js";
import { Line } from "vue-chartjs";
import { ref } from "vue";
//   import * as chartConfig from './chartConfig.js'

ChartJS.register(
  CategoryScale,
  LinearScale,
  PointElement,
  LineElement,
  Title,
  Tooltip,
  Legend
);

import { useChartStore } from "@/stores/chart.js";
const chartStore = useChartStore();
const chartOptions = ref({ responseive: true });
</script>

<template>
  <Line
    id="my-chart-id"
    :options="chartOptions"
    :data="chartStore.chartData"
  ></Line>
</template>
