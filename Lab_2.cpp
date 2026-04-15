#include <iostream>
#include <string>

using namespace std;

struct Ship

{
private:
    string name;
    float power;

public:
    Ship() {
        cout << "Podaj nazwe: ";
        cin >> name;
        cout << "Podaj moc: "; 
            cin >> power;
    };

    float getPower() const {
        return power;
    }

    string getname() const {
        return name;
    }

};

class Squadron
{
    const int ID;
    int statki;
    Ship* sta;

public:

    Squadron(int id, int n = 3) : ID(id), statki(n) {
        sta = new Ship[statki];
    }

    float getTotalPower() const
    {
        float sum = 0;
        for (int i = 0; i < statki; i++)

        {
            sum += sta[i].getPower();
        }
        return sum;
    }

    void displayStatus() const {
        cout << "ID: " << ID << endl;
        for (int i = 0; i < statki; i++)
        {
            cout << "  - " << sta[i].getname() << " \tMoc: " << sta[i].getPower() << endl;

        }
    }
    void usun() {
        delete[] sta;
    }
};

class CommandCenter

{
    int liczba_squadron;
    Squadron** Squad;
public:

    CommandCenter(int n) : liczba_squadron(n) {
        Squad = new Squadron * [liczba_squadron];
        for (int i = 0; i < liczba_squadron; i++)
            Squad[i] = new Squadron(10 + i);
    }

    void generateReport() const {
        cout << "Eskadra: " << endl;
        for (int i = 0; i < liczba_squadron; i++)

        {
            Squad[i]->displayStatus();
            cout << " Suma mocy: " << Squad[i]->getTotalPower() << endl;
        }
    }

    void usun()
    {
        for (int i = 0; i < liczba_squadron; i++)
        {
            Squad[i]->usun();
            delete Squad[i];
        }
        delete[] Squad;
    }

};
int main()

{
    int n;
    cout << "Podaj liczbe eskadr: ";
    cin >> n;
    CommandCenter low{ n };
    low.generateReport();
    low.usun();

}

