#include <iostream>
#include <stdexcept>
#include <cstring>
using namespace std;

class smart_array {
private:
    int* _data;
    size_t _capacity;
    size_t _size;

public:
    // Конструктор, принимающий количество элементов
    explicit smart_array(size_t initial_capacity)
        : _capacity(initial_capacity), _size(0) {
        if (initial_capacity == 0) {
            throw invalid_argument("Capacity must be greater than 0");
        }
        _data = new int[_capacity];
    }

    // Функция добавления нового элемента
    void add_element(int element) {
        if (_size >= _capacity) {
            // Увеличиваем емкость в 2 раза (стандартный подход)
            size_t new_capacity = _capacity * 2;
            int* new_data = new int[new_capacity];

            // Копируем существующие данные
            for (size_t i = 0; i < _size; ++i) {
                new_data[i] = _data[i];
            }

            // Освобождаем старую память
            delete[] _data;

            // Обновляем указатель и емкость
            _data = new_data;
            _capacity = new_capacity;
        }

        _data[_size] = element;
        ++_size;
    }

    // Функция получения элемента по индексу
    int get_element(size_t index) const {
        if (index >= _size) {
            throw out_of_range("Index out of range");
        }
        return _data[index];
    }

    // Деструктор
    ~smart_array() {
        delete[] _data;
    }

    // Запрещаем копирование и присваивание для предотвращения проблем с памятью
    smart_array(const smart_array&) = delete;
    smart_array& operator=(const smart_array&) = delete;

    // Можно добавить move-семантику для улучшения производительности
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
        smart_array arr(5);
        arr.add_element(1);
        arr.add_element(4);
        arr.add_element(155);
        arr.add_element(14);
        arr.add_element(15);
        cout << arr.get_element(1) << endl;

        // Тестирование добавления сверх начальной емкости
        arr.add_element(100);
        arr.add_element(200);
        cout << arr.get_element(5) << endl; // 100
        cout << arr.get_element(6) << endl; // 200

    }
    catch (const exception& ex) {
        cout << ex.what() << endl;
    }

    return 0;
}