#ifndef functions
#define functions

#include <iostream>
#include <iomanip>
#include <termios.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

char getch()
{
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if (tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    printf("%c\n", buf);
    return buf;
}

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

void clear_screen()
{
#ifdef WINDOWS
    std::clear_screen();
#else
    // POSIX
    std::system("clear");
#endif
}

#endif