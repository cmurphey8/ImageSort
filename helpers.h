#include "bmp.h"

// test rgb <<>> hsb transformations
void transform(int height, int width, RGBTRIPLE image[height][width]);

// selection sort by hue
void selectionSort(int height, int width, RGBTRIPLE image[height][width]);

// try combinations of sorting methods
void combinationSort(int height, int width, RGBTRIPLE image[height][width]);
