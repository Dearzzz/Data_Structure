#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nama[50];
    int waktu_kedatangan;
} Konsumen;

typedef struct
{
    Konsumen *items;
    int front;
    int rear;
    int size;
    int capacity;
} Queue;

// Inisialisasi queue
Queue *createQueue(int capacity)
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->items = (Konsumen *)malloc(capacity * sizeof(Konsumen));
    q->front = q->rear = -1;
    q->size = 0;
    q->capacity = capacity;
    return q;
}

// Mengecek apakah queue kosong
int isQueueEmpty(Queue *q)
{
    return q->size == 0;
}

// Mengecek apakah queue penuh
int isQueueFull(Queue *q)
{
    return q->size == q->capacity;
}

// Menambahkan konsumen ke dalam queue
void enqueue(Queue *q, Konsumen konsumen)
{
    if (isQueueFull(q))
    {
        printf("Error: Queue penuh\n");
        return;
    }
    q->rear = (q->rear + 1) % q->capacity;
    q->items[q->rear] = konsumen;
    if (q->front == -1)
    {
        q->front = 0;
    }
    q->size++;
}

// Mengeluarkan konsumen dari queue
Konsumen dequeue(Queue *q)
{
    if (isQueueEmpty(q))
    {
        printf("Error: Queue kosong\n");
        Konsumen dummy = {"", 0};
        return dummy;
    }
    Konsumen konsumen = q->items[q->front];
    q->front = (q->front + 1) % q->capacity;
    q->size--;
    if (q->size == 0)
    {
        q->front = q->rear = -1;
    }
    return konsumen;
}

int main()
{
    Queue *antrian = createQueue(5);

    // Simulasi konsumen masuk antrian
    Konsumen konsumen1 = {"Konsumen A", 10};
    Konsumen konsumen2 = {"Konsumen B", 15};
    Konsumen konsumen3 = {"Konsumen C", 20};

    enqueue(antrian, konsumen1);
    enqueue(antrian, konsumen2);
    enqueue(antrian, konsumen3);

    printf("Antrian saat ini:\n");
    while (!isQueueEmpty(antrian))
    {
        Konsumen konsumen = dequeue(antrian);
        printf("Nama: %s, Waktu Kedatangan: %d\n", konsumen.nama, konsumen.waktu_kedatangan);
    }

    // Simulasi konsumen keluar antrian
    printf("\nAntrian setelah ada konsumen yang keluar:\n");
    Konsumen konsumen4 = {"Konsumen D", 25};
    enqueue(antrian, konsumen4);
    while (!isQueueEmpty(antrian))
    {
        Konsumen konsumen = dequeue(antrian);
        printf("Nama: %s, Waktu Kedatangan: %d\n", konsumen.nama, konsumen.waktu_kedatangan);
    }

    return 0;
}