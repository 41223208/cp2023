#include <stdio.h>

void draw_korean_flag() {
    FILE *file = fopen("korean_flag.pbm", "w");

    if (file == NULL) {
        fprintf(stderr, "Unable to create the file.\n");
        return;
    }

    // PBM header
    fprintf(file, "P1\n");
    fprintf(file, "600 400\n");  // Width and height
    fprintf(file, "# Korean Flag\n");

    // Drawing the flag
    for (int i = 0; i < 400; i++) {
        for (int j = 0; j < 600; j++) {
            // Define the colors based on the flag pattern
            int isBlue = (i >= 200) ? 1 : 0;
            int isWhite = (i >= 200 && i <= 300 && j >= 200 && j <= 400) ? 1 : 0;
            int isRed = (i >= 200 && j <= 200) ? 1 : 0;

            // Output the color
            fprintf(file, "%d ", (isBlue || isWhite || isRed) ? 1 : 0);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

int main() {
    draw_korean_flag();
    return 0;
}
