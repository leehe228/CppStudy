#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define TRUE 1

int main(int argc, char* argv[]) {
	int** arrayHead = NULL;
	int maxV = 0, N, M;

	puts("N M : ");
	scanf_s("%d %d", &N, &M);

	arrayHead = (int**)malloc(sizeof(int*) * N);

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			*(arrayHead + i) = (int*)malloc(sizeof(int) * M);

	for (int i = 0; i < N; i++) {
		int temp, j;
		scanf_s("%d", &temp);

		for (j = 0; j < temp; j++)
			*(*(arrayHead + i) + j) = 1;

		for (; j < M; j++)
			*(*(arrayHead + i) + j) = 0;
	}

	puts("\nbefore : ");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++)
			printf("%d ", arrayHead[i][j]);

		puts("");
	}

	for (int i = N - 2; i >= 0; i--) {
		for (int j = 0; j < M; j++) {
			if (!*(*(arrayHead + i) + j)) break;

			int c = 0;

			while (TRUE) {
				if (i + 1 + c == N) break;
				if (*(*(arrayHead + i + 1 + c) + j)) break;
				c++;
			}

			*(*(arrayHead + i) + j) = 0;
			*(*(arrayHead + i + c) + j) = 1;

			if (c > maxV) maxV = c;
		}
	}

	puts("\nafter : ");
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++)
			printf("%d ", arrayHead[i][j]);

		puts("");
	}

	printf("%d", maxV);

	return 0;
}