#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_ITENS 10

// Definição do Enum para os critérios de ordenação conforme o Nível Mestre
typedef enum {
    ORDEM_NOME,
    ORDEM_TIPO,
    ORDEM_PRIORIDADE
} CriterioOrdenacao;

// Struct Item atualizada para o Nível Mestre (com o campo prioridade)
typedef struct {
    char nome[30];
    char tipo[20];
    int quantidade;
    int prioridade; // Valores de 1 a 5
} Item;

// Variáveis globais de controle da mochila
Item mochila[MAX_ITENS];
int numItens = 0;
int comparacoes = 0; // Contador de comparações para análise de desempenho
bool ordenadaPorNome = false; // Controle de estado para a busca binária

// Função para simular a limpeza de tela
void limparTela() {
    for (int i = 0; i < 10; i++) {
        printf("\n");
    }
}

// Função para exibir o menu principal com status de ordenação
void exibirMenu() {
    printf("\n=================================");
    printf("\n   DESAFIO CÓDIGO DA ILHA        ");
    printf("\n   - EDIÇÃO FREE FIRE (MESTRE) - ");
    printf("\n=================================");
    printf("\n1. Adicionar um item");
    printf("\n2. Remover um item");
    printf("\n3. Listar todos os itens");
    printf("\n4. Ordenar os itens por critério");
    printf("\n5. Realizar busca binária por nome");
    printf("\n0. Sair");
    printf("\n---------------------------------");
    printf("\nStatus: Mochila %s ordenada por nome.", ordenadaPorNome ? "ESTÁ" : "NÃO ESTÁ");
    printf("\n=================================");
    printf("\nEscolha uma opção: ");
}

// Função para inserir item na mochila
void inserirItem() {
    if (numItens >= MAX_ITENS) {
        printf("\nA mochila está cheia! Não é possível carregar mais de 10 itens.\n");
        return;
    }

    Item novoItem;
    
    printf("\n--- Cadastrar Novo Componente ---\n");
    printf("Nome do item: ");
    scanf(" %[^\n]s", novoItem.nome);
    
    printf("Tipo (ex: arma, municao, cura): ");
    scanf(" %[^\n]s", novoItem.tipo);
    
    printf("Quantidade: ");
    scanf("%d", &novoItem.quantidade);
    
    do {
        printf("Prioridade (1 a 5 - sendo 5 a mais alta): ");
        scanf("%d", &novoItem.prioridade);
        if (novoItem.prioridade < 1 || novoItem.prioridade > 5) {
            printf("Prioridade inválida! Digite um valor entre 1 e 5.\n");
        }
    } while (novoItem.prioridade < 1 || novoItem.prioridade > 5);

    mochila[numItens] = novoItem;
    numItens++;
    
    // Sempre que insere um novo item, a ordem alfabética pode quebrar
    ordenadaPorNome = false;

    printf("Item '%s' adicionado com sucesso!\n", novoItem.nome);
}

// Função para remover um item pelo nome
void removerItem() {
    if (numItens == 0) {
        printf("\nA mochila está vazia. Nada para remover.\n");
        return;
    }

    char nomeRemover[30];
    printf("\nDigite o nome do item que deseja remover: ");
    scanf(" %[^\n]s", nomeRemover);

    for (int i = 0; i < numItens; i++) {
        if (strcasecmp(mochila[i].nome, nomeRemover) == 0) {
            for (int j = i; j < numItens - 1; j++) {
                mochila[j] = mochila[j + 1];
            }
            numItens--;
            printf("Item '%s' removido com sucesso!\n", nomeRemover);
            
            // Se esvaziar ou sobrar apenas 1 item, tecnicamente continua ordenado
            if (numItens <= 1) ordenadaPorNome = true;
            return;
        }
    }
    printf("Item '%s' não encontrado na mochila.\n", nomeRemover);
}

// Função para listar os itens em formato de tabela
void listarItens() {
    if (numItens == 0) {
        printf("\nA mochila está vazia.\n");
        return;
    }

    printf("\n-------------------------------------------------------------\n");
    printf("%-5s | %-20s | %-15s | %-5s | %-5s\n", "Pos", "Nome", "Tipo", "Qtd", "Prio");
    printf-------------------------------------------------------------\n");
    for (int i = 0; i < numItens; i++) {
        printf("[%02d]  | %-20s | %-15s | %-5d | %-5d\n", 
               i + 1, mochila[i].nome, mochila[i].tipo, mochila[i].quantidade, mochila[i].prioridade);
    }
    printf("-------------------------------------------------------------\n");
}

// Algoritmo Insertion Sort adaptado para múltiplos critérios
void insertionSort(CriterioOrdenacao criterio) {
    comparacoes = 0; // Reinicia o contador para esta ordenação
    
    for (int i = 1; i < numItens; i++) {
        Item chave = mochila[i];
        int j = i - 1;
        bool mover = false;

        while (j >= 0) {
            comparacoes++; // Incrementa cada comparação realizada
            mover = false;

            if (criterio == ORDEM_NOME) {
                if (strcasecmp(mochila[j].nome, chave.nome) > 0) mover = true;
            } else if (criterio == ORDEM_TIPO) {
                if (strcasecmp(mochila[j].tipo, chave.tipo) > 0) mover = true;
            } else if (criterio == ORDEM_PRIORIDADE) {
                // Prioridade mais alta (5) vai para o topo da mochila
                if (mochila[j].prioridade < chave.prioridade) mover = true;
            }

            if (mover) {
                mochila[j + 1] = mochila[j];
                j--;
            } else {
                break;
            }
        }
        mochila[j + 1] = chave;
    }

    if (criterio == ORDEM_NOME) {
        ordenadaPorNome = true;
    } else {
        ordenadaPorNome = false;
    }
}

// Menu secundário para escolher o critério de ordenação
void menuDeOrdenacao() {
    if (numItens <= 1) {
        printf("\nQuantidade de itens insuficiente para ordenar.\n");
        return;
    }

    int escolha;
    printf("\n--- Escolha o Critério de Ordenação ---\n");
    printf("1. Ordenar por Nome (Ordem Alfabética)\n");
    printf("2. Ordenar por Tipo\n");
    printf("3. Ordenar por Prioridade (Mais alta para mais baixa)\n");
    printf("Escolha uma opção: ");
    scanf("%d", &escolha);

    switch (escolha) {
        case 1:
            insertionSort(ORDEM_NOME);
            printf("\nMochila ordenada por NOME com sucesso!\n");
            break;
        case 2:
            insertionSort(ORDEM_TIPO);
            printf("\nMochila ordenada por TIPO com sucesso!\n");
            break;
        case 3:
            insertionSort(ORDEM_PRIORIDADE);
            printf("\nMochila ordenada por PRIORIDADE com sucesso!\n");
            break;
        default:
            printf("\nOpção de ordenação inválida!\n");
            return;
    }

    printf("Quantidade de comparações realizadas: %d\n", comparacoes);
    listarItens();
}

// Busca Binária por Nome (Exigência do Nível Mestre)
void buscaBinariaPorNome() {
    if (numItens == 0) {
        printf("\nA mochila está vazia. Não há nada para buscar.\n");
        return;
    }

    // Validação de pré-requisito obrigatório
    if (!ordenadaPorNome) {
        printf("\n[ERRO] A mochila precisa estar ordenada por NOME para realizar a busca binária.\n");
        printf("Por favor, selecione a opção 4 do menu primeiro e ordene por nome.\n");
        return;
    }

    char nomeBusca[30];
    printf("\n[Busca Binária] Digite o nome do item que deseja buscar: ");
    scanf(" %[^\n]s", nomeBusca);

    int inicio = 0;
    int fim = numItens - 1;
    int meio;

    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        int resultadoComp = strcasecmp(mochila[meio].nome, nomeBusca);

        if (resultadoComp == 0) {
            printf("\nItem Encontrado com Sucesso via Busca Binária!\n");
            printf("Nome: %s\n", mochila[meio].nome);
            printf("Tipo: %s\n", mochila[meio].tipo);
            printf("Quantidade: %d\n", mochila[meio].quantidade);
            printf("Prioridade: %d\n", mochila[meio].prioridade);
            return;
        }
        else if (resultadoComp < 0) {
            inicio = meio + 1;
        }
        else {
            fim = meio - 1;
        }
    }

    printf("\nItem '%s' não foi encontrado na mochila.\n", nomeBusca);
}

// Função Principal
int main() {
    int opcao;

    do {
        exibirMenu();
        
        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida. Por favor, digite um número.\n");
            while (getchar() != '\n');
            opcao = -1;
            continue;
        }

        limparTela();

        switch (opcao) {
            case 1:
                inserirItem();
                break;
            case 2:
                removerItem();
                break;
            case 3:
                listarItens();
                break;
            case 4:
                menuDeOrdenacao();
                break;
            case 5:
                buscaBinariaPorNome();
                break;
            case 0:
                printf("\nFechando inventário. Até a próxima aventura na ilha!\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}