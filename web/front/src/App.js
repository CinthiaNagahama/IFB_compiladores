import React, { useRef, useState } from "react";
import "./App.css";
import Card from "./components/card";

function App() {
  const [code, setCode] = useState("PROGRAM\nBEGIN\n\nEND.");
  const [outData, setOutData] = useState(null);
  const textAreaRef = useRef();

  const onChange = (event) => {
    setCode(event.target.value);
  };

  const onKeyDown = (event) => {
    if (event.key === "Tab") {
      event.preventDefault();

      // TODO -> Fix tab bug
      const { selectionStart, selectionEnd } = event.target;
      // console.log(selectionStart, selectionEnd);
      setCode(code.substring(0, selectionStart) + "\t" + code.substring(selectionEnd));
      textAreaRef.current.selectionStart = textAreaRef.current.selectionEnd = selectionStart + 1;

      // console.log(textAreaRef, code);
    }
  };

  const onSubmit = async (event) => {
    event.preventDefault();
    try {
      const res = await fetch("/compiler", {
        method: "POST",
        headers: {
          Accept: "application/json",
          "Content-Type": "application/json",
        },
        body: JSON.stringify({ code: code }),
      });

      if (res.ok) {
        const { data } = await res.json();
        setOutData(data);
        return;
      }

      const { msg } = await res.json();
      setOutData(msg);
      return;
    } catch (error) {
      console.log(error);
    }
  };

  return (
    <div className='flex flex-col h-full v-full'>
      <header className='bg-purple-900 flex flex-col p-5 items-center h-full'>
        <span className='text-white text-3xl font-bold'>Tiny Kiss</span>
      </header>
      <div className='flex p-5'>
        <span className='text-zinc-900'>
          Esse site apresenta um compilador para a linguagem Tiny Kiss desenvolvido tendo como base o tutorial
          <a href='https://feliposz.github.io/tutorial-compiladores/'> "Vamos construir um compilador" </a>
          traduzido por Felipo Soranz (2002).
        </span>
      </div>
      <div className='flex flex-row gap-x-5 p-5 max-h-1/3'>
        <form className='flex flex-col items-center w-1/2' onSubmit={onSubmit}>
          <label className='bg-purple-900 flex justify-center w-full text-white text-xl font-medium py-1'>
            Entrada
          </label>
          <textarea
            ref={textAreaRef}
            className='bg-zinc-300 border w-full h-full py-1 px-2 resize-none'
            value={code}
            onChange={onChange}
            onKeyDown={onKeyDown}
          />
          <button className='bg-purple-900 w-1/2 rounded-lg text-white text-xl font-medium py-1 mt-2' type='submit'>
            Compilar
          </button>
        </form>
        <div className='flex flex-col w-1/2 h-96 border'>
          <span className='bg-purple-900 flex justify-center text-white text-xl font-medium py-1'>Saída</span>
          <span className='bg-zinc-300 h-full text-zinc-900 p-3 whitespace-pre overflow-auto'>{outData}</span>
        </div>
      </div>
      <div className='flex flex-col items-center'>
        <span className='text-purple-900 text-3xl font-bold'>Como codar</span>
        <span className='text-purple-900 text-2xl font-semibold mt-5'>Palavras Reservadas e Operadores</span>
        <div className='flex flex-row gap-x-3 mt-8 px-5 w-full'>
          <Card
            name='Palavras Reservadas'
            code={
              "PROGRAM -> Inicializa um programa\nBEGIN -> Inicia o escopo de código\nEND -> Finaliza o programa\n\nVAR -> Declara uma ou mais variáveis\n\nIF <condição> -> Inicia um bloco condicional\nELSE -> A ação é executada se a condição definida no IF for falsa\nENDIF -> Finaliza um bloco condicional\n\nWHILE <condição> -> Inicializa um laço condicional\nENDWHILE -> Finaliza um laço condicional"
            }
          />
          <Card
            name='Operadores'
            code={
              "+ -> Soma\n- -> Subtração\n* -> Multiplicação\n\\ -> Divisão\n\n!   -> Negação\n|   -> Ou\n~ -> Xor\n& -> E\n\n= -> Igual\n# -> Diferente\n< -> Menor que\n> -> Maior que\n\n; -> Colocado após uma declaração\n. -> Colocado no final do programa"
            }
          />
        </div>
        <span className='text-purple-900 text-2xl font-semibold mt-5'>Exemplos</span>
        <div className='flex flex-row gap-x-3 mt-8 px-5 w-full'>
          <Card name='Estrutura Base' code={"PROGRAM\nBEGIN\n\nEND."} />
          <Card name='Variáveis' code={"PROGRAM\nVAR a, b;\nBEGIN\na = 2;\nb = a;\nEND."} />
          <Card name='IF' code={"PROGRAM\nVAR a, b;\nBEGIN\na = 2;\nIF a > 0\nb = 10;\nELSE b = 20;\nENDIF\nEND."} />
          <Card name='WHILE' code={"PROGRAM\nVAR a;\nBEGIN\na = 0;\nWHILE a < 5\na = a + 1;\nENDWHILE\nEND."} />
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
