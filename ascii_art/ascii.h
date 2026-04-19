#pragma once

/**
 * Reads an ASCII art text file into a 2D char array.
 * 
 * @param filename The path to the text file
 * @param width Pointer to store the max width of the art
 * @param height Pointer to store the height (number of lines)
 * @return Dynamically allocated 2D char array containing the art
 */
char **getAsciiArt(char *filename, int *width, int *height);

char **freeAsciiArt(char **art, int width, int height);