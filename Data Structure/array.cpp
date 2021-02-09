#include <iostream>

#define SIZE 10

using namespace std;

int main(int argc, char* argv[]) {

	int* arr = (int*)malloc(sizeof(int) * SIZE);
	int c = 0;

	for (int i = 0; i < SIZE; i++) {
		*(arr + i) = ++c;
	}

	for (int i = 0; i < SIZE; i++) {
		cout << *(arr + i) << " ";
	}

	cout << endl;

	return 0;
}