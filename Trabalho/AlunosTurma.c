#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*1) Crie uma estrutura de dados para armazenar informações sobre alunos de uma
turmas Deve-se ter pelo menos as seguintes informações sobre cada aluno:
matrícula, nome e média final. Garanta que a implementação dessa estrutura tenha
pelo menos as seguintes operações: incluir novo aluno, remover um aluno por
matrícula e listar todos os alunos.
OBS: Não é permitido usar uma estrutura de dados já implementada de alguma
biblioteca.*/

#define MAX_ALUNOS 100 // Limite máximo de alunos

typedef struct {
    int matricula;
    char nome[50];
    float media_final;
} Aluno;

// Incluir um novo aluno
void incluir_aluno(Aluno alunos[], int *quantidade) {
    if (*quantidade >= MAX_ALUNOS) {
        printf("Limite de alunos atingido.\n");
        return;
    }

    Aluno novo_aluno;
    printf("Digite a matrícula do aluno: ");
    scanf("%d", &novo_aluno.matricula);
    
    // Verificar se matrícula já existe
    for (int i = 0; i < *quantidade; i++) {
        if (alunos[i].matricula == novo_aluno.matricula) {
            printf("Matrícula já cadastrada.\n");
            return;
        }
    }

    printf("Digite o nome do aluno: ");
    scanf(" %[^\n]s", novo_aluno.nome);  // Leitura de string com espaços
    printf("Digite a média final do aluno: ");
    scanf("%f", &novo_aluno.media_final);

    alunos[*quantidade] = novo_aluno;
    (*quantidade)++;
}

// Função para remover aluno por matrícula
void remover_aluno(Aluno alunos[], int *quantidade, int matricula) {
    for (int i = 0; i < *quantidade; i++) {
        if (alunos[i].matricula == matricula) {
            for (int j = i; j < *quantidade - 1; j++) {
                alunos[j] = alunos[j + 1];
            }
            (*quantidade)--;
            printf("Aluno removido com sucesso.\n");
            return;
        }
    }
    printf("Aluno com matrícula %d não encontrado.\n", matricula);
}

/*2) Inclua uma nova operação na estrutura de dados que tem como funcionalidade
ordenar os alunos por média final. Para isso, você deve usar implementar o algoritmo
de ordenação SelectionSort em forma recursiva.*/

/*3)  Inclua uma nova operação, igual a do item 2, porém ela deve ordenar os alunos
por matrícula.*/

void selection_sort_media(Aluno alunos[], int n, int indice);
void selection_sort_matricula(Aluno alunos[], int n, int indice);

void listar_alunos(Aluno alunos[], int quantidade) {
    if (quantidade == 0) {
        printf("Nenhum aluno cadastrado.\n");
        return;
    }

    int opcao_ordenacao;
    printf("Escolha a ordenação:\n");
    printf("1. Ordenar por matrícula\n");
    printf("2. Ordenar por média final\n");
    printf("Opção: ");
    scanf("%d", &opcao_ordenacao);

    if (opcao_ordenacao == 1) {
        // Ordena por matrícula
        selection_sort_matricula(alunos, quantidade, 0);
    } else if (opcao_ordenacao == 2) {
        // Ordena por média final
        selection_sort_media(alunos, quantidade, 0);
    } else {
        printf("Opção inválida.\n");
        return;
    }

    for (int i = 0; i < quantidade; i++) {
        printf("Matrícula: %d, Nome: %s, Média Final: %.2f\n", alunos[i].matricula, alunos[i].nome, alunos[i].media_final);
    }
}

void selection_sort_media(Aluno alunos[], int n, int indice) {
    if (indice == n - 1) return;

    int maior = indice;  // Mude de 'menor' para 'maior'
    for (int j = indice + 1; j < n; j++) {
        if (alunos[j].media_final > alunos[maior].media_final) { // Troque < por >
            maior = j;
        }
    }
    
    Aluno temp = alunos[indice];
    alunos[indice] = alunos[maior];
    alunos[maior] = temp;

    selection_sort_media(alunos, n, indice + 1);
}

// Algoritmo de ordenação recursiva por matrícula (Selection Sort)
void selection_sort_matricula(Aluno alunos[], int n, int indice) {
    if (indice == n - 1) return;

    int menor = indice;
    for (int j = indice + 1; j < n; j++) {
        if (alunos[j].matricula < alunos[menor].matricula) {
            menor = j;
        }
    }
    
    Aluno temp = alunos[indice];
    alunos[indice] = alunos[menor];
    alunos[menor] = temp;

    selection_sort_matricula(alunos, n, indice + 1);
}

/* 4) Inclua uma nova operação na estrutura de dados que tem como funcionalidade
buscar um aluno através da matrícula. Para isso, você deve implementar o algoritmo
de Busca Binária em forma recursiva. Para que a busca binária funcione, os
elementos devem estar ordenados por matrícula.*/

// Algoritmo de busca binária recursiva por matrícula
int busca_binaria(Aluno alunos[], int matricula, int inicio, int fim) {
    if (inicio > fim) {
        return -1;  // Não encontrado
    }

    int meio = (inicio + fim) / 2;

    if (alunos[meio].matricula == matricula) {
        return meio;  // Encontrado
    } else if (alunos[meio].matricula > matricula) {
        return busca_binaria(alunos, matricula, inicio, meio - 1);
    } else {
        return busca_binaria(alunos, matricula, meio + 1, fim);
    }
}

// Exportar dados de alunos para um arquivo
void exportar_alunos(Aluno alunos[], int quantidade, const char *arquivo) {
    FILE *file = fopen(arquivo, "w");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    for (int i = 0; i < quantidade; i++) {
        fprintf(file, "%d %s %.2f\n", alunos[i].matricula, alunos[i].nome, alunos[i].media_final);
    }

    fclose(file);
    printf("Dados exportados com sucesso.\n");
}

// Importar dados de alunos de um arquivo
void importar_alunos(Aluno alunos[], int *quantidade, const char *arquivo) {
    FILE *file = fopen(arquivo, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }

    while (*quantidade < MAX_ALUNOS && fscanf(file, "%d %[^\n] %f", &alunos[*quantidade].matricula, alunos[*quantidade].nome, &alunos[*quantidade].media_final) != EOF) {
        (*quantidade)++;
    }

    fclose(file);
    printf("Dados importados com sucesso.\n");
}

// Menu interativo
int main() {
    Aluno alunos[MAX_ALUNOS];
    int quantidade = 0;
    int opcao, matricula, indice;

    do {
        printf("\nMenu:\n");
        printf("1. Incluir aluno\n");
        printf("2. Remover aluno\n");
        printf("3. Listar alunos\n");
        printf("4. Buscar aluno por matrícula\n");
        printf("5. Exportar alunos\n");
        printf("6. Importar alunos\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                incluir_aluno(alunos, &quantidade);
                break;
            case 2:
                printf("Digite a matrícula do aluno a remover: ");
                scanf("%d", &matricula);
                remover_aluno(alunos, &quantidade, matricula);
                break;
            case 3:
                listar_alunos(alunos, quantidade);
                break;
            case 4:
                printf("Digite a matrícula do aluno a buscar: ");
                scanf("%d", &matricula);
                selection_sort_matricula(alunos, quantidade, 0); // Garantir que está ordenado
                indice = busca_binaria(alunos, matricula, 0, quantidade - 1);
                if (indice == -1) {
                    printf("Aluno não encontrado.\n");
                } else {
                    printf("Aluno encontrado: Matrícula: %d, Nome: %s, Média Final: %.2f\n", alunos[indice].matricula, alunos[indice].nome, alunos[indice].media_final);
                }
                break;
            case 5:
                exportar_alunos(alunos, quantidade, "alunos.txt");
                break;
            case 6:
                importar_alunos(alunos, &quantidade, "alunos.txt");
                break;
            case 0:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida.\n");
        }
    } while (opcao != 0);

    return 0;
}
