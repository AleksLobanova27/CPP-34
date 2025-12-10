#include <iostream>
#include <vector>
#include <string>
#include <utility> 
using namespace std;

template<typename T>
void move_vectors(vector<T>& source, vector<T>& destination) {
    destination = move(source);

}

int main() {
    vector<string> one = { "test_string1", "test_string2" };
    vector<string> two;

    cout << "Before move:" << endl;
    cout << "one size: " << one.size() << endl;
    cout << "two size: " << two.size() << endl;

    move_vectors(one, two);

    cout << "\nAfter move:" << endl;
    cout << "one size: " << one.size() << endl;
    cout << "two size: " << two.size() << endl;
    cout << "two contents: ";
    for (const auto& str : two) {
        cout << str << " ";
    }
    cout << endl;

    return 0;
}