#include <stdio.h>
#include <string.h>
#include <conio.h>

struct orang {
	char nama[100];
	char jkelamin[10];
	char alamat[200];
	int umur;
	int antrian;
};
struct orang pasien[200];

int jmlPasien = 0;

int noAntrian() {
	int base = 500;
	int *atr = &jmlPasien;
	int etc = *atr * 11;
	return base + etc;
}

void inputPasien() {
	system("cls");
	
	if (jmlPasien >= 200) {
        printf("Jumlah pasien sudah maksimal!\n");
        return;
    }
	
	printf("Masukkan Nama Lengkap : ");
	fgets(pasien[jmlPasien].nama, sizeof(pasien[jmlPasien].nama), stdin);
	pasien[jmlPasien].nama[strcspn(pasien[jmlPasien].nama, "\n")] = 0;
	
	printf("Masukkan Jenis Kelamin : ");
	fgets(pasien[jmlPasien].jkelamin, sizeof(pasien[jmlPasien].jkelamin), stdin);
	pasien[jmlPasien].jkelamin[strcspn(pasien[jmlPasien].jkelamin, "\n")] = 0;
	
	printf("Masukkan Umur : ");
	scanf("%d", &pasien[jmlPasien].umur);
	getchar();
	
	printf("Masukkan Alamat : ");
	fgets(pasien[jmlPasien].alamat, sizeof(pasien[jmlPasien].alamat), stdin);
	pasien[jmlPasien].alamat[strcspn(pasien[jmlPasien].alamat, "\n")] = 0;
	
	pasien[jmlPasien].antrian = noAntrian();
	printf("Nomor antrian Anda adalah %d", pasien[jmlPasien].antrian);
	
	FILE *file = fopen("infopasien.txt", "a");
    if (file != NULL) {
        fprintf(file, "Nama: %s\nJenis Kelamin: %c\nUmur: %d\nalamat: %s\nNomor Antrian: %d\n\n===========================\n\n",
                pasien[jmlPasien].nama, pasien[jmlPasien].jkelamin, pasien[jmlPasien].umur,
                pasien[jmlPasien].alamat, pasien[jmlPasien].antrian);
        fclose(file);
        printf("\n\nData pasien berhasil disimpan!\n");
    } else {
        printf("Tidak dapat membuka file untuk menyimpan data.\n");
    }
    
	jmlPasien++;
	getch();
}

void searchPasien() {
	system("cls");
	int antri, src = 0;
	
	printf("Masukkan nomor antrian : ");
	scanf("%d", &antri);
	
	int i = 0;
	while (i < jmlPasien) {
		if (pasien[i].antrian == antri) {
			printf("Nomor %d terdaftar atas nama %s.\n", antri, pasien[i].nama);
			src = 1;
			getch();
			break;
		}
		i++;
	}
	if (!src) {
		printf("Nomor antrian %d tidak terdaftar.\n", antri);
		getch();
	}
}

void showPasien() {
	system("cls");
	
	FILE *file = fopen("infopasien.txt", "r");
    if (jmlPasien == 0) {
        printf("Belum ada data pasien.\n");
        return;
    }

    char line[2000];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    printf("=======================================\n");

    fclose(file);
}

int main()
{
	char ch;
	
	FILE *file = fopen("infopasien.txt", "r");
	if (file != NULL) {
		while (fscanf(file, "Nama: %99[^\n]\nJenisKelamin: %c\nUmur: %d\nalamat: %99[^\n]\nNomor Antrian: %d\n\n===========================\n\n",
            	pasien[jmlPasien].nama, pasien[jmlPasien].jkelamin, &pasien[jmlPasien].umur,
                pasien[jmlPasien].alamat, &pasien[jmlPasien].antrian) == 4) {
            jmlPasien++;
        }
        fclose(file);
        printf("Data pasien berhasil dimuat!\n");
	}
	else {
		printf("Tidak ada data pasien yang tersimpan.\n");
	}
	
	do {
		system("cls");
		printf("1. Masukkan Data Pasien\n");
		printf("2. Cari Data Pasien\n\n");
		printf("Tentukan pilihan Anda (Klik 'x' untuk keluar) : ");
		scanf(" %c", &ch);
		getchar();
		
		if (ch == '1') {
			inputPasien();
		}
		else if (ch == '2') {
			searchPasien();
		}
		else if (ch == 'p') {
			showPasien();
			getch();
		}
		else if (ch == 'x') {
			break;
		}
		else {
			printf("Pilihan invalid!");
			getch();
		}
	} while (ch != 'x');
	
	return 0;
}
