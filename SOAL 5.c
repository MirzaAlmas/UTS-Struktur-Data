#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUKU 100
#define MAX_RIWAYAT 100
#define MAX_ANTRIAN 100

typedef struct {
    char isbn[20];
    char judul[50];
    char pengarang[50];
    int tahunTerbit;
} Buku;

typedef struct {
    Buku* data[MAX_BUKU];
    int count;
} ArrayBuku;

typedef struct {
    char isbn[20];
    char tanggalPinjam[11]; // format: dd-mm-yyyy
} Riwayat;

typedef struct {
    Riwayat data[MAX_RIWAYAT];
    int top;
} Stack;

typedef struct {
    char isbn[20];
} Antrian;

typedef struct {
    Antrian data[MAX_ANTRIAN];
    int front;
    int rear;
} Queue;

// Fungsi untuk menambah buku
void tambahBuku(ArrayBuku* arr) {
    if (arr->count >= MAX_BUKU) {
        printf("Buku sudah penuh!\n");
        return;
    }

    Buku* bukuBaru = (Buku*)malloc(sizeof(Buku));
    printf("Masukkan ISBN: ");
    scanf("%s", bukuBaru->isbn);
    printf("Masukkan judul: ");
    getchar(); // Membersihkan newline
    fgets(bukuBaru->judul, sizeof(bukuBaru->judul), stdin);
    bukuBaru->judul[strcspn(bukuBaru->judul, "\n")] = 0; // Menghapus newline
    printf("Masukkan pengarang: ");
    fgets(bukuBaru->pengarang, sizeof(bukuBaru->pengarang), stdin);
    bukuBaru->pengarang[strcspn(bukuBaru->pengarang, "\n")] = 0; // Menghapus newline
    printf("Masukkan tahun terbit: ");
    scanf("%d", &bukuBaru->tahunTerbit);

    arr->data[arr->count++] = bukuBaru;
    printf("Buku berhasil ditambahkan!\n");
}

// Fungsi untuk mencari buku
void cariBuku(ArrayBuku* arr, const char* isbn) {
    for (int i = 0; i < arr->count; i++) {
        if (strcmp(arr->data[i]->isbn, isbn) == 0) {
            printf("Buku ditemukan:\n");
            printf("ISBN: %s\nJudul: %s\nPengarang: %s\nTahun Terbit: %d\n",
                   arr->data[i]->isbn, arr->data[i]->judul,
                   arr->data[i]->pengarang, arr->data[i]->tahunTerbit);
            return;
        }
    }
    printf("Buku tidak ditemukan!\n");
}

// Fungsi untuk menampilkan semua buku
void tampilkanBuku(ArrayBuku* arr) {
    printf("Daftar Buku:\n");
    for (int i = 0; i < arr->count; i++) {
        printf("ISBN: %s, Judul: %s, Pengarang: %s, Tahun Terbit: %d\n",
               arr->data[i]->isbn, arr->data[i]->judul,
               arr->data[i]->pengarang, arr->data[i]->tahunTerbit);
    }
}

// Fungsi untuk menambah riwayat peminjaman
void pinjamBuku(Stack* stack, const char* isbn, const char* tanggal) {
    if (stack->top >= MAX_RIWAYAT - 1) {
        printf("Riwayat peminjaman sudah penuh!\n");
        return;
    }

    Riwayat riwayat;
    strcpy(riwayat.isbn, isbn);
    strcpy(riwayat.tanggalPinjam, tanggal);
    stack->data[++stack->top] = riwayat;

    printf("Buku dengan ISBN %s berhasil dipinjam pada %s\n", isbn, tanggal);
}

// Fungsi untuk mengembalikan buku
void kembalikanBuku(Stack* stack) {
    if (stack->top < 0) {
        printf("Tidak ada buku yang dipinjam!\n");
        return;
    }

    Riwayat riwayat = stack->data[stack->top--];
    printf("Buku dengan ISBN %s berhasil dikembalikan. Tanggal peminjaman: %s\n",
           riwayat.isbn, riwayat.tanggalPinjam);
}

// Fungsi untuk mengelola antrian peminjaman
void enqueue(Queue* q, const char* isbn) {
    if (q->rear >= MAX_ANTRIAN - 1) {
        printf("Antrian penuh!\n");
        return;
    }

    strcpy(q->data[++q->rear].isbn, isbn);
    if (q->front == -1) {
        q->front = 0;
    }
    printf("Buku dengan ISBN %s ditambahkan ke antrian.\n", isbn);
}

void dequeue(Queue* q) {
    if (q->front == -1) {
        printf("Antrian kosong!\n");
        return;
    }

    printf("Buku dengan ISBN %s diambil dari antrian.\n", q->data[q->front].isbn);
    if (q->front >= q->rear) {
        q->front = q->rear = -1; // Reset antrian
    } else {
        q->front++;
    }
}

int main() {
    ArrayBuku arrBuku = { .count = 0 };
    Stack stackRiwayat = { .top = -1 };
    Queue queuePeminjaman = { .front = -1, .rear = -1 };

    int pilihan;
    char isbn[20], tanggal[11];

    do {
        printf("\nMenu:\n");
        printf("1. Tambah Buku\n");
        printf("2. Cari Buku\n");
        printf("3. Tampilkan Buku\n");
        printf("4. Pinjam Buku\n");
        printf("5. Kembalikan Buku\n");
        printf("6. Enqueue Antrian Peminjaman\n");
        printf("7. Dequeue Antrian Peminjaman\n");
        printf("8. Keluar\n");
        printf("Pilih opsi: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                tambahBuku(&arrBuku);
                break;
            case 2:
                printf("Masukkan ISBN yang dicari: ");
                scanf("%s", isbn);
                cariBuku(&arrBuku, isbn);
                break;
            case 3:
                tampilkanBuku(&arrBuku);
                break;
            case 4:
                printf("Masukkan ISBN buku yang ingin dipinjam: ");
                scanf("%s", isbn);
                printf("Masukkan tanggal peminjaman (dd-mm-yyyy): ");
                scanf("%s", tanggal);
                pinjamBuku(&stackRiwayat, isbn, tanggal);
                break;
            case 5:
                kembalikanBuku(&stackRiwayat);
                break;
            case 6:
                printf("Masukkan ISBN buku untuk antrian peminjaman: ");
                scanf("%s", isbn);
                enqueue(&queuePeminjaman, isbn);
                break;
            case 7:
                dequeue(&queuePeminjaman);
                break;
            case 8:
                printf("Terima kasih!\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 8);

    return 0;
}
