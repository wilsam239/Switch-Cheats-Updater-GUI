#pragma once

#define ON              1
#define OFF             0


#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <curl/curl.h>

#include <string>
#include <regex>
#include <iostream>
#include <fstream>
#include <filesystem>

#include <switch.h>
#include <pu/Plutonium>


bool downloadFile(const char *url, const char *output, int api);

std::string fetchVersion(const char *url, const char *range);

std::string readVersion(std::string path);

