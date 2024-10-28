#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PERALATAN 100
#define FILENAME "inventaris.txt"

typedef struct {
    char kode[20];
    char nama[50];
    int jumlah;
    char kondisi[20];
} Peralatan;

// Fungsi untuk menambah peralatan
void tambahPeralatan(Peralatan *inventaris, int *count) {
    if (*count >= MAX_PERALATAN) {
        printf("Inventaris sudah penuh!\n");
        return;
    }

    Peralatan p;
    printf("Masukkan kode peralatan: ");
    scanf("%s", p.kode);
    printf("Masukkan nama peralatan: ");
    getchar(); // Membersihkan newline
    fgets(p.nama, sizeof(p.nama), stdin);
    p.nama[strcspn(p.nama, "\n")] = 0; // Menghapus newline
    printf("Masukkan jumlah: ");
    scanf("%d", &p.jumlah);
    printf("Masukkan kondisi: ");
    getchar(); // Membersihkan newline
    fgets(p.kondisi, sizeof(p.kondisi), stdin);
    p.kondisi[strcspn(p.kondisi, "\n")] = 0; // Menghapus newline

    inventaris[*count] = p;
    (*count)++;
    printf("Peralatan berhasil ditambahkan!\n");
}

// Fungsi untuk mengubah data peralatan
void ubahPeralatan(Peralatan *inventaris, int count) {
    char kode[20];
    printf("Masukkan kode peralatan yang ingin diubah: ");
    scanf("%s", kode);

    for (int i = 0; i < count; i++) {
        if (strcmp(inventaris[i].kode, kode) == 0) {
            printf("Masukkan nama peralatan baru: ");
            getchar(); // Membersihkan newline
            fgets(inventaris[i].nama, sizeof(inventaris[i].nama), stdin);
            inventaris[i].nama[strcspn(inventaris[i].nama, "\n")] = 0; // Menghapus newline
            printf("Masukkan jumlah baru: ");
            scanf("%d", &inventaris[i].jumlah);
            printf("Masukkan kondisi baru: ");
            getchar(); // Membersihkan newline
            fgets(inventaris[i].kondisi, sizeof(inventaris[i].kondisi), stdin);
            inventaris[i].kondisi[strcspn(inventaris[i].kondisi, "\n")] = 0; // Menghapus newline
            printf("Peralatan berhasil diubah!\n");
            return;
        }
    }
    printf("Kode peralatan tidak ditemukan!\n");
}

// Fungsi untuk menghapus data peralatan
void hapusPeralatan(Peralatan *inventaris, int *count) {
    char kode[20];
    printf("Masukkan kode peralatan yang ingin dihapus: ");
    scanf("%s", kode);

    for (int i = 0; i < *count; i++) {
        if (strcmp(inventaris[i].kode, kode) == 0) {
            for (int j = i; j < *count - 1; j++) {
                inventaris[j] = inventaris[j + 1]; // Menggeser elemen
            }
            (*count)--;
            printf("Peralatan berhasil dihapus!\n");
            return;
        }
    }
    printf("Kode peralatan tidak ditemukan!\n");
}

// Fungsi untuk menyimpan data peralatan ke file
void simpanData(Peralatan *inventaris, int count) {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Gagal membuka file untuk menyimpan data!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s\n%s\n%d\n%s\n", inventaris[i].kode, inventaris[i].nama,
                inventaris[i].jumlah, inventaris[i].kondisi);
    }

    fclose(file);
    printf("Data peralatan berhasil disimpan ke file!\n");
}

// Fungsi untuk membaca data peralatan dari file
void bacaData(Peralatan *inventaris, int *count) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("Gagal membuka file untuk membaca data!\n");
        return;
    }

    while (fscanf(file, "%s\n%[^\n]\n%d\n%[^\n]\n", inventaris[*count].kode,
                  inventaris[*count].nama, &inventaris[*count].jumlah,
                  inventaris[*count].kondisi) != EOF) {
        (*count)++;
    }

    fclose(file);
    printf("Data peralatan berhasil dibaca dari file!\n");
}

// Fungsi untuk menampilkan laporan inventaris
void tampilkanLaporan(Peralatan *inventaris, int count) {
    printf("\nLaporan Inventaris Peralatan:\n");
    for (int i = 0; i < count; i++) {
        printf("Kode: %s, Nama: %s, Jumlah: %d, Kondisi: %s\n",
               inventaris[i].kode, inventaris[i].nama,
               inventaris[i].jumlah, inventaris[i].kondisi);
    }
}

// Fungsi untuk mengurutkan inventaris berdasarkan kode
void urutkanInventaris(Peralatan *inventaris, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(inventaris[j].kode, inventaris[j + 1].kode) > 0) {
                Peralatan temp = inventaris[j];
                inventaris[j] = inventaris[j + 1];
                inventaris[j + 1] = temp;
            }
        }
    }
    printf("Inventaris berhasil diurutkan berdasarkan kode!\n");
}

int main() {
    Peralatan inventaris[MAX_PERALATAN];
    int count = 0;
    int pilihan;

    do {
        printf("\nMenu:\n");
        printf("1. Tambah Peralatan\n");
        printf("2. Ubah Peralatan\n");
        printf("3. Hapus Peralatan\n");
        printf("4. Simpan Data\n");
        printf("5. Baca Data\n");
        printf("6. Tampilkan Laporan\n");
        printf("7. Urutkan Inventaris\n");
        printf("8. Keluar\n");
        printf("Pilih opsi: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                tambahPeralatan(inventaris, &count);
                break;
            case 2:
                ubahPeralatan(inventaris, count);
                break;
            case 3:
                hapusPeralatan(inventaris, &count);
                break;
            case 4:
                simpanData(inventaris, count);
                break;
            case 5:
                bacaData(inventaris, &count);
                break;
            case 6:
                urutkanInventaris(inventaris, count);
                tampilkanLaporan(inventaris, count);
                break;
            case 7:
                urutkanInventaris(inventaris, count);
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
