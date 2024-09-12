import { ref, computed } from "vue";
import { defineStore } from "pinia";
import { getRandomColor } from "@/utils/color";

export const useChartStore = defineStore("chart", () => {
  const chartData = ref({
    // labels: ["January", "February", "March"],
    datasets: [
      {
        label: "A",
        backgroundColor: "blue",
        borderColor: "blue",
        data: [7.179, 8.12, 15.513],
      },
      {
        label: "B",
        backgroundColor: "green",
        borderColor: "green",
        data: [10.179, 2.12, 50.513],
        tension: 0.5,
      },
    ],
  });

  function setChartData(newData) {
    chartData.value = {
      labels: newData[0].data.map((entry) => entry.period),
      datasets: newData.map((data, idx) => {
        const color = getRandomColor();
        return {
          label: data.title,
          data: data.data.map((entry) => entry.ratio),
          backgroundColor: color,
          borderColor: color,
          tension:0.3
        };
      }),
    };
    console.log(chartData.value);
  }

  return { chartData, setChartData };
});
