#include <stdio.h>
#include <stdlib.h>

#define CAPACIDADE_CACHE 3  // Definindo a capacidade do cache LRU

// Estrutura de um nó da lista duplamente encadeada
typedef struct Node {
    int chave;               // Chave (ou ID) do item
    int valor;               // Valor associado ao item
    struct Node* prev;       // Ponteiro para o nó anterior
    struct Node* next;       // Ponteiro para o próximo nó
} Node;

// Estrutura para o Cache LRU
typedef struct LRUCache {
    int capacidade;          // Capacidade do cache
    int tamanho;             // Número atual de itens no cache
    Node* head;              // Cabeça da lista (item mais recente)
    Node* tail;              // Cauda da lista (item menos recente)
    Node** mapa;             // Mapa de chaves para acesso rápido aos nós
} LRUCache;

// Função para criar um novo nó
Node* criarNovoNode(int chave, int valor) {
    Node* novoNode = (Node*)malloc(sizeof(Node));
    novoNode->chave = chave;
    novoNode->valor = valor;
    novoNode->prev = novoNode->next = NULL;
    return novoNode;
}

// Função para criar o Cache LRU
LRUCache* criarCache(int capacidade) {
    LRUCache* cache = (LRUCache*)malloc(sizeof(LRUCache));
    cache->capacidade = capacidade;
    cache->tamanho = 0;
    cache->head = cache->tail = NULL;
    cache->mapa = (Node**)malloc(sizeof(Node*) * 100); // Supondo que as chaves são números inteiros
    for (int i = 0; i < 100; i++) cache->mapa[i] = NULL;
    return cache;
}

// Função para mover um nó para o início da lista (mais recente)
void moverParaFrente(LRUCache* cache, Node* node) {
    if (cache->head == node) return;  // Já está na frente

    if (node->prev) node->prev->next = node->next;
    if (node->next) node->next->prev = node->prev;

    if (cache->tail == node) cache->tail = node->prev;

    node->next = cache->head;
    node->prev = NULL;
    if (cache->head) cache->head->prev = node;
    cache->head = node;

    if (cache->tail == NULL) cache->tail = node;  // Caso o cache estivesse vazio
}

// Função para remover o nó da cauda (menos recente)
void removerCauda(LRUCache* cache) {
    if (cache->tamanho == 0) return;

    Node* nodeRemovido = cache->tail;
    if (nodeRemovido->prev) nodeRemovido->prev->next = NULL;
    cache->tail = nodeRemovido->prev;

    cache->mapa[nodeRemovido->chave] = NULL;
    free(nodeRemovido);
    cache->tamanho--;
}

// Função para adicionar um item ao cache
void adicionarAoCache(LRUCache* cache, int chave, int valor) {
    Node* nodeExistente = cache->mapa[chave];
    if (nodeExistente) {
        // Se o item já existir, apenas atualize o valor e mova-o para a frente
        nodeExistente->valor = valor;
        moverParaFrente(cache, nodeExistente);
    } else {
        // Se o item não existe no cache
        if (cache->tamanho == cache->capacidade) {
            // Cache cheio, removemos o item menos recente (cauda)
            removerCauda(cache);
        }

        // Cria um novo nó e o adiciona à frente
        Node* novoNode = criarNovoNode(chave, valor);
        cache->mapa[chave] = novoNode;

        if (cache->tamanho == 0) {
            cache->head = cache->tail = novoNode;
        } else {
            novoNode->next = cache->head;
            cache->head->prev = novoNode;
            cache->head = novoNode;
        }

        cache->tamanho++;
    }
}

// Função para exibir o cache (ordem de uso)
void exibirCache(LRUCache* cache) {
    Node* temp = cache->head;
    while (temp) {
        printf("Chave: %d, Valor: %d\n", temp->chave, temp->valor);
        temp = temp->next;
    }
}

// Função para buscar um item no cache
int buscarNoCache(LRUCache* cache, int chave) {
    Node* nodeExistente = cache->mapa[chave];
    if (nodeExistente) {
        // Mova o nó para a frente, já que foi acessado
        moverParaFrente(cache, nodeExistente);
        return nodeExistente->valor;
    }
    return -1;  // Retorna -1 se o item não for encontrado
}

int main() {
    LRUCache* cache = criarCache(CAPACIDADE_CACHE);

    adicionarAoCache(cache, 1, 10);
    adicionarAoCache(cache, 2, 20);
    adicionarAoCache(cache, 3, 30);
    exibirCache(cache);

    printf("\nBuscando chave 2: %d\n", buscarNoCache(cache, 2));  // Acessando chave 2
    exibirCache(cache);

    adicionarAoCache(cache, 4, 40);  // Cache está cheio, remove o item menos usado (chave 1)
    exibirCache(cache);

    adicionarAoCache(cache, 5, 50);  // Cache está cheio, remove o item menos usado (chave 3)
    exibirCache(cache);

    return 0;
}
