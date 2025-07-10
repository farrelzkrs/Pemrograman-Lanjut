#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Barang {
    char kode[10];
    char nama[50];
    float harga;
    int stok;
};

void tampilkan_menu()
{
    printf("===========================================\n");
    printf("|   SISTEM MANAJEMEN INVENTARIS BARANG    |\n");
    printf("===========================================\n");
    printf("|   1. Tambah Barang                      |\n");
    printf("|   2. Lihat Daftar Barang                |\n");
    printf("|   3. Update Stok Barang                 |\n");
    printf("|   4. Hapus Barang                       |\n");
    printf("|   5. Cari Barang                        |\n");
    printf("|   6. Urutkan Barang                     |\n");
    printf("|   7. Simpan Data ke File                |\n");
    printf("|   8. Baca Data dari File                |\n");
    printf("|   9. Keluar                             |\n");
    printf("===========================================\n");
    printf("Masukkan pilihan Anda: ");
}

struct Barang *cari_barang(struct Barang *arr, int n, char kode[])
{
    if (n == 0)
        return NULL;
    if (strcmp(arr[n - 1].kode, kode) == 0)
        return &arr[n - 1];
    return cari_barang(arr, n - 1, kode);
}

void urutkan_barang(struct Barang *arr, int n, int kriteria, int urutan)
{
    struct Barang temp;
    int swap_condition;

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            switch (kriteria)
            {
            case 1:
                swap_condition = (urutan == 1) ? strcmp(arr[j].kode, arr[j + 1].kode) > 0
                                             : strcmp(arr[j].kode, arr[j + 1].kode) < 0;
                break;
            case 2:
                swap_condition = (urutan == 1) ? strcmp(arr[j].nama, arr[j + 1].nama) > 0
                                             : strcmp(arr[j].nama, arr[j + 1].nama) < 0;
                break;
            case 3:
                swap_condition = (urutan == 1) ? arr[j].harga > arr[j + 1].harga
                                             : arr[j].harga < arr[j + 1].harga;
                break;
            case 4:
                swap_condition = (urutan == 1) ? arr[j].stok > arr[j + 1].stok
                                             : arr[j].stok < arr[j + 1].stok;
                break;
            default:
                printf("Kriteria tidak valid!\n");
                return;
            }

            if (swap_condition)
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void tampilkan_barang(struct Barang *arr, int n)
{
    if (n == 0)
    {
        printf("Data barang kosong!\n");
        return;
    }
    printf("=====================================================================\n");
    printf("| %-10s | %-20s       | %-10s  | %-10s|\n", "Kode", "Nama Barang", "Harga", "Stok");
    printf("=====================================================================\n");
    for (int i = 0; i < n; i++)
    {
        printf("| %-10s | %-20s       | %-10.2f  | %-10d|\n",
               arr[i].kode, arr[i].nama, arr[i].harga, arr[i].stok);
    }
    printf("=====================================================================\n");
}

void simpan_ke_file(struct Barang *arr, int n)
{
    char nama_file[50];
    printf("Masukkan nama file untuk disimpan: ");
    scanf("%s", nama_file);

    FILE *fp = fopen(nama_file, "w");
    if (fp == NULL)
    {
        printf("Error: File tidak bisa dibuka!\n");
        return;
    }
    for (int i = 0; i < n; i++)
    {
        fprintf(fp, "%s %s %.2f %d\n", arr[i].kode, arr[i].nama, arr[i].harga, arr[i].stok);
    }
    fclose(fp);
    printf("Data berhasil disimpan ke file %s!\n", nama_file);
}

int baca_dari_file(struct Barang *arr)
{
    char nama_file[50];
    printf("Masukkan nama file untuk dibuka: ");
    scanf("%s", nama_file);

    FILE *fp = fopen(nama_file, "r");
    if (fp == NULL)
    {
        printf("Error: File tidak ditemukan!\n");
        return 0;
    }

    int i = 0;
    while (fscanf(fp, "%s %s %f %d", arr[i].kode, arr[i].nama, &arr[i].harga, &arr[i].stok) != EOF)
    {
        i++;
    }
    fclose(fp);
    printf("Data berhasil dibaca dari file %s!\n", nama_file);
    return i;
}

int main()
{
    struct Barang daftar_barang[100];
    int jumlah_barang = 0, pilihan;

    do
    {
        system("cls");
        tampilkan_menu();
        scanf("%d", &pilihan);

        system("cls");
        switch (pilihan)
        {
        case 1:
            printf("Masukkan Kode Barang: ");
            scanf("%s", daftar_barang[jumlah_barang].kode);
            printf("Masukkan Nama Barang: ");
            scanf("%s", daftar_barang[jumlah_barang].nama);
            printf("Masukkan Harga Barang: ");
            scanf("%f", &daftar_barang[jumlah_barang].harga);
            printf("Masukkan Stok Barang: ");
            scanf("%d", &daftar_barang[jumlah_barang].stok);
            jumlah_barang++;
            printf("Barang berhasil ditambahkan!\n");
            break;

        case 2:
            tampilkan_barang(daftar_barang, jumlah_barang);
            break;

        case 3:
        {
            char kode[10];
            printf("Masukkan Kode Barang: ");
            scanf("%s", kode);
            struct Barang *barang = cari_barang(daftar_barang, jumlah_barang, kode);
            if (barang)
            {
                printf("Stok lama: %d\nMasukkan Stok Baru: ", barang->stok);
                scanf("%d", &barang->stok);
                printf("Stok berhasil diperbarui!\n");
            }
            else
            {
                printf("Barang tidak ditemukan!\n");
            }
            break;
        }

        case 4:
        {
            char kode[10];
            printf("Masukkan Kode Barang: ");
            scanf("%s", kode);
            struct Barang *barang = cari_barang(daftar_barang, jumlah_barang, kode);
            if (barang)
            {
                int index = barang - daftar_barang;
                for (int i = index; i < jumlah_barang - 1; i++)
                {
                    daftar_barang[i] = daftar_barang[i + 1];
                }
                jumlah_barang--;
                printf("Barang berhasil dihapus!\n");
            }
            else
            {
                printf("Barang tidak ditemukan!\n");
            }
            break;
        }

        case 5:
        {
            char kode[10];
            printf("Masukkan Kode Barang: ");
            scanf("%s", kode);
            struct Barang *barang = cari_barang(daftar_barang, jumlah_barang, kode);
            if (barang)
            {
                printf("Barang Ditemukan: %s - %s - %.2f - %d\n",
                       barang->kode, barang->nama, barang->harga, barang->stok);
            }
            else
            {
                printf("Barang tidak ditemukan!\n");
            }
            break;
        }

        case 6:
        {
            int kriteria, urutan;
            printf("Urutkan Berdasarkan:\n1. Kode\n2. Nama\n3. Harga\n4. Stok\nPilihan: ");
            scanf("%d", &kriteria);
            printf("1. Ascending\n2. Descending\nPilihan: ");
            scanf("%d", &urutan);
            urutkan_barang(daftar_barang, jumlah_barang, kriteria, urutan);
            printf("Barang berhasil diurutkan!\n");
            break;
        }

        case 7:
            simpan_ke_file(daftar_barang, jumlah_barang);
            break;

        case 8:
            jumlah_barang = baca_dari_file(daftar_barang);
            break;

        case 9:
            printf("Keluar dari program. Terima kasih!\n");
            break;

        default:
            printf("Pilihan tidak valid!\n");
        }
        printf("\nTekan Enter untuk melanjutkan...");
        getchar();
        getchar();
    } while (pilihan != 9);

    return 0;
}
