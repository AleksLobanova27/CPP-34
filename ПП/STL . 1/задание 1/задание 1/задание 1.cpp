#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	string text;
	cout << "Введите текст: ";
	getline(cin, text);

	map<char, int> freqMap;
	for (char c : text) {
		freqMap[c]++;
	}

	vector<pair<char,int>> freqVector(freqMap.begin(), freqMap.end());
	
	sort(freqVector.begin(), freqVector.end(), [](auto& a, auto& b) {
		return a.second > b.second;
		});
	cout << "[IN]: " << text << endl;
	cout << "[OUT]: " << endl;
	for (const auto& p : freqVector) {
		cout << p.first << ": " << p.second << "\n";
	}
	return 0;
}