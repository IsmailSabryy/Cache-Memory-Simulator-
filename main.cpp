#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>
using namespace std;
vector<pair<bool, string>> cache;
int memoryclock = 100;
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
    cout << "Cache memory after excecuting adress: " << address << endl;
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
    cout << "AMAT: " << double(cycles) + double(memoryclock * missrate) << endl;
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
    cache.resize(C);
    for (int i = 0; i < C; i++)
    {
        cache[i].first = false;
        for (int j = 0; j < tag; j++)
        {
            cache[i].second += '0';
        }
    }
    numofaccess = 0;
    hits = 0;
    misses = 0;
    ifstream filereader(filename);
    string fileline, address;
    while (getline(filereader, fileline))
    {
        address = fileline;
        cachesimulatorline(address, Cycles, index, disp, tag, numofaccess, hits, misses);
    }
}