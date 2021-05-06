#include "helpers.h"
#import <stdio.h>
#include <stdlib.h>
#include <math.h>

// template functions
int findMinIndex(int height, int width, HSVTRIPLE image[height][width], int index[height]);
int findMin(int start, int width, HSVTRIPLE image[width]);

HSVTRIPLE rgbHSV(RGBTRIPLE px);
int max(int x, int y);
int min(int x, int y);
double getHue(RGBTRIPLE px, double cMax, double cMin);
double getSat(RGBTRIPLE px, double cMax, double cMin);

RGBTRIPLE hsvRGB(HSVTRIPLE px);

// TODO: selection sort
void selectionSort(int height, int width, RGBTRIPLE image[height][width]) {

    // convert image from rgb to hsv
    HSVTRIPLE newIm[height][width];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            newIm[i][j] = rgbHSV(image[i][j]);
        }
    }

    // selection sort by hue
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            int index = findMin(j, width, newIm[i]);
            if (index > j) {
                // TODO: swap our current HSVTRIPLE element (column j) with the element in column index
                HSVTRIPLE tmp = newIm[i][j];
                newIm[i][j] = newIm[i][index];
                newIm[i][index] = tmp;
            }
        }
    }

    // convert image from hsv to rgb
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            image[i][j] = hsvRGB(newIm[i][j]);
        }
    }
    return;
}

// TODO: selection sort helper function
int findMin(int start, int width, HSVTRIPLE image[width]) {
    int min = image[start].hue;
    int index = start;
    // TODO: find the index in range [start,width) of the row image[width] with the minimum hue

    return index;
}



/*  -------------------------------------------------------------------------------------------------------------------------------------
    NOTE: ALL FUNCTIONS BELOW ARE COMPLETE! NO CHANGES PLEASE!!
    -------------------------------------------------------------------------------------------------------------------------------------  */


// Convert from rgb to hsv and back
void transform(int height, int width, RGBTRIPLE image[height][width]) {
    HSVTRIPLE newIm[height][width];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            newIm[i][j] = rgbHSV(image[i][j]);
            image[i][j] = hsvRGB(newIm[i][j]);

            // image[i][j].rgbtRed = (rand() % (256));
            // image[i][j].rgbtGreen = (rand() % (256));
            // image[i][j].rgbtBlue = (rand() % (256));
        }
    }
    return;
}

HSVTRIPLE rgbHSV(RGBTRIPLE px) {
    HSVTRIPLE newPx;
    double cMax = max(max(px.rgbtRed, px.rgbtGreen), px.rgbtBlue);
    double cMin = min(min(px.rgbtRed, px.rgbtGreen), px.rgbtBlue);
    newPx.hue = getHue(px, cMax, cMin);
    newPx.sat = 0.85; //getSat(px, cMax, cMin);
    newPx.val = 1; //cMax / 255.0;
    return newPx;
}

// generic max / min functions
int max(int x, int y) {
    if(x > y) {
        return x;
    }
    return y;
}

int min(int x, int y) {
    if(x < y) {
        return x;
    }
    return y;
}

// helper function to convert rgb to hsv
double getHue(RGBTRIPLE px, double cMax, double cMin) {
    double dx = cMax - cMin;
    if (dx == 0) return 0.0;
    if (cMax == px.rgbtRed) return (int) (60.0 * ((px.rgbtGreen - px.rgbtBlue) / dx) + 360) % 360;
    if (cMax == px.rgbtGreen) return (int) (60.0 * ((px.rgbtBlue - px.rgbtRed) / dx) + 120) % 360;
    if (cMax == px.rgbtBlue) return (int) (60.0 * ((px.rgbtRed - px.rgbtGreen) / dx) + 240) % 360;
    return 0.0;
}

// helper function to convert rgb to hsv
double getSat(RGBTRIPLE px, double cMax, double cMin) {
    if (cMax < 0.0001) {
        return 0.0;
    }
    return (cMax - cMin) / cMax;
}

RGBTRIPLE hsvRGB(HSVTRIPLE px) {
    RGBTRIPLE newPx;
    double c = px.val * px.sat;
    double decimal = px.hue / 60 - (int) (px.hue / 60);
    double x = c * (1 - fabs(( ((int) px.hue / 60) % 2) + decimal - 1));
    double m = px.val - c;

    double red = c, green = x, blue = 0;

    if (px.hue < 60) {
        // do nothing, already initialized!
    } else if (px.hue < 120) {
        red = x; green = c; blue = 0;
    } else if (px.hue < 180) {
        red = 0; green = c; blue = x;
    } else if (px.hue < 240) {
        red = 0; green = x; blue = c;
    } else if (px.hue < 300) {
        red = x; green = 0; blue = c;
    } else if (px.hue < 360) {
        red = c; green = 0; blue = x;
    }

    newPx.rgbtRed = (red + m) * 255;
    newPx.rgbtGreen = (green + m) * 255;
    newPx.rgbtBlue = (blue + m) * 255;
    return newPx;
}
