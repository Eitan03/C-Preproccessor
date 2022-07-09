#include "Utils.h"
#include <string.h>
#include <stdlib.h>

int startsWith(char* str, char* delim)
{
	return strncmp(str, delim, strlen(delim)) == 0;
}

char** split(const char* str, char* delim, int* outpotLength)
{
	int size = 1;
	for (int i = 0; i < strlen(str); i++) {
		if (str[i] == delim[0]) size++;
	}
	*outpotLength = size;
	char** arr = malloc(sizeof(char*) * size);
	int i = 0;

	char* nextToken = NULL;
	for (char* token = strtok_s(str, delim, &nextToken); token != NULL; token = strtok_s(NULL, delim, &nextToken)) {
		char* temp = _strdup(token);
		arr[i] = temp;
		i++;
	}
	return arr;
}

int getLastIndexOf(const char* str, char delim)
{
	for (int i = strlen(str); i >= 0; i--) {
		if (str[i] == delim) return i;
	}
	return -1;
}

char* deleteAndInsert(const char* str, int deleteFrom, int deleteSize, const char* replaceWith)
{
	int replaceWithLength = strlen(replaceWith);

	int newStrLength = (strlen(str) - (deleteSize - 1) + strlen(replaceWith) + 1);
	char* newStr = (char*)malloc(newStrLength * sizeof(char));
	strncpy(newStr, str, deleteFrom);
	strcpy(newStr + deleteFrom, replaceWith);
	strcpy(newStr + deleteFrom + strlen(replaceWith), str + deleteFrom + deleteSize - 1);
	newStr[newStrLength - 1] = '\0';
	return newStr;
}
