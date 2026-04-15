#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

// Functie care arata cuvantul ascuns
void arataCuvant(string cuvant, int ghicit[]) {
    for (int i = 0; i < cuvant.length(); ++i) {
        if (ghicit[i] == 1) {
            cout << cuvant[i] << " ";
        } else {
            cout << "_ ";
        }
    }
    cout << endl;
}

// Functie care deseneaza omuletul spanzurat
void deseneazaOmulet(int greseli) {
    cout << "  +---+" << endl;
    cout << "  |   |" << endl;
    if (greseli >= 1) cout << "  O   |" << endl;
    else cout << "      |" << endl;
    if (greseli >= 3) cout << " /|\\  |" << endl;
    else if (greseli >= 2) cout << " /|   |" << endl;
    else cout << "      |" << endl;
    if (greseli >= 5) cout << " / \\  |" << endl;
    else if (greseli >= 4) cout << " /    |" << endl;
    else cout << "      |" << endl;
    cout << "      |" << endl;
    cout << "=========" << endl;
}

int main() {
    // Lista de cuvinte pentru joc
    string listaCuvinte[] = {"calculator", "programare", "algoritm", "variabila", "functie"};
    int numarCuvinte = 5;

    // Pornim generatorul de numere aleatorii
    srand(time(0));

    // Alegem un cuvant la intamplare
    string cuvantSecret = listaCuvinte[rand() % numarCuvinte];

    // Array care tine minte literele ghicite
    int litereGhicite[20]; // Cuvantul are maxim 20 litere
    for (int i = 0; i < cuvantSecret.length(); ++i) {
        litereGhicite[i] = 0;
    }

    // Numarul de greseli facute
    int numarGreseli = 0;
    int maximGreseli = 6;

    // Literele incercate pana acum
    string litereIncercate = "";

    cout << "Salut! Hai sa jucam Spanzuratoarea!" << endl;
    cout << "Ghiceste cuvantul scriind litere." << endl;

    while (numarGreseli < maximGreseli) {
        cout << "\nCuvantul ascuns: ";
        arataCuvant(cuvantSecret, litereGhicite);

        cout << "Litere incercate: " << litereIncercate << endl;
        deseneazaOmulet(numarGreseli);

        // Vedem daca am ghicit tot cuvantul
        int amGhicitTot = 1;
        for (int i = 0; i < cuvantSecret.length(); ++i) {
            if (litereGhicite[i] == 0) {
                amGhicitTot = 0;
            }
        }
        if (amGhicitTot == 1) {
            cout << "Bravo! Ai castigat! Cuvantul era: " << cuvantSecret << endl;
            return 0;
        }

        // Citim litera de la jucator
        char litera;
        cout << "Scrie o litera: ";
        cin >> litera;
        litera = tolower(litera);

        // Vedem daca am incercat deja litera asta
        if (litereIncercate.find(litera) != string::npos) {
            cout << "Ai incercat deja aceasta litera!" << endl;
            continue;
        }

        litereIncercate += litera;
        litereIncercate += " ";

        // Vedem daca litera e in cuvant
        int amGasit = 0;
        for (int i = 0; i < cuvantSecret.length(); ++i) {
            if (cuvantSecret[i] == litera) {
                litereGhicite[i] = 1;
                amGasit = 1;
            }
        }

        if (amGasit == 0) {
            numarGreseli++;
            cout << "Greseala!" << endl;
        }
    }

    // Jocul s-a terminat
    deseneazaOmulet(numarGreseli);
    cout << "Joc terminat! Cuvantul era: " << cuvantSecret << endl;

    return 0;
}