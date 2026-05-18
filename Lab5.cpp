#include <iostream>
#include <string>
using namespace std;

class Drukowalny {
public:
    virtual void drukuj() const = 0;
    virtual ~Drukowalny() {}
};

class Osoba : public Drukowalny {
protected:
    string imie;
    string nazwisko;

public:
    Osoba() : imie(""), nazwisko("") {}

    Osoba(string im, string nazw) : imie(im), nazwisko(nazw) {}

    ~Osoba() override {}
    
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
};

class Student : public Osoba {
protected:
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

    void drukuj() const override {
        cout << "[Student] "
             << nrIndexu << " "
             << imie << " "
             << nazwisko;
    }
};

class StudentZaoczny : public Student {
private:
    int semestr;

public:
    StudentZaoczny() : Student(), semestr(1) {}

    StudentZaoczny(string im, string nazw, int nr, int sem)
        : Student(im, nazw, nr), semestr(sem) {}

    void setSemestr(int sem) {
        semestr = sem;
    }

    int getSemestr() const {
        return semestr;
    }

    string getTyp() const override {
        return "Student zaoczny";
    }

    void drukuj() const override {
        cout << "[Student zaoczny] "
             << nrIndexu << " "
             << imie << " "
             << nazwisko
             << " semestr: " << semestr;
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

    void drukuj() const override {
        cout << "[Stazysta] "
             << nrStazysty << " "
             << imie << " "
             << nazwisko;
    }
};

class ListaObecnosci : public Drukowalny {
private:
    static const int osobyMAX = 20;
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

    bool czyPelna() const {
        return iloscOsob >= osobyMAX;
    }

    void dodajOsobe(Osoba* osoba) {
        if (czyPelna()) {
            cout << "Brak miejsca na kolejna osobe." << endl;
            delete osoba;
            return;
        }

        osoby[iloscOsob] = osoba;
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

    void drukuj() const override {
        if (iloscOsob == 0) {
            cout << "Lista jest pusta." << endl;
            return;
        }

        for (int i = 0; i < iloscOsob; i++) {
            osoby[i]->drukuj();
            cout << " | obecny: " << obecnosc[i] << endl;
        }
    }
};

class InterfejsUzytkownika {
private:
    ListaObecnosci lista;

    void dodajStudenta() {
        string nazw, im;
        int nr;

        cout << "Podaj nazwisko: ";
        cin >> nazw;

        cout << "Podaj imie: ";
        cin >> im;

        cout << "Podaj nr indeksu: ";
        cin >> nr;

        Osoba* osoba = new Student(im, nazw, nr);
        lista.dodajOsobe(osoba);
    }

    void dodajStudentaZaocznego() {
        string nazw, im;
        int nr, semestr;

        cout << "Podaj nazwisko: ";
        cin >> nazw;

        cout << "Podaj imie: ";
        cin >> im;

        cout << "Podaj nr indeksu: ";
        cin >> nr;

        cout << "Podaj semestr: ";
        cin >> semestr;

        Osoba* osoba = new StudentZaoczny(im, nazw, nr, semestr);
        lista.dodajOsobe(osoba);
    }

    void dodajStazyste() {
        string nazw, im;
        int nr;

        cout << "Podaj nazwisko: ";
        cin >> nazw;

        cout << "Podaj imie: ";
        cin >> im;

        cout << "Podaj nr stazysty: ";
        cin >> nr;

        Osoba* osoba = new Stazysta(im, nazw, nr);
        lista.dodajOsobe(osoba);
    }

    void zmienObecnosc() {
        int id;
        bool ob;

        cout << "Podaj identyfikator osoby: ";
        cin >> id;

        cout << "Podaj obecnosc (0 lub 1): ";
        cin >> ob;

        lista.ustawObecnosc(id, ob);
    }

    void usunOsobe() {
        int id;

        cout << "Podaj identyfikator osoby: ";
        cin >> id;

        lista.usunOsobe(id);
    }

    void zmienDane() {
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

public:
    void uruchom() {
        int n = 0;

        while (n != 8) {
            cout << endl;
            cout << "Co chcesz zrobic?" << endl;
            cout << "1. Wyswietl liste" << endl;
            cout << "2. Dodaj studenta" << endl;
            cout << "3. Dodaj studenta zaocznego" << endl;
            cout << "4. Dodaj stazyste" << endl;
            cout << "5. Zmien obecnosc" << endl;
            cout << "6. Usun osobe" << endl;
            cout << "7. Wprowadz zmiany" << endl;
            cout << "8. Wyjdz" << endl;
            cin >> n;

            if (n == 1) {
                Drukowalny* d = &lista;
                d->drukuj();
            }
            else if (n == 2) {
                dodajStudenta();
            }
            else if (n == 3) {
                dodajStudentaZaocznego();
            }
            else if (n == 4) {
                dodajStazyste();
            }
            else if (n == 5) {
                zmienObecnosc();
            }
            else if (n == 6) {
                usunOsobe();
            }
            else if (n == 7) {
                zmienDane();
            }
            else if (n == 8) {
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