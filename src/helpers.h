#include <string>
#include <random>
#include <iostream>
#include "HashTable.h"

#ifndef HELPERS_H
#define HELPERS_H

using namespace std;

string genRandomString(const int len);

keyValPair_t genRandKeyValPair(const int len);

void println(string str);

#endif // HELPERS_H