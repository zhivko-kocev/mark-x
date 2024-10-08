require("dotenv").config();
const { connect } = require("./config/db");
const { app } = require("./config/appConfig");

const port = process.env.PORT;

connect()
  .then(() => {
    app.listen(port, () => {
      console.log(`Server is running on http://localhost:${port}`);
    });
  })
  .catch((error) => {
    console.log("Failed to connect to the database:", error);
  });
