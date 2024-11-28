#include <stdio.h>

typedef struct {
    int id;
    char nome[50];
    float saldo;
} Pagador;

typedef struct {
    int pagadorId;
    float valor;
} Conta;

void listarPagadores(Pagador *pagadores, int *ultimoPagadorId) {
    printf("-------- Listar Pagadores --------\n\n");

    for (int c=0; c<=*ultimoPagadorId; c++) {
        printf("%d. %s | Saldo: %.2f;\n", c+1, pagadores[c].nome, pagadores[c].saldo);
    }

    printf("\n");
}

void listarContas(Pagador *pagadores, Conta *contas, int *ultimaContaIndice) {
    printf("-------- Listar Contas --------\n\n");

    if (*ultimaContaIndice==-1) {
        printf("Sem contas a exibir.\n");
    }

    for (int c=0; c<=*ultimaContaIndice; c++) {
        printf("%d Conta - Pagador: %s | Valor: %.2f;\n", c+1, pagadores[contas[c].pagadorId].nome, contas[c].valor);
    }

    printf("\n");
}

void criarPagador(Pagador *pagadores, int *ultimoPagadorId) {
    printf("-------- Criar Pagador --------\n\n");

    // implementar esta função

    *ultimoPagadorId++;

    printf("\n");
}

void criarConta(Pagador *pagadores, Conta *contas, int *ultimaContaIndice) {
    printf("-------- Criar Conta --------\n\n");

    // implementar esta função. Não esquecer de anexar o id do pagador a conta (no campo pagadorId) e subtrair do saldo do pagador o valor da conta

    *ultimaContaIndice++;

    printf("\n");
}

void exibirMenu() {
    printf("1. Listar Pagadores;\n2. Listar Contas;\n3. Criar Novo Pagador;\n4. Criar nova conta;\n5. Sair;\n");
}

void executarTarefaEscolhida(int escolha, Pagador *pagadores, Conta *contas, int *ultimoPagadorId, int *ultimaContaIndice) {
    switch (escolha) {
        case 1:
            listarPagadores(pagadores, ultimoPagadorId);
            break;
        case 2:
            listarContas(pagadores, contas, ultimaContaIndice);
            break;
        case 3:
            criarPagador(pagadores, ultimoPagadorId);
            break;
        case 4:
            criarConta(pagadores, contas, ultimaContaIndice);
            break;
    }
}

int main(void) {
    Pagador pagadores[10] = {{0, "Rafael Medeiros", 1332}, {1, "Matheus Cavalheiro", 1332}};
    Conta contas[30] = {};

    int ultimoPagadorId = 1;        // mantem armazenado qual o id do ultimo pagador. Serve para iterar sobre a struct pagadores mais facilmente
    int ultimaContaIndice = -1;     // mantem armazenado qual o indice baseado em zero da ultima conta, serve para iterar sobre a struct. É -1 pois não há contas

    int escolha = 0;

    do {
        printf("\n");
        exibirMenu();       // exibe menú de opções
        printf("Escolha a opcao: ");
        scanf("%d", &escolha);
        printf("\n");

        executarTarefaEscolhida(escolha, pagadores, contas, &ultimoPagadorId, &ultimaContaIndice);      // executa a função associada a escolha feita pelo usuário
    } while (escolha != 5);

    return 0;
}
