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
    for (keyValPair_t v : vec)
    {
        if (v.key == key)
        {
            return v;
        }
    }
    return {string(""), 0};
}

int main()
{


#define NUM_ITEMS 2000       //!< number of randomly generated items to fill in table
#define TABLE_INIT_SIZE 2287 //!< prime numbers lead to nice distribution of the indices in the array e.g. 7877, 2287, 461, 41
#define KEY_LEN 5            //!< length of the key that will be hashed

    HashTable myTable(TABLE_INIT_SIZE);
    vector<keyValPair_t> refVec; //keep track of the items in reference vector
    refVec.reserve(NUM_ITEMS);

    // generate random items and put them into both structures
    for (int i = 0; i < NUM_ITEMS; i++)
    {
        keyValPair_t item = genRandKeyValPair(KEY_LEN);
        myTable.insert(item);
        refVec.push_back(item);
    }

    auto totDurationHash = chrono::duration<unsigned int, ratio<1, 1000000>>::zero();
    auto totDurationNaive = chrono::duration<unsigned int, ratio<1, 1000000>>::zero();


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
        keyValPair_t naiveFind = findKeyNaive(keyToFind, refVec); //the naive search simply scans the refVec
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

    // try to find non-existing key
    keyValPair_t hashFind = myTable.find("non_existing_key");
    if (hashFind.key != string(""))
    {
        cout << "found non-existing key: that's an error" << endl;
    }

    return 0;
}
