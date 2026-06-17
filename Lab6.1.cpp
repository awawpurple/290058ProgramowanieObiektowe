#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Serializable {
public:
    virtual string serialize() const = 0;
    virtual ~Serializable() {}
};

class Osoba : public Serializable {
protected:
    string imie;
    string nazwisko;

public:
    Osoba() : imie(""), nazwisko("") {}
    Osoba(string im, string nazw) : imie(im), nazwisko(nazw) {}
    virtual ~Osoba() {}

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
    Student(string im, string nazw, int nr) : Osoba(im, nazw), nrIndexu(nr) {}

    int getId() const override {
        return nrIndexu;
    }

    void setId(int noweId) override {
        nrIndexu = noweId;
    }

    string getTyp() const override {
        return "Student";
    }

    string serialize() const override {
        return "[Student] " + to_string(nrIndexu) + " " + imie + " " + nazwisko;
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

    string serialize() const override {
        return "[Student Zaoczny] " + to_string(nrIndexu) + " " + imie + " " + nazwisko +
               " semestr: " + to_string(semestr);
    }
};

class Stazysta : public Osoba {
private:
    int nrStazysty;

public:
    Stazysta() : Osoba(), nrStazysty(0) {}
    Stazysta(string im, string nazw, int nr) : Osoba(im, nazw), nrStazysty(nr) {}

    int getId() const override {
        return nrStazysty;
    }

    void setId(int noweId) override {
        nrStazysty = noweId;
    }

    string getTyp() const override {
        return "Stazysta";
    }

    string serialize() const override {
        return "[Stazysta] " + to_string(nrStazysty) + " " + imie + " " + nazwisko;
    }
};

class Prowadzacy : public Osoba {
private:
    int nrPracownika;

public:
    Prowadzacy() : Osoba(), nrPracownika(0) {}
    Prowadzacy(string im, string nazw, int nr) : Osoba(im, nazw), nrPracownika(nr) {}

    int getId() const override {
        return nrPracownika;
    }

    void setId(int noweId) override {
        nrPracownika = noweId;
    }

    string getTyp() const override {
        return "Prowadzacy";
    }

    string serialize() const override {
        return "[Prowadzacy] " + to_string(nrPracownika) + " " + imie + " " + nazwisko;
    }
};

void serialize(const Serializable* obj) {
    cout << obj->serialize() << endl;
}

class ListaObecnosci : public Serializable {
private:
    static const int osobyMAX = 20;
    Osoba* osoby[osobyMAX];
    bool obecnosc[osobyMAX];
    int iloscOsob;
    string nazwaGrupy;

public:
    ListaObecnosci() : iloscOsob(0), nazwaGrupy("Bez nazwy") {
        for (int i = 0; i < osobyMAX; i++) {
            osoby[i] = nullptr;
            obecnosc[i] = false;
        }
    }

    ListaObecnosci(string nazwa) : iloscOsob(0), nazwaGrupy(nazwa) {
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

    string getNazwaGrupy() const {
        return nazwaGrupy;
    }

    void setNazwaGrupy(string nazwa) {
        nazwaGrupy = nazwa;
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

    void zapisDoPliku(int id, string nazwaPliku) {
        ofstream plik(nazwaPliku);

        if (!plik.is_open()) {
            cout << "Nie udalo sie otworzyc pliku." << endl;
            return;
        }

        for (int i = 0; i < iloscOsob; i++) {
            if (osoby[i]->getId() == id) {
                plik << osoby[i]->serialize()
                     << " | obecny: " << obecnosc[i] << endl;
                plik.close();
                cout << "Zapisano osobe do pliku." << endl;
                return;
            }
        }

        cout << "Nie znaleziono osoby o podanym identyfikatorze." << endl;
        plik.close();
    }

    void zapisOgolny(string nazwaPliku) {
        ofstream plik(nazwaPliku);

        if (!plik.is_open()) {
            cout << "Nie udalo sie otworzyc pliku." << endl;
            return;
        }

        plik << "Grupa: " << nazwaGrupy << endl;

        if (iloscOsob == 0) {
            plik << "Lista jest pusta." << endl;
        } else {
            for (int i = 0; i < iloscOsob; i++) {
                plik << osoby[i]->serialize()
                     << " | obecny: " << obecnosc[i] << endl;
            }
        }

        plik.close();
        cout << "Zapisano liste do pliku." << endl;
    }

    string serialize() const override {
        string wynik = "Grupa: " + nazwaGrupy + "\n";

        if (iloscOsob == 0) {
            wynik += "Lista jest pusta.";
            return wynik;
        }

        for (int i = 0; i < iloscOsob; i++) {
            wynik += osoby[i]->serialize();
            wynik += " | obecny: " + to_string(obecnosc[i]);
            wynik += "\n";
        }

        return wynik;
    }
};

class InterfejsUzytkownika {
private:
    static const int MAX_GRUP = 10;
    ListaObecnosci* grupy[MAX_GRUP];
    int iloscGrup;
    int aktywnaGrupa;

    ListaObecnosci* pobierzAktywnaListe() {
        if (aktywnaGrupa < 0 || aktywnaGrupa >= iloscGrup) {
            return nullptr;
        }
        return grupy[aktywnaGrupa];
    }

    void utworzGrupe() {
        if (iloscGrup >= MAX_GRUP) {
            cout << "Nie mozna utworzyc wiecej grup." << endl;
            return;
        }

        string nazwa;
        cout << "Podaj nazwe grupy: ";
        cin >> nazwa;

        grupy[iloscGrup] = new ListaObecnosci(nazwa);
        aktywnaGrupa = iloscGrup;
        iloscGrup++;

        cout << "Utworzono grupe i ustawiono jako aktywna." << endl;
    }

    void wybierzGrupe() {
        if (iloscGrup == 0) {
            cout << "Brak grup." << endl;
            return;
        }

        cout << "Dostepne grupy:" << endl;
        for (int i = 0; i < iloscGrup; i++) {
            cout << i << ". " << grupy[i]->getNazwaGrupy();
            if (i == aktywnaGrupa) {
                cout << " [aktywna]";
            }
            cout << endl;
        }

        cout << "Podaj numer grupy: ";
        int nr;
        cin >> nr;

        if (nr >= 0 && nr < iloscGrup) {
            aktywnaGrupa = nr;
            cout << "Zmieniono aktywna grupe." << endl;
        } else {
            cout << "Nieprawidlowy numer grupy." << endl;
        }
    }

    void dodajStudenta() {
        ListaObecnosci* lista = pobierzAktywnaListe();
        if (lista == nullptr) {
            cout << "Najpierw utworz lub wybierz grupe." << endl;
            return;
        }

        string nazw, im;
        int nr;

        cout << "Podaj nazwisko: ";
        cin >> nazw;
        cout << "Podaj imie: ";
        cin >> im;
        cout << "Podaj nr indeksu: ";
        cin >> nr;

        Osoba* osoba = new Student(im, nazw, nr);
        lista->dodajOsobe(osoba);
    }

    void dodajStudentaZaocznego() {
        ListaObecnosci* lista = pobierzAktywnaListe();
        if (lista == nullptr) {
            cout << "Najpierw utworz lub wybierz grupe." << endl;
            return;
        }

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
        lista->dodajOsobe(osoba);
    }

    void dodajStazyste() {
        ListaObecnosci* lista = pobierzAktywnaListe();
        if (lista == nullptr) {
            cout << "Najpierw utworz lub wybierz grupe." << endl;
            return;
        }

        string nazw, im;
        int nr;

        cout << "Podaj nazwisko: ";
        cin >> nazw;
        cout << "Podaj imie: ";
        cin >> im;
        cout << "Podaj nr stazysty: ";
        cin >> nr;

        Osoba* osoba = new Stazysta(im, nazw, nr);
        lista->dodajOsobe(osoba);
    }

    void dodajProwadzacego() {
        ListaObecnosci* lista = pobierzAktywnaListe();
        if (lista == nullptr) {
            cout << "Najpierw utworz lub wybierz grupe." << endl;
            return;
        }

        string nazw, im;
        int nr;

        cout << "Podaj nazwisko: ";
        cin >> nazw;
        cout << "Podaj imie: ";
        cin >> im;
        cout << "Podaj nr prowadzacego: ";
        cin >> nr;

        Osoba* osoba = new Prowadzacy(im, nazw, nr);
        lista->dodajOsobe(osoba);
    }

    void zmienObecnosc() {
        ListaObecnosci* lista = pobierzAktywnaListe();
        if (lista == nullptr) {
            cout << "Najpierw utworz lub wybierz grupe." << endl;
            return;
        }

        int id;
        bool ob;

        cout << "Podaj identyfikator osoby: ";
        cin >> id;
        cout << "Podaj obecnosc (0 lub 1): ";
        cin >> ob;

        lista->ustawObecnosc(id, ob);
    }

    void usunOsobe() {
        ListaObecnosci* lista = pobierzAktywnaListe();
        if (lista == nullptr) {
            cout << "Najpierw utworz lub wybierz grupe." << endl;
            return;
        }

        int id;
        cout << "Podaj identyfikator osoby: ";
        cin >> id;

        lista->usunOsobe(id);
    }

    void zmienDane() {
        ListaObecnosci* lista = pobierzAktywnaListe();
        if (lista == nullptr) {
            cout << "Najpierw utworz lub wybierz grupe." << endl;
            return;
        }

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

        lista->zmienDaneOsoby(stareId, noweId, im, nazw);
    }

    void zapiszDoPliku() {
        ListaObecnosci* lista = pobierzAktywnaListe();
        if (lista == nullptr) {
            cout << "Najpierw utworz lub wybierz grupe." << endl;
            return;
        }

        cout << "Podaj nazwe pliku: ";
        string nazwa;
        cin >> nazwa;

        cout << "1 - jedna osoba, 2 - cala lista: ";
        int wybor;
        cin >> wybor;

        if (wybor == 1) {
            cout << "Podaj identyfikator osoby: ";
            int id;
            cin >> id;
            lista->zapisDoPliku(id, nazwa);
        } else if (wybor == 2) {
            lista->zapisOgolny(nazwa);
        } else {
            cout << "Nieprawidlowy wybor." << endl;
        }
    }

    void wyswietlAktywnaListe() {
        ListaObecnosci* lista = pobierzAktywnaListe();
        if (lista == nullptr) {
            cout << "Najpierw utworz lub wybierz grupe." << endl;
            return;
        }

        Serializable* s = lista;
        serialize(s);
    }

public:
    InterfejsUzytkownika() : iloscGrup(0), aktywnaGrupa(-1) {
        for (int i = 0; i < MAX_GRUP; i++) {
            grupy[i] = nullptr;
        }
    }

    ~InterfejsUzytkownika() {
        for (int i = 0; i < iloscGrup; i++) {
            delete grupy[i];
        }
    }

    void uruchom() {
        int n = 0;

        while (n != 11) {
            cout << endl;
            cout << "AKTYWNA GRUPA: ";
            if (aktywnaGrupa == -1) {
                cout << "brak";
            } else {
                cout << grupy[aktywnaGrupa]->getNazwaGrupy();
            }
            cout << endl;

            cout << "1. Utworz grupe" << endl;
            cout << "2. Wybierz grupe" << endl;
            cout << "3. Wyswietl liste" << endl;
            cout << "4. Dodaj studenta" << endl;
            cout << "5. Dodaj studenta zaocznego" << endl;
            cout << "6. Dodaj stazyste" << endl;
            cout << "7. Dodaj prowadzacego" << endl;
            cout << "8. Zmien obecnosc" << endl;
            cout << "9. Usun osobe" << endl;
            cout << "10. Wprowadz zmiany" << endl;
            cout << "11. Wyjdz" << endl;
            cout << "12. Zapisz do pliku" << endl;

            cin >> n;

            if (n == 1) {
                utworzGrupe();
            }
            else if (n == 2) {
                wybierzGrupe();
            }
            else if (n == 3) {
                wyswietlAktywnaListe();
            }
            else if (n == 4) {
                dodajStudenta();
            }
            else if (n == 5) {
                dodajStudentaZaocznego();
            }
            else if (n == 6) {
                dodajStazyste();
            }
            else if (n == 7) {
                dodajProwadzacego();
            }
            else if (n == 8) {
                zmienObecnosc();
            }
            else if (n == 9) {
                usunOsobe();
            }
            else if (n == 10) {
                zmienDane();
            }
            else if (n == 11) {
                cout << "Koniec programu." << endl;
            }
            else if (n == 12) {
                zapiszDoPliku();
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