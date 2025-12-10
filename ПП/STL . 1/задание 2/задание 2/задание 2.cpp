#include <iostream>
#include <set>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");
    int n;
    cout << "Введите сначало количество цифрБ а затем сами цифры через пробел." << endl;
    cout << "[IN]: " ;
    cin >> n;

    set<int, greater<int>> numbers;

    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        numbers.insert(x);
    }
    
    cout << "[OUT]: " << endl;
    for (int num : numbers) {
        cout << num << "\n";
    }

    return 0;
}