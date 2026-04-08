#include <iostream>
#include <string>
using namespace std;

class Student {
private:
    string imie;
    string nazwisko;
    int nrIndexu;

public:
    Student() {
        imie = "";
        nazwisko = "";
        nrIndexu = 0;
    }

    Student(string im, string nazw, int nr) {
        imie = im;
        nazwisko = nazw;
        nrIndexu = nr;
    }

    void ustawDane(string im, string nazw, int nr) {
        imie = im;
        nazwisko = nazw;
        nrIndexu = nr;
    }

    string getImie() const {
        return imie;
    }

    string getNazwisko() const {
        return nazwisko;
    }

    int getNrIndexu() const {
        return nrIndexu;
    }
};

void wyswietl(Student* studenci, bool* obecnosc, int iloscIndexow) {
    for (int i = 0; i < iloscIndexow; i++) {
        cout << studenci[i].getNrIndexu() << " "
             << studenci[i].getImie() << " "
             << studenci[i].getNazwisko() << " "
             << obecnosc[i] << endl;
    }
}

void dodajOsobe(Student* studenci, bool* obecnosc,
                string nazw, string im, int nr, int& iloscIndexow) {
    studenci[iloscIndexow] = Student(im, nazw, nr);
    obecnosc[iloscIndexow] = false; // domyślnie nieobecny
    iloscIndexow++;
}

void usunOsobe(Student* studenci, bool* obecnosc, int nr, int& iloscIndexow) {
    int pozycja = -1;

    for (int i = 0; i < iloscIndexow; i++) {
        if (nr == studenci[i].getNrIndexu()) {
            pozycja = i;
            break;
        }
    }

    if (pozycja == -1) {
        cout << "Nie znaleziono studenta o podanym numerze indeksu." << endl;
        return;
    }

    for (int i = pozycja; i < iloscIndexow - 1; i++) {
        studenci[i] = studenci[i + 1];
        obecnosc[i] = obecnosc[i + 1];
    }

    iloscIndexow--;
}

void ustawObecnosc(Student* studenci, bool* obecnosc, string nazw, bool ob, int iloscIndexow) {
    bool jest = false;

    for (int i = 0; i < iloscIndexow; i++) {
        if (nazw == studenci[i].getNazwisko()) {
            obecnosc[i] = ob;
            jest = true;
        }
    }

    if (!jest) {
        cout << "Nie znaleziono studenta o podanym nazwisku." << endl;
    }
}

void zmiana(Student* studenci, int nr, int nr2, string im, string nazw, int iloscIndexow) {
    bool jest = false;

    for (int i = 0; i < iloscIndexow; i++) {
        if (nr == studenci[i].getNrIndexu()) {
            studenci[i].ustawDane(im, nazw, nr2);
            jest = true;
            break;
        }
    }

    if (!jest) {
        cout << "Nie znaleziono studenta o podanym numerze indeksu." << endl;
    }
}

int main() {
    Student studenci[10];
    bool obecnosc[10];
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
            wyswietl(studenci, obecnosc, iloscIndexow);
        }
        else if (n == 2) {
            if (iloscIndexow >= 10) {
                cout << "Brak miejsca na kolejnego studenta." << endl;
                continue;
            }

            cout << "podaj nazwisko" << endl;
            string nazw;
            cin >> nazw;

            cout << "podaj imie" << endl;
            string im;
            cin >> im;

            cout << "podaj nrIndexu" << endl;
            int nr;
            cin >> nr;

            dodajOsobe(studenci, obecnosc, nazw, im, nr, iloscIndexow);
        }
        else if (n == 3) {
            cout << "podaj nazwisko" << endl;
            string nazw;
            cin >> nazw;

            cout << "podaj obecnosc (0 lub 1)" << endl;
            bool ob;
            cin >> ob;

            ustawObecnosc(studenci, obecnosc, nazw, ob, iloscIndexow);
        }
        else if (n == 4) {
            cout << "podaj nr Indexu" << endl;
            int nr;
            cin >> nr;

            usunOsobe(studenci, obecnosc, nr, iloscIndexow);
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

            zmiana(studenci, nr, nr2, im, nazw, iloscIndexow);
        }
    }

    return 0;
}