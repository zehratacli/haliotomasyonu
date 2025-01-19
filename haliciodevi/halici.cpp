#include <iomanip>
#include <cstring>
#include <stdlib.h>
#include <conio.h>
#include <stdio.h>
#include <fstream>
#include <iostream>

using namespace std;

struct Halisiparisi
{
    char musteriad[80];
    char musterisoyad[80];
    char siparisno[20];
    char renk[30];
    char desen[30];
    char boyut[50];
    char kumas[30];
    float fiyat;  
    char kupon[20];
};

void Siparisekle();
void Siparisarama();
void siparisSil();
void siparisDuzenle();
void SiparisListeleme();

int main() {
    setlocale(LC_ALL, "Turkish");
    char anamenu;
    do {
        system("cls");

        cout << "******************************" << endl;
        cout << "-Taçlý Halý Evine Hoþgeldiniz-" << endl;
        cout << "***************************" << endl;
        cout << "*"; cout << "1-Halý sipariþi ekle."; cout << "    *" << endl;
        cout << "*"; cout << "2-Halý sipariþi ara."; cout << "     *" << endl;
        cout << "*"; cout << "3-Halý sipariþi sil."; cout << "     *" << endl;
        cout << "*"; cout << "4-Halý sipariþi güncelle."; cout << "*"<< endl;
        cout << "*"; cout << "5-Halý sipariþi listele."; cout << " *" << endl;
        cout << "***************************" << endl;
        
        char secim;
        cin >> secim;

        switch(secim) 
        {
            case '1': 
            {
                Siparisekle();
                break;    
            }
            case '2': 
            {
                Siparisarama();
                break;
            }
            case '3': 
            {
                siparisSil();
                break;
            }
            case '4': 
            {
                siparisDuzenle();
                break;
            }
            case '5': 
            {
                SiparisListeleme();
                break;
            }
        }    
        cout << "Anamenüye dönmek istermisiniz?(E/H)" << endl; 
        anamenu = getche();
    } while(anamenu == 'e');
    
    return 0;
}

Halisiparisi siparis;

void Siparisekle() {
    ofstream yaz("hali.dat", ios::binary | ios::app);
    char secim;

    do {
        cout << "Musteri Adi Giriniz: ";
        cin >> siparis.musteriad;
        cout << "Musteri Soyadi Giriniz: ";
        cin >> siparis.musterisoyad;
        cout << "Siparis Numarasi Giriniz: ";
        cin >> siparis.siparisno;
        cout << "Hali Renk Giriniz: ";
        cin >> siparis.renk;
        cout << "Hali Deseni Giriniz: ";
        cin >> siparis.desen;
        cout << "Hali Boyutunu Giriniz (m2): ";
        cin >> siparis.boyut;
        cout << "Hali Kumaþi Giriniz: ";
        cin >> siparis.kumas;
        cout << "Kupon Kodu (varsa): ";
        cin >> siparis.kupon;

       
        float boyut = atof(siparis.boyut); // Boyut deðerini char olarak tanýmlamýstým  float'a çevirmek icin kullandým
        siparis.fiyat = boyut * 30;
        
        if (strcmp(siparis.kupon, "INDIRIM10") == 0) {
            siparis.fiyat *= 0.9;    //kupon kodu eklemek istedim programa
            cout << "Kupon uygulandý"<<endl;
			cout<<" Yeni fiyat: " << siparis.fiyat << " TL" << endl;
        }

        cout << endl;
        yaz.write((char*)&siparis, sizeof(siparis));
        cout << "Baska Kayit Eklemek Istermisin (E/H)" << endl;
        secim = getche();
        cout << endl;
    } while(secim == 'e' || secim == 'E');

    yaz.close();
}

void Siparisarama() {
    ifstream oku("hali.dat", ios::binary | ios::app);
    oku.seekg(0, ios::end);
    int kayits = oku.tellg() / sizeof(siparis);

    cout << "Aranan siparis numarasýný giriniz" << endl;
    char spr_no[80];
    cin >> spr_no;

    if(kayits > 0) {
        for(int i = 0; i < kayits; i++) {
            oku.seekg(i * sizeof(siparis));
            oku.read((char*)&siparis, sizeof(siparis));

            if(strcmp(siparis.siparisno, spr_no) == 0) {
                cout << "Bulunan Siparis Bilgileri : " << endl;
                cout << "Musteri Adi: " << siparis.musteriad << endl;
                cout << "Musteri Soyadi: " << siparis.musterisoyad << endl;
                cout << "Siparis No: " << siparis.siparisno << endl;
                cout << "Hali Rengi: " << siparis.renk << endl;
                cout << "Hali Deseni: " << siparis.desen << endl;
                cout << "Hali Boyutu: " << siparis.boyut << endl;
                cout << "Hali Kumaþý: " << siparis.kumas << endl;
                cout << "Fiyat: " << siparis.fiyat << " TL" << endl;  
            }
        }
    } else {
        cout << "Kayit Bulunamadi..." << endl;
    }

    oku.close();
}

void siparisSil() {
    char siparis_no[80];
    char secim = ' ';
    bool var = false;

    ifstream oku("hali.dat", ios::binary | ios::app);
    oku.seekg(0, ios::end);

    int kayitsayisi = oku.tellg() / sizeof(siparis);
    cout << "Kaydini Sileceginiz siparis No Giriniz : ";
    cin >> siparis_no;

    for(int i = 0; i < kayitsayisi; i++) {
        oku.seekg(i * sizeof(siparis));
        oku.read((char*)&siparis, sizeof(siparis));

        if(strcmp(siparis.siparisno, siparis_no) == 0) {
            cout << "\nMusteri Adi: " << siparis.musteriad;
            cout << "\nMusteri Soyadi: " << siparis.musterisoyad;
            cout << "\nSiparis No: " << siparis.siparisno;
            cout << "\nHali Rengi: " << siparis.renk;
            cout << "\nHali Deseni: " << siparis.desen;
            cout << "\nHali Boyutu: " << siparis.boyut;
            cout << "\nHali Kumaþý: " << siparis.kumas;
            cout << "\nFiyat: " << siparis.fiyat << " TL" << endl; 

            cout << "\n\nSilmek Istediginiz Kayit Bu Mu? [E/H] : ";
            secim = getche();
            if(secim == 'H' || secim == 'h') {
                Halisiparisi ysiparis;
                ofstream y_dosya("Yedek.dat", ios::app | ios::binary);
                strcpy(ysiparis.musteriad, siparis.musteriad);
                strcpy(ysiparis.musterisoyad, siparis.musterisoyad);
                strcpy(ysiparis.siparisno, siparis.siparisno);
                strcpy(ysiparis.renk, siparis.renk);
                strcpy(ysiparis.desen, siparis.desen);
                strcpy(ysiparis.boyut, siparis.boyut);
                strcpy(ysiparis.kumas, siparis.kumas);
                ysiparis.fiyat = siparis.fiyat;

                y_dosya.write((char*)&ysiparis, sizeof(siparis));
                y_dosya.close();
            }

            if(secim == 'e' || secim == 'E') {
                var = true;
            }
        } else {
            Halisiparisi ysiparis;
            ofstream y_dosya("Yedek.dat", ios::app | ios::binary);
            strcpy(ysiparis.musteriad, siparis.musteriad);
            strcpy(ysiparis.musterisoyad, siparis.musterisoyad);
            strcpy(ysiparis.siparisno, siparis.siparisno);
            strcpy(ysiparis.renk, siparis.renk);
            strcpy(ysiparis.desen, siparis.desen);
            strcpy(ysiparis.boyut, siparis.boyut);
            strcpy(ysiparis.kumas, siparis.kumas);
            ysiparis.fiyat = siparis.fiyat;

            y_dosya.write((char*)&ysiparis, sizeof(siparis));
            y_dosya.close();
        }
    }

    oku.close();
    if(var) {
        remove("hali.dat");
        rename("Yedek.dat", "hali.dat");
        cout << "\n Kayit Silindi" << endl;
    } else {
        remove("Yedek.dat");
        cout << "\n Kayit Bulunamadi" << endl;
    }
}

void siparisDuzenle() {
    char nosiparis[80];
    char secim = ' ';
    bool var = false;

    ifstream oku("hali.dat", ios::binary | ios::app);
    oku.seekg(0, ios::end);

    int kayitsayisi = oku.tellg() / sizeof(siparis);
    cout << "Kaydini Duzelteceginiz siparis No Giriniz : ";
    cin >> nosiparis;

    for(int i = 0; i < kayitsayisi; i++) {
        oku.seekg(i * sizeof(siparis));
        oku.read((char*)&siparis, sizeof(siparis));

        if(strcmp(siparis.siparisno, nosiparis) == 0) {
            cout << "\nMusteri Adi: " << siparis.musteriad;
            cout << "\nMusteri Soyadi: " << siparis.musterisoyad;
            cout << "\nSiparis No: " << siparis.siparisno;
            cout << "\nHali Rengi: " << siparis.renk;
            cout << "\nHali Deseni: " << siparis.desen;
            cout << "\nHali Boyutu: " << siparis.boyut;
            cout << "\nHali Kumaþý: " << siparis.kumas;
            cout << "\nFiyat: " << siparis.fiyat << " TL" << endl;

            cout << "\n\nDuzeltmek Istediginiz Kayit Bu Mu? [E/H] : ";
            secim = getche();

            if(secim == 'E' || secim == 'e') {
                var = true;
                ofstream dosya("Yedek.dat", ios::app | ios::binary);
                cout << "Musteri Adi Giriniz: ";
                cin >> siparis.musteriad;
                cout << "Musteri Soyadi Giriniz: ";
                cin >> siparis.musterisoyad;
                cout << "Siparis Numarasi Giriniz: ";
                cin >> siparis.siparisno;
                cout << "Hali Renk Giriniz: ";
                cin >> siparis.renk;
                cout << "Hali Deseni Giriniz: ";
                cin >> siparis.desen;
                cout << "Hali Boyutunu Giriniz (m2): ";
                cin >> siparis.boyut;
                cout << "Hali Kumaþi Giriniz: ";
                cin >> siparis.kumas;

                
                float boyut = atof(siparis.boyut);
                siparis.fiyat = boyut * 30; 

                cout << endl;
                dosya.write((char*)&siparis, sizeof(siparis));
                dosya.close();
            }
        }
    }

    oku.close();
    if(var) {
        remove("hali.dat");
        rename("Yedek.dat", "hali.dat");
        cout << "\nKayit Duzeltildi." << endl;
    } else {
        remove("Yedek.dat");
        cout << "\nKayit Bulunamadi" << endl;
    }
}

void SiparisListeleme() {
    ifstream oku("hali.dat", ios::binary | ios::app);
    oku.seekg(0, ios::end);
    int kayits = oku.tellg() / sizeof(siparis);
    cout << "Toplam siparis kayýt sayýsý: " << kayits << endl;

    if(kayits > 0) {
        for(int i = 0; i < kayits; i++) {
            oku.seekg(i * sizeof(siparis));
            oku.read((char*)&siparis, sizeof(siparis));

            cout << "\nMusteri Adi: " << siparis.musteriad;
            cout << "\nMusteri Soyadi: " << siparis.musterisoyad;
            cout << "\nSiparis No: " << siparis.siparisno;
            cout << "\nHali Rengi: " << siparis.renk;
            cout << "\nHali Deseni: " << siparis.desen;
            cout << "\nHali Boyutu: " << siparis.boyut;
            cout << "\nHali Kumaþý: " << siparis.kumas;
            cout << "\nFiyat: " << siparis.fiyat << " TL" << endl;
            cout << "----------------------------------------" << endl;
        }
    } else {
        cout << "Kayit Bulunamadi..." << endl;
    }

    oku.close();
}
