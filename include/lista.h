#ifndef LISTA_H
#define LISTA_H

// Estrutura para os doces
typedef struct Doce {
    int id;
    char tipo;       // A cor, se vai ser vermelho, verde(em inglês como: red, green)
    int especial;    // 0 = normal, 1 = especial
} Doce;

// Estrutura do nó da lista encadeada
typedef struct Node {
    Doce doce;
    struct Node* proximo;
} Node;

// Protótipos das funções que iremos usar
Node* criar_doce_node(int id, char tipo);
void inserir_fila_entrada(Node** head, int id, char tipo);
Doce remover_fila_entrada(Node** head);
void preencher_fila_inicial(Node** head, int quantidade);
void imprimir_fila(Node* head);
void liberar_fila(Node** head);

#endif // LISTA_H
