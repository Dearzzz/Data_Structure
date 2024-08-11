#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define V 5 // Jumlah vertex (Data center, Kantor1, Kantor2, Pemukiman1, Pemukiman2)

// Fungsi untuk menemukan vertex dengan nilai key minimum
// dari himpunan vertex yang belum termasuk dalam MST
int minKey(int key[], int mstSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < V; v++)
        if (mstSet[v] == 0 && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

// Fungsi untuk mencetak MST yang dibangun
void printMST(int parent[], int graph[V][V]) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < V; i++)
        if (graph[i][parent[i]] != INT_MAX)
            printf("%d - %d \t%d \n", parent[i], i, graph[i][parent[i]]);
}

// Fungsi untuk mengimplementasikan algoritma Prim
void primMST(int graph[V][V]) {
    int parent[V];  // Array untuk menyimpan MST
    int key[V];     // Nilai key untuk memilih edge dengan bobot minimum
    int mstSet[V];  // Untuk melacak vertex yang sudah termasuk dalam MST

    // Inisialisasi semua key sebagai INFINITE
    for (int i = 0; i < V; i++)
        key[i] = INT_MAX, mstSet[i] = 0;

    // Selalu sertakan vertex pertama dalam MST
    key[0] = 0;     // Buat key 0 sehingga vertex ini dipilih pertama
    parent[0] = -1; // Node pertama selalu merupakan root dari MST

    // MST akan memiliki V vertex
    for (int count = 0; count < V - 1; count++) {
        // Pilih vertex dengan nilai key minimum dari himpunan vertex
        // yang belum termasuk dalam MST
        int u = minKey(key, mstSet);

        // Tambahkan vertex yang dipilih ke dalam MST Set
        mstSet[u] = 1;

        // Perbarui nilai key dan parent index dari vertex yang berdekatan
        // dari vertex yang dipilih. Hanya pertimbangkan vertex yang belum
        // termasuk dalam MST
        for (int v = 0; v < V; v++)
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v])
                parent[v] = u, key[v] = graph[u][v];
    }

    // Cetak MST yang dibangun
    printMST(parent, graph);
}

int main() {
    // Representasi graf menggunakan adjacency matrix
    int graph[V][V] = {
        {0, 30, 20, 10, INT_MAX},   
        {30, 0, INT_MAX, 5, 25},
        {20, INT_MAX, 0, 13, 40},
        {10, 5, 13, 0, INT_MAX},
        {INT_MAX, 25, 40, INT_MAX, 0}
    };

    // Panggil fungsi primMST
    primMST(graph);

    return 0;
}