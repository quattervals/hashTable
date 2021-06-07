#include <string>
#include <random>
#include <iostream>
#include "helpers.h"
#include "HashTable.h"


using namespace std;

void println(string str)
{
    cout << str + "\n";
}

string genRandomString(const int len)
{
    static const char letters[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
    string str;
    str.reserve(len);

    random_device generator; // use default_random_engine to have something deterministic
    uniform_int_distribution<int> distribution(0, sizeof(letters) - 1);

    for (int i = 0; i < len; i++)
    {
        str += letters[distribution(generator)];
    }
    return str;
}

keyValPair_t genRandKeyValPair(const int len)
{
    random_device generator; // use default_random_engine to have something deterministic
    uniform_int_distribution<int> distribution;

    keyValPair_t ret;
    ret.payload = distribution(generator);
    ret.key = genRandomString(len);
    return ret;
}

