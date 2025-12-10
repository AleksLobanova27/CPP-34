#include <iostream> 
#include <vector>
#include <algorithm>
#include <set>
using namespace std;

vector<int> remove_duplicates(const vector<int>& input) {
	vector<int> result = input;
	sort(result.begin(), result.end());
	auto it = unique(result.begin(), result.end());
	result.erase(it, result.end());
	return result;
}

void print(const vector<int> vec) {
	for (auto it = vec.begin(); it != vec.end(); it++) {
		cout << *it;
		if (next(it) != vec.end()) {
			cout << " ";
		}
	}
	cout << endl;
}

int main() {
	vector<int> input = { 1,1,2,5,6,1,2,4 };
	cout << "[IN]: ";
	print(input);

	vector<int> result = remove_duplicates(input);

	cout << "[OUT]: ";
	print(result);

	return 0;
}