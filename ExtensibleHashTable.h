#ifndef EXTENSIBLEHASHTABLE_H
#define EXTENSIBLEHASHTABLE_H

#include <vector>
#include "Bucket.h"

using namespace std;

class ExtensibleHashTable {
    private:
         int globalDepth; // global depth
        int bucketSize; // Size of buckets
        vector<Bucket *> directory; // directory of buckets

    public: 
        // ExtensibleHashTable constructor without param
        ExtensibleHashTable();

        // ExtensibleHashTable constructor with param
        ExtensibleHashTable(int);

        // ExtensibleHashTable destructor
        ~ExtensibleHashTable();

        // return true if found the key from the hash table, false otherwise
        bool find(int key);

        // insert key into hash table
        void insert(int key);

        // remove key from hash table
        bool remove(int key);

        // print all hash table contents
        void print();

        // used to calculate hash value of the key
        int hash(int key);
};

#endif