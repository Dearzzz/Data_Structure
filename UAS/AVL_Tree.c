#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    int key;
    struct node *left;
    struct node *right;
    int height;
};

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int getHeight(struct node *n)
{
    if (n == NULL)
    {
        return 0;
    }
    return n->height;
}

int getBF(struct node *root)
{
    if (root == NULL)
    {
        return 0;
    }
    else
    {
        return getHeight(root->left) - getHeight(root->right);
    }
}

struct node *minValueNode(struct node *root)
{
    struct node *curr = root;
    while (curr->left != NULL)
    {
        curr = curr->left;
    }
    return curr;
}

struct node *createNode(int key)
{
    struct node *newP = (struct node *)malloc(sizeof(struct node));
    newP->key = key;
    newP->left = NULL;
    newP->right = NULL;
    newP->height = 1;
    return newP;
}

struct node *leftRotate(struct node *x)
{
    struct node *y = x->right;
    struct node *T2 = y->left;

    // rotate
    y->left = x;
    x->right = T2;

    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

struct node *rightRotate(struct node *y)
{
    struct node *x = y->left;
    struct node *T2 = x->right;

    // rotate
    x->right = y;
    y->left = T2;

    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

struct node *insert(struct node *root, int value)
{
    if (root == NULL)
    {
        return createNode(value);
    }
    if (value > root->key)
    {
        root->right = insert(root->right, value);
    }
    else
    {
        root->left = insert(root->left, value);
    }
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    int BF = getBF(root);

    if (BF > 1 && value < root->left->key) // RR rotation
    {
        return rightRotate(root);
    }
    if (BF < -1 && value > root->right->key) // LL rotation
    {
        return leftRotate(root);
    }
    if (BF > 1 && value > root->left->key) // LR rotation
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (BF < -1 && value < root->right->key) // RL rotation
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

void inorder(struct node *node)
{
    if (node == NULL)
    {
        return;
    }
    inorder(node->left);
    printf(" %d|%d ", node->key, node->height);
    inorder(node->right);
}

struct node *freeAll(struct node *root)
{
    if (root == NULL)
    {
        return NULL;
    }
    root->left = freeAll(root->left);
    root->right = freeAll(root->right);
    free(root);
    return NULL;
}

struct node *delete(struct node *root, int value)
{
    if (root == NULL)
    {
        return root;
    }
    else if (value < root->key)
    {
        root->left = delete (root->left, value);
    }
    else if (value > root->key)
    {
        root->right = delete (root->right, value);
    }
    // Jika value yang kita cari sama dengan root maka kita akan melakukan delete
    else
    {
        // node hanya memiliki 1 child atau tidak memiliki child
        if ((root->left == NULL) || (root->right == NULL))
        {
            struct node *temp = root->left ? root->left : root->right;

            // jika tidak punya child
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
            { // jika hanya 1 anak
                *root = *temp;
            }
            free(temp);
        }
        else
        { // Node dengan 2 child
            struct node *temp = minValueNode(root->right);

            root->key = temp->key;

            root->right = delete (root->right, temp->key);
        }
    }
    if (root == NULL)
    {
        return root;
    }
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int BF = getBF(root);

    if (BF > 1 && getBF(root->left) >= 0)
    {
        return rightRotate(root);
    }
    else if (BF > 1 && getBF(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    else if (BF < -1 && getBF(root->right) <= 0)
    {
        return leftRotate(root);
    }
    else if (BF < -1 && getBF(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

int main()
{
    struct node *root = NULL;
    root = insert(root, 10);
    root = insert(root, 5);
    root = insert(root, 7);
    root = insert(root, 15);
    root = insert(root, 20);
    root = insert(root, 17);

    inorder(root);
    printf("\n");

    root = insert(root, 16);
    inorder(root);
    printf("\n");

    root = delete (root, 5);
    inorder(root);
    printf("\n");

    root = delete (root, 7);
    inorder(root);
    printf("\n");
    root = freeAll(root);
    return 0;
}
