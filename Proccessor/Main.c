#include <stdio.h>
#include <stdlib.h>
#include "ProccessFunctions.h"

int main() {
	FILE* proccessedFile = fopen("./testingFiles/main.c", "r");
	FILE* outpotFile = fopen("./testingFiles/main.c.outpot", "wb+");

	HandledFiles files = { proccessedFile, outpotFile, "./testingFiles/"};
	
	Defenitions* defenitions = createDefenitions();
	proccessFile(defenitions, files);
	
	printf("done");
	free(defenitions);

	fclose(proccessedFile);
	fclose(outpotFile);

	return 0;
}