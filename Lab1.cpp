#include <iostream>
#include <string>
using namespace std;

void wyswietl(int* nrIndexu, string* imie, string* nazwisko, bool* obecnosc, int iloscIndexow) {
    for (int i = 0; i < iloscIndexow; i++) {
        cout << nrIndexu[i] << " " << imie[i] << " " << nazwisko[i] << " " << obecnosc[i] << endl;
    }
}

void dodajOsobe(string* nazwisko, string* imie, int* nrIndexu, string nazw, string im, int nr, int& iloscIndexow) {
    nazwisko[iloscIndexow] = nazw;
    imie[iloscIndexow] = im;
    nrIndexu[iloscIndexow] = nr;
    iloscIndexow++;
}

void usunOsobe(string* nazwisko, string* imie, int* nrIndexu, bool* obecnosc, int nr, int& iloscIndexow) {
    int pozycja = -5;
    for (int i = 0; i < iloscIndexow; i++) {
        if (nr == nrIndexu[i]) {
            pozycja = i;
            break;
        }
    }
    for (int i = pozycja; i < iloscIndexow - 1; i++) {
        nazwisko[i] = nazwisko[i + 1];
        imie[i] = imie[i + 1];
        nrIndexu[i] = nrIndexu[i + 1];
        obecnosc[i] = obecnosc[i + 1];
    }

    iloscIndexow--;
}

void ustawObecnosc(string* nazwisko, bool* obecnosc, string nazw, bool ob, int iloscIndexow) {
    for (int i = 0; i < iloscIndexow; i++) {
        if (nazw == nazwisko[i]) {
            obecnosc[i] = ob;
        }
    }
}

void Zmiana(string* nazwisko, string* imie, int* nrIndexu,
            int nr, int nr2, string im, string nazw, int iloscIndexow) {
    for (int i = 0; i < iloscIndexow; i++) {
        if (nr == nrIndexu[i]) {
            nrIndexu[i] = nr2;
            nazwisko[i] = nazw;
            imie[i] = im;
        }
    }
}

int main() {
    string nazwisko[10];
    bool obecnosc[10];
    string imie[10];
    int nrIndexu[10];
    int iloscIndexow = 0;

    int n = 0;
    while (n != 6) {
        cout << "co chcesz zrobic?" << endl;
        cout << "1. wyswietl liste" << endl;
        cout << "2. dodaj osobe" << endl;
        cout << "3. zmien obecnosc" << endl;
        cout << "4. usun osobe" << endl;
        cout << "5. wprowadz zmiany" << endl;
        cout << "6. wyjdz" << endl;
        cin >> n;

        if (n == 1) {
            wyswietl(nrIndexu, imie, nazwisko, obecnosc, iloscIndexow);
        }
        else if (n == 2) {
            cout << "podaj nazwisko" << endl;
            string nazw;
            cin >> nazw;

            cout << "podaj imie" << endl;
            string im;
            cin >> im;

            cout << "podaj nrIndexu" << endl;
            int nr;
            cin >> nr;

            dodajOsobe(nazwisko, imie, nrIndexu, nazw, im, nr, iloscIndexow);
        }
        else if (n == 3) {
            cout << "podaj nazwisko" << endl;
            string nazw;
            cin >> nazw;

            cout << "podaj obecnosc" << endl;
            bool ob;
            cin >> ob;

            ustawObecnosc(nazwisko, obecnosc, nazw, ob, iloscIndexow);
        }
        else if (n == 4) {
            cout << "podaj nr Indexu" << endl;
            int nr;
            cin >> nr;

            usunOsobe(nazwisko, imie, nrIndexu, obecnosc, nr, iloscIndexow);
        }
        else if (n == 5) {
            cout << "podaj nr Indexu" << endl;
            int nr;
            cin >> nr;

            cout << "zmiany dla indexu: " << nr << endl;
            cout << "podaj nowy numer indexu" << endl;
            int nr2;
            cin >> nr2;

            cout << "podaj nowe imie" << endl;
            string im;
            cin >> im;

            cout << "podaj nowe nazwisko" << endl;
            string nazw;
            cin >> nazw;

            Zmiana(nazwisko, imie, nrIndexu, nr, nr2, im, nazw, iloscIndexow);
        }
    }
}