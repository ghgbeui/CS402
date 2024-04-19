#include "readfile.h"

static FILE *file = NULL;

int open_file(const char *filename) {
    file = fopen(filename, "r");
    if (file == NULL) {
        return -1; // Failed to open file
    }
    return 0; // File opened successfully
}

int read_int(int *value) {
    if (fscanf(file, "%d", value) == EOF) {
        return -1; // End of file reached
    }
    return 0; // Successfully read
}

int read_float(float *value) {
    if (fscanf(file, "%f", value) == EOF) {
        return -1; // End of file reached
    }
    return 0; // Successfully read
}

int read_string(char *value) {
    if (fscanf(file, "%s", value) == EOF) {
        return -1; // End of file reached
    }
    return 0; // Successfully read
}

void close_file() {
    if (file != NULL) {
        fclose(file);
        file = NULL;
    }
}
