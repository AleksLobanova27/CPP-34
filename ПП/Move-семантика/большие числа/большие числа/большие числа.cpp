#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class big_integer {
    string digits;

    void remove_zeros() {
        digits.erase(0, digits.find_first_not_of('0'));
        if (digits.empty()) digits = "0";
    }

public:
    big_integer(const string& num = "0") : digits(num) { remove_zeros(); }

    big_integer(big_integer&& other) noexcept : digits(move(other.digits)) {
        other.digits = "0";
    }

    big_integer& operator=(big_integer&& other) noexcept {
        digits = move(other.digits);
        other.digits = "0";
        return *this;
    }

    big_integer operator+(const big_integer& other) const {
        string result;
        int carry = 0;

        auto it1 = digits.rbegin(), it2 = other.digits.rbegin();

        while (it1 != digits.rend() || it2 != other.digits.rend() || carry) {
            int sum = carry;
            if (it1 != digits.rend()) sum += *it1++ - '0';
            if (it2 != other.digits.rend()) sum += *it2++ - '0';

            carry = sum / 10;
            result += (sum % 10) + '0';
        }

        reverse(result.begin(), result.end());
        return big_integer(result);
    }

    big_integer operator*(int n) const {
        if (n == 0) return big_integer("0");

        big_integer result;
        for (int i = 0; i < n; ++i) {
            result = result + *this;
        }
        return result;
    }

    friend ostream& operator<<(ostream& os, const big_integer& num) {
        return os << num.digits;
    }

    big_integer(const big_integer&) = delete;
    big_integer& operator=(const big_integer&) = delete;
};

int main() {
    auto number1 = big_integer("114575");
    auto number2 = big_integer("78524");

    auto result = number1 + number2;
    cout << result << endl; 
    auto multiplied = number1 * 3;
    cout << multiplied << endl; 
    big_integer number3 = std::move(number1);
    cout << number3 << endl; 
    cout << number1 << endl; 

    return 0;
}