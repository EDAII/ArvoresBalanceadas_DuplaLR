#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct AVLNode {
    int key;
    int height;
    int size; // tamanho da subárvore
    struct AVLNode* left;
    struct AVLNode* right;
} AVLNode;

// Função auxiliar para criar nó
AVLNode* newNode(int key) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    node->key = key;
    node->height = 1;
    node->size = 1;
    node->left = node->right = NULL;
    return node;
}

// Altura
int height(AVLNode* node) {
    return node ? node->height : 0;
}

// Tamanho da subárvore
int size(AVLNode* node) {
    return node ? node->size : 0;
}

// Atualizar altura e tamanho
void update(AVLNode* node) {
    if(node) {
        node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));
        node->size = 1 + size(node->left) + size(node->right);
    }
}

// Rotação direita
AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    update(y);
    update(x);
    return x;
}

// Rotação esquerda
AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    update(x);
    update(y);
    return y;
}

// Fator de balanceamento
int getBalance(AVLNode* node) {
    return node ? height(node->left) - height(node->right) : 0;
}

// Inserção
AVLNode* insert(AVLNode* node, int key) {
    if(!node) return newNode(key);

    if(key < node->key)
        node->left = insert(node->left, key);
    else if(key > node->key)
        node->right = insert(node->right, key);
    else
        return node; // duplicado não ocorre no problema

    update(node);

    int balance = getBalance(node);

    // Rotação LL
    if(balance > 1 && key < node->left->key) return rotateRight(node);
    // Rotação RR
    if(balance < -1 && key > node->right->key) return rotateLeft(node);
    // Rotação LR
    if(balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    // Rotação RL
    if(balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

// Função para encontrar índice de x (1-based)
int findIndex(AVLNode* node, int x) {
    if(!node) return -1;

    if(x < node->key) return findIndex(node->left, x);
    else if(x > node->key) {
        int idx = findIndex(node->right, x);
        if(idx == -1) return -1;
        return size(node->left) + 1 + idx;
    } else {
        return size(node->left) + 1; // achou
    }
}

int main() {
    int Q;
    scanf("%d", &Q);
    AVLNode* root = NULL;

    for(int i = 0; i < Q; i++) {
        int type, x;
        scanf("%d %d", &type, &x);
        if(type == 1) {
            root = insert(root, x);
        } else if(type == 2) {
            int idx = findIndex(root, x);
            if(idx == -1)
                printf("Data tidak ada\n");
            else
                printf("%d\n", idx);
        }
    }

    return 0;
}
