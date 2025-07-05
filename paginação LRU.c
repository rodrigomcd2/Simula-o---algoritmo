#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAM_MEM 3
#define TAM_ACESSOS 12

int acessos[] = {1, 2, 3, 2, 4, 1, 5, 2, 1, 2, 3, 4};

// FIFO
int fifo(int tempo_subst) {
    int memoria[TAM_MEM], inicio = 0, page_faults = 0;
    for (int i = 0; i < TAM_MEM; i++) memoria[i] = -1;

    for (int i = 0; i < TAM_ACESSOS; i++) {
        int pagina = acessos[i];
        bool presente = false;

        for (int j = 0; j < TAM_MEM; j++) {
            if (memoria[j] == pagina) {
                presente = true;
                break;
            }
        }

        if (!presente) {
            memoria[inicio] = pagina;
            inicio = (inicio + 1) % TAM_MEM;
            page_faults++;
        }
    }

    int tempo_total = page_faults * tempo_subst;
    printf("\n[FIFO] Page Faults: %d | Tempo total: %d ms\n", page_faults, tempo_total);
    return tempo_total;
}

// LRU
int lru(int tempo_subst) {
    int memoria[TAM_MEM], uso[TAM_MEM], page_faults = 0;
    for (int i = 0; i < TAM_MEM; i++) memoria[i] = uso[i] = -1;

    for (int i = 0; i < TAM_ACESSOS; i++) {
        int pagina = acessos[i];
        bool presente = false;

        for (int j = 0; j < TAM_MEM; j++) {
            if (memoria[j] == pagina) {
                presente = true;
                uso[j] = i;
                break;
            }
        }

        if (!presente) {
            int pos = 0;
            for (int j = 1; j < TAM_MEM; j++) {
                if (uso[j] < uso[pos]) pos = j;
            }
            memoria[pos] = pagina;
            uso[pos] = i;
            page_faults++;
        }
    }

    int tempo_total = page_faults * tempo_subst;
    printf("\n[LRU] Page Faults: %d | Tempo total: %d ms\n", page_faults, tempo_total);
    return tempo_total;
}

// CLOCK
int clock_alg(int tempo_subst) {
    int memoria[TAM_MEM], ref[TAM_MEM], ponteiro = 0, page_faults = 0;
    for (int i = 0; i < TAM_MEM; i++) {
        memoria[i] = -1;
        ref[i] = 0;
    }

    for (int i = 0; i < TAM_ACESSOS; i++) {
        int pagina = acessos[i];
        bool presente = false;

        for (int j = 0; j < TAM_MEM; j++) {
            if (memoria[j] == pagina) {
                presente = true;
                ref[j] = 1;
                break;
            }
        }

        if (!presente) {
            while (ref[ponteiro] == 1) {
                ref[ponteiro] = 0;
                ponteiro = (ponteiro + 1) % TAM_MEM;
            }
            memoria[ponteiro] = pagina;
            ref[ponteiro] = 1;
            ponteiro = (ponteiro + 1) % TAM_MEM;
            page_faults++;
        }
    }

    int tempo_total = page_faults * tempo_subst;
    printf("\n[CLOCK] Page Faults: %d | Tempo total: %d ms\n", page_faults, tempo_total);
    return tempo_total;
}

void menu() {
    int opcao;
    while (1) {
        printf("\n=== SIMULADOR DE SUBSTITUIÇÃO DE PÁGINAS ===\n");
        printf("1. Simular FIFO\n");
        printf("2. Simular LRU\n");
        printf("3. Simular CLOCK\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                fifo(8);     // tempo por substituição em ms
                break;
            case 2:
                lru(12);     // tempo por substituição mais alto
                break;
            case 3:
                clock_alg(10); // médio custo
                break;
            case 4:
                printf("Encerrando...\n");
                return;
            default:
                printf("Opção inválida!\n");
        }
    }
}

int main() {
    menu();
    return 0;
}

