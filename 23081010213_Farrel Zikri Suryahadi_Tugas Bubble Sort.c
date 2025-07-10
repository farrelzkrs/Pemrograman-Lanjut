#include <stdio.h>
#include <string.h>
#include <conio.h>

typedef struct Mahasiswa {
    char* npm;
    char* nama;
    char* prodi;
    float ipk;
} mhs;

void swp(mhs *a, mhs *b) {
    mhs t = *a;
    *a = *b;
    *b = t;
}

void showMhs(mhs *mahasw, int n);
void sortMhs(mhs *mahasw, int n, int ch, int ch2);

int main() {
    mhs mahasw[7] = {
        {"23081010213", "Farrel Zikri", "Informatika", 3.73},
        {"23082010119", "Alhamdulillah Lanang Anakku", "Sistem Informasi", 3.5},
        {"23022010038", "Azhar Junaedi", "Agroteknologi", 3.81},
        {"23071010091", "Sherlyn Dara Shifa", "Kedokteran", 4.0},
        {"23045010310", "Anazwah Pratama", "Pariwisata", 3.54},
        {"23011010001", "Anita Zahrotul", "Manajemen", 3.79},
        {"23021010163", "Krisna Reynaldi", "Agribisnis", 3.92}
    };
    
    int ch, ch1, ch2;
    
    do {
    	system("cls");
        printf("1. Tampilkan seluruh data mahasiswa.\n");
        printf("2. Urutkan data mahasiswa.\n");
        printf("3. Dadahh!\n");
        printf("Tentukan pilihan : ");
        scanf("%d", &ch);
        
        switch (ch) {
            case 1:
            	system("cls");
                showMhs(mahasw, 7);
                getch();
                break;
            case 2:
            	system("cls");
                printf("Urutkan berdasarkan\n");
                printf("1. NPM\n");
                printf("2. Nama\n");
                printf("3. Prodi\n");
                printf("4. IPK\n");
                printf("Tentukan pilihan : ");
                scanf("%d", &ch1);
                
                printf("\nMau diurutkan gimana?\n");
                printf("1. Ascending (menaik)\n");
                printf("2. Descending (menurun)\n");
                printf("Tentukan pilihan : ");
                scanf("%d", &ch2);
                
                system("cls");
                sortMhs(mahasw, 7, ch1, ch2);
                showMhs(mahasw, 7);
                getch();
                break;
            case 3:
                printf("Terima kasih!\n");
                break;
            default:
                printf("Pilihan salah!!!\n");
        }
    } while (ch != 3);
    
    return 0;
}

void showMhs(mhs *mahasw, int n) {
    int i = 0;
    while (i < n) {
        printf("%d. %s - %s - %s - %.2f\n\n", i+1, mahasw[i].npm, mahasw[i].nama, mahasw[i].prodi, mahasw[i].ipk);
        i++;
    }
}

void sortMhs(mhs *mahasw, int n, int ch, int ch2) {
    int i = 0;
    while (i < n - 1) {
        int j = 0;
        while (j < n - i - 1) {
            int con = 0;
            
            if (ch == 1) {
                if (ch2 == 1) {
                    if (strcmp(mahasw[j].npm, mahasw[j + 1].npm) > 0) {
                        con = 1;
                    }
                }
				else {
                    if (strcmp(mahasw[j].npm, mahasw[j + 1].npm) < 0) {
                        con = 1;
                    }
                }
            }
			else if (ch == 2) {
                if (ch2 == 1) {
                    if (strcmp(mahasw[j].nama, mahasw[j + 1].nama) > 0) {
                        con = 1;
                    }
                }
				else {
                    if (strcmp(mahasw[j].nama, mahasw[j + 1].nama) < 0) {
                        con = 1;
                    }
                }
            }
            else if (ch == 3) {
            	if (ch2 == 1) {
            		if (strcmp(mahasw[j].prodi, mahasw[j + 1].prodi) > 0) {
            			con = 1;
					}
				}
				else {
					if (strcmp(mahasw[j].prodi, mahasw[j + 1].prodi) < 0) {
						con = 1;
					}
				}
			}
			else if (ch == 4) {
                if (ch2 == 1) {
                    if (mahasw[j].ipk > mahasw[j + 1].ipk) {
                        con = 1;
                    }
                }
				else {
                    if (mahasw[j].ipk < mahasw[j + 1].ipk) {
                        con = 1;
                    }
                }
            }
            
            if (con) {
                swp(&mahasw[j], &mahasw[j + 1]);
            }
            j++;
        }
        i++;
    }
}

