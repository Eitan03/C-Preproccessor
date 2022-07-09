#include "FileUtils.h"
#include <stdlib.h>
#include <string.h>

char* getLine(FILE* file)
{
    char* line = malloc(sizeof(char)*2049);
    
    int curChar;
    int curPos = 0;

	curChar = fgetc(file);
    while (curChar != EOF && curChar != '\n') {
        line[curPos++] = (char)curChar;
        curChar = fgetc(file);
    }
    if (curChar == EOF && curPos == 0) {
        line[0] = 0;
        return line;
    }
    if (curPos == 0) {
        line[curPos++] = curChar;
    }

    line[curPos++] = '\0';
    return line;
}

void writeLine(FILE* file, char* line) {
    if (line[strlen(line) - 1] == '\n') {

        fprintf(file, "%s", line);
    }
    else {
	    fprintf(file, "%s\n", line);
    }
}
