#ifndef __CACHE__H__
#define __CACHE__H__

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <map>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <inttypes.h>
#include <cmath>

#define ADDRESS_LENGTH 32

using namespace std;


struct address_t{
    uint32_t tag;
    uint32_t index;
    uint32_t offset;
};

class Cache{
    private:
        uint32_t cacheSize;
        uint32_t blockSize;
        int sets;
        int nWays; //1: direct, 0: fully associative
        int indexBits, tagBits, offsetBits; //bit assignment
        int hits;
        vector <vector <uint32_t>> cache;
        int totalAccesses;
        bool debug;

        address_t parseAddress(string, int);

    public:
        Cache(uint32_t, uint32_t, int, bool);
        bool accessCache(string, int);
        void printStats();

};

#endif
