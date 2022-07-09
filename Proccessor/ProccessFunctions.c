#include "ProccessFunctions.h"
#include <string.h>
#include "Utils.h";

void proccessFile(Defenitions* defenitions, HandledFiles files)
{
	char* line = getLine(files.proccessedFile);
	while (line[0] != 0) {
		proccessLine(defenitions, line, files);
		line = getLine(files.proccessedFile);
	}
	free(line);
}

void proccessLine(Defenitions* defenitions, char* line, HandledFiles files)
{
	if (line[0] != '#') {
		char* newLine = _switchDefenitions(defenitions, line);
		writeLine(files.outpotFile, newLine);
		free(newLine);
		return;
	}

	if (startsWith(line, "#include")) {
		proccessInclude(defenitions, line, files);
	}
	else if (startsWith(line, "#define")) {
		proccessDefine(defenitions, line);
	} else if (startsWith(line, "#ifdef") || startsWith(line, "#ifndef")) {
		proccessIfDefined(defenitions, line, files, getLine);
	}
	else {
		printf("Invalid Line was given! (%s) skipping!\n", line);
	}
	free(line);
}

char* _switchDefenitions(Defenitions* defenitions, const char* line) {
	
	char* tempLine = _strdup(line);

	int numOfQuatations = 0;
	int wordStartingPlace = -1;
	for (int i = 0; i < strlen(tempLine); i++) {
		if (
			((tempLine[i] >= 'a') && (tempLine[i] <= 'z')) ||
			((tempLine[i] >= 'A') && (tempLine[i] <= 'Z')) ||
			((tempLine[i] >= '0') && (tempLine[i] <= '9')) ||
			(tempLine[i] == '_')
			) {
			if (wordStartingPlace == -1) {
				wordStartingPlace = i;
			}
		}
		else{
			if (wordStartingPlace != -1 && (( numOfQuatations % 2) == 0)) {
				
				int curWordLength = i - wordStartingPlace + 1;
				char* curWord = malloc(curWordLength);
				strncpy(curWord, tempLine + wordStartingPlace, curWordLength);
				curWord[curWordLength - 1] = '\0';
				
				Defenition def;
				if (tryGetDefenition(defenitions, curWord, &def)) {
					char* newLine = deleteAndInsert(tempLine, wordStartingPlace, curWordLength, def.value);
					free(tempLine);
					tempLine = newLine;
				}
			}
			if (tempLine[i] == '\"') { 
				numOfQuatations++;
			}
			wordStartingPlace = -1;
		}
	}
	return tempLine;
}

void proccessDefine(Defenitions* defenitions, char* line)
{
	int arrLen = 0;
	char** arr = split(line, " ", &arrLen);

	char* value;
	if (arrLen <= 1 || arrLen > 3) {
		printf("invalid define was given! (%s)", line);
		return;
	} 
	if (arrLen == 3) {
		value = _strdup(arr[2]);
	}
	else {
		value = NULL;
	}
	addDefenition(defenitions, (Defenition){ _strdup(arr[1]), value });
	for (int i = 0; i < arrLen; i++) {
		free(arr[i]);
	}
	free(arr);

}

void _proccessIf(Defenitions* defenitions, int trueFalse, HandledFiles files) {
	char* line = getLine(files.proccessedFile);
	while ((strcmp(line, "#else")) && (strcmp(line, "#endif"))) {
		if (line == NULL) {
			printf("the if statement never ended!\n");
			return;
		}
		if (trueFalse) {
			proccessLine(defenitions, line, files);
		}
		line = getLine(files.proccessedFile);
	}

	if (!strcmp(line, "#else")) {
		line = getLine(files.proccessedFile);
		while (strcmp(line, "#endif")) {
			if (line == NULL) {
				printf("the if statement never ended!");
				return;
			}
			if (!trueFalse) {
				proccessLine(defenitions, line, files);
			}
			line = getLine(files.proccessedFile);
		}
	}
}

void proccessIfDefined(Defenitions* defenitions, char* line, HandledFiles files)
{
	int arrLen = 0;
	char** arr = split(line, " ", &arrLen);

	char* curLine = line;

	if (arrLen != 2) {
		printf("Invalid if statement was given (%s) skipping", line);
		while (!strcmp(curLine, "#endif")) {
			if (curLine[0] == '\0') {
				printf("the if statement never ended!");
				return;
			}
			curLine = getLine(files.proccessedFile);
		}
	}

	_proccessIf(defenitions,
		(
			((!strcmp(arr[0], "#ifdef")) && isDefined(defenitions, arr[1])) ||
			((!strcmp(arr[0], "#ifndef")) && (!isDefined(defenitions, arr[1])))
			), files
	);


	for (int i = 0; i < arrLen; i++) {
		free(arr[i]);
	}
	free(arr);

}

void proccessInclude(Defenitions* defenitions, char* line, HandledFiles files)
{
	int arrLen = 0;
	char** arr = split(line, " ", &arrLen);
	if (arrLen != 2) {
		printf("invalid include (%s) skipping\n", line);
	}
	if (arr[1][0] != '\"') {
		printf("an include that is out of scope encountered (%s) skipping\n", arr[1]);
	}
	
	char* fileName = malloc((strlen(arr[1]) + strlen(files.filesDirectory)  + 1) * sizeof(char));
	fileName = strncpy(fileName, arr[1]+1, strlen(arr[1])-2);
	fileName[strlen(arr[1]) - 2] = '\0';
	char* pathName = NULL;

	char* temp = _strdup(fileName);
	sprintf(fileName, "%s%s", files.filesDirectory, temp);
	free(temp);

	FILE* includedFile = fopen( fileName, "r");
	free(fileName);
	
	HandledFiles includeFiles = {includedFile, files.outpotFile};
	proccessFile(defenitions, includeFiles);
	fclose(includedFile);

	for (int i = 0; i < arrLen; i++) {
		free(arr[i]);
	}
	free(arr);

}
