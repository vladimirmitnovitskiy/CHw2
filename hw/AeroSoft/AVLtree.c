#include "AVLtree.h"

#include <stdlib.h>
#include <string.h>

#define MAX_CODE_LEN 16
#define MAX_NAME_LEN 256
#define MAX_LINE_LEN 512

typedef struct Node {
    char code[MAX_CODE_LEN];
    char name[MAX_NAME_LEN];
    int height;
    struct Node* left;
    struct Node* right;
} Node;

struct AVLtree {
    Node* root;
};

static int max(int a, int b)
{
    return (a > b) ? a : b;
}

static int height(Node* node)
{
    if (!node)
        return 0;
    return node->height;
}

static Node* newNode(const char* code, const char* name)
{
    Node* node = (Node*)malloc(sizeof(Node));
    if (!node)
        return NULL;

    strncpy(node->code, code, MAX_CODE_LEN - 1);
    node->code[MAX_CODE_LEN - 1] = '\0';

    strncpy(node->name, name, MAX_NAME_LEN - 1);
    node->name[MAX_NAME_LEN - 1] = '\0';

    node->left = NULL;
    node->right = NULL;
    node->height = 1;

    return node;
}

static Node* rightRotate(Node* y)
{
    Node* x = y->left;
    Node* t2 = x->right;

    x->right = y;
    y->left = t2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

static Node* leftRotate(Node* x)
{
    Node* y = x->right;
    Node* t2 = y->left;

    y->left = x;
    x->right = t2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

static int getBalance(Node* node)
{
    if (!node)
        return 0;
    return height(node->left) - height(node->right);
}

static Node* minValueNode(Node* node)
{
    Node* current = node;
    while (current->left)
        current = current->left;
    return current;
}

static Node* balanceNode(Node* node)
{
    if (!node)
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1) {
        if (getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
        }
        return rightRotate(node);
    }

    if (balance < -1) {
        if (getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
        }
        return leftRotate(node);
    }

    return node;
}

Node* insertNode(Node* node, const char* code, const char* name, bool* added)
{
    if (!node) {
        Node* createNode = newNode(code, name);
        if (createNode != NULL) {
            *added = true;
        }
        return createNode;
    }

    int cmp = strcmp(code, node->code);

    if (cmp < 0) {
        node->left = insertNode(node->left, code, name, added);
    } else if (cmp > 0) {
        node->right = insertNode(node->right, code, name, added);
    } else {
        *added = false;
        return node;
    }

    return balanceNode(node);
}

static Node* deleteNode(Node* root, const char* code, bool* deleted)
{
    if (!root)
        return root;

    int cmp = strcmp(code, root->code);

    if (cmp < 0) {
        root->left = deleteNode(root->left, code, deleted);
    } else if (cmp > 0) {
        root->right = deleteNode(root->right, code, deleted);
    } else {
        *deleted = true;

        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = NULL;
            } else {
                *root = *temp;
            }
            free(temp);
        } else {
            Node* temp = minValueNode(root->right);

            strcpy(root->code, temp->code);
            strcpy(root->name, temp->name);

            bool dummy = false;
            root->right = deleteNode(root->right, temp->code, &dummy);
        }
    }

    if (!root)
        return root;

    return balanceNode(root);
}

static bool searchValueInternal(Node* root, const char* code, char* outValue, size_t maxLength)
{
    if (!root)
        return false;

    int cmp = strcmp(code, root->code);

    if (cmp == 0) {
        strncpy(outValue, root->name, maxLength - 1);
        outValue[maxLength - 1] = '\0';
        return true;
    }

    if (cmp < 0)
        return searchValueInternal(root->left, code, outValue, maxLength);

    return searchValueInternal(root->right, code, outValue, maxLength);
}

static void saveTreeToFileInternal(Node* root, FILE* file, int* count)
{
    if (root) {
        saveTreeToFileInternal(root->left, file, count);
        fprintf(file, "%s:%s\n", root->code, root->name);
        (*count)++;
        saveTreeToFileInternal(root->right, file, count);
    }
}

static void freeNode(Node* root)
{
    if (root) {
        freeNode(root->left);
        freeNode(root->right);
        free(root);
    }
}

AVLtree* createTree()
{
    AVLtree* tree = (AVLtree*)malloc(sizeof(AVLtree));
    if (tree) {
        tree->root = NULL;
    }
    return tree;
}

void insertValue(AVLtree* tree, const char* code, const char* name, bool* added)
{
    if (!tree) {
        return;
    }
    tree->root = insertNode(tree->root, code, name, added);
}

void deleteValue(AVLtree* tree, const char* code, bool* deleted)
{
    if (!tree)
        return;
    tree->root = deleteNode(tree->root, code, deleted);
}

bool searchValue(AVLtree* tree, const char* code, char* outValue, size_t maxLength)
{
    if (!tree)
        return false;
    return searchValueInternal(tree->root, code, outValue, maxLength);
}

void saveTreeToFile(AVLtree* tree, FILE* file, int* count)
{
    if (!tree)
        return;
    saveTreeToFileInternal(tree->root, file, count);
}

void loadTreeFromFile(AVLtree* tree, FILE* file, int* count)
{
    if (!tree || !file)
        return;

    char line[MAX_LINE_LEN];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        line[strcspn(line, "\r")] = 0;

        char* colon = strchr(line, ':');
        if (colon) {
            *colon = '\0';
            bool added = false;
            insertValue(tree, line, colon + 1, &added);
            if (added && count) {
                (*count)++;
            }
        }
    }
}

void freeTree(AVLtree* tree)
{
    if (tree) {
        freeNode(tree->root);
        free(tree);
    }
}