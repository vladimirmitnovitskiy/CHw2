#include "AVLtree.h"

#include <stdlib.h>
#include <string.h>

#define MAX_CODE_LEN 16
#define MAX_NAME_LEN 256

struct Node {
    char code[MAX_CODE_LEN];
    char name[MAX_NAME_LEN];
    int height;
    Node* left;
    Node* right;
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

Node* insertNode(Node* node, const char* code, const char* name, bool* added)
{
    if (!node) {
        *added = true;
        return newNode(code, name);
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

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && strcmp(code, node->left->code) < 0)
        return rightRotate(node);

    if (balance < -1 && strcmp(code, node->right->code) > 0)
        return leftRotate(node);

    if (balance > 1 && strcmp(code, node->left->code) > 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && strcmp(code, node->right->code) < 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

Node* deleteNode(Node* root, const char* code, bool* deleted)
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

    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

bool findAirport(Node* root, const char* code, char* outName, size_t maxLength)
{
    if (!root)
        return false;

    int cmp = strcmp(code, root->code);

    if (cmp == 0) {
        strncpy(outName, root->name, maxLength - 1);
        outName[maxLength - 1] = '\0';
        return true;
    }

    if (cmp < 0)
        return findAirport(root->left, code, outName, maxLength);

    return findAirport(root->right, code, outName, maxLength);
}

void saveTreeToFile(Node* root, FILE* file, int* count)
{
    if (root) {
        saveTreeToFile(root->left, file, count);
        fprintf(file, "%s:%s\n", root->code, root->name);
        (*count)++;
        saveTreeToFile(root->right, file, count);
    }
}

void freeTree(Node* root)
{
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}