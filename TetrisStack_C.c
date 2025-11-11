#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Biblioteca responsável por gerar números automáticos.
#define MAX 4 // Número maximo da fila.


typedef struct // 🔽 Estrutura principal 
{
    char part; // Peças: 'I', 'O', 'T', 'L'
} Part;

typedef struct // Criando uma estrutura pré-definida de valor(Um alias).
{
    Part itens[MAX]; 
    int enqueue, dequeue, total, exit;
} File;

void initFile(File *f) // 🔽 Iniciando os valores da estrutura 
{
    f -> enqueue = 0, // Colocar um novo elemento no final da fila.
    f -> dequeue = 0; // Eliminar o elemento mais antigo, localizado na frente
    f -> total = 0;
}

// 🔽 Verificadores 

int fileEmpty(File *f){ return f -> total == 0; } // Verifica se a fila está vazia
int fileFull(File *f){ return f -> total == MAX; } // Verifica se a vfila está cheia


void insertPart_Enqueue(File *f, Part p) { // Adiciona peças no ultimo index da fila.
    if (fileFull(f)) {
        printf("\n⚠️  Fila cheia. Não será inserido mais valores.\n");
        return;
    }

    f->itens[f->enqueue] = p; // Insere a peça passada como parâmetro
    printf("\n✅ Adicionando peça: %c na posição [%d]\n", p.part, f->enqueue);

    f->enqueue = (f->enqueue + 1) % MAX; // Avança o índice circular
    f->total++;
}

void removePart_Dequeue(File *f, Part *p) { // remove peças no primeiro index da fila.
    if (fileEmpty(f)) {
        printf("\nFila vazia. Nenhum elemento para remover.\n");
        return;
    }

    *p = f->itens[f->dequeue]; 
    printf("\n❌ Removendo peça: %c da posição [%d]\n", p->part, f->dequeue);

    f->dequeue = (f->dequeue + 1) % MAX;
    f->total--;
}

void showFile_Peek(File *f) {
    if (fileEmpty(f)) {
        printf("\nFila vazia!\n");
        return;
    }

    printf("\n===== FILA ATUAL =====\n");
    printf("Posições: ");

    for (int i = 0, idx = f->dequeue; i < f->total; i++, idx = (idx + 1) % MAX)
        printf("%d  ", idx);

    printf("\nPeças:    ");
    for (int i = 0, idx = f->dequeue; i < f->total; i++, idx = (idx + 1) % MAX) 
        printf("%c  ", f->itens[idx].part);

    printf("\n======================\n");
}

int main(File *f) 
{
    File fila;
    initFile(&fila);
    srand(time(NULL)); // Garante resultados diferentes a cada execução.

    Part pecas[MAX] = {{'I'}, {'O'}, {'T'}, {'L'}}; //🧩 Peças do array com o a largura 4;
    int opcao = 0;
    Part p;

    // Inserir 4 peças aleatórias no início
    for (int i = 0; i < MAX; i++) 
        insertPart_Enqueue(&fila, pecas[rand() % MAX]); // 🔹 Índice entre 0 e MAX-1
    

    do {
        showFile_Peek(&fila);

        printf("\nEscolha uma opção:\n");
        printf("1 - Jogar peça (dequeue)\n");
        printf("2 - Inserir nova peça (enqueue)\n");
        printf("3 - Sair\n");
        printf("Opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                removePart_Dequeue(&fila, &p);
                break;
            case 2:
                insertPart_Enqueue(&fila, pecas[rand() % MAX]);
                break;
            case 3:
                printf("\n🚪 Saindo do jogo...\n");
                break;
            default:
                printf("\n❌ Opção inválida. Tente novamente.\n");
        }

    } while (opcao != 3);

    return 0;
}