const Subject = require("../models/Subject");

const getSubjects = async (req, res) => {
  try {
    const subjects = await Subject.findAll();
    res.status(200).json(subjects);
  } catch (error) {
    res.status(400).json({ error: error.message });
  }
};

module.exports = { getSubjects };
