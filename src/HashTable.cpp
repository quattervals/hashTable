#include <string>
#include <random>
#include <iostream>
#include "HashTable.h"
#include "helpers.h"

using namespace std;

#define INITIAL_SIZE 227     //!< default hash table size
#define USE_GOOD_HASHING_FCT //!< if defined, use the built in hashing function
#define PROBING_EXPONENT 2   //!< exponent of the probing function 0 -> increment by 1, 1 -> linear, 2 -> quadratic

HashTable::HashTable(int size = INITIAL_SIZE) : table(size) // use list initializer to zero initialize the vec.
{
    //zero intialized table vector is equivalent to "table(size, {string(""), 0})"
    itemCount = 0;
    totalShiftCount = 0;
}

/*! Simple hashing function
    Works on strings
    \param key: some string
    \return hash table index
*/
int HashTable::oha1(string key)
{
    int idx = 0;
    for (string::size_type i = 0; i < key.size(); i++)
    {
        idx += (i + 1) * (int)key[i];
    }
    return idx % table.size();
}

int HashTable::builtInHash(string key)
{
    hash<std::string> str_hash;
    return str_hash(key) % table.size();
}

void HashTable::insert(keyValPair_t pair)
{
#ifdef USE_GOOD_HASHING_FCT
    int ix = builtInHash(pair.key);
#else
    int ix = oha1(pair.key);
#endif

    //is the next slot free?
    int psteps = 1; // probing steps
    while (table[ix].key != string(""))
    {
        ix = (ix + intPow(psteps, PROBING_EXPONENT)) % table.size();
        psteps++;
        totalShiftCount++;
    }
    table.at(ix) = pair;
    itemCount++;
}

keyValPair_t HashTable::find(string key)
{
#ifdef USE_GOOD_HASHING_FCT
    int ix = builtInHash(key);
#else
    int ix = oha1(key);
#endif
    // as long as we don't have the key, we go forward
    // if we find an empty slot (i.e. ""), the key does not exist in table
    int psteps = 1; // probing steps
    while (table[ix].key != key && table[ix].key != string(""))
    {
        ix = (ix + intPow(psteps, PROBING_EXPONENT)) % table.size();
        psteps++;
    }
    if (table[ix].key == key)
    {
        return table[ix];
    }
    else
    {
        return {string(""), 0}; // if not found, return empty struct
    }
}

int HashTable::getTotShiftCount(void)
{
    return totalShiftCount;
}

int HashTable::intPow(int base, int exp)
{
    // no error checking on the ranges done!
    // no overflow checking done!
    int ret = 1;
    while (exp > 0)
    {
        ret = base*ret;
        exp--;
    }
    return ret;
}
