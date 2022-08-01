const express = require("express");
const shell = require("shelljs");
const fs = require("fs");

const PORT = 3001;
const app = express();
app.use(express.json());

app.post("/compiler", (req, res) => {
  try {
    const inputProgram = req.body.code;
    if (!inputProgram) {
      res.status(400).json({ msg: "Insira algum código" });
      return;
    }

    fs.writeFileSync("./in.txt", inputProgram);

    const { code: exitCode } = shell.exec("./compiler/tiny_kiss < in.txt > out.txt");
    if (exitCode != 0) {
      res.status(400).json({ msg: "Não foi possível compilar o programa!" });
      return;
    }

    const compiledProgram = fs.readFileSync("./out.txt").toString();
    // console.log(compiledProgram);

    res.status(200).json({ data: compiledProgram });
  } catch (error) {
    console.log(error);
    res.status(500).json({ msg: error });
  }
});

app.listen(PORT, () => {
  shell.cd("./compiler");
  shell.exec("make clean");
  shell.exec("make build");
  shell.cd("..");

  console.log(`Server listening on ${PORT}`);
});
