#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <unordered_map>
#include <conio.h>
#include <fstream>
#include <cstdlib>

using namespace std;

// Deklarasi Struct Node
struct InventoryBarang
{
    string nama;
    string kode;
    string kategori;
    int stok;
    int harga;
    InventoryBarang *next;
};

struct BarangKeluar{
    string nama;
    string kode;
    string kategori;
    int stok;
    int harga;
    BarangKeluar* next;
};

BarangKeluar* front = NULL;
BarangKeluar* back  = NULL;

vector<InventoryBarang> gudang;
// Deklarasi Node
InventoryBarang *head, *tail, *baru, *bantu, *hapus;

// Inisialisasi Node
void init()
{
    head = NULL;
    tail = NULL;
}

// Buat Node Baru
void buatNode(string nama, string kode, string kategori, int stok, int harga)
{
    baru = new InventoryBarang;
    baru->nama = nama;
    baru->kode = kode;
    baru->kategori = kategori;
    baru->stok = stok;
    baru->harga = harga;
    baru->next = NULL;
}

// Pengecekan
bool isEmpty()
{
    if (head == NULL)
        return true;
    else
        return false;
}

// Hitung Jumlah List
int hitungList()
{
    InventoryBarang *hitung;
    hitung = head;
    int jumlah = 0;
    while (hitung != NULL)
    {
        jumlah++;
        hitung = hitung->next;
    }
    return jumlah;
}

// Tambah Depan
void insertBarang(string nama, string kode, string kategori,int stok, int harga)
{
    // Buat Node baru
    buatNode(nama, kode, kategori,stok,harga);

    if (isEmpty() == true)
    {
        head = tail = baru;
        tail->next = NULL;
    }
    else
    {
        baru->next = head;
        head = baru;
    }

    // push node ke dalam vector
    gudang.push_back(*baru);

    cout << " Data " << baru->nama << " berhasil diinput!" << endl;
}

// Hapus Tengah
void hapusBarang(int posisi)
{
    InventoryBarang *bantu2;
    if (posisi < 1 || posisi > hitungList())
    {
        cout << " Posisi di luar jangkauan" << endl;
    }
    else
    {
        int nomor = 1;
        bantu = head;
        while (nomor <= posisi)
        {
            if (nomor == posisi - 1)
            {
                bantu2 = bantu;
            }
            if (nomor == posisi)
            {
                hapus = bantu;
            }
            bantu = bantu->next;
            nomor++;
        }
        bantu2->next = bantu;
        cout << " Data " << hapus->nama << " berhasil dihapus!" << endl;
        delete hapus;
    }
}

// Ubah Barang
void ubahBarang(string nama, string kode, string kategori, int stok, int harga, int posisi)
{
    if (isEmpty() == 0)
    {
        if (posisi < 1 || posisi > hitungList())
        {
            cout << "Posisi di luar jangkauan" << endl;
        }
        else
        {
            bantu = head;
            int nomor = 1;
            while (nomor < posisi)
            {
                bantu = bantu->next;
                nomor++;
            }
            cout << "Data " << bantu->nama << " telah diganti dengan data";
            bantu->nama = nama;
            bantu->kode = kode;
            bantu->kategori = kategori;
            bantu->stok = stok;
            bantu->harga = harga;
            cout << bantu->nama << "!" << endl;
        }
    }
    else
    {
        cout << "List masih kosong!" << endl;
    }
}

// Hapus Semua Barang
void clearList()
{
    bantu = head;
    while (bantu != NULL)
    {
        hapus = bantu;
        bantu = bantu->next;
        delete hapus;
    }
    head = tail = NULL;
    cout << "List berhasil dihapus!" << endl;
}

// Cari Barang dengan binary search
void binarySearch(vector<InventoryBarang> &data, string target)
{
    int low = 0;
    int high = data.size() - 1;
    bool found = false;

    if(data[low].nama == target){
        found = true;
        cout << "Barang ditemukan: " << endl;
        cout << "Nama Barang: " << data[low].nama << endl;
        cout << "Kode Barang: " << data[low].kode << endl;
        cout << "Stok Barang: " << data[low].stok << endl;
        cout << "Harga Barang: " << data[low].harga << endl;
        cout << "Kategori Barang: " << data[low].kategori << endl;
    }else{
        while (low <= high)
        {
            int mid = (low + high) / 2;
            if (data[mid].nama == target)
            {
                found = true;
                cout << "Barang ditemukan: " << endl;
                cout << "Nama Barang: " << data[mid].nama << endl;
                cout << "Kode Barang: " << data[mid].kode << endl;
                cout << "Stok Barang: " << data[mid].stok << endl;
                cout << "Harga Barang: " << data[mid].harga << endl;
                cout << "Kategori Barang: " << data[mid].kategori << endl;
                break;
            }
            else if (data[mid].nama < target){
                low = mid + 1;
            }else{
                high = mid - 1;
            }
        }
    }


    if (!found){
        cout << "Barang tidak ditemukan." << endl;
    }
}

// Cari Barang
void cariBarang()
{
    unordered_map<string, string> hashTable;
    string kategori;
    cout << "Masukkan Kategori Barang yang ingin dicari: ";
    getline(cin >> ws , kategori);

    bool found = false;
    for (const InventoryBarang &b : gudang)
    {
        hashTable[b.nama] = b.kategori;
    }

    cout << "Barang ditemukan: " << endl;
    for (const auto &item : hashTable)
    {
        if (item.second == kategori)
        {
            found = true;
            cout << "Nama Barang: " << item.first << endl;
            cout << "Kode Barang: " << hashTable[item.first] << endl;
            cout << "Kategori Barang: " << item.second << endl;
            cout << "---------------------" << endl;
        }
    }

    if (!found)
    {
        cout << "Barang dengan kategori " << kategori << " tidak ditemukan." << endl;
    }
}

// Tampilkan Semua Barang
void tampil(){
    bantu = head;
    if (isEmpty() == false)
    {
        cout << "\nData Barang" << endl;
        cout << "==================================================\n";
        cout << left << setw(12) << "Nama" << setw(8) << "Kode" << setw(10) << "Stok" << setw(10) << "Harga" << setw(10)<< "Kategori" << endl;
        cout << "==================================================\n";
        while (bantu != NULL)
        {
            cout << left << setw(12) << bantu->nama << setw(8) << bantu->kode << setw(10) << bantu->stok << setw(10) << bantu->harga << setw(10) << bantu->kategori << endl;
            bantu = bantu->next;
        }
        cout << endl;
    }
    else
    {
        cout << "List masih kosong!" << endl;
    }
}

// Input Nama, Kode, dan Kategori
string inputNama;
string inputKode;
string inputKategori;
int inputStok;
int inputHarga;
void inputList()
{
    cout << "Masukkan Nama Barang : ";
    getline(cin >> ws, inputNama);
    cout << "Masukkan Kode Barang : ";
    getline(cin >> ws, inputKode);
    cout << "Masukkan Stok Barang : ";
    cin  >> inputStok;
    cout << "Masukkan Harga Barang : ";
    cin  >> inputHarga;
    cout << "Masukkan Kategori Barang : ";
    getline(cin >> ws, inputKategori);
}


// Queue

//cek queue
bool kosong(){
    return front == NULL;
}

void searchByKode(vector<InventoryBarang> &data, string target, int qty){
    bool found = false;

    for (const InventoryBarang &item : data){
        if (item.kode == target){
            found = true;
            bantu = head;

            while (bantu != nullptr){
                if (bantu->kode == target)
                {
                    bantu->stok -= qty;
                    break;
                }
                bantu = bantu->next;
            }

            BarangKeluar *newNode = new BarangKeluar;
            newNode->nama = item.nama;
            newNode->kode = item.kode;
            newNode->kategori = item.kategori;
            newNode->stok = qty;
            newNode->harga = item.harga;

            if (kosong()){
                front = newNode;
                back = newNode;
            }else{
                back->next = newNode;
                back = newNode;
            }

            cout << "Barang dengan kode " << target << " berhasil keluar" << endl;
            break;
        }
    }

    if (!found)
    {
        cout << "Kode Barang tidak ditemukan." << endl;
    }
}

void tampilBarangKeluar(){
    if (kosong()){
        cout << "Barang Keluar Kosong" << endl;
    }else{
        BarangKeluar* temp = front;
        int index = 1;
        cout << "\n\nData Barang Keluar" << endl;
        cout << "==================================================\n";
        cout << left << setw(12) << "Nama" << setw(8) << "Kode" << setw(10) << "Stok" << setw(10) << "Harga" << setw(10) << "Kategori" << endl;
        cout << "==================================================\n";
        while (temp != NULL){
            cout << left << setw(12) << temp->nama << setw(8) << temp->kode << setw(10) << temp->stok << setw(10) << temp->harga << setw(10) << temp->kategori << endl;
            temp = temp->next;
            index++;
        }
        cout << endl;
    }
}

void barangKeluar(){
    string kode;
    int stok;
    cout <<endl<<endl;
    int j,qty;
    tampil();

    cout << "\n\n=========================== Barang Keluar ============================" << endl;
    cout << "----------------------------------------------------------------------\n";
    cout << "Jumlah Barang Keluar :";
    cin >> j;
    cout << " " << endl;

    for(int i = 0; i < j; i++){
        cout << "Masukkan Kode Barang " << i + 1 << " : ";
        getline(cin >> ws, kode);
        cout << "Masukkan Jumlah Barang : ";
        cin  >> qty;
        searchByKode(gudang, kode,qty);

        cout << " " <<endl;
    }

}

void laporanBarang(){
    ofstream myFile;

    myFile.open("laporan.csv");

    bantu = head;
    if (isEmpty() == false){
        myFile <<  "Nama," << "Kode," <<  "Stok," <<  "Harga," <<  "Kategori" << endl;
        while (bantu != NULL){
            myFile << bantu->nama << ","  << bantu->kode << "," << bantu->stok << "," <<  bantu->harga << "," <<  bantu->kategori << endl;
            bantu = bantu->next;
        }
        myFile << endl;

        cout << "Berhasil mengexport data barang";
    }
    else
    {
        myFile << "Barang masih kosong" << endl;
    }
}

int main(){
    int pilihan;
    int posisi;

    init();
    do
    {
        system("cls");
        cout << "======================================" << endl;
        cout << " PROGRAM INVENTORY BARANG" << endl;
        cout << "======================================" << endl;
        cout << " 1. Tambah Barang" << endl;
        cout << " 2. Hapus Barang" << endl;
        cout << " 3. Ubah Barang" << endl;
        cout << " 4. Cari Barang (Binary Search)" << endl;
        cout << " 5. Cari Barang (Menampilkan Berdasarkan Kategori)" << endl;
        cout << " 6. Tampil Barang" << endl;
        cout << " 7. Hapus Semua Barang" << endl;
        cout << " 8. Barang Keluar" << endl;
        cout << " 9. Tampil Barang Keluar" << endl;
        cout << " 10. Export Excel (Data Barang)" << endl;
        cout << " 11. Exit" << endl;
        cout << "======================================" << endl;
        cout << " Pilihan : ";
        cin >> pilihan;
        switch (pilihan)
        {
        case 1:
            inputList();
            insertBarang(inputNama, inputKode, inputKategori, inputStok, inputHarga);
            break;
        case 2:
            cout << "Masukkan posisi data yang akan dihapus : ";
            cin >> posisi;
            hapusBarang(posisi);
            break;
        case 3:
            cout << "Masukkan posisi data yang akan diubah : ";
            cin >> posisi;
            inputList();
            ubahBarang(inputNama, inputKode, inputKategori,inputStok,inputHarga, posisi);
            break;
        case 4:
            cout << "Masukkan nama barang yang ingin dicari: ";
            getline(cin >> ws, inputNama);
            binarySearch(gudang, inputNama);
            break;
        case 5:
            cariBarang();
            break;
        case 6:
            tampil();
            break;
        case 7:
            clearList();
            break;
        case 8:
            barangKeluar();
            break;
        case 9:
            tampilBarangKeluar();
            break;
        case 10:
            laporanBarang();
            break;
        case 11:
            exit(0);
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
            break;
        }
        getch();
    } while (true);

    return 0;
}
