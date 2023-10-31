#include <iostream>
#include <algorithm>
#include "Bucket.h"

using namespace std;

Bucket::Bucket(int numOfKeys)
{
    this->localDepth = 1;
    this->keys.resize(numOfKeys, -1);
}

void Bucket::insertKey(int key)
{
    for (int i = 0; i < keys.size(); i++)
    {
        if (keys[i] == -1)
        {
            keys[i] = key;
            return;
        }
    }
    // will only get to this step when the bucket is full
    // at this point, keys.size() > numOfKeys
    keys.push_back(key);
}

void Bucket::removeKey(int key)
{
    keys.erase(remove(keys.begin(), keys.end(), key), keys.end());
}

void Bucket::printKey()
{
    cout << "[";
    for (int i = 0; i < keys.size(); i++)
    {
        if (keys[i] == -1)
        {
            cout << "-";
        }
        else
        {
            cout << keys[i];
        }
        if (i != keys.size() - 1)
        {
            cout << ",";
        }
    }
    cout << "] "
         << "(" << localDepth << ")";
}

int Bucket::getLocalDepth()
{
    return localDepth;
}

void Bucket::setLocalDepth(int depth)
{
    localDepth = depth;
}

vector<int> Bucket::getKeys()
{
    return keys;
}

void Bucket::setBucketSize(int size)
{
    keys.resize(size, -1);
}

bool Bucket::isFull()
{
    return (keys[keys.size() - 1] != -1);
}