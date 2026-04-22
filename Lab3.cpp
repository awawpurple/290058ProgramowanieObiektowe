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

class ListaObecnosci {
private:
    static const int studenciM = 10;
    Student studenci[studenciM];
    bool obecnosc[studenciM];
    int iloscStudentow;

public:
    ListaObecnosci() {
        iloscStudentow = 0;
    }

    void wyswietl() const {
        if (iloscStudentow == 0) {
            cout << "Lista jest pusta." << endl;
            return;
        }

        for (int i = 0; i < iloscStudentow; i++) {
            cout << studenci[i].getNrIndexu() << " "
                 << studenci[i].getImie() << " "
                 << studenci[i].getNazwisko() << " "
                 << obecnosc[i] << endl;
        }
    }

    void dodajOsobe(string nazw, string im, int nr) {
        if (iloscStudentow >= studenciM) {
            cout << "Lista jest pełna." << endl;
            return;
        }

        studenci[iloscStudentow] = Student(im, nazw, nr);
        obecnosc[iloscStudentow] = false;
        iloscStudentow++;
    }

    void usunOsobe(int nr) {
        int pozycja = -1;

        for (int i = 0; i < iloscStudentow; i++) {
            if (studenci[i].getNrIndexu() == nr) {
                pozycja = i;
                break;
            }
        }

        if (pozycja == -1) {
            cout << "Nie znaleziono studenta." << endl;
            return;
        }

        for (int i = pozycja; i < iloscStudentow - 1; i++) {
            studenci[i] = studenci[i + 1];
            obecnosc[i] = obecnosc[i + 1];
        }

        iloscStudentow--;
    }

    void ustawObecnosc(string nazw, bool ob) {
        bool znaleziono = false;

        for (int i = 0; i < iloscStudentow; i++) {
            if (studenci[i].getNazwisko() == nazw) {
                obecnosc[i] = ob;
                znaleziono = true;
            }
        }

        if (!znaleziono) {
            cout << "Nie znaleziono studenta." << endl;
        }
    }

    void zmienDaneStudenta(int nr, int nowyNr, string noweImie, string noweNazwisko) {
        bool znaleziono = false;

        for (int i = 0; i < iloscStudentow; i++) {
            if (studenci[i].getNrIndexu() == nr) {
                studenci[i].ustawDane(noweImie, noweNazwisko, nowyNr);
                znaleziono = true;
                break;
            }
        }

        if (!znaleziono) {
            cout << "Nie znaleziono studenta." << endl;
        }
    }
};

class InterfejsUzytkownika {
private:
    ListaObecnosci lista;

public:
    void uruchom() {
        int n = 0;

        while (n != 6) {
            cout << endl;
            cout << "Co chcesz zrobic?" << endl;
            cout << "1. Wyswietl liste" << endl;
            cout << "2. Dodaj osobe" << endl;
            cout << "3. Zmien obecnosc" << endl;
            cout << "4. Usun osobe" << endl;
            cout << "5. Wprowadz zmiany" << endl;
            cout << "6. Wyjdz" << endl;
            cin >> n;

            if (n == 1) {
                lista.wyswietl();
            }
            else if (n == 2) {
                string nazw, im;
                int nr;

                cout << "Podaj nazwisko: " << endl;
                cin >> nazw;

                cout << "Podaj imie: " << endl;
                cin >> im;

                cout << "Podaj nr indeksu: " << endl;
                cin >> nr;

                lista.dodajOsobe(nazw, im, nr);
            }
            else if (n == 3) {
                string nazw;
                bool ob;

                cout << "Podaj nazwisko: " << endl;
                cin >> nazw;

                cout << "Podaj obecnosc (0 lub 1): " << endl;
                cin >> ob;

                lista.ustawObecnosc(nazw, ob);
            }
            else if (n == 4) {
                int nr;

                cout << "Podaj nr indeksu: " << endl;
                cin >> nr;

                lista.usunOsobe(nr);
            }
            else if (n == 5) {
                int nr, nr2;
                string im, nazw;

                cout << "Podaj nr indeksu: " << endl;
                cin >> nr;

                cout << "Zmiany dla indeksu: " << nr << endl;

                cout << "Podaj nowy numer indeksu: " << endl;
                cin >> nr2;

                cout << "Podaj nowe imie: " << endl;
                cin >> im;

                cout << "Podaj nowe nazwisko: " << endl;
                cin >> nazw;

                lista.zmienDaneStudenta(nr, nr2, im, nazw);
            }
            else if (n == 6) {
                cout << "Good night and good luck :)." << endl;
            }
            else {
                cout << "Nieprawidlowa opcja." << endl;
            }
        }
    }
};

int main() {
    InterfejsUzytkownika ui;
    ui.uruchom();
    return 0;
}