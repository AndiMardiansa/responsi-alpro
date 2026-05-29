#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

struct Mahasiswa {
    string nim;
    string nama;
    float tugas;
    float uts;
    float uas;
    float akhir;
    char grade;
};

Mahasiswa mhs[100];
int jumlahData = 0;

float rekursiJumlah(float arr[], int n) {
    
    if (n == 0) {
        return 0;
    }

    return arr[n - 1] + rekursiJumlah(arr, n - 1);
}

float hitungNilaiAkhir(float tugas, float uts, float uas) {

    float nilai[3];

    nilai[0] = 0.3 * tugas;
    nilai[1] = 0.3 * uts;
    nilai[2] = 0.4 * uas;

    return rekursiJumlah(nilai, 3);
}

char tentukanGrade(float nilai) {

    if (nilai >= 85) {
        return 'A';
    }
    else if (nilai >= 70) {
        return 'B';
    }
    else if (nilai >= 60) {
        return 'C';
    }
    else if (nilai >= 50) {
        return 'D';
    }
    else {
        return 'E';
    }
}

void bacaFile() {

    ifstream file("data_nilai.txt");

    if (!file) {
        cout << "File tidak ditemukan!" << endl;
        return;
    }

    while (
        file >> mhs[jumlahData].nim
             >> mhs[jumlahData].nama
             >> mhs[jumlahData].tugas
             >> mhs[jumlahData].uts
             >> mhs[jumlahData].uas
    ) {

        mhs[jumlahData].akhir =
            hitungNilaiAkhir(
                mhs[jumlahData].tugas,
                mhs[jumlahData].uts,
                mhs[jumlahData].uas
            );

        mhs[jumlahData].grade =
            tentukanGrade(mhs[jumlahData].akhir);

        jumlahData++;
    }

    file.close();
}

void tampilData() {

    cout << fixed << setprecision(2);

    cout << "\nDATA MAHASISWA\n";
    cout << "============================================================\n";
    cout << "NIM\tNama\tTugas\tUTS\tUAS\tAkhir\tGrade\n";
    cout << "============================================================\n";

    for (int i = 0; i < jumlahData; i++) {

        cout << mhs[i].nim << "\t"
             << mhs[i].nama << "\t"
             << mhs[i].tugas << "\t"
             << mhs[i].uts << "\t"
             << mhs[i].uas << "\t"
             << mhs[i].akhir << "\t"
             << mhs[i].grade << endl;
    }
}

void cariNIM() {

    string cari;
    bool ditemukan = false;

    cout << "\nMasukkan NIM yang dicari : ";
    cin >> cari;

    for (int i = 0; i < jumlahData; i++) {

        if (mhs[i].nim == cari) {

            cout << "\nDATA DITEMUKAN\n";
            cout << "NIM          : " << mhs[i].nim << endl;
            cout << "Nama         : " << mhs[i].nama << endl;
            cout << "Nilai Akhir  : " << mhs[i].akhir << endl;
            cout << "Grade        : " << mhs[i].grade << endl;

            ditemukan = true;
            break;
        }
    }

    if (!ditemukan) {
        cout << "Data tidak ditemukan!\n";
    }
}

void nilaiTerendah() {

    int index = 0;

    for (int i = 1; i < jumlahData; i++) {

        if (mhs[i].akhir < mhs[index].akhir) {
            index = i;
        }
    }

    cout << "\nMAHASISWA DENGAN NILAI TERENDAH\n";
    cout << "Nama         : " << mhs[index].nama << endl;
    cout << "Nilai Akhir  : " << mhs[index].akhir << endl;
}

void rataRata() {

    float total = 0;

    for (int i = 0; i < jumlahData; i++) {
        total += mhs[i].akhir;
    }

    float rata = total / jumlahData;

    cout << "\nRata-rata Nilai Akhir : "
         << rata << endl;
}

void simpanFile() {

    ofstream output("hasil_analisis_nilai.txt");

    output << fixed << setprecision(2);

    output << "HASIL ANALISIS NILAI MAHASISWA\n";
    output << "============================================================\n";
    output << "NIM\tNama\tTugas\tUTS\tUAS\tAkhir\tGrade\n";
    output << "============================================================\n";

    for (int i = 0; i < jumlahData; i++) {

        output << mhs[i].nim << "\t"
               << mhs[i].nama << "\t"
               << mhs[i].tugas << "\t"
               << mhs[i].uts << "\t"
               << mhs[i].uas << "\t"
               << mhs[i].akhir << "\t"
               << mhs[i].grade << endl;
    }

    output.close();

    cout << "\nData berhasil disimpan ke file!\n";
}

// Main program
int main() {

    // Membaca file
    bacaFile();

    // Menampilkan data
    tampilData();

    // Searching berdasarkan NIM
    cariNIM();

    // Menampilkan nilai terendah
    nilaiTerendah();

    // Menghitung rata-rata
    rataRata();

    // Menyimpan hasil ke file
    simpanFile();

    return 0;
}