#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include "HashTable.h"
#include "helpers.h"

using namespace std;

keyValPair_t findKeyNaive(string key, vector<keyValPair_t> const &vec)
{
    for (vector<keyValPair_t>::size_type i = 0; i < vec.size(); i++)
    {
        if (vec[i].key == key)
        {
            return vec[i];
        }
    }

#ifdef USE_SLOW
    for (keyValPair_t v : vec)
    {
        if (v.key == key)
        {
            return v;
        }
    }
#endif

    return {string(""), 0};
}

/*
linear hashing
Time taken by hash function: 949 microseconds
Time taken by naive function: 47517 microseconds
speedup hash compared to naive: 5000%
Total shift count: 8112
#define NUM_ITEMS 2000       //!< number of randomly generated items to fill in table
#define TABLE_INIT_SIZE 2287 //!< prime numbers lead to nice distribution of the indices in the array e.g. 7877, 2287, 461, 41
#define KEY_LEN 5            //!< length of the key that will be hashed
*/


/*
Quadratic hashing
Time taken by hash function: 304 microseconds
Time taken by naive function: 43594 microseconds
speedup hash compared to naive: 14300%
Total shift count: 2999
#define NUM_ITEMS 2000       //!< number of randomly generated items to fill in table
#define TABLE_INIT_SIZE 2287 //!< prime numbers lead to nice distribution of the indices in the array e.g. 7877, 2287, 461, 41
#define KEY_LEN 5            //!< length of the key that will be hashed
*/


/*
linear hashing, dumb hashing function
Time taken by hash function: 123290 microseconds
Time taken by naive function: 39221 microseconds
speedup hash compared to naive: 0%
Total shift count: 1265151
#define NUM_ITEMS 2000       //!< number of randomly generated items to fill in table
#define TABLE_INIT_SIZE 2287 //!< prime numbers lead to nice distribution of the indices in the array e.g. 7877, 2287, 461, 41
#define KEY_LEN 5            //!< length of the key that will be hashed
*/

/*
quadratic hashing, dumb hashing function
Time taken by hash function: 1536 microseconds
Time taken by naive function: 39487 microseconds
speedup hash compared to naive: 2500%
Total shift count: 19599
define NUM_ITEMS 2000       //!< number of randomly generated items to fill in table
#define TABLE_INIT_SIZE 2287 //!< prime numbers lead to nice distribution of the indices in the array e.g. 7877, 2287, 461, 41
#define KEY_LEN 5            //!< length of the key that will be hashed
*/

int main()
{


/*
5 items
Time taken by hash function: 8 microseconds
Time taken by naive function: 0 microseconds
speedup hash compared to naive: 0%
Total shift count: 0

10 items
Time taken by hash function: 8 microseconds
Time taken by naive function: 2 microseconds
speedup hash compared to naive: 0%
Total shift count: 0

15 items
Time taken by hash function: 8 microseconds
Time taken by naive function: 6 microseconds
speedup hash compared to naive: 0%
Total shift count: 0

20 items
Time taken by hash function: 8 microseconds
Time taken by naive function: 11 microseconds
speedup hash compared to naive: 100%
Total shift count: 0

100 items
Time taken by hash function: 22 microseconds
Time taken by naive function: 516 microseconds
speedup hash compared to naive: 2300%
Total shift count: 4

// depends a lot on the number of collisions
1000 items
Time taken by hash function: 34 microseconds
Time taken by naive function: 13380 microseconds
speedup hash compared to naive: 39300%
Total shift count: 353

2000 items
Time taken by hash function: 138 microseconds
Time taken by naive function: 41391 microseconds
speedup hash compared to naive: 29900%
Total shift count: 2976


2287 items - full capacity
Time taken by hash function: 8145 microseconds
Time taken by naive function: 53435 microseconds
speedup hash compared to naive: 600% ... 3500% but varying a lot
Total shift count: 79931
*/

#define NUM_ITEMS 2000       //!< number of randomly generated items to fill in table
#define TABLE_INIT_SIZE 2287 //!< prime numbers lead to nice distribution of the indices in the array e.g. 7877, 2287, 461, 41
#define KEY_LEN 5            //!< length of the key that will be hashed

    HashTable myTable(TABLE_INIT_SIZE);
    //keep track of the items in reference vector
    vector<keyValPair_t> refVec;
    refVec.reserve(NUM_ITEMS);

    // generate random items and put them into both structures
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        keyValPair_t item = genRandKeyValPair(KEY_LEN);
        myTable.insert(item);
        refVec.push_back(item);
    }

    chrono::duration<unsigned int, ratio<1, 1000000>> totDurationHash;
    chrono::duration<unsigned int, ratio<1, 1000000>> totDurationNaive;

    for (int i = 0; i < NUM_ITEMS; i++)
    {
        string keyToFind = refVec[i].key;

        auto start = chrono::high_resolution_clock::now();
        keyValPair_t hashFind = myTable.find(keyToFind);
        auto stop = chrono::high_resolution_clock::now();
        if (hashFind.key != keyToFind)
        {
            cout << "wrong key in hash table" << endl;
        }
        totDurationHash += chrono::duration_cast<chrono::microseconds>(stop - start);

        start = chrono::high_resolution_clock::now();
        keyValPair_t naiveFind = findKeyNaive(keyToFind, refVec);
        stop = chrono::high_resolution_clock::now();
        if (naiveFind.key != keyToFind)
        {
            cout << "wrong key in naive table" << endl;
        }
        totDurationNaive += chrono::duration_cast<chrono::microseconds>(stop - start);
    }

    cout << "Time taken by hash function: "
         << totDurationHash.count() << " microseconds" << endl;
    cout << "Time taken by naive function: "
         << totDurationNaive.count() << " microseconds" << endl;
    cout << "speedup hash compared to naive: "
         << totDurationNaive.count() / totDurationHash.count() * 100 << "%" << endl;
    cout << "Total shift count: " << myTable.getTotShiftCount() << endl;

    return 0;
}
