import <iostream>;
import <cstdlib>;
import <ctime>;
import <cassert>;

namespace DataStorage {
    class Vector {
        friend std::ostream& operator<<(std::ostream&, const Vector&);
        int rozmiar;
        double* tab;
    public:
        Vector(int rozmiarTab) {
            rozmiar = rozmiarTab;
            tab = new double[rozmiar];
            assert(tab != 0);
            for (int i = 0; i < rozmiar; i++)
                tab[i] = 0;
        }

        Vector(const Vector& Tab) {
            rozmiar = Tab.rozmiar;
            tab = new double[rozmiar];
            assert(tab != 0);
            for (int i = 0; i < rozmiar; i++)
                tab[i] = Tab.tab[i];
        }

        ~Vector(void) {
            delete[] tab;
        }

        int operator==(const Vector& zprawejStrony) const
        {
            if (rozmiar != zprawejStrony.rozmiar)
                return 0;
            for (int i = 0; i < rozmiar; i++)
                if (tab[i] != zprawejStrony.tab[i])
                    return 0;
            return 1;
        }

        double& operator[](int index) {
            assert(0 <= index && index < rozmiar);
            return tab[index];
        }

        double operator[](int index) const {
            assert(0 <= index && index < rozmiar);
            return tab[index];
        }

        int getRozmiar() const {
            return rozmiar;
        }
    };

    std::ostream& operator<<(std::ostream& wyjscie, const Vector& t) {
        wyjscie << "[ ";
        for (int i = 0; i < t.rozmiar; i++)
            wyjscie << t.tab[i] << " ";
        wyjscie << "]";
        return wyjscie;
    }

    class Matrix {
        double** tab;
        int wiersze, kolumny;
        mutable int licznik;
    public:

        Matrix(int n, int m) : wiersze(n), kolumny(m), licznik(0) {
            tab = new double* [wiersze];
            for (int i = 0; i < wiersze; i++)
                tab[i] = new double[kolumny];
            for (int i = 0; i < wiersze; i++)
                for (int j = 0; j < kolumny; j++)
                    tab[i][j] = 0;
        }

        Matrix(const Matrix& other) : wiersze(other.wiersze), kolumny(other.kolumny), licznik(other.licznik) {
            tab = new double* [wiersze];
            for (int i = 0; i < wiersze; i++) {
                tab[i] = new double[kolumny];
                for (int j = 0; j < kolumny; j++)
                    tab[i][j] = other.tab[i][j];
            }
        }

        ~Matrix(void) {
            for (int i = 0; i < wiersze; i++)
                delete[] tab[i];
            delete[] tab;
        }

        Matrix& operator=(const Matrix& other)
        {
            if (this == &other) return *this;
            for (int i = 0; i < wiersze; i++)
                delete[] tab[i];
            delete[] tab;
            wiersze = other.wiersze;
            kolumny = other.kolumny;
            licznik = other.licznik;
            tab = new double* [wiersze];
            for (int i = 0; i < wiersze; i++)
                tab[i] = new double[kolumny];
            for (int i = 0; i < wiersze; i++)
                for (int j = 0; j < kolumny; j++)
                    tab[i][j] = other.tab[i][j];
            return *this;
        }

        int getWiersze() const { return wiersze; }
        int getKolumny() const { return kolumny; }

        double& operator()(int i, int j) {
            licznik++;
            return tab[i][j];
        }

        double operator()(int i, int j) const {
            return tab[i][j];
        }

        Matrix operator+(const Matrix& other) const {
            Matrix result(wiersze, kolumny);
            for (int i = 0; i < wiersze; i++) {
                for (int j = 0; j < kolumny; j++) {
                    result(i, j) = tab[i][j] + other.tab[i][j];
                }
            }
            return result;
        }

        Matrix operator*(double skalar) const {
            Matrix result(wiersze, kolumny);
            for (int i = 0; i < wiersze; i++) {
                for (int j = 0; j < kolumny; j++) {
                    result(i, j) = tab[i][j] * skalar;
                }
            }
            return result;
        }

        Vector operator*(const Vector& v) const {
            Vector result(wiersze);
            for (int i = 0; i < wiersze; i++) {
                double sum = 0;
                for (int j = 0; j < kolumny; j++) {
                    sum += tab[i][j] * v[j];
                }
                result[i] = sum;
            }
            return result;
        }
    };
}

namespace Utils {
    class MatrixToolbox {
        MatrixToolbox() {}
    public:
        static void fillRandom(DataStorage::Vector& v) {
            for (int i = 0; i < v.getRozmiar(); i++) {
                v[i] = std::rand() % 10;
            }
        }

        static void fillRandom(DataStorage::Matrix& m) {
            for (int i = 0; i < m.getWiersze(); i++) {
                for (int j = 0; j < m.getKolumny(); j++) {
                    m(i, j) = std::rand() % 10;
                }
            }
        }
    };
}

void laba_4() {
    //std::srand(static_cast<unsigned int>(std::time(0)));
    std::srand(static_cast<unsigned int>(42));
    using namespace DataStorage;
    using namespace Utils;

    // 1. Test dodawania i skalara
    Matrix A(2, 2), B(2, 2);
    MatrixToolbox::fillRandom(A);
    MatrixToolbox::fillRandom(B);

    Matrix C = A + B;
    Matrix D = A * 10.0;

    std::cout << "Macierz A:\n";
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) std::cout << A(i, j) << " ";
        std::cout << "\n";
    }

    // 2. Test mnożenia Macierz * Wektor
    Matrix M(3, 2); // 3 wiersze, 2 kolumny
    Vector V(2);    // Wektor musi mieć 2 elementy

    MatrixToolbox::fillRandom(M);
    MatrixToolbox::fillRandom(V);

    Vector res = M * V;

    std::cout << "\nMnozenie M * V:\n";
    std::cout << "M (3x2):\n";
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 2; ++j) std::cout << M(i, j) << " ";
        std::cout << "\n";
    }
    std::cout << "V (2x1): " << V << "\n";
    std::cout << "Wynik V_res (3x1): " << res << "\n";

    std::cout << "\nTest operatora przypisania\n";
    Matrix M1(2, 2);
    MatrixToolbox::fillRandom(M1);

    std::cout << "M1 przed zmiana:\n";
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) std::cout << M1(i, j) << " ";
        std::cout << "\n";
    }

    Matrix M2(2, 2);
    M2 = M1;
    M2(0, 0) = 999;

    std::cout << "M1 po zmianie M2(0,0) na 999:\n";
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) std::cout << M1(i, j) << " ";
        std::cout << "\n";
    }
}

int main() {
    laba_4();
    return 0;
}