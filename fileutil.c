#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileutil.h"

// Load the text file from the given filename.
// Return a pointer to the array of strings.
// Sets the value of size to be the number of valid
// entries in the array (not the total array length).
char **loadFileAA(char *filename, int *size)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Can't open file");
        exit(1);
    }

    char **lines = NULL; // Array of strings
    char lineBuffer[1024]; // Temporary buffer for reading lines
    *size = 0; // Initialize size

    while (fgets(lineBuffer, sizeof(lineBuffer), file))
    {
        // Trim newline character if present
        lineBuffer[strcspn(lineBuffer, "\n")] = '\0';

        // Reallocate memory to expand the array for one more string
        char **temp = realloc(lines, (*size + 1) * sizeof(char *));
        if (!temp)
        {
            fprintf(stderr, "Memory allocation failed.\n");
            freeAA(lines, *size);
            fclose(file);
            exit(1);
        }
        lines = temp;

        // Allocate memory for the new string and copy it
        lines[*size] = malloc(strlen(lineBuffer) + 1);
        if (!lines[*size])
        {
            fprintf(stderr, "Memory allocation failed.\n");
            freeAA(lines, *size);
            fclose(file);
            exit(1);
        }
        strcpy(lines[*size], lineBuffer);

        // Increment size
        (*size)++;
    }

    fclose(file);
    return lines;
}

// Search the array for the target string.
// Return the found string or NULL if not found.
char *substringSearchAA(char *target, char **lines, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (strstr(lines[i], target))
        {
            return lines[i]; // Return the first match
        }
    }
    return NULL; // No match found
}

int linearSearch(char **hashArray, int numHashes, const char *hash)
{
    for (int i = 0; i < numHashes; i++)
    {
        if (strcmp(hashArray[i], hash) == 0)
        {
            return i; // If found
        }
    }
    return -1; // If not found
}

// Free the memory used by the array
void freeAA(char **lines, int size)
{
    for (int i = 0; i < size; i++)
    {
        free(lines[i]); // Free each individual string
    }
    free(lines); // Free the array of pointers
}
