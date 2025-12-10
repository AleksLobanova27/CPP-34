#include "INI_Parser.h"
#include <fstream>
#include <algorithm>
#include <cstdlib>
using namespace std;

string ini_parser::trim(const string& str) {
    string result = str;
    result.erase(result.begin(),
        find_if(result.begin(), result.end(),
            [](unsigned char ch) { return !isspace(ch); }));
    result.erase(find_if(result.rbegin(), result.rend(),
        [](unsigned char ch) { return !isspace(ch); }).base(),
        result.end());
    return result;
}

ini_parser::ini_parser(const string& filename) {
    ifstream file(filename);
    if (!file.is_open())
        throw runtime_error("Не удаётся открыть файл: " + filename);

    string line;
    string current_section;

    while (getline(file, line)) {
        string trimmed = trim(line);
        if (trimmed.empty() || trimmed[0] == ';')
            continue;

        if (trimmed[0] == '[') {
            auto end = trimmed.find(']');
            if (end == string::npos)
                throw runtime_error("Некорректная строка секции: " + line);
            current_section = trim(trimmed.substr(1, end - 1));
            sections[current_section];  
            continue;
        }

        auto eq = trimmed.find('=');
        if (eq == string::npos)
            throw runtime_error("Некорректная строка параметра: " + line);

        string key = trim(trimmed.substr(0, eq));
        string value = trim(trimmed.substr(eq + 1));

        if (current_section.empty())
            throw runtime_error("Параметр вне секции: " + line);

        sections[current_section][key] = value;
    }

    if (sections.empty())
        throw runtime_error("Файл INI пуст или некорректен");
}

string ini_parser::get_value_string(const string& section,
    const string& key) {
    auto sec_it = sections.find(section);
    if (sec_it == sections.end())
        throw runtime_error("Секция '" + section + "' не найдена");

    auto key_it = sec_it->second.find(key);
    if (key_it == sec_it->second.end())
        throw runtime_error("Ключ '" + key + "' не найден в секции '" + section + "'");

    return key_it->second;
}


int value_converter<int>::convert(const std::string& value) {
    try {
        return std::stoi(value);
    }
    catch (...) {
        throw std::runtime_error("Невозможно преобразовать '" + value + "' в int");
    }
}

double value_converter<double>::convert(const std::string& value) {
    try {
        return std::stod(value);
    }
    catch (...) {
        throw std::runtime_error("Невозможно преобразовать '" + value + "' в double");
    }
}
