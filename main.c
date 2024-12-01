/*
Disciplina: Linguagem de Programação C

Integrantes:
- João Victor De Andrade Martinho
- Matheus Cavalheiro De Camargo 
- Pedro Henrique Nunes Oliveira
- Pedro Pereira Guaita
- Rafael Ribeiro De Souza Medeiros

Descrição do Problema:
O objetivo deste programa é gerenciar informações de contas e pagadores para uma empresa.
Ele permite o cadastro, listagem, busca de contas e pagadores, além de associar contas
a seus respectivos pagadores. O sistema utiliza vetores, structs e inclui operações com 
persistência de dados em memória.

Descrição do Funcionamento do Algoritmo:
O algoritmo apresenta um menu principal com as seguintes funcionalidades:
1. Cadastro de novos pagadores e contas.
2. Listagem completa de pagadores e contas, incluindo a associação entre eles.
3. Busca de pagadores ou contas pelo ID, exibindo informações detalhadas.
4. Salvar os dados de pagadores e contas em arquivos para garantir persistência.
5. Carregar os dados de pagadores e contas ao iniciar o programa, mantendo as informações 
   entre execuções.

O programa utiliza estruturas de dados `struct` para armazenar informações e verifica relações
de integridade entre contas e pagadores. Após cada operação, o menu é exibido novamente até 
que o usuário escolha a opção de sair.
*/

#include <stdio.h>
#include <string.h>

#define MAX_CONTAS 100
#define MAX_PAGADORES 100

typedef struct {
    int idConta;         // Identificador único da conta
    float valor;         // Valor associado à conta
    char status[20];     // Status (ex.: "Pago", "Pendente")
    char vencimento[10]; // Data de vencimento (ex.: "YYYY-MM-DD")
    int idpagador;       // ID do pagador associado
} Conta;

typedef struct {
    int id;             // Identificador único do pagador
    char nome[50];      // Nome do pagador
    char cpfCnpj[20];   // CPF ou CNPJ do pagador
    char telefone[15];  // Telefone de contato
} Pagador;

// Função para exibir o menu principal
void menu() {
    printf("\nGerenciamento de Contas e Pagadores\n");
    printf("1. Cadastrar Pagador\n");
    printf("2. Cadastrar Conta\n");
    printf("3. Listar Pagadores\n");
    printf("4. Listar Contas\n");
    printf("5. Buscar Pagador por ID\n");
    printf("6. Buscar Conta por ID\n");
    printf("7. Sair\n");
    printf("Escolha uma opção: ");
}

// Função para verificar se um ID de pagador já existe
int verificar_pagador_existente(Pagador *pagadores, int num_pagadores, int id) {
    for (int i = 0; i < num_pagadores; i++) {
        if (pagadores[i].id == id) {
            return 1; // Pagador encontrado
        }
    }
    return 0; // Pagador não encontrado
}

// Função para verificar se um ID de conta já existe
int verificar_conta_existente(Conta *contas, int num_contas, int idConta) {
    for (int i = 0; i < num_contas; i++) {
        if (contas[i].idConta == idConta) {
            return 1; // Conta encontrada
        }
    }
    return 0; // Conta não encontrada
}

// Função para cadastrar um novo pagador
void cadastrar_pagador(Pagador *pagadores, int *num_pagadores) {
    if (*num_pagadores >= MAX_PAGADORES) {
        printf("Limite máximo de pagadores atingido!\n");
        return;
    }

    Pagador novoPagador;
    printf("Digite o ID do pagador: ");
    scanf("%d", &novoPagador.id);

    if (verificar_pagador_existente(pagadores, *num_pagadores, novoPagador.id)) {
        printf("Erro: Já existe um pagador com esse ID.\n");
        return;
    }

    printf("Digite o nome do pagador: ");
    scanf(" %[^\n]", novoPagador.nome);
    printf("Digite o CPF/CNPJ do pagador: ");
    scanf("%s", novoPagador.cpfCnpj);
    printf("Digite o telefone do pagador: ");
    scanf("%s", novoPagador.telefone);

    pagadores[*num_pagadores] = novoPagador;
    (*num_pagadores)++;
    printf("Pagador cadastrado com sucesso!\n");
}

// Função para cadastrar uma nova conta
void cadastrar_conta(Conta *contas, int *num_contas, Pagador *pagadores, int num_pagadores) {
    if (*num_contas >= MAX_CONTAS) {
        printf("Limite máximo de contas atingido!\n");
        return;
    }

    Conta novaConta;
    printf("Digite o ID da conta: ");
    scanf("%d", &novaConta.idConta);

    if (verificar_conta_existente(contas, *num_contas, novaConta.idConta)) {
        printf("Erro: Já existe uma conta com esse ID.\n");
        return;
    }

    printf("Digite o valor da conta: ");
    scanf("%f", &novaConta.valor);
    printf("Digite o status da conta (Pago/Pendente): ");
    scanf("%s", novaConta.status);
    printf("Digite a data de vencimento (YYYY-MM-DD): ");
    scanf("%s", novaConta.vencimento);
    printf("Digite o ID do pagador associado: ");
    scanf("%d", &novaConta.idpagador);

    if (!verificar_pagador_existente(pagadores, num_pagadores, novaConta.idpagador)) {
        printf("Erro: Pagador com ID %d não encontrado.\n", novaConta.idpagador);
        return;
    }

    contas[*num_contas] = novaConta;
    (*num_contas)++;
    printf("Conta cadastrada com sucesso!\n");
}

void salvar_dados(Pagador *pagadores, int num_pagadores, Conta *contas, int num_contas) {
    FILE *arquivo_pagadores = fopen("pagadores.txt", "w");
    FILE *arquivo_contas = fopen("contas.txt", "w");

    if (arquivo_pagadores == NULL || arquivo_contas == NULL) {
        printf("Erro ao abrir os arquivos para salvar os dados!\n");
        return;
    }

    // Salvar pagadores
    for (int i = 0; i < num_pagadores; i++) {
        fprintf(arquivo_pagadores, "ID: %d|Nome:%s|CPF/CNJP: %s|TEL: %s\n",
                pagadores[i].id, pagadores[i].nome, pagadores[i].cpfCnpj, pagadores[i].telefone);
    }

    // Salvar contas
    for (int i = 0; i < num_contas; i++) {
        fprintf(arquivo_contas, "ID: %d|VALOR: %.2f| STATUS: %s| VALIDADE: %s| ID (Padagor):%d\n",
                contas[i].idConta, contas[i].valor, contas[i].status,
                contas[i].vencimento, contas[i].idpagador);
    }

    fclose(arquivo_pagadores);
    fclose(arquivo_contas);

    printf("Dados salvos com sucesso!\n");
}

void carregar_dados(Pagador *pagadores, int *num_pagadores, int max_pagadores,
                    Conta *contas, int *num_contas, int max_contas) {
    // Abrir os arquivos
    FILE *arquivo_pagadores = fopen("pagadores.txt", "r");
    FILE *arquivo_contas = fopen("contas.txt", "r");

    if (arquivo_pagadores == NULL) {
        perror("Erro ao abrir arquivo de pagadores");
    } else {
        *num_pagadores = 0;
        while (*num_pagadores < max_pagadores &&
               fscanf(arquivo_pagadores, "%d|%49[^|]|%19[^|]|%14[^\n]\n",
                      &pagadores[*num_pagadores].id,
                      pagadores[*num_pagadores].nome,
                      pagadores[*num_pagadores].cpfCnpj,
                      pagadores[*num_pagadores].telefone) == 4) {
            (*num_pagadores)++;
                      }
        fclose(arquivo_pagadores);
    }

    if (arquivo_contas == NULL) {
        perror("Erro ao abrir arquivo de contas");
    } else {
        *num_contas = 0;
        while (*num_contas < max_contas &&
               fscanf(arquivo_contas, "%d|%f|%19[^|]|%9[^|]|%d\n",
                      &contas[*num_contas].idConta,
                      &contas[*num_contas].valor,
                      contas[*num_contas].status,
                      contas[*num_contas].vencimento,
                      &contas[*num_contas].idpagador) == 5) {
            (*num_contas)++;
                      }
        fclose(arquivo_contas);
    }

    // Avisos para indicar o número de registros carregados
    printf("Pagadores carregados: %d\n", *num_pagadores);
    printf("Contas carregadas: %d\n", *num_contas);
}

// Função para listar todos os pagadores
void listar_pagadores(Pagador *pagadores, int num_pagadores) {
    printf("\nPagadores cadastrados:\n");
    for (int i = 0; i < num_pagadores; i++) {
        printf("ID: %d | Nome: %s | CPF/CNPJ: %s | Telefone: %s\n",
               pagadores[i].id, pagadores[i].nome, pagadores[i].cpfCnpj, pagadores[i].telefone);
    }
}

// Função para listar todas as contas
void listar_contas(Conta *contas, int num_contas, Pagador *pagadores, int num_pagadores) {
    printf("\nContas cadastradas:\n");
    for (int i = 0; i < num_contas; i++) {
        // Encontra o nome do pagador associado
        char nomePagador[50] = "Desconhecido";
        for (int j = 0; j < num_pagadores; j++) {
            if (pagadores[j].id == contas[i].idpagador) {
                strcpy(nomePagador, pagadores[j].nome);
                break;
            }
        }

        printf("ID Conta: %d | Valor: %.2f | Status: %s | Vencimento: %s | Pagador: %s (ID: %d)\n",
               contas[i].idConta, contas[i].valor, contas[i].status, contas[i].vencimento,
               nomePagador, contas[i].idpagador);
    }
}

// Função para buscar um pagador pelo ID
void buscar_pagador_por_id(Pagador *pagadores, int num_pagadores) {
    int idBusca;
    printf("Digite o ID do pagador que deseja buscar: ");
    scanf("%d", &idBusca);

    for (int i = 0; i < num_pagadores; i++) {
        if (pagadores[i].id == idBusca) {
            printf("\nPagador encontrado!\n");
            printf("ID: %d | Nome: %s | CPF/CNPJ: %s | Telefone: %s\n",
                   pagadores[i].id, pagadores[i].nome, pagadores[i].cpfCnpj, pagadores[i].telefone);
            return;
        }
    }

    printf("\nErro: Nenhum pagador encontrado com o ID %d.\n", idBusca);
}

// Função para buscar uma conta pelo ID
void buscar_conta_por_id(Conta *contas, int num_contas, Pagador *pagadores, int num_pagadores) {
    int idBusca;
    printf("Digite o ID da conta que deseja buscar: ");
    scanf("%d", &idBusca);

    for (int i = 0; i < num_contas; i++) {
        if (contas[i].idConta == idBusca) {
            // Encontra o nome do pagador associado
            char nomePagador[50] = "Desconhecido";
            for (int j = 0; j < num_pagadores; j++) {
                if (pagadores[j].id == contas[i].idpagador) {
                    strcpy(nomePagador, pagadores[j].nome);
                    break;
                }
            }

            printf("\nConta encontrada!\n");
            printf("ID Conta: %d | Valor: %.2f | Status: %s | Vencimento: %s | Pagador: %s (ID: %d)\n",
                   contas[i].idConta, contas[i].valor, contas[i].status, contas[i].vencimento,
                   nomePagador, contas[i].idpagador);
            return;
        }
    }

    printf("\nErro: Nenhuma conta encontrada com o ID %d.\n", idBusca);
}

int main() {
    Conta contas[MAX_CONTAS];
    Pagador pagadores[MAX_PAGADORES];
    int num_contas = 0;
    int num_pagadores = 0;

    // Carregar dados dos arquivos ao iniciar
    carregar_dados(pagadores, &num_pagadores, MAX_PAGADORES, contas, &num_contas, MAX_CONTAS);
    
    int opcao;
    do {
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                cadastrar_pagador(pagadores, &num_pagadores);
                break;

            case 2:
                cadastrar_conta(contas, &num_contas, pagadores, num_pagadores);
                break;

            case 3:
                listar_pagadores(pagadores, num_pagadores);
                break;

            case 4:
                listar_contas(contas, num_contas, pagadores, num_pagadores);
                break;

            case 5:
                buscar_pagador_por_id(pagadores, num_pagadores);
                break;

            case 6:
                buscar_conta_por_id(contas, num_contas, pagadores, num_pagadores);
                break;

            case 7:
                printf("Saindo do programa...\n");
                // Salvar os dados ao sair
                salvar_dados(pagadores, num_pagadores, contas, num_contas);
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 7);

    return 0;
}
