# Tiny Compiler

Compilador para a linguagem Tiny feito tendo como base o tutorial [**Vamos construir um compilador**](https://feliposz.github.io/tutorial-compiladores/) traduzido por Felipo Soranz (2002)

## Pilares

- Filosofia KISS (_Keep It Simple, Stupid_): nunca fazer as coisas da forma mais difícil sem uma razão
- Codificação Preguiçosa: “Nunca deixar para amanhã o que pode ser adiado para sempre” (com os créditos para P.J.Plauger)
- Ceticismo: Recusar teimosamente fazer algo apenas por ser a forma como sempre foi feito
- Aceitação de código ineficiente
- Rejeição de limitações arbitrárias

## Sobre a Linguagem

- [BNF](language.bnf) (Bachus-Naur Form)

## Sobre o Compilador

- O compilador foi escrito em linguagem C

## Observação Importante

Código Final Gerado em Assembly para CPUs 80x86 16 bits.

## Utilizando o Compilador

| Comando    | Resultado                                  |
| ---------- | ------------------------------------------ |
| make build | Constrói o binário do compilador           |
| make run   | Executa o arquivo binário                  |
| make clean | Limpa os códigos objeto do diretório build |
