// Program untuk mengelola data film
#include <iostream>
#include <string>

using namespace std;

// Struktur yang menyimpang data sutradara
struct sutradara{
    string nama;
    int umur;
    string negara;
    
};

// Struktur yang akan menyimpan data film
struct data_film{
    string judul;
    float rating;
    int tahunRilis;
    sutradara direktor;
};
// Function & Procedure Prototype
void clearScreen();
bool login(string user, string pass, int maxTry, int countTry);
int mainMenu();
void addFilm(data_film array[], int *dataSize);
void readFilm_Letter_Descend(data_film array[], int *dataSize);
void readFilm_Number_Ascend(data_film array[], int *dataSize);
void updateFilm(data_film array[], int *dataSize);
void deleteFilm(data_film array[], int *dataSize);

int main(){
    // Data login
    string user = "Injil";
    string pass = "2309106028";
    data_film film [100];
    int n_elemen = 0;
    bool retry;
    
    // Prosedur login
    if (login(user, pass, 3, 1) == false){
        //  Hentikan program jika gagal login
        return 0;
    }

    do{
        retry = true;
        // Tampilkan Menu lalu jalankan perintah sesuai pilihan
        switch (mainMenu()){
            case 1: // Tambah Data Film (sort)
                addFilm(film, &n_elemen);
                break;
            case 2: // Tampilkan data film (search)
                // Tentukan Tipe Sort
                int pilihan;
                while(true){
                    pilihan;
                    cout << "== TIPE SORT ==\n";
                    cout << "[1] Descending - Judul Film\n";
                    cout << "[2] Ascending -  Rating Film\n";
                    cout << "Masukkan Pilihan [1-2] : ";
                    // Jika pilihan sesuai, kembalikan nilai yang dipilih
                    if ((cin >> pilihan) && (pilihan >= 1) && (pilihan <=2)){
                        clearScreen();
                        cin.ignore();
                        break;
                    }
                    clearScreen();
                    cin.clear(); // Menghapus penanda error pada input
                    cin.ignore(100, '\n');
                }
                switch (pilihan){
                    case 1: // Descending, Huruf (Original Sort)
                        readFilm_Letter_Descend(film, &n_elemen);
                        break;
                    case 2: // Ascending, Angka (Re-Sort)
                        readFilm_Number_Ascend(film, &n_elemen);
                        break;
                }
                break;
            case 3: // Ubah data film (search & sort)
                if (n_elemen > 0){
                    updateFilm(film, &n_elemen);
                }
                else {
                    cout << "Tidak ada data film untuk diupdate\n\n";
                }
                break;
            case 4: // Hapus data film (search)
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
    cout << "\033[2J\033[1;1H" << endl;
}

bool login(string user, string pass, int maxTry, int countTry){
    if(countTry == 1){
        clearScreen();
    }
    string inp_user;
    string inp_pass;
    cout << "== LOGIN ==\n";
    // Masukkan data login
    cout << "Masukkan Username : "; getline(cin, inp_user);
    cout << "Masukkan Password : "; getline(cin, inp_pass);
    // Mengecek kebenaran login
    if ((inp_user == user) && (inp_pass == pass)){
        // Login berhasil
        clearScreen();
        return true;
    }
    else if(countTry < maxTry){
        // Login gagal, masih ada kesempatan tersisa
        clearScreen();
        cout << "Login Gagal, " << (maxTry - countTry) << " Kesempatan Tersisa\n";
        return login(user, pass, maxTry, countTry+1);
    }
    else{
        // Login gagal, kesempatan telah habis
        clearScreen();
        cout << "Kesempatan Login Telah Habis\n";
        return false;
    }
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

// Bubble Sort (Huruf, Descending) + Interpolation search
void addFilm(data_film array[], int *dataSize){
    clearScreen();
    string inp_judul, inp_nama, inp_negara, key;
    int inp_tahun, inp_umur, low , high, posisi;
    float inp_rating;
    bool retry;
    cout  << "== TAMBAH FILM ==\n";
    // Input Judul Film, tidak boleh ada judul yang duplikat
    while (true){
        retry = false;
        cout  << "Judul Film : ";
        getline(cin, inp_judul);
        // Mengecek apakah terdapat judul duplikat
        if (*dataSize == 1 && array[0].judul == inp_judul){
            cout << "Judul Film Tidak Dapat Digunakan" << endl;
            continue;
        }

        if (*dataSize > 1){
            // Interpolation Search untuk mengecek apakah ada duplikat
            low = 0;
            high = *dataSize - 1;
            posisi = 0;
            while (low <= high  && inp_judul <= array[low].judul && inp_judul >= array[high].judul){
                // Mengubah huruf awal string menjadi int
                int firstCharX = inp_judul[0];
                int firstCharLow = array[low].judul[0];
                int firstCharHigh = array[high].judul[0];
                // Perhitungan perkiraan posisi key
                posisi = low + ((double)(high - low) / (firstCharHigh - firstCharLow)) * (firstCharX - firstCharLow);

                // Jika key ditemukan
                if (array[posisi].judul == inp_judul){
                    retry = true;
                    break;
                }
                // Jika key lebih kecil dari elemen posisi
                else if (array[posisi].judul < inp_judul){
                    low = posisi + 1;
                }
                // Jika key lebih besar dari elemen posisi
                else
                {
                    high = posisi - 1;
                }
            }
        }
        if (retry == true){
            cout << "Judul Film Tidak Dapat Digunakan" << endl;
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

    // Input Data Sutradara
    cout << "Nama Sutradara : "; cin.ignore(); getline(cin, inp_nama);
    while(true){
        cout << "Umur Sutradara : ";
        if ((cin >> inp_umur) && (inp_umur > 0)){
            break; // Input umur sudah sesuai
        }
        else {
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Masukkan Umur yang sesuai\n";
        }
    }
    cout << "Negara asal Sutradara :"; cin.ignore(); getline(cin, inp_negara);

    // Masukkan nilai input ke dalam array
    array[*dataSize].judul = inp_judul;
    array[*dataSize].rating = inp_rating;
    array[*dataSize].tahunRilis = inp_tahun;
    array[*dataSize].direktor.nama = inp_nama;
    array[*dataSize].direktor.umur = inp_umur;
    array[*dataSize].direktor.negara = inp_negara;
    (*dataSize)++;

    clearScreen();
    cout << "Film Berhasil Ditambahkan\n\n";


    // Bubble Sort (Huruf, Descending)
    data_film swap;
    bool swapped = true;
    if (*dataSize > 1){
        while (swapped){
            swapped = false;
            for (int i = 0; i < *dataSize - 1; i++){
                    if (array[i+1].judul > array[i].judul){
                        swapped = true;
                        swap = array[i];
                        array[i] = array[i+1];
                        array[i+1] = swap;
                    }
            }
        }
    }
    return;
}

// Menampilkan Data Film
void readFilm_Letter_Descend(data_film array[], int *dataSize){
    clearScreen();
    // Jika data kosong, kembali
    if (*dataSize <= 0){
        cout << "Tidak ada data film untuk ditampilkan\n\n";
        return;
    }

    cout << "== TAMPILKAN DATA FILM ==\n";
    string back;
    // Tampilkan data masing-masing film
    for (int i = 0; i < *dataSize; i++){
        cout << (i+1) << ". " << array[i].judul << endl;
        cout << "Rating : " << array[i].rating << endl;
        cout << "Tahun Rilis : " << array[i].tahunRilis << endl;
        cout << "Nama Sutradara :" << array[i].direktor.nama << endl;
        cout << "Umur Sutradara :" << array[i].direktor.umur << endl;
        cout << "Asal Negara Sutradara :" << array[i].direktor.negara << endl;
        cout << endl;
    }
    return;
}

// Insetion Sort (Angka, Ascending), Interpolation Search 
void readFilm_Number_Ascend(data_film array[], int *dataSize){
    clearScreen();
    // Jika data kosong, kembali
    if (*dataSize <= 0){
        cout << "Tidak ada data film untuk ditampilkan" << endl << endl;
        return;
    }
    cout << "== TAMPILKAN DATA FILM ==" << endl;
    data_film swap;
    string back;
    int min;
    bool swapped;
    // Duplicate Array
    data_film dupe_array[100];
    for (int i = 0; i < *dataSize; i++){
        dupe_array[i] = array[i];
    }
    // Insertion Sort berdasarkan Rating
    for (int i = 1; i < *dataSize; i++){
        swapped = false;
        min = i;
        for (int j = i-1; j >= 0; j--){
            if (dupe_array[min].rating < dupe_array[j].rating){
                // Proses swap
                swap = dupe_array[j];
                dupe_array[j] = dupe_array[min];
                dupe_array[min] = swap;
                swapped = true;
                min = j;
            }
            if (!swapped){
                break;
            }
        }
    }

    // Tampilkan data masing-masing film
    for (int i = 0; i < *dataSize; i++){
        cout << (i+1) << ". " << dupe_array[i].judul << endl;
        cout << "Rating : " << dupe_array[i].rating << endl;
        cout << "Tahun Rilis : " << dupe_array[i].tahunRilis << endl;
        cout << "Nama Sutradara :" << dupe_array[i].direktor.nama << endl;
        cout << "Umur Sutradara :" << dupe_array[i].direktor.umur << endl;
        cout << "Asal Negara Sutradara :" << dupe_array[i].direktor.negara << endl;
        cout << endl;
    }  

    // Interpolation Search uuntuk data ascending
    int low = 0, high = *dataSize - 1, posisi = 0, inp_rating;
    cout << "== SEARCHING RATING FILM ==" << endl;
    cout << "Masukkan Rating Film yang ingin dicari : "; cin >> inp_rating;
    while (low <= high  && inp_rating >= array[low].rating && inp_rating <= array[high].rating){
        // Mengubah huruf awal string menjadi int
        int elemen_x = inp_rating;
        int elemen_low = array[low].rating;
        int elemen_high = array[high].rating;
        // Perhitungan perkiraan posisi key
        posisi = low + ((double)(high - low) / (elemen_high - elemen_low)) * (elemen_x - elemen_low);

        // Jika key ditemukan, tampilkan data rating itu
        if (array[posisi].rating == inp_rating){
            cout << "== FILM RATING " << inp_rating << " ==" << endl;
            cout << "Judul : " << array[posisi].judul << endl;
            cout << "Rating : " << array[posisi].rating << endl;
            cout << "Tahun Rilis : " << array[posisi].tahunRilis << endl;
            cout << "Nama Sutradara :" << array[posisi].direktor.nama << endl;
            cout << "Umur Sutradara :" << array[posisi].direktor.umur << endl;
            cout << "Asal Negara Sutradara :" << array[posisi].direktor.negara << endl;
            cout << endl;
            return;
        }
        // Jika key lebih kecil dari elemen posisi
        else if (array[posisi].rating < inp_rating){
            low = posisi + 1;
        }
        // Jika key lebih besar dari elemen posisi
        else
        {
            high = posisi - 1;
        }
    }
    clearScreen();
    cout << "TIdak ditemukan film dengan rating " << inp_rating << endl;
    return;
}

// Selection Sort (Huruf, Descending) Binary Search
void updateFilm(data_film array[], int *dataSize){
    clearScreen();
    data_film swap;
    string inp_judul, inp_nama, inp_negara;
    float inp_rating;
    int inp_tahun, inp_umur, low, mid, high, posisi, max;
    bool retry, swapped;

    cout << " == EDIT DATA FILM ==\n";
    while (true){
        cout << "Masukkan judul dari film yang akan diubah : "; 
        getline (cin, inp_judul);

        // Binary Search untuk mencari judul film yang diinput
        low = 0, high = *dataSize-1;
        retry = true;
        while (low <= high){
            mid = (low + high)/ 2;
            // Jika input judul sesuai
            if (array[mid].judul == inp_judul){
                retry = false;
                break;
            }
            // Jika judul yang dicari ada di kiri (key > pos)
            else if (inp_judul.compare(array[mid].judul) > 0){
                high = mid-1;
            }
            // Jika judul yang dicari ada di kanan (key < pos)
            else if (inp_judul.compare(array[mid].judul) < 0){
                low = mid+1;
            }
        }
        if (retry == false){
            break;
        }
    }

    // Tampilkan data dari film yang ditemukan
    cout << "Judul Film : " << array[mid].judul << endl;
    cout << "Rating : " << array[mid].rating << endl;
    cout << "Tahun Rilis : " << array[mid].tahunRilis << endl << endl;

    // Input Judul Baru
    while (true){
        retry = false;
        cout  << "Masukkan Judul Baru : "; getline(cin, inp_judul);

        // Mengecek apakah terdapat judul duplikat
        if (inp_judul == array[mid].judul){
            break;
        }
        if (*dataSize == 1 && array[0].judul == inp_judul){
            cout << "Judul Film Tidak Dapat Digunakan" << endl;
            continue;
        }
        if (*dataSize > 1){
            // Interpolation Search untuk mengecek apakah ada duplikat
            low = 0;
            high = *dataSize - 1;
            posisi = 0;
            while (low <= high  && inp_judul <= array[low].judul && inp_judul >= array[high].judul){
                // Mengubah huruf awal string menjadi int
                int firstCharX = inp_judul[0];
                int firstCharLow = array[low].judul[0];
                int firstCharHigh = array[high].judul[0];
                // Perhitungan perkiraan posisi key
                posisi = low + ((double)(high - low) / (firstCharHigh - firstCharLow)) * (firstCharX - firstCharLow);

                // Jika key ditemukan
                if (array[posisi].judul == inp_judul){
                    retry = true;
                    break;
                }
                // Jika key lebih kecil dari elemen posisi
                else if (array[posisi].judul < inp_judul){
                    low = posisi + 1;
                }
                // Jika key lebih besar dari elemen posisi
                else
                {
                    high = posisi - 1;
                }
            }
        }
        if (retry == true){
            cout << "Judul Film Tidak Dapat Digunakan" << endl;
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

    // Inpt Data Sutradara
    cout << "Masukkan Nama Sutradara : "; cin.ignore(); getline(cin, inp_nama);
    while (true){
        cout << "Masukkan Umur Sutradara : ";
        if ((cin >> inp_umur) && (inp_umur > 0)){
            break; // Sesuai
        }
        else{
            cin.clear();
            cin.ignore(100, '\n');
            cout << "Masukkan Umur Yang Sesuai";
        }
    }
    cout << "Masukkan Asal Negara Sutradara : "; cin.ignore(); getline(cin, inp_nama);

    // Gantikan data lama dengan data baru yang diinput
    array[mid].judul = inp_judul;
    array[mid].rating = inp_rating;
    array[mid].tahunRilis = inp_tahun;
    array[mid].direktor.nama = inp_nama;
    array[mid].direktor.umur = inp_umur;
    array[mid].direktor.negara = inp_negara;

    // Selection Sort (Huruf, Descending)
    for (int i = 0; i < *dataSize; i++){
        max = i;
        swapped = false;
        for (int j = i; j < *dataSize; j++){
            if (array[j].judul > array[max].judul){
                max = j;
                swapped = true;
            }
        }
        if (!swapped){
            break;
        }
        swap = array[i];
        array[i] = array[max];
        array[max] = swap;
    }


    clearScreen();
    cout << "Data Film Berhasil Diedit\n\n";
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
