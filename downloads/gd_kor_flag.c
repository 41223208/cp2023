#include <stdio.h>
#include <gd.h>
#include <math.h>
int main() {
    int width = 600, height = 400;
    gdImagePtr img = gdImageCreateTrueColor(width, height);
    int white = gdImageColorAllocate(img, 255, 255, 255);
    int black = gdImageColorAllocate(img, 0, 0, 0);
    int red = gdImageColorAllocate(img, 255, 0, 0);
    int blue = gdImageColorAllocate(img, 0, 0, 255);

    // Draw white background
    gdImageFilledRectangle(img, 0, 0, width, height, white);

    // Draw blue rectangle
    gdImageFilledRectangle(img, 0, 0, width, height / 2, blue);

    // Draw red circle
    int cx = width / 2, cy = height / 4;
    int r = height / 5;
    gdImageFilledArc(img, cx, cy, r * 2, r * 2, 0, 360, red, gdArc);

    // Draw black bars
    int bar_width = width / 10, bar_height = height / 10;
    int x = 0, y = 0;
    for (int i = 0; i < 4; i++) {
        x = width / 2 - bar_width / 2;
        y = i * bar_height + height / 4;
        gdImageFilledRectangle(img, x, y, x + bar_width, y + bar_height, black);
    }
    for (int i = 0; i < 4; i++) {
        x = i * bar_width + width / 4;
        y = height / 2 - bar_height / 2;
        gdImageFilledRectangle(img, x, y, x + bar_width, y + bar_height, black);
    }

    // Save image to file
    FILE *fp;
    fp = fopen("korean_flag.png", "wb");
    gdImagePng(img, fp);
    fclose(fp);

    // Free memory
    gdImageDestroy(img);

    return 0;
}