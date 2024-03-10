// Program untuk mengelola data film
#include <iostream>

using namespace std;

// Struktur yang akan menyimpan data film
struct data_film{
    string judul;
    float rating;
    int tahunRilis;
};
// Function Prototype
void clearScreen();
bool login(string user, string pass);
int mainMenu();
void addFilm(data_film array[], int *dataSize);
void readFilm(data_film array[], int *dataSize);
void updateFilm(data_film array[], int *dataSize);
void deleteFilm(data_film array[], int *dataSize);


int main(){
    // Data login
    string user = "Injil Karepowan";
    string pass = "2309106028";

    data_film film [100];
    int n_elemen = 0;
    bool retry;
    
    // Prosedur login
    if (login(user, pass) == false){
        //  Hentikan program jika gagal login
        return 0;
    }

    do{
        retry = true;
        // Tampilkan Menu lalu jalankan perintah sesuai pilihan
        switch (mainMenu()){
            case 1: // Tambah Data Film
                addFilm(film, &n_elemen);
                break;
            case 2: // Tampilkan data film
                readFilm(film, &n_elemen);
                break;
            case 3: // Ubah data film
                updateFilm(film, &n_elemen);
                break;
            case 4: // Hapus data film
                deleteFilm(film, &n_elemen);
                break;
            case 5: // Keluar program
                retry = false;
                clearScreen();
                cout << "Program Berhenti";
                break;
        }
    } while (retry == true);
}

// Untuk membersihkan terminal
void clearScreen(){
    cout << "\033[2J\033[1;1H";
}

bool login(string user, string pass){
    clearScreen();
    string inp_user;
    string inp_pass;
    // Batas percobaan login 3 kali
    cout << "== LOGIN ==\n";
    for (int i = 0; i < 3; i++){
        // Masukkan data login
        cout << "Masukkan Username : "; getline(cin, inp_user);
        cout << "Masukkan Password : "; getline(cin, inp_pass);

        // Mengecek kebenaran login
        if ((inp_user == user) && (inp_pass == pass)){
            // Login berhasil
            clearScreen();
            return true;
        }
        else if(i<2){
            // Login gagal, masih ada kesempatan tersisa
            clearScreen();
            cout << "Login Gagal, " << (2-i) << " Kesempatan Tersisa\n";
        }
        else{
            // Login gagal, kesempatan telah habis
            clearScreen();
            cout << "Kesempatan Login Telah Habis\n";
        }
    }
    return false;
}

int mainMenu(){
    while(true){
        int pilihan;
        cout << "== MENU UTAMA ==\n";
        cout << "[1] Tambah Data Film\n";
        cout << "[2] Tampilkan Data Film\n";
        cout << "[3] Edit Data Film\n";
        cout << "[4] Hapus Data Film\n";
        cout << "[5] Exit\n";
        cout << "Masukkan Pilihan [1-5] : ";
        // Jika pilihan sesuai, kembalikan nilai yang dipilih
        if ((cin >> pilihan) && (pilihan >= 1) && (pilihan <=5)){
            clearScreen();
            cin.ignore();
            return pilihan;
        }
        clearScreen();
        cin.clear(); // Menghapus penanda error pada input
        cin.ignore(100, '\n');
    }
}

void addFilm(data_film array[], int *dataSize){
    clearScreen();
    string inp_judul;
    float inp_rating;
    int inp_tahun;
    bool retry;
    cout  << "== TAMBAH FILM ==\n";
    // Input  Judul Film, tidak boleh ada judul yang duplikat
    while (true){
        retry = false;
        cout  << "Judul Film : ";
        getline(cin, inp_judul);
        // Mengecek apakah terdapat judul duplikat
        if (*dataSize > 0){
            for (int i = 0; i < *dataSize; i++){
                // Jika terdapat judul duplikat, minta input ulang
                if (inp_judul == array[i].judul){
                    cout << "Judul yang dimasukkan tidak bisa digunakan\n";
                    retry = true;
                }
            }
        }
        if (retry == true){
            continue;
        }
        else{
            break;
        }
    }
    // Input Rating
    while (true){
        cout  << "Rating : "; 
        if ((cin >> inp_rating) && (inp_rating >= 0) && (inp_rating<=10)){
            break; // Input sesuai
        }
        else{
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Masukkan Rating yang sesuai [0-10]\n";
        }
    }
    // Input Tahun Rilis
    while (true){
        cout  << "Tahun Rilis : "; 
        if ((cin >> inp_tahun) && (inp_tahun > 0) && (inp_tahun <= 2024)){
            break; // Input sesuai
        }
        else{
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Masukkan Tahun Rilis yang sesuai\n";
        }
    }
    // Masukkan nilai input ke dalam array
    array[*dataSize].judul = inp_judul;
    array[*dataSize].rating = inp_rating;
    array[*dataSize].tahunRilis = inp_tahun;

    clearScreen();
    cout << "Film Berhasil Ditambahkan\n\n";
    (*dataSize)++;
    return;
}

void readFilm(data_film array[], int *dataSize){
    clearScreen();
    string back;
    cout << "== TAMPILKAN DATA FILM ==\n";
    // Jika data kosong, kembali
    if (*dataSize <= 0){
        clearScreen();
        cout << "Tidak ada data film untuk ditampilkan\n\n";
        return;
    }
    // Tampilkan data masing-masing film
    for (int i = 0; i < *dataSize; i++){
        cout << (i+1) << ". " << array[i].judul << endl;
        cout << "Rating : " << array[i].rating << endl;
        cout << "Tahun Rilis : " << array[i].tahunRilis << endl;
        cout << endl;
    }
    return;
}

void updateFilm(data_film array[], int *dataSize){
    clearScreen();
    string inp_judul;
    float inp_rating;
    int inp_tahun;
    bool retry;
    cout << " == EDIT DATA FILM ==\n";
    cout << "Masukkan judul dari film yang akan diubah : "; 
    getline (cin, inp_judul);
    for (int i = 0; i < (*dataSize); i++){
        if (inp_judul == (array[i].judul)){
            // Tampilkan data dari film yang ditemukan
            cout << "Judul Film : " << array[i].judul << endl;
            cout << "Rating : " << array[i].rating << endl;
            cout << "Tahun Rilis : " << array[i].tahunRilis << endl << endl;
            // Input Judul Baru
            while (true){
                retry = false;
                cout  << "Masukkan Judul Baru : "; getline(cin, inp_judul);
                // Mengecek apakah terdapat judul duplikat
                if (*dataSize > 0){
                    for (int i = 0; i < *dataSize; i++){
                        // Jika terdapat judul duplikat, minta input ulang
                        if (inp_judul == array[i].judul){
                            cout << "Judul yang dimasukkan tidak bisa digunakan\n";
                            retry = true;
                        }
                    }
                }
                if (retry == true){
                    continue;
                }
                else{
                    break;
                }
            }
            // Input Rating
            while (true){
                cout  << "Masukkan Rating Baru : "; 
                if ((cin >> inp_rating) && (inp_rating >= 0) && (inp_rating<=10)){
                    break; // Input sudah sesuai
                }
                else{ // Input belum sesuai
                    cin.clear();
                    cin.ignore(100, '\n');
                    cout << "Masukkan Rating Yang Sesuai [0-10]\n";
                }
            }
            // Input Tahun Rilis
            while (true){
                cout  << "Masukkan Tahun Rilis Baru : "; 
                if ((cin >> inp_tahun) && (inp_tahun > 0) && (inp_tahun <= 2024)){
                    break; // Input sudah sesuai
                }
                else{ // Input belum sesuai
                    cin.clear();
                    cin.ignore(100, '\n');
                    cout << "Masukkan Tahun Rilis Yang Sesuai\n";
                }
            }
            // Gantikan data lama dengan data baru yang diinput
            array[i].judul = inp_judul;
            array[i].rating = inp_rating;
            array[i].tahunRilis = inp_tahun;

            clearScreen();
            cout << "Data Film Berhasil Diedit\n\n";
            return;
        }
    }
    cout << "Tidak ditemukan film dengan judul " << inp_judul << endl << endl;
    return;
}

void deleteFilm(data_film array[], int *dataSize){
    clearScreen();
    string inp_judul;
    int lastIndex = *dataSize-1;
    cout << "== HAPUS DATA FILM ==\n";
    cout << "Masukkan judul dari film yang akan dihapus : ";
    getline(cin, inp_judul);
    // Jika ada data dalam array, cari yang sama dengan input
    if (*dataSize > 0){
        for (int i = 0; i < (*dataSize); i++){
            if (inp_judul == array[i].judul){
                // Jika ada yang sama, geser index setelahnya satu kali ke kiri
                for (int j = i; j < (*dataSize); j++){
                    if (j != lastIndex){
                        array[j] = array[j+1];
                    }
                }
                clearScreen();
                // Kurangi 1 jumlah data 
                (*dataSize)--;
                cout << "Data dari film " << inp_judul << " berhasil dihapus\n\n";
                return;
            }
        }
    }
    clearScreen();
    cout << "Tidak ditemukan film dengan judul " << inp_judul << endl << endl;
    return;
}
