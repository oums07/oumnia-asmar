#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

Node* newNode(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; 
    return node;
}
Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    // Rotation
    x->right = y;
    y->left = T2;

    // Mettre à jour les hauteurs
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Nouvelle racine
    return x;
}

Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    // Rotation
    y->left = x;
    x->right = T2;

    // Mettre à jour les hauteurs
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Nouvelle racine
    return y;
}

int getBalance(Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

Node* insert(Node* node, int key) {
    // Insertion classique BST
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node; // pas de doublon

    // Mise à jour de la hauteur
    node->height = 1 + max(height(node->left), height(node->right));

    // Calcul du facteur d’équilibre
    int balance = getBalance(node);

    // Cas 4 rotations
    // Gauche-Gauche
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Droite-Droite
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Gauche-Droite
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Droite-Gauche
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Aucun déséquilibre
    return node;
}

int search(Node* root, int key) {
    if (root == NULL)
        return 0;
    if (key == root->key)
        return 1;
    else if (key < root->key)
        return search(root->left, key);
    else
        return search(root->right, key);
}
int main() {
    struct Node *root = NULL;
    FILE *fptr;
    int n_insert, n_search, key;

    fptr = fopen("test7.txt", "r");
    fscanf(fptr, "%d", &n_insert);
    for (int i = 0; i < n_insert; i++) {
        fscanf(fptr, "%d", &key);
        root = insert(root, key);
    }
    fscanf(fptr, "%d", &n_search);
    for (int i = 0; i < n_search; i++) {
        fscanf(fptr, "%d", &key);
        if (search(root, key))
            printf("true\n");
        else
            printf("false\n");
    }

    fclose(fptr);
    return 0;
}
