#include <iostream>
#include <string>
#include "Leaver.h"

int main()
{
    setlocale(LC_ALL, "Russian");
    std::cout << "Введите имя: ";
    std::string name;
    std::cin >> name;
    NameGoodbye::Leaver men;
    std::cout << men.leave(name);
}

