

#ifndef _BITSET_H_
#define _BITSET_H_

typedef unsigned int bitset_t;

bitset_t *createBitset(unsigned int entries);
int testBit(bitset_t *bitset, unsigned int bit);
void setBit(bitset_t *bitset, unsigned int bit);
void clearBit(bitset_t *bitset, unsigned int bit);
unsigned int findFirstBit(bitset_t *bitset);

#endif
