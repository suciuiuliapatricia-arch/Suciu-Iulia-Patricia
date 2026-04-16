#include <iostream>    // Pentru cout (afișare pe ecran) și cin (citire de la tastatura)
#include <string>      // Pentru lucrul cu șiruri de caractere (string-uri)
#include <cstdlib>     // Pentru funcția rand() - generează numere aleatorii
#include <ctime>       // Pentru funcția time() - obține momentul actual în secunde

using namespace std;   // Simplificare: nu mai trebuie să scriem std:: în fața funcțiilor

// Funcție care afișează cuvântul ascuns cu litere ghicite și liniuțe pentru restul
void arataCuvant(string cuvant, int ghicit[]) {  // Primește cuvântul și o listă cu literele ghicite
    for (int i = 0; i < cuvant.length(); ++i) {  // Parcurge fiecare literă din cuvânt
        if (ghicit[i] == 1) {                    // Dacă litera a fost ghicită (valoarea e 1)
            cout << cuvant[i] << " ";           // Afișează litera cu spațiu
        } else {                                  // Altfel
            cout << "_ ";                        // Afișează liniuță (o ascunde)
        }
    }
    cout << endl;                                // Trecem la rând nou
}

// Funcție care desenează spânzurătoarea - se completează cu fiecare greșeală
void deseneazaOmulet(int greseli) {  // Primește numărul de greșeli făcute
    cout << "  +---+" << endl;       // Linia de sus a spânzurătorii
    cout << "  |   |" << endl;       // Bara verticală
    if (greseli >= 1) cout << "  O   |" << endl;      // La 1 greșeală: se desenează capul
    else cout << "      |" << endl;                  // Altfel: gol
    if (greseli >= 3) cout << " /|\\  |" << endl;     // La 3 greșeli: brațele complete (/ și \)
    else if (greseli >= 2) cout << " /|   |" << endl; // La 2 greșeli: doar brațul stâng (/)
    else cout << "      |" << endl;                   // Altfel: gol
    if (greseli >= 5) cout << " / \\  |" << endl;     // La 5 greșeli: picioarele complete
    else if (greseli >= 4) cout << " /    |" << endl; // La 4 greșeli: piciorul stâng
    else cout << "      |" << endl;                   // Altfel: gol
    cout << "      |" << endl;       // Linia de sprijin
    cout << "=========" << endl;     // Baza spânzurătorii
}

int main() {  // Funcția principală - de aici începe execuția programului
    // Lista de cuvinte din care jocul va alege și ascunde una
    string listaCuvinte[] = {"calculator", "programare", "algoritm", "variabila", "functie"};
    int numarCuvinte = 5;    // Se numără cuvintele din listă

    // Inițializează generatorul de numere aleatorii
    srand(time(0));          // seed-ul depinde de ora curentă = numere diferite de fiecare dată

    // Alege aleatoriu un cuvânt din listă
    string cuvantSecret = listaCuvinte[rand() % numarCuvinte];  // rand() % 5 dă 0-4, indexe valide

    // Array care ține minte care litere au fost ghicite (1 = ghicite, 0 = nu)
    int litereGhicite[20];  // Array cu 20 poziții (suficient pentru cuvintele noastre)
    for (int i = 0; i < cuvantSecret.length(); ++i) {  // Parcurge fiecare literă din cuvântul secret
        litereGhicite[i] = 0;  // Inițial, nici o literă nu e ghicită (0 = fals)
    }

    // Variabile pentru a ține minte erori
    int numarGreseli = 0;    // Contorul de greșeli - începe de la 0
    int maximGreseli = 6;    // Limita: după 6 greșeli, pierzi jocul

    // String pentru a ține minte toate literele pe care le-a incercat deja jucătorul
    string litereIncercate = "";  // Inițial gol

    cout << "Salut! Hai sa jucam Spanzuratoarea!" << endl;  // Mesaj de bun venit
    cout << "Ghiceste cuvantul scriind litere." << endl;    // Instrucțiuni pentru jucător

    while (numarGreseli < maximGreseli) {  // Cât timp nu ai pierdut (greșeli < 6), continuă jocul
        cout << "\nCuvantul ascuns: ";    // Afișează cuvântul cu liniuțe și litere ghicite
        arataCuvant(cuvantSecret, litereGhicite);  // Apelează funcția de display

        cout << "Litere incercate: " << litereIncercate << endl;  // Arată literele pe care le-ai încercat
        deseneazaOmulet(numarGreseli);  // Desenează omulețul cu numărul curent de greșeli

        // Verifică dacă toată le sunt ghicite (condiție de victorie)
        int amGhicitTot = 1;  // Presupunem că da (1 = adevărat)
        for (int i = 0; i < cuvantSecret.length(); ++i) {  // Parcurge fiecare literă
            if (litereGhicite[i] == 0) {  // Dacă găsești o literă negicită
                amGhicitTot = 0;          // Schimbă la 0 (fals) - nu le-ai ghicit pe toate
            }
        }
        if (amGhicitTot == 1) {  // Dacă toți sunt în 1 (toate ghicite)
            cout << "Bravo! Ai castigat! Cuvantul era: " << cuvantSecret << endl;  // Mesaj victorie
            return 0;  // Ieși din program cu succes
        }

        // Cere jucătorului să introducă o literă
        char litera;           // Variabilă pentru a stoca o singură literă
        cout << "Scrie o litera: ";  // Cere intrare
        cin >> litera;         // Citește o literă de la tastatură
        litera = tolower(litera);  // Convertește la minusculă (a-z) pentru comparare uniformă

        // Verifică dacă litera a fost deja încercată
        if (litereIncercate.find(litera) != string::npos) {  // find() returnează npos dacă nu găsește
            cout << "Ai incercat deja aceasta litera!" << endl;  // Avertisment
            continue;  // Sari la următoarea iterație (nu face nimic cu această literă)
        }

        litereIncercate += litera;  // Adaugă litera la stringul de litere încercate
        litereIncercate += " ";     // Adaugă spațiu pentru separare

        // Caută litera în cuvântul secret
        int amGasit = 0;  // Presupunem că litera NU e în cuvânt (0 = fals)
        for (int i = 0; i < cuvantSecret.length(); ++i) {  // Parcurge fiecare poziție în cuvânt
            if (cuvantSecret[i] == litera) {  // Dacă poziția i conține litera
                litereGhicite[i] = 1;  // Marchează că e ghicită (1 = adevărat)
                amGasit = 1;           // Schimbă la 1 (litera a fost găsită)
            }
        }

        if (amGasit == 0) {  // Dacă litera NU a fost găsită în cuvânt
            numarGreseli++;  // Incrementează contorul de greșeli
            cout << "Greseala!" << endl;  // Mesaj de greșeală
        }
    }  // Sfârșit buclei while

    // Jocul s-a terminat - ai depășit limita de 6 greșeli
    deseneazaOmulet(numarGreseli);  // Desenează omulețul complet (spânzurat)
    cout << "Joc terminat! Cuvantul era: " << cuvantSecret << endl;  // Dezvăluie cuvântul

    return 0;  // Încheie programul cu succes
}  // Sfârșit funcția main