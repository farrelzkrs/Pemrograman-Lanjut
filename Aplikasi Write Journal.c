#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// Jumlah Kata
int countwrd(const char *str) {
    int cnt = 0, word = 0;
    while (*str) {
        if (*str == ' ' || *str == '\n' || *str == '\t') {
            word = 0;
        } else if (!word) {
            word = 1;
            cnt++;
        }
        str++;
    }
    return cnt;
}

// Jumlah Koma
int countcm(const char *str) {
    int cnt = 0;
    while (*str) {
        if (*str == ',') {
            cnt++;
        }
        str++;
    }
    return cnt + 1;
}

// Email Validate
int valEmail(const char *email) {
    const char *domain = strstr(email, "@");
    if (domain && strstr(domain, ".ac.id")) {
        return 1;
    }
    return 0;
}

// Aplikasi Write Journal
void writeJournalApk() {
    FILE *file = fopen("journal.txt", "a");
    if (file == NULL) {
        printf("Error membuka file untuk menulis jurnal.\n");
        return;
    }

    char judul[70], penulis[100], instansi[300], email[200], abstrak[200], katakunci[300];
    
    // Input Judul
    system("cls");
    printf("\nMasukkan judul jurnal (5-14 kata) : ");
    fgets(judul, sizeof(judul), stdin);
    judul[strcspn(judul, "\n")] = 0;
    int jumlahjudul = countwrd(judul);
    if (jumlahjudul < 5 || jumlahjudul > 14) {
        printf("Judul harus terdiri dari 5-14 kata.\n");
        getch();
        system("cls");
        fclose(file);
        return;
    }

    // Input Nama Penulis
    printf("Masukkan nama penulis (maksimal 3) : ");
    fgets(penulis, sizeof(penulis), stdin);
    penulis[strcspn(penulis, "\n")] = 0;
    int jumlahpenulis = countcm(penulis);
    if (jumlahpenulis > 3) {
        printf("Jumlah penulis maksimal adalah 3.\n");
        getch();
        system("cls");
        fclose(file);
        return;
    }

    // Input Instansi
    printf("Masukkan instansi : ");
    fgets(instansi, sizeof(instansi), stdin);
    instansi[strcspn(instansi, "\n")] = 0;

    // Input Email
    printf("Masukkan email penulis : ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = 0;
    if (!valEmail(email)) {
        printf("Email tidak valid. Harus menggunakan domain .ac.id\n");
        getch();
        system("cls");
        fclose(file);
        return;
    }

    // Input Abstrak
    printf("Masukkan abstrak (maksimal 200 kata) : ");
    fgets(abstrak, sizeof(abstrak), stdin);
    abstrak[strcspn(abstrak, "\n")] = 0;
    int jumlahkata = countwrd(abstrak);
    if (jumlahkata > 200) {
        printf("Abstrak melebihi 200 kata.\n");
        getch();
        system("cls");
        fclose(file);
        return;
    }

    // Input Kata Kunci
    printf("Masukkan kata kunci (3-5 kata): ");
    fgets(katakunci, sizeof(katakunci), stdin);
    katakunci[strcspn(katakunci, "\n")] = 0;
    int jmlkatakunci = countcm(katakunci);
    if (jmlkatakunci > 5 || jmlkatakunci < 3) {
        printf("Jumlah kata kunci harus antara 3-5.\n");
        getch();
        system("cls");
        fclose(file);
        return;
    }

    // Simpan ke file
    fprintf(file, "Judul: %s\n", judul);
    fprintf(file, "Penulis: %s\n", penulis);
    fprintf(file, "Instansi: %s\n", instansi);
    fprintf(file, "Email: %s\n", email);
    fprintf(file, "Abstrak: %s\n", abstrak);
    fprintf(file, "Kata Kunci: %s\n\n", katakunci);

    fclose(file);
    printf("Jurnal berhasil disimpan.\n");
    getch();
}

// Menampilkan jurnal
void bacaJurnal() {
	system("cls");
    FILE *file = fopen("journal.txt", "r");
    if (file == NULL) {
        printf("Mohon maaf, jurnal kamu belom ditulis/terdaftar.\n");
        return;
    }

    char line[1000];
    printf("\n=========== Daftar Jurnal ===========\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    printf("=======================================\n");

    fclose(file);
    getch();
}

// Tampilan awal
int main() {
    int pilihan;

    do {
    	system("cls");
        printf("\n========== Write Journal Apk (KW) ==========\n");
        printf("1. Tulis jurnalmu sekarang!\n");
        printf("2. Baca jurnal yang sudah kamu masukkan!\n");
        printf("3. Keluar\n");
        printf("Pilih opsi (1-3): ");
        fflush(stdin);
        scanf("%d", &pilihan);
        getchar();

        switch (pilihan) {
            case 1:
                writeJournalApk();
                break;
                getch();
            case 2:
                bacaJurnal();
                break;
            case 3:
                printf("Keluar dari aplikasi.\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan coba lagi.\n");
                getch();
        }
    }while (pilihan != 3);

    return 0;
}
