#include <iostream>
#include <vector>
#include <set>
#include <list>
#include <string>
using namespace std;

template<typename Container>void print(const Container& container) {
	auto it = container.begin();
	if(it != container.end()) {
		cout << *it;
		++it;
	}

	while (it != container.end()) {
		cout << ", " << *it;
		++it;
	}
		

}

int main() {
	set<string> test_set = { "one", "two", "three", "four" };
	cout << "set: ";
	print(test_set);
	cout << endl;

	list<string> test_list = { "one", "two", "three", "four" };
	cout << "list: ";
	print(test_list);
	cout << endl;

	vector<string> test_vector = { "one", "two", "three", "four" };
	cout << "vector: ";
	print(test_vector);

	return 0;
	
}