#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

extern void imgCvtGrayDoubleToInt(double* src, uint8_t* dst, int count);

#define REPEATS 30

void benchmark(int height, int width) {
    int size = height * width;
    double* src = (double*)malloc(sizeof(double) * size);
    uint8_t* dst = (uint8_t*)malloc(sizeof(uint8_t) * size);

    // Fill src with random floats [0.0, 1.0]
    for (int i = 0; i < size; ++i)
        src[i] = (double)rand() / RAND_MAX;

    LARGE_INTEGER freq, start, end;
    double totalTime = 0.0;
    double runTimes[REPEATS];

    QueryPerformanceFrequency(&freq);

    for (int i = 0; i < REPEATS; ++i) {
        QueryPerformanceCounter(&start);
        imgCvtGrayDoubleToInt(src, dst, size);
        QueryPerformanceCounter(&end);

        runTimes[i] = (double)(end.QuadPart - start.QuadPart) / freq.QuadPart * 1000000.0; // microseconds
        totalTime += runTimes[i];
    }

    printf("\n--- Benchmark for %dx%d image ---\n", height, width);
    for (int i = 0; i < REPEATS; ++i) {
        printf("Run %2d: %.2f microseconds\n", i + 1, runTimes[i]);
    }
    printf("Average: %.2f microseconds\n\n", totalTime / REPEATS);

    free(src);
    free(dst);
}

int main() {
    srand((unsigned int)time(NULL));

    benchmark(10, 10);
    benchmark(100, 100);
    benchmark(1000, 1000);

    return 0;
}
