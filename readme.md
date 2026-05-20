# Candy Crush C

Este é um jogo em C inspirado na mecânica básica do Candy Crush. O projeto utiliza uma **lista encadeada** dinâmica para gerenciar a fila de doces de entrada e uma **matriz dinâmica** para o tabuleiro.

## Estrutura do Projeto

O código está dividido nos seguintes arquivos:
*   [main.c]: Ponto de entrada do programa, contendo a lógica de inicialização e controle do tabuleiro do jogo.
*   [lista.h]: Definição das estruturas `Doce` e `Node` (lista encadeada), além dos protótipos das funções de manipulação da fila de doces.
*   [lista.c]: Implementação de todas as funções responsáveis pela gerência da fila de doces (criação, inserção, remoção e desalocação).

## Como Compilar e Executar

Caso você possua um compilador C (como o `gcc`) instalado em seu sistema, siga os passos abaixo no terminal:

1. **Compilar os arquivos:**
   ```bash
   gcc main.c lista.c -o candy_crush.exe
   ```

2. **Executar o jogo:**
   ```bash
   ./candy_crush.exe
   ```