#include "INI_Parser.h"
#include <iostream>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    try {
        ini_parser parser("config.ini");

        int i = parser.get_value<int>("Section1.var1");
        double d = parser.get_value<double>("Section1.var2");
        string s = parser.get_value<string>("Section2.var2");

        cout << "int: " << i << '\n';
        cout << "double: " << d << '\n';
        cout << "string: " << s << '\n';

    }
    catch (const exception& e) {
        cerr << "Ошибка: " << e.what() << '\n';
    }
}
