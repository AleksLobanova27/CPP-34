#include <iostream>
#include <stdexcept>
#include <algorithm>
using namespace std;

class smart_array {
private:
    int* _data;
    size_t _capacity;
    size_t _size;

public:
    
    explicit smart_array(size_t initial_capacity)
        : _capacity(initial_capacity), _size(0) {
        if (initial_capacity == 0) {
            throw std::invalid_argument("Capacity must be greater than 0");
        }
        _data = new int[_capacity];
    }

    smart_array(const smart_array& other)
        : _capacity(other._capacity), _size(other._size) {
        _data = new int[_capacity];
        for (size_t i = 0; i < _size; ++i) {
            _data[i] = other._data[i];
        }
    }

    smart_array& operator=(const smart_array& other) {
        if (this != &other) {
            delete[] _data;
            _capacity = other._capacity;
            _size = other._size;
            
            _data = new int[_capacity];

            for (size_t i = 0; i < _size; ++i) {
                _data[i] = other._data[i];
            }
        }
        return *this;
    }

    void add_element(int element) {
        if (_size >= _capacity) {
            size_t new_capacity = _capacity * 2;
            int* new_data = new int[new_capacity];

            for (size_t i = 0; i < _size; ++i) {
                new_data[i] = _data[i];
            }

            delete[] _data;
            _data = new_data;
            _capacity = new_capacity;
        }

        _data[_size] = element;
        ++_size;
    }

    
    int get_element(size_t index) const {
        if (index >= _size) {
            throw std::out_of_range("Index out of range");
        }
        return _data[index];
    }

    ~smart_array() {
        delete[] _data;
    }

    void print() const {
        cout << "Array (size: " << _size << ", capacity: " << _capacity << "): ";
        for (size_t i = 0; i < _size; ++i) {
            cout << _data[i] << " ";
        }
        cout << endl;
    }

    smart_array(smart_array&& other) noexcept
        : _data(other._data), _capacity(other._capacity), _size(other._size) {
        other._data = nullptr;
        other._capacity = 0;
        other._size = 0;
    }

    smart_array& operator=(smart_array&& other) noexcept {
        if (this != &other) {
            delete[] _data;
            _data = other._data;
            _capacity = other._capacity;
            _size = other._size;
            other._data = nullptr;
            other._capacity = 0;
            other._size = 0;
        }
        return *this;
    }
};

int main() {
    try {
        cout << "Creating first array..." << endl;
        smart_array arr(5);
        arr.add_element(1);
        arr.add_element(4);
        arr.add_element(155);
        arr.print();

        cout << "\nCreating second array..." << endl;
        smart_array new_array(2);
        new_array.add_element(44);
        new_array.add_element(34);
        new_array.print();

        cout << "\nAssigning second array to first..." << endl;
        arr = new_array; // Теперь это работает правильно!
        arr.print();

        cout << "\nModifying original array to verify deep copy..." << endl;
        new_array.add_element(999);
        new_array.print();
        arr.print(); // arr не изменился - это разные объекты

        cout << "\nTesting copy constructor..." << endl;
        smart_array copied_array = arr;
        copied_array.add_element(777);
        copied_array.print();
        arr.print(); // Исходный массив не изменился

    }
    catch (const std::exception& ex) {
        cout << "Exception: " << ex.what() << endl;
    }

    return 0;
}