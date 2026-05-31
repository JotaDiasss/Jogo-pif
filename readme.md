# Candy Crush C

Este é um jogo em C inspirado na mecânica básica do Candy Crush. O projeto utiliza uma **lista encadeada** dinâmica para gerenciar a fila de doces de entrada e uma **matriz dinâmica** para o tabuleiro.

## Estrutura do Projeto

O código está dividido nos seguintes arquivos:
*   `src/main.c`: Ponto de entrada do programa, responsável pelo ciclo principal e inicialização.
*   `src/lista.c`: Implementação das funções da fila de doces.
*   `src/matriz.c`: Implementação das funções da matriz do tabuleiro.
*   `src/raylib_utils.c`: Carregamento e gerenciamento das texturas dos doces.
*   `src/render.c`: Desenho da grade e dos doces na tela.
*   `include/lista.h`: Definição das estruturas `Doce` e `Node`, e protótipos da fila.
*   `include/matriz.h`: Protótipos das funções da matriz.
*   `include/raylib_utils.h`: Protótipos do módulo de Raylib e declaração das texturas.
*   `include/render.h`: Protótipos das funções de renderização.
*   `include/game_constants.h`: Constantes de cores e layout do jogo.
*   `assets/`: Imagens dos doces usadas pelo jogo.

## Como Compilar e Executar

O projeto possui um `Makefile` cross-platform que funciona em Windows e Linux.

1.  **Compilar:**
    ```bash
    make
    ```

2.  **Executar:**
    ```bash
    make run
    ```

3. Jogo:

https://github.com/user-attachments/assets/1aea6543-84ad-410f-8716-e1abee99418a



*  As texturas dos doces devem estar na pasta `assets/` na raiz do projeto.
*  O `Makefile` usa bibliotecas diferentes para Windows e Linux:
   * Windows: `-lopengl32 -lgdi32 -lwinmm -lcomdlg32 -luser32`
   * Linux: `-lraylib -lm -lpthread -ldl -lrt -lX11`
*  O projeto depende da biblioteca `raylib`; certifique-se de que ela esteja instalada e acessível ao compilador.
