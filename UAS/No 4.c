#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct book
{
    int id;
    char title[100];
    char author[50];
    int year_publish;
};

struct node
{
    struct book book_data;
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

struct node *createNode(struct book book_data)
{
    struct node *newP = (struct node *)malloc(sizeof(struct node));
    newP->book_data = book_data;
    newP->left = NULL;
    newP->right = NULL;
    newP->height = 1;
    return newP;
}

struct node *insert(struct node *root, struct book book_data)
{
    if (root == NULL)
    {
        return createNode(book_data);
    }
    if (book_data.id < root->book_data.id)
    {
        root->left = insertNode(root->left, book_data);
    }
    else if (book_data.id > root->book_data.id)
    {
        root->right = insertNode(root->right, book_data);
    }
    else
    {
        return root;
    }

    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    int BF = getBF(root);

    if (BF > 1)
    {
        if (getBF(root->left) >= 0)
        {
            return rightRotate(root);
        }
        else
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    if (BF < -1)
    {
        if (getBF(root->right) <= 0)
        {
            return leftRotate(root);
        }
        else
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }

    return root;
}

struct node *delete(struct node *root, int book_id)
{
    if (root == NULL)
    {
        return root;
    }

    // Jika ID buku yang akan dihapus lebih kecil dari ID buku pada root,
    // hapus dari cabang kiri
    if (book_id < root->book_data.id)
    {
        root->left = deleteNode(root->left, book_id);
    }

    // Jika ID buku yang akan dihapus lebih besar dari ID buku pada root,
    // hapus dari cabang kanan
    else if (book_id > root->book_data.id)
    {
        root->right = deleteNode(root->right, book_id);
    }
    // Jika ID buku yang akan dihapus sama dengan ID buku pada root,
    // ini adalah node yang akan dihapus
    else
    {
        // Node dengan satu anak atau tanpa anak
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

            root->book_data = temp->book_data;

            root->right = delete (root->right, temp->book_data.id);
        }
    }

    // Jika tree hanya memiliki satu node, kembalikan node tersebut

    if (root == NULL)
    {
        return root;
    }

    // Perbarui tinggi node
    root->height = 1 + max(getHeight(root->left), getHeight(root->right));
    int BF = getBF(root);

    // Jika tree tidak seimbang, lakukan rotasi
    if (BF > 1)
    {
        if (getBF(root->left) >= 0)
        {
            return rightRotate(root);
        }
        else
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    if (BF < -1)
    {
        if (getBF(root->right) <= 0)
        {
            return leftRotate(root);
        }
        else
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    return root;
}

struct node *searchNode(struct node *root, int book_id)
{
    // Jika tree kosong atau ID buku yang dicari sama dengan ID buku pada root,
    // kembalikan root
    if (root == NULL || root->book_data.id == book_id)
    {
        return root;
    }

    // Jika ID buku yang dicari lebih kecil dari ID buku pada root,
    // lanjutkan pencarian ke cabang kiri
    if (book_id < root->book_data.id)
    {
        return searchNode(root->left, book_id);
    }
    // Jika ID buku yang dicari lebih besar dari ID buku pada root,
    // lanjutkan pencarian ke cabang kanan
    else
    {
        return searchNode(root->right, book_id);
    }
}

void inorderTraversal(struct node *root)
{
    if (root != NULL)
    {
        inorderTraversal(root->left);
        printf("ID Buku: %d, Judul: %s, Penulis: %s\n", root->book_data.id, root->book_data.title, root->book_data.author ? "Ya" : "Tidak");
        inorderTraversal(root->right);
    }
}

int main()
{
    struct node *root = NULL;

    // Menambahkan buku
    struct book book1 = {1, "Buku A", "Penulis A", 2020};
    root = insert(root, book1);

    struct book book2 = {2, "Buku B", "Penulis B", 2021};
    root = insert(root, book2);

    struct book book3 = {3, "Buku C", "Penulis C", 2022};
    root = insert(root, book3);

    // Mencetak tree secara inorder
    printf("Daftar buku:\n");
    inorderTraversal(root);

    // Mencari buku
    struct node *found = searchNode(root, 2);
    if (found)
    {
        printf("\nBuku ditemukan: %s\n", found->book_data.title);
    }
    else
    {
        printf("\nBuku tidak ditemukan\n");
    }

    // Menghapus buku
    root = delete (root, 2);
    printf("\nDaftar buku setelah penghapusan:\n");
    inorderTraversal(root);

    return 0;
}
