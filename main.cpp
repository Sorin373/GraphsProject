#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <conio.h>

using namespace std;

constexpr int MAXN = 100;

int n, v[MAXN];
bool **adj;
char **nume;

void underline(const unsigned int vWidth)
{
    cout << setw(5 - 2) << " ";
    char fillLine;
    fillLine = cout.fill('_');
    cout.width(vWidth);
    cout << '_' << endl;
    cout.fill(fillLine);
    cout << endl;
}

void getData()
{
    ifstream fin("data.in");

    if (!fin.is_open())
    {
        cerr << "Failed to open file!" << endl;
        return;
    }

    fin >> n;

    nume = new char *[n];
    for (int i = 0; i < n; i++)
        nume[i] = new char[101];

    for (int i = 0; i < n; i++)
        fin >> nume[i];

    adj = new bool *[n + 1];
    for (int i = 1; i <= n; i++)
        adj[i] = new bool[n + 1];

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            adj[i][j] = false;

    int x, y;
    while (fin >> x >> y)
    {
        if (x > n || y > n)
        {
            cerr << "Input invalid!" << endl;
            return;
        }
        adj[x][y] = adj[y][x] = true;
    }

    fin.close();
}

void printData()
{
    cout << "\n\n"
         << setw(5) << " "
         << "Oamenii trecuti in baza de data:"
         << "\n"
         << setw(5) << " ";

    for (unsigned int i = 0; i < n; i++)
        if (i == n - 1)
            cout << nume[i];
        else
            cout << nume[i] << ", ";
}

void verifcarePrieten()
{
    system("CLS");

    char *numeCautat_1 = new char[101], *numeCautat_2 = new char[101];
    bool isFound = false;

    cout << "\n\n";
    cout << setw(5) << " "
         << "APASA TASTA '0' PENTRU A ANULA";

    printData();

    cout << "\n\n"
         << setw(5) << " "
         << "Introduceti numele:\n";
    cout << setw(5) << " "
         << "Nume_1: ";
    cin >> numeCautat_1;

    if (strcmp(numeCautat_1, "0") == 0)
    {
        delete[] numeCautat_1;
        delete[] numeCautat_2;
        return;
    }

    cout << setw(5) << " "
         << "Nume_2: ";
    cin >> numeCautat_2;

    if (strcmp(numeCautat_2, "0") == 0)
    {
        delete[] numeCautat_1;
        delete[] numeCautat_2;
        return;
    }
    else
    {
        cout << "\n";
        for (int i = 1; i <= n && !isFound; i++)
            for (int j = 1; j <= n && !isFound; j++)
                if (adj[i][j])
                {
                    if (stricmp(nume[i - 1], numeCautat_1) == 0 && stricmp(nume[j - 1], numeCautat_2) == 0)
                    {
                        cout << setw(5) << " " << numeCautat_1 << " este prieten cu " << numeCautat_2;
                        isFound = true;
                    }
                    else if (stricmp(nume[i - 1], numeCautat_2) == 0 && stricmp(nume[j - 1], numeCautat_1) == 0)
                    {
                        cout << setw(5) << " " << numeCautat_1 << " este prieten cu " << numeCautat_2;
                        isFound = true;
                    }
                }
        if (!isFound)
            cout << setw(5) << " "
                 << "Nu isFound aceasta prietenie!";

        delete[] numeCautat_1;
        delete[] numeCautat_2;

        getch();
        verifcarePrieten();
    }
}

void gradNod(int i)
{
    int contor = 0;
    if (i >= n)
        return;
    else
    {
        cout << setw(5) << " " << nume[i - 1] << ": ";
        for (int j = 1; j <= n; j++)
            if (adj[i][j])
            {
                if (contor > 0)
                    cout << ", ";
                cout << nume[j - 1];
                contor++;
            }
        cout << " (" << contor << " prieteni)\n";

        gradNod(i + 1);
    }
}

int gradMaxRec(int i, int contorV)
{
    int contor = 0;
    if (i >= n)
        return contorV;
    else
    {
        for (int j = 1; j <= n; j++)
            if (adj[i][j])
                contor++;
        v[contorV] = contor;
        gradMaxRec(i + 1, contorV + 1);
    }
}

void gradMax()
{
    int maxim = -(n * (n - 1)) / 2, contorV = gradMaxRec(1, 0);

    for (unsigned int i = 0; i < contorV; i++)
        if (v[i] > maxim)
            maxim = v[i];

    cout << "\n"
         << setw(5) << " "
         << "Numarul maxim de prietenii este: " << maxim << "\n"
         << setw(5) << " "
         << "Persoanele cu numarul acesta de prieteni sunt: ";

    for (unsigned int i = 0; i < contorV; i++)
        if (v[i] == maxim)
            cout << nume[i] << " ";
}

void grafComplet()
{
    int contor = 0;

    for (unsigned int i = 1; i < n; i++)
        for (unsigned int j = 1; j < n; j++)
            if (adj[i][j] == 1 && i < j)
                contor++;

    cout << "\n"
         << setw(5) << " " << (n * (n - 1)) / 2
         << " muchii - " << contor << " muchii ramase = "
         << (n * (n - 1)) / 2 - contor
         << " muchii pana la un graf complet";
}

int main()
{
    getData();

    int meniu;
    do
    {
        system("CLS");

        cout << "\n\n";
        cout << setw(25) << " "
             << "MENIU\n";

        underline(50);
        cout << setw(5) << " "
             << "1) Verifica daca X este prieten cu Y\n"
             << setw(5) << " "
             << "2) Determina gradele persoanei X\n"
             << setw(5) << " "
             << "3) Persoanele cu nr. maxim de prieteni\n"
             << setw(5) << " "
             << "4) Cate muchii pentru a deveni graf complet\n"
             << setw(5) << " "
             << "0) EXIT";
        cout << "\n";
        underline(50);

        cout << setw(5) << " "
             << "Introduceti optiunea: ";
        cin >> meniu;

        switch (meniu)
        {
        case 1:
            verifcarePrieten();
            break;
        case 2:
            cout << "\n";
            gradNod(1);
            getch();
            break;
        case 3:
            gradMax();
            getch();
            break;
        case 4:
            grafComplet();
            getch();
            break;
        }
    } while (meniu != 0);

    for (int i = 0; i < n; i++)
        delete[] nume[i];

    delete[] nume;

    for (int i = 1; i <= n; i++)
        delete[] adj[i];

    delete[] adj;

    return 0;
}
