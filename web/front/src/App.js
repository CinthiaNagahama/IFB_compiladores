import React, { useRef, useState } from "react";
import "./App.css";
import Card from "./components/card";

function App() {
  const [data, setData] = useState("PROGRAM\nBEGIN\n\nEND.");
  const textAreaRef = useRef();

  // React.useEffect(() => {
  //   fetch("/api")
  //     .then((res) => res.json())
  //     .then((data) => setData(data.message));
  // }, []);

  const onChange = (event) => {
    setData(event.target.value);
  };

  const onKeyDown = (event) => {
    if (event.key === "Tab") {
      event.preventDefault();

      // TODO -> Fix tab bug
      const { selectionStart, selectionEnd } = event.target;
      // console.log(selectionStart, selectionEnd);
      setData(data.substring(0, selectionStart) + "\t" + data.substring(selectionEnd));
      textAreaRef.current.selectionStart = textAreaRef.current.selectionEnd = selectionStart + 1;

      // console.log(textAreaRef, data);
    }
  };

  const onSubmit = (event) => {
    event.preventDefault();
    console.log(data);
    // TODO -> Save data as file and call API
  };

  return (
    <div className='flex flex-col h-full v-full'>
      <header className='bg-purple-900 flex flex-col p-5 items-center h-full'>
        <span className='text-white text-3xl font-bold'>Tiny Kiss</span>
      </header>
      <div className='flex p-5'>
        <span className='text-zinc-900'>
          Esse site apresenta um compilador para a linguagem Tiny Kiss feito tendo como base o tutorial
          <a href='https://feliposz.github.io/tutorial-compiladores/'> "Vamos construir um compilador" </a>
          traduzido por Felipo Soranz (2002).
        </span>
      </div>
      <div className='flex flex-row gap-x-3 p-5'>
        <form className='flex flex-col items-center w-1/2 h-96' onSubmit={onSubmit}>
          <label className='bg-purple-900 flex justify-center w-full text-white text-xl font-medium py-1'>
            Entrada
          </label>
          <textarea
            ref={textAreaRef}
            className='bg-zinc-300 border w-full h-4/5 py-1 px-2'
            value={data}
            onChange={onChange}
            onKeyDown={onKeyDown}
          />
          <button className='bg-purple-900 w-1/2 rounded-lg text-white text-xl font-medium py-1 mt-2' type='submit'>
            Compilar
          </button>
        </form>
        <div className='flex flex-col w-1/2 border'>
          <span className='bg-purple-900 flex justify-center text-white text-xl font-medium py-1'>Saída</span>
          <span className='bg-zinc-300 h-full text-zinc-900 p-3 whitespace-pre'>{data}</span>
        </div>
      </div>
      <div className='flex flex-col items-center'>
        <span className='text-purple-900 text-3xl font-bold'>Como codar</span>
        <div className='flex flex-row gap-x-3 mt-8 px-5 w-full'>
          <Card name='Estrutura Base' code={"PROGRAM\nBEGIN\n\nEND."} />
          <Card name='Variáveis' code={"PROGRAM\nVAR a, b;\nBEGIN\na = 2;\nb = a;\nEND."} />
          <Card name='IF' code={"PROGRAM\nVAR a, b;\nBEGIN\na = 2;\nIF a > 0\nb = 10;\nELSE b = 20;\nENDIF\nEND."} />
          <Card name='WHILE' code={"PROGRAM\nVAR a;\nBEGIN\na=0;\nWHILE a < 5\na = a + 1;\nENDWHILE\nEND."} />
        </div>
      </div>
      <footer className='flex flex-col items-center p-5'>
        <span className='text-zinc-900'>Criado por Cinthia M. N. Ungefehr</span>
        <span className='text-zinc-900'>
          Disponível no{" "}
          <a className='text-purple-900' href='https://github.com/CinthiaNagahama/IFB_compiladores/final_project'>
            GitHub
          </a>
        </span>
      </footer>
    </div>
  );
}

export default App;
