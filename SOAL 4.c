#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct {
    int nomorAntrian;
    int waktuLayanan; // dalam menit
} Pelanggan;

typedef struct {
    Pelanggan data[MAX];
    int front;
    int rear;
} Queue;

// Fungsi untuk membuat queue
void initQueue(Queue *q) {
    q->front = -1;
    q->rear = -1;
}

// Fungsi untuk mengecek apakah queue kosong
int isEmpty(Queue *q) {
    return (q->front == -1);
}

// Fungsi untuk menambahkan elemen ke queue
void enqueue(Queue *q, Pelanggan p) {
    if (q->rear == MAX - 1) {
        printf("Queue penuh!\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
    }
    q->rear++;
    q->data[q->rear] = p;
}

// Fungsi untuk menghapus elemen dari queue
Pelanggan dequeue(Queue *q) {
    Pelanggan p = {0, 0};
    if (isEmpty(q)) {
        printf("Queue kosong!\n");
        return p; // Mengembalikan pelanggan kosong
    }
    p = q->data[q->front];
    if (q->front >= q->rear) {
        // Jika hanya ada satu elemen, reset queue
        q->front = -1;
        q->rear = -1;
    } else {
        q->front++;
    }
    return p;
}

// Fungsi untuk menghitung statistik
void hitungStatistik(Queue *q, int totalPelayanan) {
    int totalWaktuTunggu = 0;
    int pelangganDilayani = 0;

    for (int i = 0; i <= q->rear; i++) {
        totalWaktuTunggu += q->data[i].waktuLayanan;
        pelangganDilayani++;
    }

    if (pelangganDilayani > 0) {
        double rataRataWaktuTunggu = (double)totalWaktuTunggu / pelangganDilayani;
        printf("Statistik:\n");
        printf("Rata-rata waktu tunggu: %.2f menit\n", rataRataWaktuTunggu);
        printf("Pelanggan terlayani: %d\n", pelangganDilayani);
        printf("Sisa antrian: %d\n", q->rear - q->front + 1);
    } else {
        printf("Tidak ada pelanggan dalam antrian.\n");
    }
}

int main() {
    Queue antrian;
    initQueue(&antrian);

    Pelanggan p;
    int i, jumlahPelanggan, waktuLoket[3] = {0, 0, 0}; // Menyimpan waktu pelayanan per loket
    int loketSelesai[3] = {0, 0, 0}; // Menyimpan jumlah pelanggan terlayani per loket

    printf("Masukkan jumlah pelanggan: ");
    scanf("%d", &jumlahPelanggan);

    for (i = 0; i < jumlahPelanggan; i++) {
        p.nomorAntrian = i + 1;
        printf("Masukkan waktu layanan untuk pelanggan %d (dalam menit): ", p.nomorAntrian);
        scanf("%d", &p.waktuLayanan);
        enqueue(&antrian, p);
    }

    // Proses pelayanan
    while (!isEmpty(&antrian)) {
        for (int j = 0; j < 3; j++) { // Tiga loket
            if (!isEmpty(&antrian)) {
                Pelanggan pLayani = dequeue(&antrian);
                waktuLoket[j] += pLayani.waktuLayanan;
                loketSelesai[j]++;
                printf("Pelanggan %d dilayani di loket %d selama %d menit\n", 
                       pLayani.nomorAntrian, j + 1, pLayani.waktuLayanan);
            }
        }
    }

    // Hitung dan tampilkan statistik
    hitungStatistik(&antrian, jumlahPelanggan);

    return 0;
}
