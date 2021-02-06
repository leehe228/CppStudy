#include <iostream>
#include <random>
#include <cmath>
#include <conio.h>

#define SIZE 4

using namespace std;

void generate(int** mapPtr) {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> posDis(0, SIZE - 1);
	uniform_int_distribution<int> dieDis(1, 3);

	int i, j;
	do {
		i = posDis(gen); j = posDis(gen);
	} while (*(*(mapPtr + i) + j) != 0);

	*(*(mapPtr + i) + j) = (int)pow(2.0, (double)dieDis(gen));

	return;
}

void setToZero(int** mapPtr) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			*(*(mapPtr + i) + j) = 0;
		}
	}
}

void draw(int** mapPtr) {
	cout << endl;

	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			printf(" %4d", *(*(mapPtr + i) + j));
		}
		cout << endl << endl;
	}
}

int finishCheck(int** mapPtr) {
	for (int i = 0; i < SIZE; i++) {
		for (int j = 0; j < SIZE; j++) {
			if (*(*(mapPtr + i) + j) == 0) return 0;
			else if (*(*(mapPtr + i) + j) == 2048) return 1;
		}
	}

	return -1;
}

void move(int** mapPtr, int direction) {
	switch (direction) {
		// UP
		case 1: {
			break;
		}

		// DOWN
		case 2: {
			for (int i = SIZE - 2; i >= 0; i--) {
				for (int j = 0; j < SIZE; j++) {
					if (*(*(mapPtr + i) + j) != 0) {
						int t = i;
						while (true) {
							if (t == SIZE - 1) {
								*(*(mapPtr + t - 1) + j) = *(*(mapPtr + i) + j);
								*(*(mapPtr + i) + j) = 0;
								break;
							}
							else if (*(*(mapPtr + t) + j) != 0) {
								if (*(*(mapPtr + i) + j) == *(*(mapPtr + t) + j)){
									*(*(mapPtr + t) + j) = 2 * (*(*(mapPtr + i) + j));
									*(*(mapPtr + i) + j) = 0;
								}
								else {
									*(*(mapPtr + t - 1) + j) = *(*(mapPtr + i) + j);
									*(*(mapPtr + i) + j) = 0;
								}
								break;
							}
							t++;
						}
						
					}
				}
			}

			break;
		}

		// LEFT
		case 3: {
			break;
		}

		// RIGHT
		case 4: {
			break;
		}
	}
}

int main() {
	int** mapPtr = (int**)malloc(sizeof(int*) * SIZE);
	for (int i = 0; i < SIZE; i++) *(mapPtr + i) = (int*)malloc(sizeof(int) * SIZE);

	setToZero(mapPtr);

	for (int i = 0; i < 3; i++) generate(mapPtr);

	draw(mapPtr);

	while (true) {
		if (_getch() == 224) {
			switch (_getch()) {
				// UP
				case 72: {
					move(mapPtr, 1);
					break;
				}

				// DOWN
				case 80: {
					move(mapPtr, 2);
					break;
				}

				// LEFT
				case 75: {
					move(mapPtr, 3);
					break;
				}

				// RIGHT
				case 77: {
					move(mapPtr, 4);
					break;
				}

				default: {
					continue;
				}
			}
			
			if (finishCheck(mapPtr) == 1) {
				// system("cls");
				cout << "WIN!" << endl;
				break;
			}
			else if (finishCheck(mapPtr) == -1) {
				// system("cls");
				cout << "LOSE!" << endl;
				break;
			}

			system("cls");
			generate(mapPtr);
			draw(mapPtr);
		}
	}

	return 0;
}
