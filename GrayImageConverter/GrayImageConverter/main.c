#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

extern void imgCvtGrayDoubleToInt(double* src, uint8_t* dst, int count);

#define MAX_HW 1024

int main() {
    char name1[100];
    int height, width;

    printf("Enter your first name: ");
    fgets(name1, sizeof(name1), stdin);

    printf("Enter image height: ");
    scanf("%d", &height);
    printf("Enter image width: ");
    scanf("%d", &width);

    if (height <= 0 || width <= 0 || height * width > MAX_HW * MAX_HW) {
        printf("Invalid image size.\n");
        return 1;
    }

    double* src = (double*)malloc(sizeof(double) * height * width);
    uint8_t* dst = (uint8_t*)malloc(sizeof(uint8_t) * height * width);

    printf("Enter %d pixel values (floats 0.0 - 1.0):\n", height * width);
    for (int i = 0; i < height * width; ++i) {
        scanf("%lf", &src[i]);
    }

    imgCvtGrayDoubleToInt(src, dst, height * width);

    printf("\nHello, %s:\n", name1);

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            printf("%3d ", dst[i * width + j]);
        }
        printf("\n");
    }

    free(src);
    free(dst);

    return 0;
}
