# Jogo Pif (Candy Crush C)

Este projeto é um jogo em C inspirado em mecânicas de combinação de peças semelhantes ao Candy Crush. Ele usa **Raylib** para renderização e estrutura o jogo com matrizes dinâmicas e listas encadeadas.

## Recursos

* Tabuleiro em grade com quedas automáticas e resolução de cascatas.
* Fila de doces de entrada implementada com **lista encadeada**.
* Ranking de pontuações salvo em `scoreboard.txt`.
* Animações de troca e movimento de doces.
* Texturas de doces em `assets/` com fallback colorido quando necessário.

## Estrutura do Projeto

* `src/main.c` - inicialização do jogo, loop principal e lógica de entradas.
* `src/lista.c` - gerenciamento da fila de doces.
* `src/matriz.c` - criação e manipulação do tabuleiro.
* `src/raylib_utils.c` - carregamento de texturas e placeholders.
* `src/render.c` - desenho do tabuleiro, interface e textos.
* `src/score_manager.c` - leitura e gravação de ranking.
* `include/game_constants.h` - constantes de configuração do jogo.
* `include/lista.h` - protótipos e definições da fila encadeada.
* `include/matriz.h` - protótipos de funções de matriz.
* `include/raylib_utils.h` - protótipos de utilitários do Raylib.
* `include/render.h` - protótipos de renderização.
* `include/score_manager.h` - protótipos do gerenciador de pontuações.
* `assets/` - imagens das peças do jogo.
* `scoreboard.txt` - arquivo de ranking de pontuações.

## Requisitos

* `gcc` ou compilador compatível com C.
* Biblioteca `raylib` instalada e acessível no sistema.
* Diretório `assets/` com imagens de doces para o modo gráfico.

## Compilar e Executar

1. Compile o projeto:

```bash
make
```

2. Execute o jogo:

```bash
make run
```

3. Limpe os arquivos gerados:

```bash
make clean
```

## Vídeo do Jogo

* Veja o gameplay em vídeo para entender a mecânica e a interface.
* Link do vídeo:
  https://github.com/user-attachments/assets/1aea6543-84ad-410f-8716-e1abee99418a

## Detalhes Adicionais

* O executável gerado é `candy_crush` ou `candy_crush.exe` no Windows.
* O `Makefile` ajusta automaticamente os flags de link para Windows e Linux.
* Caso as texturas não sejam encontradas, o jogo tenta usar placeholders coloridos para continuar funcionando.

## Controles

* Mouse para selecionar e trocar doces.
* `Enter` para confirmar o nome do jogador na tela inicial.
* `Backspace` para apagar caracteres no nome.
* Feche a janela do jogo para sair.

## Ranking

* O ranking é carregado e salvo em `scoreboard.txt`.
* O jogo suporta até `10` entradas no ranking.
* O arquivo é atualizado sempre que o jogador termina o jogo com uma pontuação válida.
