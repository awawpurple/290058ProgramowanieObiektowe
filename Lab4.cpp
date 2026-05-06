#include <iostream>
#include <string>
using namespace std;

class Osoba {
protected:
    string imie;
    string nazwisko;

public:
    Osoba() : imie(""), nazwisko("") {}

    Osoba(string im, string nazw) : imie(im), nazwisko(nazw) {}

    string getImie() const {
        return imie;
    }

    string getNazwisko() const {
        return nazwisko;
    }

    void setImie(string im) {
        imie = im;
    }

    void setNazwisko(string nazw) {
        nazwisko = nazw;
    }

    virtual int getId() const = 0;
    virtual void setId(int noweId) = 0;
    virtual string getTyp() const = 0;

    virtual void wyswietl() const {
        cout << imie << " " << nazwisko;
    }
};

class Student : public Osoba {
private:
    int nrIndexu;

public:
    Student() : Osoba(), nrIndexu(0) {}

    Student(string im, string nazw, int nr)
        : Osoba(im, nazw), nrIndexu(nr) {}

    int getId() const override {
        return nrIndexu;
    }

    void setId(int noweId) override {
        nrIndexu = noweId;
    }

    string getTyp() const override {
        return "Student";
    }

    void wyswietl() const override {
        cout << "[Student] "
             << nrIndexu << " "
             << imie << " "
             << nazwisko;
    }
};

class Stazysta : public Osoba {
private:
    int nrStazysty;

public:
    Stazysta() : Osoba(), nrStazysty(0) {}

    Stazysta(string im, string nazw, int nr)
        : Osoba(im, nazw), nrStazysty(nr) {}

    int getId() const override {
        return nrStazysty;
    }

    void setId(int noweId) override {
        nrStazysty = noweId;
    }

    string getTyp() const override {
        return "Stazysta";
    }

    void wyswietl() const override {
        cout << "[Stazysta] "
             << nrStazysty << " "
             << imie << " "
             << nazwisko;
    }
};

class ListaObecnosci {
private:
    static const int osobyMAX = 10;
    Osoba* osoby[osobyMAX];
    bool obecnosc[osobyMAX];
    int iloscOsob;

public:
    ListaObecnosci() : iloscOsob(0) {
        for (int i = 0; i < osobyMAX; i++) {
            osoby[i] = nullptr;
            obecnosc[i] = false;
        }
    }

    ~ListaObecnosci() {
        for (int i = 0; i < iloscOsob; i++) {
            delete osoby[i];
        }
    }

    void wyswietl() const {
        if (iloscOsob == 0) {
            cout << "Lista jest pusta." << endl;
            return;
        }

        for (int i = 0; i < iloscOsob; i++) {
            osoby[i]->wyswietl();
            cout << " | obecny: " << obecnosc[i] << endl;
        }
    }

    void dodajStudenta(string nazw, string im, int nr) {
        if (iloscOsob >= osobyMAX) {
            cout << "Brak miejsca na kolejna osobe." << endl;
            return;
        }

        osoby[iloscOsob] = new Student(im, nazw, nr);
        obecnosc[iloscOsob] = false;
        iloscOsob++;
    }

    void dodajStazyste(string nazw, string im, int nr) {
        if (iloscOsob >= osobyMAX) {
            cout << "Brak miejsca na kolejna osobe." << endl;
            return;
        }

        osoby[iloscOsob] = new Stazysta(im, nazw, nr);
        obecnosc[iloscOsob] = false;
        iloscOsob++;
    }

    void usunOsobe(int id) {
        int pozycja = -1;

        for (int i = 0; i < iloscOsob; i++) {
            if (osoby[i]->getId() == id) {
                pozycja = i;
                break;
            }
        }

        if (pozycja == -1) {
            cout << "Nie znaleziono osoby o podanym identyfikatorze." << endl;
            return;
        }

        delete osoby[pozycja];

        for (int i = pozycja; i < iloscOsob - 1; i++) {
            osoby[i] = osoby[i + 1];
            obecnosc[i] = obecnosc[i + 1];
        }

        osoby[iloscOsob - 1] = nullptr;
        obecnosc[iloscOsob - 1] = false;
        iloscOsob--;
    }

    void ustawObecnosc(int id, bool ob) {
        for (int i = 0; i < iloscOsob; i++) {
            if (osoby[i]->getId() == id) {
                obecnosc[i] = ob;
                return;
            }
        }

        cout << "Nie znaleziono osoby o podanym identyfikatorze." << endl;
    }

    void zmienDaneOsoby(int id, int noweId, string noweImie, string noweNazwisko) {
        for (int i = 0; i < iloscOsob; i++) {
            if (osoby[i]->getId() == id) {
                osoby[i]->setId(noweId);
                osoby[i]->setImie(noweImie);
                osoby[i]->setNazwisko(noweNazwisko);
                return;
            }
        }

        cout << "Nie znaleziono osoby o podanym identyfikatorze." << endl;
    }
};

class InterfejsUzytkownika {
private:
    ListaObecnosci lista;

public:
    void uruchom() {
        int n = 0;

        while (n != 7) {
            cout << endl;
            cout << "Co chcesz zrobic?" << endl;
            cout << "1. Wyswietl liste" << endl;
            cout << "2. Dodaj studenta" << endl;
            cout << "3. Dodaj stazyste" << endl;
            cout << "4. Zmien obecnosc" << endl;
            cout << "5. Usun osobe" << endl;
            cout << "6. Wprowadz zmiany" << endl;
            cout << "7. Wyjdz" << endl;
            cin >> n;

            if (n == 1) {
                lista.wyswietl();
            }
            else if (n == 2) {
                string nazw, im;
                int nr;

                cout << "Podaj nazwisko: ";
                cin >> nazw;

                cout << "Podaj imie: ";
                cin >> im;

                cout << "Podaj nr indeksu: ";
                cin >> nr;

                lista.dodajStudenta(nazw, im, nr);
            }
            else if (n == 3) {
                string nazw, im;
                int nr;

                cout << "Podaj nazwisko: ";
                cin >> nazw;

                cout << "Podaj imie: ";
                cin >> im;

                cout << "Podaj nr stazysty: ";
                cin >> nr;

                lista.dodajStazyste(nazw, im, nr);
            }
            else if (n == 4) {
                int id;
                bool ob;

                cout << "Podaj identyfikator osoby: ";
                cin >> id;

                cout << "Podaj obecnosc (0 lub 1): ";
                cin >> ob;

                lista.ustawObecnosc(id, ob);
            }
            else if (n == 5) {
                int id;

                cout << "Podaj identyfikator osoby: ";
                cin >> id;

                lista.usunOsobe(id);
            }
            else if (n == 6) {
                int stareId, noweId;
                string im, nazw;

                cout << "Podaj identyfikator osoby: ";
                cin >> stareId;

                cout << "Podaj nowy identyfikator: ";
                cin >> noweId;

                cout << "Podaj nowe imie: ";
                cin >> im;

                cout << "Podaj nowe nazwisko: ";
                cin >> nazw;

                lista.zmienDaneOsoby(stareId, noweId, im, nazw);
            }
            else if (n == 7) {
                cout << "Koniec programu." << endl;
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
