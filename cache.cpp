#include "cache.h"

unsigned int leastRecentlyUsed;
bool d = true;
bool a = true;
bool m = true;
bool v = true;

vector <vector <uint32_t>> LRU; 
unsigned int checkForUpdate (unsigned int index){
    unsigned int most = 0;
    for (unsigned int i = 0; i < LRU[index].size(); i++)
        if (LRU[index][i] > LRU[index][most])
            most = i;
    for (unsigned int j = 0; j < LRU[index].size(); j++)
        LRU[index][j]++;
    LRU[index][most] = 0;
    return most;
}


Cache::Cache(uint32_t cacheSize, uint32_t blockSize, int nWays, bool debug){

    // Cache configuration
    this->cacheSize = cacheSize;
    this->blockSize = blockSize;
    this->nWays = nWays;

    // Cache stats
    this->hits = 0;
    this->totalAccesses = 0;
    this->debug = debug;
    
    // Cache number of sets
    this->sets = (int)(cacheSize / (blockSize*nWays));
    cache.resize(this->sets, vector<uint32_t>(nWays));

    // Address field bits
    LRU.resize(this->sets, vector<uint32_t>(nWays));
    this->offsetBits = log2(blockSize);
    this->indexBits = log2(this->sets);
    this->tagBits = ADDRESS_LENGTH - this->indexBits - this->offsetBits;


    // Do not change the following print statements
    printf("------------------------------\n");
    printf("Cache size: %" PRIu32 " Bytes\nBlock Size: %" PRIu32 " Bytes\nSets: %d\nWays: %d\nTag bits: %d\nIndex bits: %d\nOffset bits: %d\n", 
            this->cacheSize, this->blockSize, this->sets, this->nWays, this->tagBits, this->indexBits, this->offsetBits);
    printf("------------------------------\n");
}
bool checkCacheHit(vector<vector<uint32_t>> &cache, unsigned k, unsigned b, unsigned c){
    for (unsigned i = 0; i< b;i++){
        if (cache[k][i] == c){
            if (m){
                for (unsigned int j = 0;j < LRU[k].size();j++)
                    LRU[k][j]++;
                LRU[k][i] = 0;
            }
            return true;
        }
        }
        return false;
}

bool Cache::accessCache(string address, int addressOffset){
    // Get address fields
    address_t addr = this->parseAddress(address, addressOffset);

    // Check for cache hit
    bool hit = checkCacheHit (cache, addr.index,this->nWays, addr.tag);
    v = true;
    //(cache[addr.index] == addr.tag);

    if(hit){
        // Cache hit. Yay!
    }
    else // If miss, then load cache block
     {
         if(m)
        {       leastRecentlyUsed = checkForUpdate (addr.index);
                cache[addr.index][leastRecentlyUsed] = addr.tag;
        }

        if (d)
            cache[addr.index][this->nWays-1] = addr.tag;

        if(a){
            for(unsigned int i=0;i < cache[addr.index].size() && v;i++){
                if (cache[0][i] == 0){
                    cache[0][i] = addr.tag; 
                    v = false;
                }
            }
            if(v){
                cache[0][0] = addr.tag;
                v = true;
                }
            }  
    }

    // Update stats
    if(hit)
      this->hits += 1;
    this->totalAccesses += 1;

    return hit;
}


// DO NOT CHANGE FILE BELOW THIS LINE

address_t Cache::parseAddress(string address, int addressOffset){
    istringstream converter(address);
    uint64_t conversion;
    converter >> std::hex >> conversion;

    // Add the addressOffset to the address
    conversion += addressOffset;

    // Truncate to 32-bit address
    uint32_t conversion32;
    conversion32 = (uint32_t)(conversion);
    
    /*calculate the offset */ 
    unsigned int mask = (1 << this->offsetBits) - 1; 
    uint32_t offset = conversion32 & mask;

    /*calculate the index */
    mask = (1 << this->indexBits) - 1;
    uint32_t index = (conversion32 >> this->offsetBits) & mask; 

    /*calculate the tag */
    uint32_t tag = conversion32 >> (this->offsetBits + this->indexBits);

    if(this->debug){
        printf("Address: %s\n",address.c_str());
        printf("Offset: %d\n",addressOffset);
        printf("address + offest: %lu\n",(unsigned long)conversion32);
        printf("tag: %" PRIu32 "\n",(uint32_t)tag);
        printf("index: %" PRIu32 "\n",(uint32_t)index);   
        printf("offset: %" PRIu32 "\n",(uint32_t)offset);

    }  

    address_t parts = { (uint32_t)tag, (uint32_t)index, (uint32_t)offset} ;

    return parts;
}
void Cache::printStats(){ 
    if(this->totalAccesses == 0){
        printf("Error, Cannot get rate \n");
    }
    else{
        printf("Hit rate: %.2f%%\n", 100.00 * (double)(this->hits)/this->totalAccesses);
        printf("Miss rate: %.2f%%\n", 100.00 * (1 - (double)(this->hits)/this->totalAccesses));
    } 
    printf("Hits: %d\n", this->hits);
    printf("total: %d\n",this->totalAccesses);
    printf("------------------------------\n\n"); 
}
