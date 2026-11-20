#include "../include/savefile.h"

// Implements binary File I/O requirement
void saveGame(const Player *p, const char *filename) {
    FILE *file = fopen(filename, "wb");
    if (file == NULL) {
        printf("Error: Could not open file for saving!\n");
        return;
    }
    fwrite(p, sizeof(Player), 1, file);
    fclose(file);
}

int loadGame(Player *p, const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        return 0; // File doesn't exist
    }
    size_t readStatus = fread(p, sizeof(Player), 1, file);
    fclose(file);
    return (readStatus == 1);
}