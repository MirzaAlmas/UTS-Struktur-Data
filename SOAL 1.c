#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MAHASISWA 10

typedef struct {
    char NIM[20];
    char nama[50];
    float IPK;
} Mahasiswa;

// Fungsi untuk menambah data mahasiswa
void tambahMahasiswa(Mahasiswa** arr, int* count) {
    if (*count >= MAX_MAHASISWA) {
        printf("Data mahasiswa sudah penuh!\n");
        return;
    }

    arr[*count] = (Mahasiswa*)malloc(sizeof(Mahasiswa));

    printf("Masukkan NIM: ");
    scanf("%s", arr[*count]->NIM);
    printf("Masukkan Nama: ");
    getchar(); // Membersihkan newline dari input sebelumnya
    fgets(arr[*count]->nama, sizeof(arr[*count]->nama), stdin);
    arr[*count]->nama[strcspn(arr[*count]->nama, "\n")] = 0; // Menghapus newline
    printf("Masukkan IPK: ");
    scanf("%f", &(arr[*count]->IPK));

    (*count)++;
    printf("Mahasiswa berhasil ditambahkan!\n");
}

// Fungsi untuk menghapus data mahasiswa
void hapusMahasiswa(Mahasiswa** arr, int* count) {
    if (*count <= 0) {
        printf("Tidak ada data mahasiswa untuk dihapus!\n");
        return;
    }

    printf("Masukkan index mahasiswa yang ingin dihapus (0-%d): ", *count - 1);
    int index;
    scanf("%d", &index);

    if (index < 0 || index >= *count) {
        printf("Index tidak valid!\n");
        return;
    }

    free(arr[index]); // Menghapus data mahasiswa
    for (int i = index; i < *count - 1; i++) {
        arr[i] = arr[i + 1]; // Menggeser elemen
    }

    (*count)--;
    printf("Mahasiswa berhasil dihapus!\n");
}

// Fungsi untuk menampilkan data mahasiswa
void tampilkanMahasiswa(Mahasiswa** arr, int count) {
    if (count == 0) {
        printf("Tidak ada data mahasiswa untuk ditampilkan!\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("Mahasiswa %d:\n", i + 1);
        printf("NIM: %s\n", arr[i]->NIM);
        printf("Nama: %s\n", arr[i]->nama);
        printf("IPK: %.2f\n\n", arr[i]->IPK);
    }
}

// Fungsi untuk mengurutkan data mahasiswa berdasarkan IPK menggunakan bubble sort
void urutkanMahasiswa(Mahasiswa** arr, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (arr[j]->IPK > arr[j + 1]->IPK) {
                // Menukar posisi
                Mahasiswa* temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    printf("Data mahasiswa berhasil diurutkan berdasarkan IPK!\n");
}

int main() {
    Mahasiswa* arr[MAX_MAHASISWA]; // Array of pointers
    int count = 0;
    int pilihan;

    do {
        printf("Menu:\n");
        printf("1. Tambah Mahasiswa\n");
        printf("2. Hapus Mahasiswa\n");
        printf("3. Tampilkan Mahasiswa\n");
        printf("4. Urutkan Mahasiswa berdasarkan IPK\n");
        printf("5. Keluar\n");
        printf("Pilih opsi: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                tambahMahasiswa(arr, &count);
                break;
            case 2:
                hapusMahasiswa(arr, &count);
                break;
            case 3:
                tampilkanMahasiswa(arr, count);
                break;
            case 4:
                urutkanMahasiswa(arr, count);
                break;
            case 5:
                printf("Terima kasih!\n");
                break;
            default:
                printf("Pilihan tidak valid!\n");
        }
    } while (pilihan != 5);

    // Menghapus semua data mahasiswa sebelum keluar
    for (int i = 0; i < count; i++) {
        free(arr[i]);
    }

    return 0;
}
