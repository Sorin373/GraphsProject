#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>

#include "functions.hpp"

using namespace std;

const int MAXN = 100;

int n, v[MAXN];
bool adj[MAXN][MAXN];
char nume[100][101];

void citireDate()
{
    ifstream fin("data.in");
    fin >> n;
    for (unsigned int i = 0; i < n; i++)
        fin >> nume[i];
    int x, y;
    while (fin >> x >> y)
        adj[x][y] = adj[y][x] = true;
    fin.close();
}

void afisareDate()
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
    clear_screen();

    char numeCautat_1[101], numeCautat_2[101];
    bool exista = false;

    cout << "\n\n";
    cout << setw(5) << " "
         << "APASA TASTA '0' PENTRU A ANULA";

    afisareDate();

    cout << "\n\n"
         << setw(5) << " "
         << "Introduceti numele:\n";
    cout << setw(5) << " "
         << "Nume_1: ";
    cin >> numeCautat_1;
    if (strcmp(numeCautat_1, "0") == 0)
        return;
    cout << setw(5) << " "
         << "Nume_2: ";
    cin >> numeCautat_2;
    if (strcmp(numeCautat_2, "0") == 0)
        return;
    else
    {
        cout << "\n";
        for (unsigned int i = 1; i <= n && !exista; i++)
            for (unsigned int j = 1; j <= n && !exista; j++)
                if (adj[i][j] == 1)
                {
                    if (strcasecmp(nume[i - 1], numeCautat_1) == 0 && strcasecmp(nume[j - 1], numeCautat_2) == 0)
                    {   
                        cout << setw(5) << " " << numeCautat_1 << " este prieten cu " << numeCautat_2;
                        exista = true;
                    }
                    else if (strcasecmp(nume[i - 1], numeCautat_2) == 0 && strcasecmp(nume[j - 1], numeCautat_1) == 0)
                    {
                        cout << setw(5) << " " << numeCautat_1 << " este prieten cu " << numeCautat_2;
                        exista = true;
                    }
                }
        if (!exista) cout << setw(5) << " " << "Nu exista aceasta prietenie!";

        getch();
        verifcarePrieten();
    }
}

void gradNod(int i)
{
    int contor = 0;
    if (i > n)
        return;
    else
    { 
        if (i != 0)
            cout << setw(5) << " " << nume[i - 1] << ": ";
        for (unsigned int j = 0; j < n; j++)
            if (adj[i][j] == 1)
            {
                if (j == n - 1) cout << nume[j - 1];
                else cout << nume[j - 1] << ", ";
                contor++;
            }
        if (i != 0)
            cout << "(" << contor << " prieteni)\n";

        gradNod(i + 1);
    }
}

int gradMaxRec(int i, int contorV)
{
    int contor = 0;
    if (i > n)
        return contorV;
    else
    {
        for (unsigned int j = 0; j < n; j++)
            if (adj[i][j] == 1)
                contor++;
        v[contorV] = contor;
        gradMaxRec(i + 1, contorV + 1);
    }
}

void gradMax()
{
    int maxim = -(n * (n - 1)) / 2, contorV = gradMaxRec(0, 0);
    for (unsigned int i = 0; i < contorV; i++)
        if (v[i] > maxim)
            maxim = v[i];
    cout << "\n" << setw(5) << " " << "Numarul maxim de prietenii este: " << maxim << "\n"
         << setw(5) << " " << "Persoanele cu numarul acesta de prieteni sunt: ";
    for (unsigned int i = 0; i < contorV; i++)
        if (v[i] == maxim)
            cout << nume[i - 1] << " ";
}

void grafComplet()
{
    int contor = 0;
    for (unsigned int i = 1; i < n; i++)
        for (unsigned int j = 1; j < n; j++)
            if (adj[i][j] == 1 && i < j)
                contor++;
    cout << "\n" << setw(5) << " " << (n * (n - 1)) / 2 
         << " muchii - " << contor << " muchii ramase = " 
         << (n * (n - 1)) / 2 - contor 
         << " muchii pana la un graf complet";
}

int main()
{
    citireDate();

    int meniu;
    do
    {
        clear_screen();

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
            gradNod(0);
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
    return 0;
}