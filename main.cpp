/*
 * This program performs operations on a social network represented as a graph.
 * The graph is read from a file named "data.in", and various operations can be
 * performed through a menu-driven interface.
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <conio.h>

using namespace std;

#define DATA "edges.txt"
#define MAXN 100
#define MAXL 101

int n, v[MAXN];
bool **adj;
char **name;

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
    ifstream file(DATA);

    if (!file.is_open())
    {
        cerr << "Failed to open file!\n";
        return;
    }

    file >> n;

    name = new char *[n];
    for (int i = 0; i < n; i++)
        name[i] = new char[MAXL];

    for (int i = 0; i < n; i++)
        file >> name[i];

    adj = new bool *[n + 1];
    for (int i = 1; i <= n; i++)
        adj[i] = new bool[n + 1];

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            adj[i][j] = false;

    int x, y;
    while (file >> x >> y)
    {
        if (x > n || y > n)
        {
            cerr << "Invalid input!\n";
            return;
        }
        adj[x][y] = adj[y][x] = true;
    }

    file.close();
}

void printData()
{
    cout << "\n\n"
         << setw(5) << " "
         << "People recorded in the database:"
         << "\n"
         << setw(5) << " ";

    for (unsigned int i = 0; i < n; i++)
        if (i == n - 1)
            cout << name[i];
        else
            cout << name[i] << ", ";
}

void checkFriendship()
{
    system("CLS");

    char *name_1 = new char[MAXL], *name_2 = new char[MAXL];
    bool isFound = false;

    cout << "\n\n";
    cout << setw(5) << " "
         << "PRESS KEY '0' TO CANCEL";

    printData();

    cout << "\n\n"
         << setw(5) << " "
         << "Introduceti numele:\n";
    cout << setw(5) << " "
         << "Nume_1: ";
    cin >> name_1;

    if (stricmp(name_1, "0") == 0)
    {
        delete[] name_1;
        delete[] name_2;
        return;
    }

    cout << setw(5) << " "
         << "Nume_2: ";
    cin >> name_2;

    if (stricmp(name_2, "0") == 0)
    {
        delete[] name_1;
        delete[] name_2;
        return;
    }
    else
    {
        cout << "\n";
        for (int i = 1; i <= n && !isFound; i++)
            for (int j = 1; j <= n && !isFound; j++)
                if (adj[i][j])
                {
                    if (stricmp(name[i - 1], name_1) == 0 && stricmp(name[j - 1], name_2) == 0)
                    {
                        cout << setw(5) << " " << name_1 << " is friends with " << name_2;
                        isFound = true;
                    }
                    else if (stricmp(name[i - 1], name_2) == 0 && stricmp(name[j - 1], name_1) == 0)
                    {
                        cout << setw(5) << " " << name_1 << " is friends with " << name_2;
                        isFound = true;
                    }
                }
        if (!isFound)
            cout << setw(5) << " "
                 << "Not found!\n";

        delete[] name_1;
        delete[] name_2;

        getch();
        checkFriendship();
    }
}

void nodeDegree(int i)
{
    int cnt = 0;
    if (i >= n)
        return;
    else
    {
        cout << setw(5) << " " << name[i - 1] << ": ";
        for (int j = 1; j <= n; j++)
            if (adj[i][j])
            {
                if (cnt > 0)
                    cout << ", ";
                cout << name[j - 1];
                cnt++;
            }
        cout << " (" << cnt << " friends)\n";

        nodeDegree(i + 1);
    }
}

int maxDegreeRec(int i, int cntV)
{
    int cnt = 0;
    if (i >= n)
        return cntV;
    else
    {
        for (int j = 1; j <= n; j++)
            if (adj[i][j])
                cnt++;
        v[cntV] = cnt;
        maxDegreeRec(i + 1, cntV + 1);
    }
}

void maxDegree()
{
    int max = -(n * (n - 1)) / 2, cntV = maxDegreeRec(1, 0);

    for (unsigned int i = 0; i < cntV; i++)
        if (v[i] > max)
            max = v[i];

    cout << "\n"
         << setw(5) << " "
         << "The maximum number of friends is: " << max << "\n"
         << setw(5) << " "
         << "People with this number of friends are: ";

    for (unsigned int i = 0; i < cntV; i++)
        if (v[i] == max)
            cout << name[i] << " ";
}

void completeGraph()
{
    int cnt = 0;

    for (unsigned int i = 1; i < n; i++)
        for (unsigned int j = 1; j < n; j++)
            if (adj[i][j] == 1 && i < j)
                cnt++;

    cout << "\n"
         << setw(5) << " " << (n * (n - 1)) / 2
         << " edges - " << cnt << " edges remaining = "
         << (n * (n - 1)) / 2 - cnt
         << " edges until a complete graph";
}

int main()
{
    getData();

    int MENU;

    do
    {
        system("CLS");

        cout << "\n\n";
        cout << setw(25) << " "
             << "MENIU\n";

        underline(50);
        cout << setw(5) << " "
             << "1) Check if X is friends with Y\n"
             << setw(5) << " "
             << "2) Determine the degrees of person X\n"
             << setw(5) << " "
             << "3) People with the maximum number of friends\n"
             << setw(5) << " "
             << "4) How many edges to become a complete graph\n"
             << setw(5) << " "
             << "0) EXIT";

        cout << "\n";
        underline(50);

        cout << setw(5) << " "
             << "Enter: ";
        cin >> MENU;

        switch (MENU)
        {
        case 1:
            checkFriendship();
            break;
        case 2:
            cout << "\n";
            nodeDegree(1);
            getch();
            break;
        case 3:
            maxDegree();
            getch();
            break;
        case 4:
            completeGraph();
            getch();
            break;
        }
    } while (MENU != 0);

    for (int i = 0; i < n; i++)
        delete[] name[i];

    delete[] name;

    for (int i = 1; i <= n; i++)
        delete[] adj[i];

    delete[] adj;

    return 0;
}
