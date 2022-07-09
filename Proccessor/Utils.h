#pragma once

int startsWith(char* str, char* delim);

char** split(const char* str,char* delim, int* outpotLength);

int getLastIndexOf(const char* str, char delim);

char* deleteAndInsert(const char* str, int deleteFrom, int deleteTo, const char* replaceWith);
