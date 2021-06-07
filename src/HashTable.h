#include <string>
#include <vector>

#ifndef HASHTABLE_H
#define HASHTABLE_H

using namespace std;

//public type
typedef struct keyValPair_s
{
    string key;  //!< the key as string
    int payload; //!< payload
} keyValPair_t;

class HashTable
{
private:
    std::vector<keyValPair_t>::size_type itemCount; //!< number of key val pairs in vector
    std::vector<keyValPair_t> table;                //!< vector containing key val pairs
    int totalShiftCount;                            //!< when a collision happens, the ix is incremented: this value sums all increments over all inserts operations

    int oha1(string key);          //!< oli's hashing algo 1: simple hashing function
    int builtInHash(string key);   //!< built-in STL hashing function
    int intPow(int base, int exp); //!< power of integers

public:
    HashTable(int size);            //!< constructor
    void insert(keyValPair_t pair); //!< insert a keyValPair to hash table
    keyValPair_t find(string key);  //!< find keyValPair in hash table
    int getTotShiftCount(void);     //!< get debug info: how many collisions happened since the object lives
};

#endif // HASHTABLE_H
