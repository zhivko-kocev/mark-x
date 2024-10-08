const express = require("express");
const cors = require("cors");
const subjectsRoutes = require("../routes/subjects");

const app = express();

app.use(express.json());
app.use(cors());

app.use((req, res, next) => {
  console.log(req.path, req.method);
  next();
});

app.use("/api/subjects", subjectsRoutes);

module.exports = { app };
