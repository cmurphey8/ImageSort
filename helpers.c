#include "helpers.h"
#import <stdio.h>
#include <stdlib.h>
#include <math.h>

/*  -------------------------------------------------------------------------------------------------------------------------------------
    FUNCTION PROTOTYPES
    -------------------------------------------------------------------------------------------------------------------------------------  */

// selection sort helper
int findMin(int start, int width, HSVTRIPLE image[width]);

// convert rgb to hsv and helpers
HSVTRIPLE rgbHSV(RGBTRIPLE px);
int max(int x, int y);
int min(int x, int y);
double getHue(RGBTRIPLE px, double cMax, double cMin);

// convert hsv to rgb
RGBTRIPLE hsvRGB(HSVTRIPLE px);

/*  -------------------------------------------------------------------------------------------------------------------------------------
    TODOS: SELECTION SORT AND HELPER
    -------------------------------------------------------------------------------------------------------------------------------------  */

// TODO: selection sort
void selectionSort(int height, int width, RGBTRIPLE image[height][width]) {

    // convert image from rgb to hsv
    HSVTRIPLE newIm[height][width];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            newIm[i][j] = rgbHSV(image[i][j]);
        }
    }

    // selection sort each row by hue
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // YOU DO: complete helper function findMin to find the minimum in range [j,width)
            int index = findMin(j, width, newIm[i]);

            // WE DO: swap values at minimum index and j
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

// YOU DO: selection sort helper function
int findMin(int start, int width, HSVTRIPLE image[width]) {
    int min = image[start].hue;
    int index = start;
    // YOU DO: find the index in range [start,width) of the row image[width] with the minimum hue

    return index;
}

/*  -------------------------------------------------------------------------------------------------------------------------------------
   COMPLETE HELPER FUNCTIONS -- MAKE NO CHANGES BELOW
    -------------------------------------------------------------------------------------------------------------------------------------  */

HSVTRIPLE rgbHSV(RGBTRIPLE px) {
    HSVTRIPLE newPx;
    double cMax = max(max(px.rgbtRed, px.rgbtGreen), px.rgbtBlue);
    double cMin = min(min(px.rgbtRed, px.rgbtGreen), px.rgbtBlue);
    newPx.hue = getHue(px, cMax, cMin);

    // regularize saturation and value across all pixels
    newPx.sat = 0.85;
    newPx.val = 1;
    return newPx;
}

// generic max && min functions
int max(int x, int y) {
    if(x > y) return x;
    return y;
}

int min(int x, int y) {
    if(x < y) return x;
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
