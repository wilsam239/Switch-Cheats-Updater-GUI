#pragma once

#define UPDATED_TITLES_PATH "/config/cheats-updater/updated.dat"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <switch.h>
#include <string.h>
#include <sstream>
#include <algorithm>

#include "titles/title.h"

static constexpr u32 MaxTitleCount = 64000;

void outputUpdatedTitles();

void writeTitlesToFile(std::vector<Title> titles);

std::vector<Title> readTitlesFromFile();

void outputUpdatedTitles();

void printTitles(std::vector<Title> titles);

std::vector<Title> getInstalledTitlesNs();

std::string formatApplicationId(u64 ApplicationId);
