#pragma once

#include <stdio.h>
#include "DefenitionsManager.h"
#include "FileUtils.h"

void proccessFile(Defenitions* defenitions, HandledFiles files);

void proccessLine(Defenitions* defenitions, char* line, HandledFiles files);

void proccessDefine(Defenitions* defenitions, char* line);

void proccessIfDefined(Defenitions* defenitions, char* line, HandledFiles files);

void proccessInclude(Defenitions* defenitions, char* line, HandledFiles files);
