#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <fstream>
#include "Timer.h"

using namespace std;

vector<int> prefixFunction(const string& str)
{
    vector<int> result(str.size());

    for (int i = 1; i < str.size(); i++)
    {
        int j = result[i - 1];
        while (str[j] != str[i] && j > 0)
            j = result[j - 1];

        if (str[j] == str[i])
        {
            result[i] = j + 1;
            continue;
        }
        result[i] = j;
    }

    return result;
}

vector<int> KMP(string substr, string str)
{
    auto prefix = prefixFunction(substr + "#" + str);
    vector<int> result;

    for (int i = 0; i < prefix.size(); i++)
        if (prefix[i] == substr.size())
            result.push_back(i - substr.size() * 2);
    return result;
}

vector<int> naive(string substr, string str)
{
    vector<int> result;

    int size = substr.size();

    for (int i = 0; i < str.size() - size + 1; i++)
    {
        if (substr == str.substr(i, size))
            result.push_back(i);
    }

    return result;
}

string randomWord(vector<char> alphabet, int k)
{
    random_device rd;
    mt19937 mersenne(rd());
    uniform_int_distribution<int> dist(0, alphabet.size() - 1);
    string result;
    for (int i = 0; i < k; i++)
        result.push_back(alphabet[dist(mersenne)]);
    return result;
}

string strPow(string s, int k)
{
    string base = s;
    for (int i = 1; i < k; i++)
        s += base;
    return s;
}

string menu(int order)
{
    system("cls");
    vector<char> alphabet;
    int choose = -1;
    int k;
    char c;
    string result = "";
    while (choose < 1 || choose > 3)
    {
        cout << "\t\t\tПоиск фрагмента в тексте\n\n";
        cout << "Выберите способ задания " << order << " слова:\n";
        cout << "1. Непосредственный ввод слова.\n";
        cout << "2. Образование слова выбранной длины k.\n";
        cout << "3. Образование слова вида (B1B2...Bs)^k на основе слова B1B2...Bs и числа k.\n";
        cin >> choose;
        system("cls");
    }

    switch (choose)
    {
    case 1:
        cout << "1. Непосредственный ввод слова.\n";
        cout << "Введите слово: ";
        cin >> result;
        break;
    case 2:
        cout << "2. Образование слова выбранной длины k.\n";
        cout << "Введите k: ";
        cin >> k;
        cout << "Введите алфавит, ввод кончается вводом дефиса:\n";
        c = 'a';
        cin >> c;
        while (c != '-')
        {
            alphabet.push_back(c);
            cin >> c;
        }
        result = randomWord(alphabet, k);
        break;
    case 3:
        cout << "3. Образование слова вида (B1B2...Bs)^k на основе слова B1B2...Bs и числа k.\n";
        cout << "Введите слово B1B2...Bs: ";
        cin >> result;
        cout << "Введите число k: ";
        cin >> k;
        result = strPow(result, k);
        break;
    default:
        break;
    }

    cout << order << " слово: " << result;
    cin.ignore(2);
    return result;
}

void test1()
{
    ofstream out1;
    out1.open("d:\\naive1.dat");
    if (!out1.is_open())
        cerr << "Cant open output file in test1";
    ofstream out2;
    out2.open("d:\\KMP1.dat");
    if (!out2.is_open())
        cerr << "Cant open output file in test1";

    string x, y;
    Timer t1, t2;
    
    for (int k = 1; k <= 1001; k += 10)
    {
        cout << k << endl;
        y = strPow("ab", k);
        x = strPow("ab", 1000 * k);

        t1.start();
        naive(y, x);
        t1.stop();

        t2.start();
        KMP(y, x);
        t2.stop();

        out1 << k << '\t' << t1.toMilliS() << endl;
        out2 << k << '\t' << t2.toMilliS() << endl;
    }

    out1.close();
    out2.close();
}

void test2()
{
    ofstream out1;
    out1.open("d:\\naive2.dat");
    if (!out1.is_open())
        cerr << "Cant open output file in test2";
    ofstream out2;
    out2.open("d:\\KMP2.dat");
    if (!out2.is_open())
        cerr << "Cant open output file in test2";

    string x, y;
    Timer t1, t2;

    for (int m = 1; m <= pow(10, 6) + 1; m += pow(10, 4))
    {
        cout << m << endl;
        y = strPow("a", m);
        x = randomWord({ 'a', 'b' }, pow(10, 6) + 1);

        t1.start();
        naive(y, x);
        t1.stop();

        t2.start();
        KMP(y, x);
        t2.stop();

        out1 << m << '\t' << t1.toMilliS() << endl;
        out2 << m << '\t' << t2.toMilliS() << endl;
    }

    out1.close();
    out2.close();
}

void test3()
{
    ofstream out1;
    out1.open("d:\\naive3.dat");
    if (!out1.is_open())
        cerr << "Cant open output file in test3";
    ofstream out2;
    out2.open("d:\\KMP3.dat");
    if (!out2.is_open())
        cerr << "Cant open output file in test3";

    string x, y;
    Timer t1, t2;

    for (int h = 1; h <= pow(10, 6) + 1; h += pow(10,4))
    {
        cout << h << endl;
        y = "aaaaa";
        x = strPow("aaaaab", h);

        t1.start();
        naive(y, x);
        t1.stop();

        t2.start();
        KMP(y, x);
        t2.stop();

        out1 << h << '\t' << t1.toMilliS() << endl;
        out2 << h << '\t' << t2.toMilliS() << endl;
    }

    out1.close();
    out2.close();
}

int main()
{
    setlocale(LC_ALL, "RUS");
    /*string word = menu(1);
    string sub = menu(2);
    

    system("cls");
    cout << "1 слово: " << word << "\n2 слово: " << sub;*/

    //test1();
    test3();

    return 0;
}
