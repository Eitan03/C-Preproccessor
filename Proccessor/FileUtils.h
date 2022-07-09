#pragma once
#include <stdio.h>

typedef struct HandledFiles {
FILE* proccessedFile;
FILE* outpotFile;
char* filesDirectory;
} HandledFiles;


char* getLine(FILE* file);
void writeLine(FILE* file, char* line);
