#include <iostream>
#include <vector>
#include <algorithm>
#include "ExtensibleHashTable.h"
#include "Bucket.h"

using namespace std;

// creates empty hash table
// num of keys in a buckets should be set to 4
// directory should consist 2 entries
// the hash function should use only the last bit of the hash value
ExtensibleHashTable::ExtensibleHashTable()
{
    this->globalDepth = 1;
    this->bucketSize = 4;
    this->directory.resize(2, NULL);
}

// create empty hash table
// num of keys in a buckets should be the param
ExtensibleHashTable::ExtensibleHashTable(int numOfKeys)
{
    this->globalDepth = 1;
    this->bucketSize = numOfKeys;
    this->directory.resize(2, NULL);
}

ExtensibleHashTable::~ExtensibleHashTable()
{
}
// return true if the key is found, false otherwise
bool ExtensibleHashTable::find(int key)
{
    int index = hash(key);
    if (directory[index] != NULL)
    {
        Bucket &currentBucket = *directory[index];
        vector<int> currentBucketKeys = currentBucket.getKeys();
        for (int i = 0; i < currentBucketKeys.size(); i++)
        {
            if (currentBucketKeys[i] == key)
            {
                return true;
            }
        }
    }
    return false;
}

void ExtensibleHashTable::insert(int key)
{
    // calculate bucket index
    int index = hash(key);
    // cout << "inserting " << key << " at index " << index << endl;

    // if the pointers is not pointing to a bucket
    if (this->directory[index] == NULL)
    {
        this->directory[index] = new Bucket(bucketSize);
    }
    // Get a reference to the bucket
    Bucket &currentBucket = *directory[index];

    // insert if bucket is not full
    if (!currentBucket.isFull())
    {
        currentBucket.insertKey(key);
    }

    // bucket is full
    else
    {
        // cout << "inserting " << key << " at index " << index << endl;
        int localDepth = currentBucket.getLocalDepth();
        int oldDirectorySize = directory.size();

        // if GD == LD, the directory size should be doubled before creating a new bucket
        if (globalDepth == currentBucket.getLocalDepth())
        {
            directory.resize(oldDirectorySize * 2);
            globalDepth++;

            // assign pointers
            for (int i = 0; i < directory.size(); i++)
            {
                directory[i] = directory[i % oldDirectorySize];
            }
        }

        // is GD > LD, make a new bucket and assign pointers and distribute values from original bucket
        if (globalDepth > currentBucket.getLocalDepth())
        {
            // go through the current bucket
            // if there are keys that have a different index, create a new bucket
            currentBucket.insertKey(key);
            vector<int> currentBucketKeys = currentBucket.getKeys();
            bool newBucketMade = false;

            for (int i = 0; i < currentBucketKeys.size(); i++)
            {
                int currentKey = currentBucketKeys[i];

                int newIndex = hash(currentKey);
                // cout << "current key: " << currentKey << ",newIndex: " << newIndex << endl;
                // if the the value has new Index after splitting the bucket
                if (newIndex != index)
                {
                    if (!newBucketMade)
                    {
                        directory[newIndex] = new Bucket(bucketSize);
                        newBucketMade = true;
                    }
                    Bucket &newBucket = *directory[newIndex];
                    newBucket.insertKey(currentKey);
                    newBucket.setLocalDepth(globalDepth);
                    currentBucket.removeKey(currentKey);
                    currentBucket.setLocalDepth(globalDepth);
                    // refill the empty ones in the previous bucket if need to
                    currentBucket.setBucketSize(bucketSize);
                }
                // // if trying to insert more duplicate keys
                // else if (currentBucket.getKeys().size() > bucketSize) {
                //     throw runtime_error("unable to insert more duplicate keys.");
                // }
            }
        }
    }
}

bool ExtensibleHashTable::remove(int key)
{
    if (find(key) == false)
        return false;
    int index = hash(key);
    Bucket &currentBucket = *directory[index];
    vector<int> currentBucketKeys = currentBucket.getKeys();
    currentBucket.removeKey(key);
    currentBucket.setBucketSize(bucketSize);
    return true;
}

void ExtensibleHashTable::print()
{
    for (int i = 0; i < this->directory.size(); i++)
    {
        cout << i << ": " << this->directory[i] << "--> ";
        if (this->directory[i] != NULL)
        {
            Bucket &currentBucket = *(this->directory[i]);
            // only print bucket details if the bucket index is the same as directory index
            if (hash(currentBucket.getKeys()[0]) == i)
            {
                currentBucket.printKey();
            }
        }
        cout << "\n";
    }
}

int ExtensibleHashTable::hash(int val)
{
    return val % this->directory.size();
}

int main()
{
    ExtensibleHashTable hashTable(3);
    hashTable.insert(64);
    hashTable.insert(200);
    hashTable.insert(153);
    hashTable.insert(66);
    hashTable.insert(218);
    hashTable.insert(67);
    hashTable.insert(13);
    hashTable.print();

    hashTable.insert(253);
    hashTable.print();

    hashTable.insert(109);
    hashTable.print();

    // hashTable.insert(64);
    // hashTable.insert(64);
    // hashTable.insert(64);
    // hashTable.insert(64);


    return 0;
}