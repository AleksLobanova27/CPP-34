#include <iostream>
#include <vector>
using namespace std;

//Для простых чисел
template<typename T>
T square(const T& value) {
	return value * value;
}

//Для векторов
template<typename T>
vector<T> square(const vector<T>& vec) {
	vector<T> result;
	
	for (size_t i = 0; i < vec.size(); ++i) {
		T num = vec[i];
		result.push_back(num * num);
	}
	return result;
}

// Общая функция вывода 
template<typename T>
void print(const T& value) {
	cout << "[IN]: " << value << endl;
	cout << "[OUT]: " << square(value) << endl;
}

// Специализация для векторов
template<typename T>
void print(const vector<T>& vecIN, const vector<T>& vecOUT) {
	cout << "[IN]: ";
	for (size_t i = 0; i < vecIN.size(); ++i) {
		cout << vecIN[i] << ", " ;
	}
	cout << endl;
	cout << "[OUt]: ";
	for (size_t i = 0; i < vecOUT.size(); ++i) {
		cout << vecOUT[i] << ", ";
	}
}

int main() {
	int num1 = 4;
	double num2 = 2.5;
	print(num1);
	print(num2);
	vector<int> vec = { -1, 4, 8 };
	print(vec,square(vec));
	return 0;
}