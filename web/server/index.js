const express = require("express");
const shell = require("shelljs");

const PORT = 3001;
const app = express();

// TODO -> Compiler call

app.get("/api", (req, res) => {
  // shell.cd("./compiler");
  // shell.exec("make build");
  res.json({ message: "Hello from server" });
});

app.listen(PORT, () => {
  console.log(`Server listening on ${PORT}`);
});
