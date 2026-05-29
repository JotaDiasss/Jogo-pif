#include <stdio.h>
#include <stdlib.h>
#include "../include/matriz.h"

Doce** criar_matriz(int linhas, int colunas) {
    Doce **matriz = (Doce **)malloc(linhas * sizeof(Doce *));
    if (matriz == NULL) {
        printf("Erro de alocacao de memoria.\n");
        exit(1);
    }
    for (int i = 0; i < linhas; i++) {
        matriz[i] = (Doce *)malloc(colunas * sizeof(Doce));
        if (matriz[i] == NULL) {
            printf("Erro de alocacao de memoria.\n");
            exit(1);
        }
        // Inicializa cada célula como vazia
        for (int j = 0; j < colunas; j++) {
            matriz[i][j].id = -1;
            matriz[i][j].tipo = ' ';
            matriz[i][j].especial = 0;
        }
    }
    return matriz;
}

// Consome doces da fila de entrada para preencher a matriz
void preencher_matriz(Doce** matriz, int linhas, int colunas, Node** fila) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            Doce d = remover_fila_entrada(fila);
            if (d.id == -1) {
                printf("Fila insuficiente para preencher a matriz!\n");
                return;
            }
            matriz[i][j] = d;
        }
    }
}

// Exibe a matriz no terminal
void imprimir_matriz(Doce** matriz, int linhas, int colunas) {
    printf("\nTabuleiro:\n\n");
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            printf("[%c] ", matriz[i][j].tipo);
        }
        printf("\n");
    }
}

// Libera toda a memória da matriz
void liberar_matriz(Doce** matriz, int linhas) {
    for (int i = 0; i < linhas; i++) {
        free(matriz[i]);   // libera cada linha
    }
    free(matriz);          // libera o array de ponteiros
}

// Função auxiliar para apenas verificar se existe alguma combinação no tabuleiro
// (Retorna 1 se existe, 0 se não existe, sem remover nada)
int tem_combinacao(Doce** matriz, int linhas, int colunas) {
    // Verificação Horizontal
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas - 2; j++) {
            char tipo = matriz[i][j].tipo;
            if (tipo != ' ' && tipo != 0) {
                if (matriz[i][j+1].tipo == tipo && matriz[i][j+2].tipo == tipo) {
                    return 1;
                }
            }
        }
    }
    // Verificação Vertical
    for (int j = 0; j < colunas; j++) {
        for (int i = 0; i < linhas - 2; i++) {
            char tipo = matriz[i][j].tipo;
            if (tipo != ' ' && tipo != 0) {
                if (matriz[i+1][j].tipo == tipo && matriz[i+2][j].tipo == tipo) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

// Troca dois doces de lugar na matriz se forem posições válidas e adjacentes.
// Retorna 1 se a troca foi realizada com sucesso e gerou uma combinação, e 0 caso contrário.
int trocar_doces(Doce** matriz, int linhas, int colunas, int l1, int c1, int l2, int c2) {
    // 1. Verifica limites
    if (l1 < 0 || l1 >= linhas || c1 < 0 || c1 >= colunas ||
        l2 < 0 || l2 >= linhas || c2 < 0 || c2 >= colunas) {
        printf("Posicao fora do tabuleiro!\n");
        return 0;
    }
    
    // 2. Verifica adjacência (apenas horizontal ou vertical, não diagonal)
    int dist_linhas = abs(l1 - l2);
    int dist_colunas = abs(c1 - c2);
    
    if ((dist_linhas == 1 && dist_colunas == 0) || (dist_linhas == 0 && dist_colunas == 1)) {
        // Realiza a troca inicial
        Doce temp = matriz[l1][c1];
        matriz[l1][c1] = matriz[l2][c2];
        matriz[l2][c2] = temp;
        
        // Verifica se a troca gerou pelo menos uma combinação
        if (!tem_combinacao(matriz, linhas, colunas)) {
            // Reverte a troca
            temp = matriz[l1][c1];
            matriz[l1][c1] = matriz[l2][c2];
            matriz[l2][c2] = temp;
            printf("Troca invalida! Nenhum trio formado.\n");
            return 0;
        }
        
        return 1;
    }
    
    printf("Os doces nao sao adjacentes!\n");
    return 0;
}

// Verifica e remove combinacoes de 3 ou mais doces iguais
// Retorna a quantidade de doces removidos
int verificar_combinacoes(Doce** matriz, int linhas, int colunas) {
    int removidos = 0;
    
    // Matriz de marcação para evitar bugs com cruzamentos
    int **para_remover = (int **)malloc(linhas * sizeof(int *));
    for (int i = 0; i < linhas; i++) {
        para_remover[i] = (int *)calloc(colunas, sizeof(int));
    }

    // Verificação Horizontal
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas - 2; j++) {
            char tipo_atual = matriz[i][j].tipo;
            if (tipo_atual != ' ' && tipo_atual != 0) {
                if (matriz[i][j+1].tipo == tipo_atual && matriz[i][j+2].tipo == tipo_atual) {
                    para_remover[i][j] = 1;
                    para_remover[i][j+1] = 1;
                    para_remover[i][j+2] = 1;
                    
                    int k = j + 3;
                    while (k < colunas && matriz[i][k].tipo == tipo_atual) {
                        para_remover[i][k] = 1;
                        k++;
                    }
                }
            }
        }
    }

    // Verificação Vertical
    for (int j = 0; j < colunas; j++) {
        for (int i = 0; i < linhas - 2; i++) {
            char tipo_atual = matriz[i][j].tipo;
            if (tipo_atual != ' ' && tipo_atual != 0) {
                if (matriz[i+1][j].tipo == tipo_atual && matriz[i+2][j].tipo == tipo_atual) {
                    para_remover[i][j] = 1;
                    para_remover[i+1][j] = 1;
                    para_remover[i+2][j] = 1;
                    
                    int k = i + 3;
                    while (k < linhas && matriz[k][j].tipo == tipo_atual) {
                        para_remover[k][j] = 1;
                        k++;
                    }
                }
            }
        }
    }

    // Remoção e contagem
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (para_remover[i][j] == 1) {
                matriz[i][j].tipo = ' ';
                matriz[i][j].id = -1;
                matriz[i][j].especial = 0;
                removidos++;
            }
        }
    }

    // Libera matriz auxiliar
    for (int i = 0; i < linhas; i++) {
        free(para_remover[i]);
    }
    free(para_remover);

    return removidos;
}

// Faz os doces caírem para preencher os espaços vazios deixados pelas combinações
void aplicar_gravidade(Doce** matriz, int linhas, int colunas) {
    for (int j = 0; j < colunas; j++) {
        int linha_escrita = linhas - 1; // Começa da base do tabuleiro
        
        // Puxa todos os doces que não são vazios para o fundo
        for (int i = linhas - 1; i >= 0; i--) {
            if (matriz[i][j].tipo != ' ' && matriz[i][j].tipo != 0) {
                matriz[linha_escrita][j] = matriz[i][j];
                linha_escrita--;
            }
        }
        
        // Preenche o resto (o topo) com espaços vazios
        while (linha_escrita >= 0) {
            matriz[linha_escrita][j].tipo = ' ';
            matriz[linha_escrita][j].id = -1;
            matriz[linha_escrita][j].especial = 0;
            linha_escrita--;
        }
    }
}

// Preenche os espaços vazios do topo com novos doces da fila de entrada
void preencher_espacos_vazios(Doce** matriz, int linhas, int colunas, Node** fila) {
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            if (matriz[i][j].tipo == ' ' || matriz[i][j].tipo == 0) {
                Doce d = remover_fila_entrada(fila);
                
                // Se por acaso a fila secar, vamos reabastecê-la para não quebrar o jogo
                if (d.id == -1) {
                    preencher_fila_inicial(fila, 50);
                    d = remover_fila_entrada(fila);
                }
                
                matriz[i][j] = d;
            }
        }
    }
}

// Cria um ciclo contínuo de remover combinações, aplicar gravidade e preencher o topo
// Retorna a quantidade total de doces estourados na reação em cadeia
int resolver_cascatas(Doce** matriz, int linhas, int colunas, Node** fila) {
    int total_removidos = 0;
    int removidos_agora = 0;
    
    do {
        // Verifica e remove as combinações atuais
        removidos_agora = verificar_combinacoes(matriz, linhas, colunas);
        
        if (removidos_agora > 0) {
            total_removidos += removidos_agora;
            
            // Cai os doces para preencher os buracos
            aplicar_gravidade(matriz, linhas, colunas);
            
            // Puxa novos doces da fila para preencher o topo
            preencher_espacos_vazios(matriz, linhas, colunas, fila);
            
            // O ciclo vai se repetir porque os novos doces podem ter formado novas combinações (cascata)
        }
    } while (removidos_agora > 0);
    
    return total_removidos;
}
