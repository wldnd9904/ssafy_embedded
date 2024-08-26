const express = require("express");
const morgan = require("morgan");

const app = express();
const PORT = 8080;
app.use(express.json());
app.use(morgan("dev"));

const infos = [
  { name: "나나", age: 12 },
  { name: "유진", age: 8 },
  { name: "재범", age: 40 },
];

app.get("/api/info/names", (_req, res) => {
  try {
    const nameList = infos.map((item) => item.name);
    return res.json(nameList);
  } catch (error) {
    return res.json(error);
  }
});

app.get("/api/info/ages", (_req, res) => {
  try {
    const ageList = infos.map((item) => item.age);
    return res.json(ageList);
  } catch (error) {
    return res.json(error);
  }
});

app.get("/api/info/:id", (req, res) => {
  try {
    if (req.params.id >= infos.length) throw Error("없는 id입니다.");
    const info = infos[req.params.id];
    return res.json(info);
  } catch (error) {
    return res.json(error);
  }
});

app.listen(PORT, () => console.log(`this application is running in ${PORT}`));
