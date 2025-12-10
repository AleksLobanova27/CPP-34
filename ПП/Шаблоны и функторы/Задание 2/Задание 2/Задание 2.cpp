#include <iostream>
#include <vector>
using namespace std;

//Шаблон
template<typename T>
class Table {
private:
    vector<vector<T>> data;
    size_t _rows;
    size_t _cols;

public:
    // Конструктор
    Table(size_t r, size_t c) : _rows(r), _cols(c) {
        data.resize(_rows);
        for (size_t i = 0; i < _rows; ++i) {
            data[i].resize(_cols);
        }
    }

    // Оператор [] для записи
    vector<T>& operator[](size_t index) {
        return data[index];
    }

    // Оператор [] для чтения
    const vector<T>& operator[](size_t index) const {
        return data[index];
    }

    // Функция Size
    void Size() const {
        cout << "Rows: " << _rows << ", Columns: " << _cols << endl;
    }
};

int main() {

    Table<int> test(2, 3);
    test[0][0] = 4;
    cout << test[0][0] << endl;
    test.Size();

    return 0;
}