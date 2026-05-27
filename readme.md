# Candy Crush C

Este é um jogo em C inspirado na mecânica básica do Candy Crush. O projeto utiliza uma **lista encadeada** dinâmica para gerenciar a fila de doces de entrada e uma **matriz dinâmica** para o tabuleiro.

## Estrutura do Projeto

O código está dividido nos seguintes arquivos:
*   [src/main.c](file:///C:/Users/Estagiario_Gabriel/Jogo-pif/src/main.c): Ponto de entrada do programa, contendo a lógica de inicialização e controle do tabuleiro do jogo.
*   [src/lista.c](file:///C:/Users/Estagiario_Gabriel/Jogo-pif/src/lista.c): Implementação de todas as funções responsáveis pela gerência da fila de doces (criação, inserção, remoção e desalocação).
*   [src/matriz.c](file:///C:/Users/Estagiario_Gabriel/Jogo-pif/src/matriz.c): Implementação das funções de criação, preenchimento, exibição e liberação da matriz.
*   [include/lista.h](file:///C:/Users/Estagiario_Gabriel/Jogo-pif/include/lista.h): Definição das estruturas `Doce` e `Node`, além dos protótipos da fila.
*   [include/matriz.h](file:///C:/Users/Estagiario_Gabriel/Jogo-pif/include/matriz.h): Protótipos das funções da matriz.

## Como Compilar e Executar

Siga os passos abaixo no seu terminal para compilar e executar o projeto com a nova estrutura de pastas:

1.  **Remova os arquivos duplicados da raiz (opcional, mas necessário se houver erro de compilação):**
    Remova `lista.c`, `lista.h`, `main.c`, `matriz.c`, `matriz.h` da raiz (deixe apenas as pastas `src/`, `include/` e o `readme.md`).

2.  **Compilar os arquivos:**
    ```bash
    gcc src/main.c src/lista.c src/matriz.c -Iinclude -o candy_crush.exe
    ```

3.  **Executar o jogo:**
    ```bash
    ./candy_crush.exe
    ```