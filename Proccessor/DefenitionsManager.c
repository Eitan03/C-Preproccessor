#include "DefenitionsManager.h"

void _createSpaceInDefenitions(Defenitions* def)
{
	if (def->length == def->_capacity) {
		def->defenitions = realloc(def->defenitions, sizeof(Defenition) * def->_capacity * 2);
		def->_capacity *= 2;
	}
}

Defenitions* createDefenitions()
{
	Defenitions* defenitions = malloc(sizeof(Defenitions));
	defenitions->_capacity = 2;
	defenitions->length = 0;
	defenitions->defenitions = malloc(sizeof(Defenition) * 2);
	return defenitions;
}

int isDefined(Defenitions* defenitions, char* name)
{
	for (int i = 0; i < defenitions->length; i++) {
		if (strcmp( (*(defenitions->defenitions[i])).name, name) == 0) {
			return 1;
		}
	}
	return 0;
}

int tryGetDefenition(Defenitions* defenitions, char* name, Defenition* outpot)
{
	for (int i = 0; i < defenitions->length; i++) {
		if (strcmp( (*(defenitions->defenitions[i])).name, name) == 0) {
			*outpot = *(defenitions->defenitions[i]);
			return 1;
		}
	}
	return 0;
}

void addDefenition(Defenitions* defenitions, Defenition defenition)
{
	Defenition existingDefenition;
	if (tryGetDefenition(defenitions, defenition.name, &existingDefenition)) {
		existingDefenition.value = defenition.value;
	}
	else {
		_createSpaceInDefenitions(defenitions);
		Defenition* newDefenition = malloc(sizeof(Defenition));
		newDefenition->name = defenition.name;
		newDefenition->value = defenition.value;
		defenitions->defenitions[defenitions->length++] = newDefenition;
	}
}


