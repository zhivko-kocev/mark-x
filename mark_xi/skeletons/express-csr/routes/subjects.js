const express = require("express");
const { getSubjects } = require("../controllers/subjectsController");

const router = express.Router();
const Subject = require("../models/Subject");

router.get("/", getSubjects);

module.exports = router;
