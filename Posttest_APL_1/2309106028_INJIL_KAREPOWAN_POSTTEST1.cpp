#include <iostream>
#include <iomanip> // Untuk membatasi angka di belakang koma
#include <cctype> // library pembanding tipe data

using namespace std;

// Program Konversi Mata Uang,
// 1 Dollar = IDR 15.700
// 1 Dollar = 0,92 Euro
// 1 dollar = 150 Yen

bool login(string usn, string pass);
int main_menu();
// Nilai tukar berpatokan pada 1 dollar
double convert(double amount, double rateInput, double rateOutput);

// Untuk Membersihkan Terminal
void clearScreen() {
    cout << "\033[2J\033[1;1H";
}

int main(){
    clearScreen();
    // Deklarasi Awal
    int pilihan;
    char pilgan;
    double dollar, rupiah, euro, yen;
    double dollarRate = 1;
    double rupiahRate = 15700;
    double euroRate = 0.92;
    double yenRate = 150;
    double inputMoney;
    bool retry;

    // Data Username & Password
    string usn = "Injil Karepowan";
    string pass = "2309106028";
    
    // Mengecek Kebehasilan Login
    if (login(usn, pass) == false){
        return 0;
    }

    // Menu Utama
    do{
        pilihan = main_menu();
        switch (pilihan){
            // Mengubah Rupiah
            case 1:
                clearScreen();
                cout << "-- [1] KONVERSI RUPIAH --\n";
                cout << "MASUKKAN JUMLAH RUPIAH > "; cin >> inputMoney;
                clearScreen();
                cout << "-- [1] KONVERSI RUPIAH --\n";
                cout << "MASUKKAN JUMLAH RUPIAH > " << inputMoney << " IDR\n";
                dollar = convert(inputMoney, rupiahRate, dollarRate);
                euro = convert(inputMoney, rupiahRate, euroRate);
                yen = convert(inputMoney, rupiahRate, yenRate);
                cout << fixed << setprecision(2) << "HASIL DALAM DOLLLAR : " << dollar << " USD" << endl;
                cout << fixed << setprecision(2) << "HASIL DALAM EURO : " << euro << " EURO" << endl;
                cout << fixed << setprecision(2) << "HASIL DALAM YEN : " << yen << " JPY" << endl;
                break;
            // Mengubah Dollar
            case 2:
                clearScreen();
                cout << "-- [2] KONVERSI DOLLAR --\n";
                cout << "MASUKKAN JUMLAH DOLLAR > "; cin >> inputMoney;
                clearScreen();
                cout << "-- [2] KONVERSI DOLLAR --\n";
                cout << "MASUKKAN JUMLAH DOLLAR > " << inputMoney << " USD\n";
                rupiah = convert(inputMoney, dollarRate, rupiahRate);
                euro = convert(inputMoney, dollarRate, euroRate);
                yen = convert(inputMoney, dollarRate, yenRate);
                cout << fixed << setprecision(2) << "HASIL DALAM RUPIAH : " << rupiah << " IDR" << endl;
                cout << fixed << setprecision(2) << "HASIL DALAM EURO : " << euro << " EURO" << endl;
                cout << fixed << setprecision(2) << "HASIL DALAM YEN : " << yen << " JPY" << endl;
                break;
            // Mengubah Euro
            case 3:
                clearScreen();
                cout << "-- [3] KONVERSI EURO --\n";
                cout << "MASUKKAN JUMLAH EURO > "; cin >> inputMoney;
                clearScreen();
                cout << "-- [3] KONVERSI EURO --\n";
                cout << "MASUKKAN JUMLAH EURO > " << inputMoney << " EURO\n";
                dollar = convert(inputMoney, euroRate, dollarRate);
                rupiah = convert(inputMoney, euroRate, rupiahRate);
                yen = convert(inputMoney, euroRate, yenRate);
                cout << fixed << setprecision(2) << "HASIL DALAM DOLLAR : " << dollar << " USD" << endl;
                cout << fixed << setprecision(2) << "HASIL DALAM RUPIAH : " << rupiah << " IDR" << endl;
                cout << fixed << setprecision(2) << "HASIL DALAM YEN : " << yen << " JPY" << endl;
                break;
            // Mengubah Yen
            case 4:
                clearScreen();
                cout << "-- [4] KONVERSI YEN --\n";
                cout << "MASUKKAN JUMLAH YEN > "; cin >> inputMoney;
                clearScreen();
                cout << "-- [4] KONVERSI YEN --\n";
                cout << "MASUKKAN JUMLAH YEN > " << inputMoney << " JPY\n";
                dollar = convert(inputMoney, yenRate, dollarRate);
                euro = convert(inputMoney, yenRate, euroRate);
                rupiah = convert(inputMoney, yenRate, rupiahRate);
                cout << fixed << setprecision(2) << "HASIL DALAM DOLLAR : " << dollar << " USD" << endl;
                cout << fixed << setprecision(2) << "HASIL DALAM EURO : " << yen << " EURO" << endl;
                cout << fixed << setprecision(2) << "HASIL DALAM RUPIAH : " << rupiah << " IDR" << endl;
                break;
            // Keluar dari program
            case 5:
                clearScreen();
                cout << "PROGRAM BERHENTI";
                return 0;
        }
        while (true){
            cout << "KEMBALI KE MENU? [Y/N] ?\n>"; cin >> pilgan;
            if (toupper(pilgan) == 'Y'){
                retry = true;
                clearScreen();
                break;
            }
            if(toupper(pilgan) == 'N'){
                retry = false;
                clearScreen();
                cout << "PROGRAM BERHENTI";
                return 0;
            }
        }
    } while (retry == true);
    return 0;
}

int main_menu(){
    int pilihan;
    cout << "----- MENU KONVERSI -----\n";
    cout << "[1] KONVERSI RUPIAH\n";
    cout << "[2] KONVERSI DOLLAR\n";
    cout << "[3] KONVERSI EURO\n";
    cout << "[4] KONVERSI YEN\n";
    cout << "[5] EXIT\n";
    do{
        cout << "MASUKKAN PILIHAN > "; cin >> pilihan; cin.ignore();
    }while (pilihan < 1 || pilihan > 5);
    return pilihan;
}

bool login(string usn, string pass){
    // Batas percobaan login 3 kali
    string inp_usn;
    string inp_pass;
    cout << "-- LOGIN --\n";
    for (int i = 0; i < 3; i++){
        cout << "MASUKKAN USERNAME > "; getline(cin, inp_usn);
        cout << "MASUKKAN PASSWORD > "; getline(cin, inp_pass);

        // Mengecek kebenaran input
        if ((inp_usn == usn) & (inp_pass == pass)){
            // Login berhasil
            clearScreen();
            cout << "LOGIN BERHASIL\n\n";
            return true;
        }
        else if (i<2){
            clearScreen();
            cout << "LOGIN GAGAL, "<<(2-i)<<" KESEMPATAN TERSISA\n";
        }
        else{
            clearScreen();
            cout << "KESEMPATAN LOGIN TELAH HABIS\n";
        }
    }
    return false;
}

double convert(double amount, double rateInput, double rateAfter){
    return (amount/rateInput*rateAfter);
}
