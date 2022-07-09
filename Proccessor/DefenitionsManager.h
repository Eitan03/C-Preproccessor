#pragma once
#include <string.h>
#include <stdlib.h>

typedef struct Defenition {
	char* name;
	char* value;
} Defenition;

typedef struct Defenitions {
	Defenition** defenitions;
	int length;
	int _capacity;
} Defenitions;

Defenitions* createDefenitions();

char* _switchDefenitions(Defenitions* defenitions, char* line);

int isDefined(Defenitions* defenitions, char* name);
int tryGetDefenition(Defenitions* defenitions, char* name, Defenition* outpot);

void addDefenition(Defenitions* defenitions, Defenition defenition);