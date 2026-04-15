#include <iostream>
#include <string>

using namespace std;

// Struktura w stylu C (bez metod wewnątrz)
struct Sensor {
    int id;
    float value;
    string name;
};

// --- TODO 1: PRZECIĄŻANIE FUNKCJI ---
// Napisz trzy wersje funkcji printInfo:
// 1. Przyjmującą stałą referencję do Sensor (wypisuje ID i Name).
// 2. Przyjmującą stałą referencję do Sensor oraz bool verbose (jeśli true, wypisuje też Value).
// 3. Przyjmującą wskaźnik na tablicę Sensor oraz jej rozmiar (wypisuje wszystkie elementy).

void printInfo(const Sensor& s) {
    cout<<"[ID: "<<s.id<< "]" << " Name: " << s.name << endl;
}

void printInfo(const Sensor* s, bool verbose) {
    cout<< "[ID: " << s->id << "]" << " Name: "<< s->name;
    if (verbose) {
        cout<<" | Value: "<< s->value<<endl;
    }
}

void printInfo(const Sensor* array, int size) {
    for (int i = 0; i < size; i++) {
        printInfo(array[i]);
    }
}

// TODO: dopisz pozostałe wersje printInfo


// --- TODO 2: REFERENCJE ---
// Napisz funkcję updateValue, która przyjmuje referencję do sensora 
// oraz nową wartość. Funkcja ma zaktualizować pole value.
// Zauważ brak konieczności używania operatora wyłuskania -> lub *
void updateValue(Sensor & s, float NewValue) {
        s.value = NewValue;
}

void stworz(Sensor*& osoba, const size_t rozmiar) {
    osoba = new Sensor[rozmiar];
}
void usun(Sensor*& osoba, const size_t rozmiar) {
    delete[] osoba;
    osoba = nullptr;
}

int main() {
    int n;
    cout << "Podaj liczbe sensorow do utworzenia: ";
    cin >> n;

    // --- TODO 3: OPERATOR NEW[] ---
    // Zamiast malloc(n * sizeof(Sensor)), użyj operatora new[].
    // Pamiętaj, że new automatycznie wywoła konstruktory (tu: dla string name).
    // TODO: alokacja
    Sensor* sensors = nullptr;
    stworz(sensors, n);


    // Inicjalizacja danych (przykładowa)
    for (int i = 0; i < n; i++) {
        sensors[i].id = i + 1;
        sensors[i].name = "Sensor_" + to_string(i + 1);
        sensors[i].value = 0.0f;
    }

    // Testowanie funkcji
    if (n > 0) {
        cout << "\nAktualizacja pierwszego sensora..." << endl;
        updateValue(sensors[0], 25.5f);

        cout << "Dane pojedyncze:" << endl;
        printInfo(sensors[0]);

        cout << "\nDane szczegolowe:" << endl;
        printInfo(sensors, true);
    }

    cout << "\nPelna lista sensorow:" << endl;
    // TODO: Wywołaj przeciążoną funkcję printInfo dla całej tablicy
    printInfo(sensors, n);

        // --- TODO 4: OPERATOR DELETE[] ---
        // Zwolnij pamięć zaalokowaną dla tablicy. 
        // Pamiętaj o użyciu wersji z nawiasami kwadratowymi.
        // TODO: zwolnienie pamięci
    usun(sensors, n);
    return 0;
}