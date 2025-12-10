#ifndef INI_PARSER_H
#define INI_PARSER_H

#include <string>
#include <unordered_map>
#include <stdexcept>

using namespace std;

class ini_parser;

template<typename T>
struct value_converter {
    static T convert(const string& value) {
        static_assert(sizeof(T) == -1, "Тип не поддерживается в ini_parser::get_value");
        return T{};
    }
};

template<>
struct value_converter<string> {
    static string convert(const string& value) {
        return value;
    }
};

template<>
struct value_converter<int> {
    static int convert(const string& value);
};

template<>
struct value_converter<double> {
    static double convert(const string& value);
};

class ini_parser {
private:
    unordered_map<string, unordered_map<string, string>> sections;

    string trim(const string& str);
    string get_value_string(const string& section, const string& key);

public:
    explicit ini_parser(const string& filename);
     
    template<typename T>
    T get_value(const string& section_dot_key) {
        auto pos = section_dot_key.find('.');
        if (pos == string::npos) {
            throw runtime_error("Неверный формат: ожидается section.key");
        }
        string section = section_dot_key.substr(0, pos);
        string key = section_dot_key.substr(pos + 1);
        string raw = get_value_string(section, key);
        return value_converter<T>::convert(raw);
    }
};

#endif
