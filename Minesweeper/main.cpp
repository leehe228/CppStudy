#include <iostream>
#include <random>
#include <algorithm>
#include <stdlib.h>

using namespace std;

#define MAP_SIZE 10
#define TARGET_NUM 10

void draw(int** mapPtr, int** maskPtr) {
	int rIndex = 1;
	
	cout << "  ";
	for (int i = 0; i < MAP_SIZE; i++) {
		printf("%3d", i + 1);
	}
	cout << endl;

	for (int i = 0; i < MAP_SIZE; i++) {
		printf("%3d", rIndex++);

		for (int j = 0; j < MAP_SIZE; j++) {
			if (*(*(maskPtr + i) + j) == 0) {
				cout << " / ";
			}
			else {
				switch (*(*(mapPtr + i) + j)) {

				case -1:
					cout << " * ";
					break;
				
				default:
					cout << " " << *(*(mapPtr + i) + j) << " ";
					break;
				
				}
			}
		}
		cout << endl;
	}
}

void drawAll(int** mapPtr) {
	int rIndex = 1;

	cout << "  ";
	for (int i = 0; i < MAP_SIZE; i++) {
		printf("%3d", i + 1);
	}
	cout << endl;

	for (int i = 0; i < MAP_SIZE; i++) {
		printf("%3d", rIndex++);

		for (int j = 0; j < MAP_SIZE; j++) {
			switch (*(*(mapPtr + i) + j)) {

			case -1:
				cout << " * ";
				break;

			default:
				cout << " " << *(*(mapPtr + i) + j) << " ";
				break;
			}
		}
		cout << endl;
	}
}

void erase(int x, int y, int** mapPtr, int** maskPtr) {
	*(*(maskPtr + x) + y) = 1;
	
	int tx = x, ty = y;

	while (true) {
		ty = y;
		if (tx == -1) break;

		if (*(*(mapPtr + tx) + ty) != 0) {
			*(*(maskPtr + tx) + ty) = 1;
			break;
		}

		*(*(maskPtr + tx) + ty) = 1;

		ty = y;
		while (true) {
			ty--;
			if (ty == -1) break;
			if (*(*(mapPtr + tx) + ty) != 0) {
				*(*(maskPtr + tx) + ty) = 1;
				break;
			}
			*(*(maskPtr + tx) + ty) = 1;
		}

		ty = y;
		while (true) {
			ty++;
			if (ty == MAP_SIZE) break;
			if (*(*(mapPtr + tx) + ty) != 0) {
				*(*(maskPtr + tx) + ty) = 1;
				break;
			}
			*(*(maskPtr + tx) + ty) = 1;
		}

		tx--;
	}

	tx = x;
	while (true) {
		tx++; ty = y;
		if (tx == MAP_SIZE) break;

		if (*(*(mapPtr + tx) + ty) != 0) {
			*(*(maskPtr + tx) + ty) = 1;
			break;
		}

		*(*(maskPtr + tx) + ty) = 1;

		ty = y;
		while (true) {
			ty--;
			if (ty == -1) break;
			if (*(*(mapPtr + tx) + ty) != 0) {
				*(*(maskPtr + tx) + ty) = 1;
				break;
			}
			*(*(maskPtr + tx) + ty) = 1;
		}

		ty = y;
		while (true) {
			ty++;
			if (ty == MAP_SIZE) break;
			if (*(*(mapPtr + tx) + ty) != 0) {
				*(*(maskPtr + tx) + ty) = 1;
				break;
			}
			*(*(maskPtr + tx) + ty) = 1;
		}
	}

	tx = x, ty = y;

	while (true) {
		tx = x;
		if (ty == -1) break;

		if (*(*(mapPtr + tx) + ty) != 0) {
			*(*(maskPtr + tx) + ty) = 1;
			break;
		}

		*(*(maskPtr + tx) + ty) = 1;

		tx = x;
		while (true) {
			tx--;
			if (tx == -1) break;
			if (*(*(mapPtr + tx) + ty) != 0) {
				*(*(maskPtr + tx) + ty) = 1;
				break;
			}
			*(*(maskPtr + tx) + ty) = 1;
		}

		tx = x;
		while (true) {
			tx++;
			if (tx == MAP_SIZE) break;
			if (*(*(mapPtr + tx) + ty) != 0) {
				*(*(maskPtr + tx) + ty) = 1;
				break;
			}
			*(*(maskPtr + tx) + ty) = 1;
		}

		ty--;
	}

	ty = y;
	while (true) {
		ty++; tx = x;
		if (ty == MAP_SIZE) break;

		if (*(*(mapPtr + tx) + ty) != 0) {
			*(*(maskPtr + tx) + ty) = 1;
			break;
		}

		*(*(maskPtr + tx) + ty) = 1;

		tx = x;
		while (true) {
			tx--;
			if (tx == -1) break;
			if (*(*(mapPtr + tx) + ty) != 0) {
				*(*(maskPtr + tx) + ty) = 1;
				break;
			}
			*(*(maskPtr + tx) + ty) = 1;
		}

		tx = x;
		while (true) {
			tx++;
			if (tx == MAP_SIZE) break;
			if (*(*(mapPtr + tx) + ty) != 0) {
				*(*(maskPtr + tx) + ty) = 1;
				break;
			}
			*(*(maskPtr + tx) + ty) = 1;
		}
	}

}

int main() {
	int** mapPtr = nullptr;
	int** maskPtr = nullptr;

	// random object
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<int> dis(0, MAP_SIZE - 1);

	// set two-dimensional array
	mapPtr = (int**)malloc(sizeof(int*) * MAP_SIZE);
	maskPtr = (int**)malloc(sizeof(int*) * MAP_SIZE);

	for (int i = 0; i < MAP_SIZE; i++) {
		*(mapPtr + i) = (int*)malloc(sizeof(int) * MAP_SIZE);
	}
	for (int i = 0; i < MAP_SIZE; i++) {
		*(maskPtr + i) = (int*)malloc(sizeof(int) * MAP_SIZE);
	}

	// set rooms to zero
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			*(*(mapPtr + i) + j) = 0;
		}
	}

	// set rooms to zero
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			*(*(maskPtr + i) + j) = 0;
		}
	}

	// generate mines
	int c = 0;
	do {
		int i = dis(gen);
		int j = dis(gen);
		if (*(*(mapPtr + i) + j) == 0) {
			*(*(mapPtr + i) + j) = -1;
			c++;
		}
	} while (c < TARGET_NUM);

	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			int count = 0;

			if (*(*(mapPtr + i) + j) != -1) {
				for (int k = max(0, i - 1); k < min(MAP_SIZE, i + 2); k++) {
					for (int l = max(0, j - 1); l < min(MAP_SIZE, j + 2); l++) {
						if (*(*(mapPtr + k) + l) == -1) count++;
					}
				}
				*(*(mapPtr + i) + j) = count;
			}
		}
	}

	draw(mapPtr, maskPtr);
	
	while (true) {
		int xIndex, yIndex;
		cout << "enter x y : ";
		scanf_s("%d %d", &xIndex, &yIndex);

		xIndex--; yIndex--;

		if (xIndex + 1 == 444) {
			break;
		}

		if (*(*(mapPtr + xIndex) + yIndex) == -1) {
			break;
		}

		if (*(*(maskPtr + xIndex) + yIndex) == 0) {
			erase(xIndex, yIndex, mapPtr, maskPtr);
		}

		system("cls");
		draw(mapPtr, maskPtr);
	}

	system("cls");
	drawAll(mapPtr);

	return 0;
}
