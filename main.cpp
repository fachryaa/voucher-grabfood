#include <iostream>
using namespace std;
#define MAX 4

class GrabFood{
private:
    static int noResto;
    string namaResto,menuMakanan[MAX];
    double hargaMenu[MAX];
    float jarak;
    int count=0;

    int pesanan[99];
    int jmlPesanan[99];
    int countP=0;

    string codeVouvher[3]={"DIRUMAHAJA1","DIRUMAHAJA2","DIRUMAHAJA3"};
    float persenDiskon[3]={0.25 , 0.35 , 0.5};

    double hargaMakanan=0;
    float potonganVoucher=0;

public:
    GrabFood(string nama , float jrk);
    void setMenuHarga(string menu , double harga);
    double getOngkir();
    double getPotonganHarga();
    double getTotalHarga();
    void tambahMakanan(int pilihan);
    void cekVoucher();
    void printPesanan();
    void printMenu();
    void printResto();
    void main();
};
int GrabFood::noResto = 1;

//==========================================================================

GrabFood::GrabFood(string nama, float jrk) {
    namaResto = nama;
    jarak = jrk;
    printResto();
    noResto++;
}

void GrabFood::setMenuHarga(string menu, double harga) {
    menuMakanan[count] = menu;
    hargaMenu[count] = harga;
    count++;
}

double GrabFood::getOngkir() {
    if(jarak>0 && jarak<=3) return 5000;
    else if(jarak>3 && jarak<=5) return 7000;
    else return 10000;
}

double GrabFood::getPotonganHarga() {
    return hargaMakanan*potonganVoucher;
}

void GrabFood::tambahMakanan(int pilihan) {
    int jml;
    cout<<"Jumlah : ";
    cin>>jml;
    hargaMakanan+=hargaMenu[pilihan-1]*jml;

    //menyimpan pesanan
    pesanan[countP] = pilihan-1;
    jmlPesanan[countP] = jml;
    countP++;
    cout<<"\n===================================================\n";
}

void GrabFood::cekVoucher() {
    string voucher;
    bool voucherBenar=false;
    menu:
    cout<<"\nMasukan voucher : ";
    cin >> voucher;

    int i;
    for(i=0 ; i<3 ; i++){
        if (voucher == codeVouvher[i]) {
            voucherBenar=true;
            break;
        }
    }

    bool voucherBerlaku;
    int a=0;
    if(voucherBenar){
        switch (i){
            case 0:
                voucherBerlaku = hargaMakanan > 25000 && hargaMakanan <= 35000;
                break;
            case 1:
                voucherBerlaku = hargaMakanan > 35000 && hargaMakanan <= 45000;
                break;
            default:
                voucherBerlaku = hargaMakanan > 45000;
                break;
        }
    }
    else {
        cout<<"Voucher yang anda masukan SALAH..."<<endl;
        cout<<"\n===================================================\n";
        cout<<"1. Masukan voucher lagi\n2. Tidak jadi\nPilih : ";
        cin>>a;
        cout<<"\n===================================================\n";
        if(a==1) goto menu;
    }

    if(a!=2){
        if(voucherBerlaku) {
            cout<<"YIAYYY... voucher berhasil dipakai.."<<endl;
            cout<<"\n===================================================\n";
            potonganVoucher = persenDiskon[i];
        }
        else {
            cout<<"Voucher tidak bisa dipakai :("<<endl;
            cout<<"\n===================================================\n";
            cout<<"1. Masukan voucher lagi\n2. Tidak jadi\nPilih : ";
            cin>>a;
            cout<<"\n===================================================\n";
            if(a==1) goto menu;
        }
    }
}

double GrabFood::getTotalHarga() {
    if(getPotonganHarga()==0)
        return hargaMakanan + getOngkir();
    else
        return getPotonganHarga() + getOngkir();
}

void GrabFood::printPesanan() {
    int i=0;
    //mencetak semua pesanan
    cout<<"No Pesanan\t\t\tHarga\n";
    while(i != countP){
        cout<<i+1<<". "<<menuMakanan[pesanan[i]]<<"("<<jmlPesanan[i]<<")\t"<<hargaMenu[pesanan[i]]*jmlPesanan[i]<<endl;
        i++;
    }
    cout<<"\nHarga Makanan\t\t: "<<hargaMakanan<<endl
        <<"Ongkos Kirim\t\t: "<<getOngkir()<<endl
        <<"Potongan Harga\t\t: -"<<getPotonganHarga()<<endl
        <<"\t\t\t\t\t  --------------- +"<<endl
        <<"Total Harga\t\t\t: "<<getTotalHarga();
}

void GrabFood::printResto() {
    cout << noResto << ". " << namaResto << " - Jarak " << jarak << " Km" << endl;
}

void GrabFood::printMenu() {
    cout<<"No\tNama Menu"<<"\t\t\t"<<"Harga\n";
    for(int i=0 ; i<MAX ; i++){
        cout<<i+1<<"\t"<<menuMakanan[i]<<"\t\t\t"<<hargaMenu[i]<<endl;
    }
    cout<<endl;
}

void GrabFood::main() {
    int choice;
    int jml=1;
    cout<<endl<<namaResto<<endl;

    menu:
    printMenu();
    cout<<"Pilih Menu : ";
    cin>>choice;
    tambahMakanan(choice);

    cout<<"\nTambah Menu?\n1. Ya\n2. Tidak\nPilih : ";
    cin>>choice;
    cout<<"\n===================================================\n";
    if (choice==1) {
        cout<<endl;
        goto menu;
    }

    cout<<"\nApakah ingin menggunakan voucher?\n1. Ya\n2. Tidak\nPilih : ";
    cin>>choice;
    cout<<"\n===================================================\n";
    if (choice==1) cekVoucher();

    cout<<"\nPesanan Anda"<<endl;
    printPesanan();
    cout<<"\n\n===================== SELESAI ====================="<<endl<<endl;
}


int main() {
    cout<<"==================== GRAB FOOD ===================="<<endl<<endl;
    GrabFood R1("Restoran A",2.7);
    GrabFood R2("Restoran B",4);
    GrabFood R3("Restoran C",5.3);

    R1.setMenuHarga("Ayam Geprek + Nasi",20000);
    R1.setMenuHarga("Ayam Bakar + Nasi",22000);
    R1.setMenuHarga("Es Teh",4000);
    R1.setMenuHarga("Es Jeruk",5000);

    R2.setMenuHarga("Nasi Goreng",15000);
    R2.setMenuHarga("Mie Goreng",16000);
    R2.setMenuHarga("Nasi Mawut",17000);
    R2.setMenuHarga("Air Mineral",5000);

    R3.setMenuHarga("Bakso Biasa",12000);
    R3.setMenuHarga("Bakso Spesial",16000);
    R3.setMenuHarga("Mie Ayam",15000);
    R3.setMenuHarga("Air Mineral",5000);

    int choice;
    cout<<"\nPilih restoran : ";
    cin>>choice;

    cout<<"\n===================================================\n";

    switch (choice){
        case 1:
            R1.main();
            break;
        case 2:
            R2.main();
            break;
        default:
            R3.main();
            break;
    }

    return 0;
}
