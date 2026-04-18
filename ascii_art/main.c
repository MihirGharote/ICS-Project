#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Reads an ASCII art text file into a 2D char array.
 * 
 * @param filename The path to the text file
 * @param width Pointer to store the max width of the art
 * @param height Pointer to store the height (number of lines)
 * @return Dynamically allocated 2D char array containing the art
 */
char **getAsciiArt(char *filename, int *width, int *height) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file %s\n", filename);
        *width = 0;
        *height = 0;
        return NULL;
    }

    int max_w = 0;
    int h = 0;
    char buffer[1024];

    // Pass 1: Count lines and find the maximum width
    while (fgets(buffer, sizeof(buffer), file)) {
        h++;
        int len = strlen(buffer);
        
        // Strip trailing newlines/carriage returns for width calculation
        while (len > 0 && (buffer[len-1] == '\n' || buffer[len-1] == '\r')) {
            len--;
        }
        
        if (len > max_w) {
            max_w = len;
        }
    }

    *width = max_w;
    *height = h;

    // Safety check for empty file
    if (h == 0) {
        fclose(file);
        return NULL;
    }

    // Reset file pointer to the beginning for Pass 2
    rewind(file);

    // Pass 2: Allocate memory and fill the 2D array
    char **art = (char **)malloc(h * sizeof(char *));
    if (!art) {
        fclose(file);
        return NULL;
    }

    int i = 0;
    while (fgets(buffer, sizeof(buffer), file) && i < h) {
        // Allocate string width + 1 for null terminator
        art[i] = (char *)malloc((max_w + 1) * sizeof(char));
        
        // Safety check for allocation failure
        if (!art[i]) {
            // Free previously allocated memory to prevent leaks
            for (int k = 0; k < i; k++) {
                free(art[k]);
            }
            free(art);
            fclose(file);
            return NULL;
        }
        
        // Initialize the line with spaces
        memset(art[i], ' ', max_w);
        art[i][max_w] = '\0';

        int len = strlen(buffer);
        // Copy actual characters into the padded string
        for (int j = 0; j < len && j < max_w; j++) {
            if (buffer[j] != '\n' && buffer[j] != '\r') {
                art[i][j] = buffer[j];
            } else {
                break; // Stop copying upon hitting a newline
            }
        }
        i++;
    }

    fclose(file);
    return art;
}


