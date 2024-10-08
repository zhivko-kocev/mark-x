const { DataTypes } = require("sequelize");
const { sequelize } = require("../config/db");

const Subject = sequelize.define(
  "Subject",
  {
    Title: {
      type: DataTypes.STRING,
      allowNull: false,
    },
    Code: {
      type: DataTypes.STRING,
      allowNull: false,
    },
    Tests: {
      type: DataTypes.INTEGER,
      allowNull: false,
    },
    Project: {
      type: DataTypes.INTEGER,
      allowNull: false,
    },
    Activities: {
      type: DataTypes.INTEGER,
      allowNull: false,
    },
    Final_Exam: {
      type: DataTypes.INTEGER,
      allowNull: false,
    },
  },
  {
    timestamps: false,
    tableName: "subjects",
  }
);

Subject.removeAttribute("id");

module.exports = Subject;
