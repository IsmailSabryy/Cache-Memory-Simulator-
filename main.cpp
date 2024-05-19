#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
#include <windows.h>
#include <conio.h>
using namespace std;
vector<pair<bool, string>> cache;
vector<pair<bool, string>> iCache;
int memoryclock = 100;
char menu[4][45]={
        {" 1]      Test   "},
        {" 2]      Test  "},
        {" 3]      Test          "},
        {" 4]               Exit      "}
};
void ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_CURSOR_INFO     cursorInfo;

    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag; // set the cursor visibility
    SetConsoleCursorInfo(out, &cursorInfo);
}
// function to locate cursor at row and col in screen
void goto_row_col(int row,int col)
{
    COORD c;
    c.X = col;
    c.Y = row;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void setColor(int color)
{
    HANDLE hConsole;

    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void showMenu()
{
    char ch;
    int pos=1;

    do
    {
        ShowConsoleCursor(false);
        setColor(15);
        goto_row_col(10,39);cout << menu[0];
        goto_row_col(11,39);cout << menu[1];
        goto_row_col(12,39);cout << menu[2];
        goto_row_col(13,39);cout << menu[3];
        setColor(240);
        goto_row_col(10+pos-1,39);cout << menu[pos-1];
        ch = getch();
        switch (ch)
        {
            case 13:
                switch(pos)
                {
                    case 1:
                        setColor(15);
                        ShowConsoleCursor(true);
                        system("cls");

                        break;
                    case 2:
                        setColor(15);
                        ShowConsoleCursor(true);
                        system("cls");

                        break;
                    case 3:
                        setColor(15);
                        ShowConsoleCursor(true);

                    case 4:
                        setColor(15);
                        ShowConsoleCursor(true);
                        exit(0);
                        break;
                }
                break;
            case -32:
                ch = getch();
                switch (ch)
                {
                    case 72:
                        pos--;
                        if (pos ==0) pos =4;
                        break;
                    case 80:
                        pos++;
                        if (pos ==5) pos =1;
                        break;
                }
        }
    } while(true);
}
string strbin_to_dec(string binary)
{
    int base = 1;
    int deci = 0;
    for (int i = binary.length() - 1; i >= 0; --i)
    {
        if (binary[i] == '1')
        {
            deci += base;
        }
        base *= 2;
    }

    return to_string(deci);
}
string hexatobinary(string hexadecimal)
{
    string binary;
    int i = 0;
    while (hexadecimal[i])
    {
        switch (hexadecimal[i])
        {
        case '0':
            binary += "0000";
            break;
        case '1':
            binary += "0001";
            break;
        case '2':
            binary += "0010";
            break;
        case '3':
            binary += "0011";
            break;
        case '4':
            binary += "0100";
            break;
        case '5':
            binary += "0101";
            break;
        case '6':
            binary += "0110";
            break;
        case '7':
            binary += "0111";
            break;
        case '8':
            binary += "1000";
            break;
        case '9':
            binary += "1001";
            break;
        case 'A':
        case 'a':
            binary += "1010";
            break;
        case 'B':
        case 'b':
            binary += "1011";
            break;
        case 'C':
        case 'c':
            binary += "1100";
            break;
        case 'D':
        case 'd':
            binary += "1101";
            break;
        case 'E':
        case 'e':
            binary += "1110";
            break;
        case 'F':
        case 'f':
            binary += "1111";
            break;
        case '.':
            binary += ".";
            break;
        default:
            std::cout << "Invalid hexadecimal digit: " << hexadecimal[i] << std::endl;
        }
        i++;
    }
    while (binary.size() < 32)
    {
        binary = "0" + binary;
    }
    return binary;
}

void cachesimulatorline(string address, int cycles, int index, int disp, int tag, int &numofaccess, int &hits, int &misses)
{
    string binaryline = hexatobinary(address);
    string tagbinary = binaryline.substr(0, tag);
    string indexbinary = binaryline.substr(tag, index);
    string dispbinary = binaryline.substr(tag + index, disp);
    if (!cache[stoi(strbin_to_dec(indexbinary))].first || cache[stoi(strbin_to_dec(indexbinary))].second != tagbinary)
    {
        misses++;
        cache[stoi(strbin_to_dec(indexbinary))].first = true;
        cache[stoi(strbin_to_dec(indexbinary))].second = tagbinary;
    }
    else
    {
        hits++;
    }
    cout << "============================================" << endl;
    cout << "Cache memory after excecuting Data adress: " << address << endl;
    for (auto &entry : cache)
    {
        cout << entry.first << "," << entry.second << endl;
    }
    numofaccess++;
    cout << "Total number of accesses:" << numofaccess << endl;
    cout << "Hits: " << hits << endl;
    cout << "Misses: " << misses << endl;
    cout << "Hit ratio: " << static_cast<double>(hits) / numofaccess << endl;
    double missrate = static_cast<double>(misses) / numofaccess;
    cout << "Miss ratio: " << missrate << endl;
    cout << "AMAT: " << double(cycles) + double(memoryclock * missrate) << "ns" << endl;
}
void Icachesimulatorline(string address, int cycles, int index, int disp, int tag, int &numofaccess, int &hits, int &misses)
{
    string binaryline = hexatobinary(address);
    string tagbinary = binaryline.substr(0, tag);
    string indexbinary = binaryline.substr(tag, index);
    string dispbinary = binaryline.substr(tag + index, disp);
    if (!iCache[stoi(strbin_to_dec(indexbinary))].first || iCache[stoi(strbin_to_dec(indexbinary))].second != tagbinary)
    {
        misses++;
        iCache[stoi(strbin_to_dec(indexbinary))].first = true;
        iCache[stoi(strbin_to_dec(indexbinary))].second = tagbinary;
    }
    else
    {
        hits++;
    }
    cout << "============================================" << endl;
    cout << "Cache memory after excecuting Instruction adress: " << address << endl;
    for (auto &entry : iCache)
    {
        cout << entry.first << "," << entry.second << endl;
    }
    numofaccess++;
    cout << "Total number of accesses:" << numofaccess << endl;
    cout << "Hits: " << hits << endl;
    cout << "Misses: " << misses << endl;
    cout << "Hit ratio: " << static_cast<double>(hits) / numofaccess << endl;
    double missrate = static_cast<double>(misses) / numofaccess;
    cout << "Miss ratio: " << missrate << endl;
    cout << "AMAT: " << double(cycles) + double(memoryclock * missrate) << "ns" << endl;
}
int main()
{
    string filename;

    int S, L, Cycles, C, index, disp, tag, numofaccess, hits, misses;
    cout << "Enter the total cache size" << endl;
    cin >> S;
    cout << "Enter the cache line size" << endl;
    cin >> L;
    cout << "Enter the number of cycles needed to access the cache " << endl;
    cin >> Cycles;
    cout << "Enter filepath: " << endl;
    cin >> filename;
    C = S / L;
    index = log2(C);
    disp = log2(L);
    tag = 32 - index - disp;
    cache.resize(C); // ?
    iCache.resize(C);
    for (int i = 0; i < C; i++)
    {
        cache[i].first = false;
        for (int j = 0; j < tag; j++)
        {
            cache[i].second += '0';
        }
    }
    for (int i = 0; i < C; i++)
    {
        iCache[i].first = false;
        for (int j = 0; j < tag; j++)
        {
            iCache[i].second += '0';
        }
    }
    numofaccess = 0;
    hits = 0;
    misses = 0;
    ifstream filereader(filename);
    string fileline, address;
    while (getline(filereader, fileline))
    {
        if (fileline[0] == 'd' || fileline[0] == 'D')
        {
            address = fileline.substr(1);
            cachesimulatorline(address, Cycles, index, disp, tag, numofaccess, hits, misses);
        }
        else if (fileline[0] == 'i' || fileline[0] == 'I')
        {
            address = fileline.substr(1);
            Icachesimulatorline(address, Cycles, index, disp, tag, numofaccess, hits, misses);
        }
        // else
        // {
        //     address = fileline;
        //     cachesimulatorline(address, Cycles, index, disp, tag, numofaccess, hits, misses);
        // }
    }
}