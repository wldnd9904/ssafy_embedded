const { createPool } = require("mysql2/promise");
const express = require("express");
const morgan = require("morgan");

const pool = createPool({
  host: "localhost",
  user: "root",
  password: "root",
  database: "ssafy",
  waitForConnections: true,
  connectionLimit: 10,
  queueLimit: 0,
});
const PORT = 8080;
const app = express();

app.use(express.json());
app.use(morgan("dev"));

const todoColumList = ["title", "is_completed", "author"];

// GET /api/todos - 모든 할 일 조회
app.get("/api/todos", async (_req, res) => {
  try {
    const data = await pool.query("select * from todos");
    if (!data[0]) throw Error("데이터 없음");
    return res.json(data[0]);
  } catch (error) {
    return res.json(error.message);
  }
});
// GET /api/todos/:id - id에 해당하는 할 일 조회
app.get("/api/todos/:id", async (req, res) => {
  try {
    const data = await pool.query("select * from todos where todo_id = ?", [
      req.params.id,
    ]);
    if (!data[0] || !data[0].length) throw Error("데이터 없음");
    return res.json(data[0][0]);
  } catch (error) {
    return res.json(error.message);
  }
});

// POST /api/todos - 할 일 생성
app.post("/api/todos", async (req, res) => {
  try {
    for (const column of todoColumList)
      if (req.body[column] == undefined) throw Error(`${column} 필드 없음`);

    const newTodoData = todoColumList.map((column) => req.body[column]);
    const _data = await pool.query(
      "insert into todos (title, is_completed, author) values (?, ?, ?)",
      newTodoData
    );
    return res.json("할 일 추가 성공");
  } catch (error) {
    return res.json(error.message);
  }
});

// PATCH /api/todos/:id - id에 해당하는 할 일 수정
app.patch("/api/todos/:id", async (req, res) => {
  try {
    for (const column of todoColumList)
      if (req.body[column] == undefined) throw Error(`${column} 필드 없음`);
    const newTodoData = todoColumList.map((column) => req.body[column]);
    const _data = await pool.query(
      "UPDATE todos SET title = ?, is_completed = ?, author = ? where todo_id = ?",
      [...newTodoData, req.params.id]
    );
    return res.json("할 일 수정 성공");
  } catch (error) {
    return res.json(error.message);
  }
});

// DELETE /api/todos/:id - id에 해당하는 할 일 삭제
app.delete("/api/todos/:id", async (req, res) => {
  try {
    const _data = await pool.query("delete from todos where todo_id = ?", [
      req.params.id,
    ]);
    return res.json("삭제 성공");
  } catch (error) {
    return res.json(error.message);
  }
});

// GET /api/author/:name - 작성자에 해당하는 할 일만 출력
app.get("/api/author/:name", async (req, res) => {
  try {
    const data = await pool.query("select * from todos where author = ?", [
      req.params.name,
    ]);
    if (!data[0]) throw Error("데이터 없음");
    return res.json(data[0]);
  } catch (error) {
    return res.json(error.message);
  }
});

app.listen(PORT, () => console.log(`${PORT} 서버 기동중...`));
