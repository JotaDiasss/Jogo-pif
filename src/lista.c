#include <stdio.h>
#include <stdlib.h>
#include "../include/lista.h"

// Função para alocar um nó de doce para a lista encadeada
Node* criar_doce_node(int id, char tipo) {
    Node* novo_node = (Node*)malloc(sizeof(Node));
    if (novo_node == NULL) {
        printf("Erro de alocacao de memoria.\n");
        exit(1);
    }
    novo_node->doce.id = id;
    novo_node->doce.tipo = tipo;
    novo_node->doce.especial = 0;
    novo_node->proximo = NULL;
    return novo_node;
}

// Função para inserir um doce no final da fila
void inserir_fila_entrada(Node** head, int id, char tipo) {
    Node* novo = criar_doce_node(id, tipo);
    if (*head == NULL) {
        *head = novo;
    } else {
        Node* atual = *head;
        while (atual->proximo != NULL) {
            atual = atual->proximo;
        }
        atual->proximo = novo;
    }
}

// Remover o doce da frente da fila e retorna seus dados
Doce remover_fila_entrada(Node** head) {
    if (*head == NULL) {
        printf("A fila de doces esta vazia!\n");
        Doce doce_vazio = {-1, ' ', 0};
        return doce_vazio;
    }
    Node* temp = *head;
    Doce doce = temp->doce;
    *head = temp->proximo;
    free(temp); // Libera o nó da lista encadeada
    return doce;
}

// Preenche a fila de entrada com uma quantidade de doces aleatórios
void preencher_fila_inicial(Node** head, int quantidade) {
    char tipos[] = {'R', 'G', 'B', 'Y', 'P'};
    static int proximo_id = 1; // Para manter IDs únicos incrementais
    for (int i = 0; i < quantidade; i++) {
        char tipo_aleatorio = tipos[rand() % 5]; //Verificar se pode utilizar 
        inserir_fila_entrada(head, proximo_id++, tipo_aleatorio);
    }
}

// Exibe a fila encadeada no terminal
void imprimir_fila(Node* head) {
    printf("Fila de Entrada: [");
    Node* atual = head;
    while (atual != NULL) {
        printf("%c", atual->doce.tipo);
        atual = atual->proximo;
        if (atual != NULL) printf(" -> ");
    }
    printf("]\n");
}

// Libera a memória de todos os nós restantes da lista 
void liberar_fila(Node** head) {
    Node* atual = *head;
    while (atual != NULL) {
        Node* temp = atual;
        atual = atual->proximo;
        free(temp);
    }
    *head = NULL;
}
