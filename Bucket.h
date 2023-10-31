#ifndef BUCKET_H
#define BUCKET_H

#include <vector>
using namespace std;

class Bucket {
private:
    int localDepth; // local depth
    vector<int> keys; // all keys 

public:
    // Bucket constructor
    Bucket(int numOfKeys);

    // get local depth
    int getLocalDepth();

    // set local depth
    void setLocalDepth(int depth);

    // get all keys from the bucket
    vector<int> getKeys();

    // set bucket size
    void setBucketSize(int size);

    // insert key in bucket
    void insertKey(int key);

    // remove key from bucket
    void removeKey(int key);

    // print all keys from bucket
    void printKey();

    // return true if bucket is full, false otherwise
    bool isFull();
};

#endif