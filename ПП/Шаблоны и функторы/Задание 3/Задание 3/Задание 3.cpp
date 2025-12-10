#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Functor {
private:
    int _sum;
    int _count;

public:

    Functor() : _sum(0), _count(0) {}

    void operator()(int num) {
        if (num % 3 == 0) {
            _sum += num;
            _count++;
        }
    }

    int get_sum() const {
        return _sum;
    }

    int get_count() const {
        return _count;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    cout << "Введите количество чисел: ";
    int n;
    cin >> n;
    vector<int> num(n);

    cout << "Введите " << n << " чисел через пробел ";
    for (int i = 0; i < n; i++) {
        cin >> num[i];
    }

    Functor counter;
    counter = for_each(num.begin(), num.end(), counter);

    // Вывод
    cout << "[IN]: ";
    for (int i = 0; i < n; i++) {
        cout << num[i] << " ";
    }
    cout << endl;
    cout << "[OUT]: get_sum() = " << counter.get_sum() << endl;
    cout << "[OUT]: get_count() = " << counter.get_count() << endl;

    return 0;
}