#pragma once
#include <utility>
#include <initializer_list>
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <typeinfo>

template <typename T>
class ExtArray
{
private:
    std::vector<T> extended_array;
    size_t _size;

    void checkRange(size_t start, size_t end) const {
        if (start >= end) {
            throw std::invalid_argument("Invalid range: start must be less than end");
        }
        if (end > _size) {
            throw std::out_of_range("Range end exceeds array size");
        }
    }

public:
    ExtArray(std::initializer_list<T> l) : extended_array(l), _size(l.size()) {}

    ExtArray(int size) : _size(size) {
        extended_array.resize(_size);
    }

    T& operator[](size_t index) {
        return extended_array[index];
    }

    size_t size() const {
        return _size;
    }

    double mean() const {
        if (_size == 0) return 0.0;

        double sum = 0;
        for (size_t i = 0; i < _size; i++) {
            sum += extended_array[i];
        }
        return sum / _size;
    }

    double mean(size_t start, size_t end) const {
        checkRange(start, end);

        double sum = 0;
        for (size_t i = start; i < end; i++) {
            sum += extended_array[i];
        }
        return sum / (end - start);
    }

    double median() const {
        if (_size == 0) return 0.0;

        std::vector<T> temp_array;
        std::copy(extended_array.begin(), extended_array.end(), back_inserter(temp_array));
        std::sort(temp_array.begin(), temp_array.end());

        if (_size % 2 == 1) {
            return temp_array[_size / 2];
        }
        else {
            return static_cast<double>(temp_array[(_size / 2) - 1] + temp_array[_size / 2]) / 2;
        }
    }

    std::pair<T, int> mode() const {
        if (_size == 0) return std::make_pair(T(), 0);

        T max = extended_array[0];
        int cmax = 0, rmax = 0;
        for (int i = 0; i < _size; i++) {
            if (cmax > rmax) {
                rmax = cmax;
                max = extended_array[i - 1];
            }
            cmax = 0;
            for (int j = i; j < _size; j++) {
                if (extended_array[j] == extended_array[i]) {
                    cmax++;
                }
            }
        }
        return std::pair<T, int>(max, rmax);
    }

    int checkSum() const {
        if (typeid(T) != typeid(bool) && typeid(T) != typeid(int)) {
            throw std::bad_typeid();
        }

        int sum = 0;

        for (const auto& elem : extended_array) {
            if (typeid(T) == typeid(int)) {
                if (elem != 0 && elem != 1) {
                    throw std::logic_error("Array contains values other than 0 and 1");
                }
            }
            sum += static_cast<int>(elem);
        }

        return sum;
    }
};