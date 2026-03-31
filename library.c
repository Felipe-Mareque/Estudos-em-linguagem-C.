#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura do livro
typedef struct biblioteca {
    char titulos[80];
    char autores[50];
    char codigos[20];
    int anos;
    struct biblioteca *prox;
} biblioteca;

// Protótipos das funções
void criarlista(biblioteca **lista, biblioteca *novo);
void mostrarlivros(biblioteca **lista);
void buscarlivros(biblioteca **lista, char *string);
void editarlivro(biblioteca **lista, char *string);
void excluirlivro(biblioteca **lista, char *string);
void inserirLivros(biblioteca **lista);
void exportarLivros(biblioteca **lista);
void freeLista(biblioteca **lista);

int main() {
    biblioteca *lista = NULL;
    char string[80];
    int opcao;

    // Tenta abrir o catálogo inicial para carregar os dados
    FILE *arq = fopen("catalogo_inicial.txt", "r");
    if (arq != NULL) {
        char linha[300];
        while (fgets(linha, sizeof(linha), arq) != NULL) {
            biblioteca *novo = malloc(sizeof(biblioteca));
            if (novo == NULL) break;
            novo->prox = NULL;

            // Remove quebras de linha
            linha[strcspn(linha, "\r\n")] = '\0';

            char *token = strtok(linha, "|");
            if (token) strcpy(novo->titulos, token);
            
            token = strtok(NULL, "|");
            if (token) strcpy(novo->autores, token);
            
            token = strtok(NULL, "|");
            if (token) strcpy(novo->codigos, token);
            
            token = strtok(NULL, "|");
            if (token) novo->anos = atoi(token);

            criarlista(&lista, novo);
        }
        fclose(arq);
    }

    // Loop do Menu
    do {
        printf("\n--- SGB - Gerenciamento de Biblioteca ---\n");
        printf("1. Inserir Livro\n");
        printf("2. Listar Livros\n");
        printf("3. Buscar por Titulo\n");
        printf("4. Editar Livro\n");
        printf("5. Excluir Livro\n");
        printf("6. Exportar Catalogo\n");
        printf("7. Sair\n");
        printf("----------------------------------------\n");
        printf("Opcao: ");
        
        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n'); // Limpa buffer em caso de erro
            continue;
        }
        getchar(); // Consome o '\n' deixado pelo scanf

        switch (opcao) {
            case 1:
                inserirLivros(&lista);
                break;
            case 2:
                mostrarlivros(&lista);
                break;
            case 3:
                printf("Titulo para busca: ");
                fgets(string, sizeof(string), stdin);
                string[strcspn(string, "\n")] = '\0';
                buscarlivros(&lista, string);
                break;
            case 4:
                printf("Titulo para editar: ");
                fgets(string, sizeof(string), stdin);
                string[strcspn(string, "\n")] = '\0';
                editarlivro(&lista, string);
                break;
            case 5:
                printf("Titulo para excluir: ");
                fgets(string, sizeof(string), stdin);
                string[strcspn(string, "\n")] = '\0';
                excluirlivro(&lista, string);
                break;
            case 6:
                exportarLivros(&lista);
                break;
            case 7:
                freeLista(&lista);
                break;
        }
    } while (opcao != 7);

    return 0;
}

// Implementação das Funções

void criarlista(biblioteca **lista, biblioteca *novo) {
    novo->prox = *lista;
    *lista = novo;
}

void inserirLivros(biblioteca **lista) {
    biblioteca *novo = malloc(sizeof(biblioteca));
    if (novo == NULL) return;

    printf("Titulo: ");
    fgets(novo->titulos, 80, stdin);
    novo->titulos[strcspn(novo->titulos, "\n")] = '\0';

    printf("Autor: ");
    fgets(novo->autores, 50, stdin);
    novo->autores[strcspn(novo->autores, "\n")] = '\0';

    printf("Codigo: ");
    fgets(novo->codigos, 20, stdin);
    novo->codigos[strcspn(novo->codigos, "\n")] = '\0';

    printf("Ano: ");
    scanf("%d", &novo->anos);
    getchar();

    criarlista(lista, novo);
    printf("Livro inserido com sucesso.\n");
}

void mostrarlivros(biblioteca **lista) {
    biblioteca *aux = *lista;
    if (aux == NULL) {
        printf("A biblioteca esta vazia.\n");
        return;
    }
    while (aux != NULL) {
        printf("[%s] %s - %s (%d)\n", aux->codigos, aux->titulos, aux->autores, aux->anos);
        aux = aux->prox;
    }
}

void buscarlivros(biblioteca **lista, char *string) {
    biblioteca *aux = *lista;
    while (aux != NULL) {
        if (strcmp(aux->titulos, string) == 0) {
            printf("Encontrado: %s | %s | %s | %d\n", aux->titulos, aux->autores, aux->codigos, aux->anos);
            return;
        }
        aux = aux->prox;
    }
    printf("Título não encontrado\n");
}

void editarlivro(biblioteca **lista, char *string) {
    biblioteca *aux = *lista;
    while (aux != NULL && strcmp(aux->titulos, string) != 0) {
        aux = aux->prox;
    }

    if (aux == NULL) {
        printf("Título não encontrado\n");
        return;
    }

    int op;
    printf("Alterar: 1.Titulo, 2.Autor, 3.Codigo, 4.Ano: ");
    scanf("%d", &op);
    getchar();

    switch (op) {
        case 1:
            printf("Novo Titulo: ");
            fgets(aux->titulos, 80, stdin);
            aux->titulos[strcspn(aux->titulos, "\n")] = '\0';
            break;
        case 2:
            printf("Novo Autor: ");
            fgets(aux->autores, 50, stdin);
            aux->autores[strcspn(aux->autores, "\n")] = '\0';
            break;
        case 3:
            printf("Novo Codigo: ");
            fgets(aux->codigos, 20, stdin);
            aux->codigos[strcspn(aux->codigos, "\n")] = '\0';
            break;
        case 4:
            printf("Novo Ano: ");
            scanf("%d", &aux->anos);
            getchar();
            break;
        default:
            printf("Opcao invalida.\n");
            return;
    }
    printf("Alteração Concluída\n");
}

void excluirlivro(biblioteca **lista, char *string) {
    biblioteca *aux = *lista;
    biblioteca *ant = NULL;

    while (aux != NULL && strcmp(aux->titulos, string) != 0) {
        ant = aux;
        aux = aux->prox;
    }

    if (aux == NULL) {
        printf("Título não encontrado\n");
        return;
    }

    if (ant == NULL) *lista = aux->prox;
    else ant->prox = aux->prox;
    
    free(aux);
    printf("Removido com sucesso.\n");
}

void exportarLivros(biblioteca **lista) {
    FILE *f = fopen("catalogo_exportado.txt", "w");
    if (!f) return;
    
    biblioteca *at = *lista;
    while (at != NULL) {
        fprintf(f, "%s|%s|%s|%d\n", at->titulos, at->autores, at->codigos, at->anos);
        at = at->prox;
    }
    fclose(f);
    printf("Catalogo exportado com sucesso.\n");
}

void freeLista(biblioteca **lista) {
    biblioteca *at = *lista;
    while (at != NULL) {
        biblioteca *t = at;
        at = at->prox;
        free(t);
    }
    *lista = NULL;
    printf("Encerrando...\n");
}
