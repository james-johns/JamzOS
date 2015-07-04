

#include <malloc.h>
#include <memory.h>
#include <bitset.h>

bitset_t *createBitset(unsigned int entries)
{
	unsigned int indexCount = (entries/sizeof(bitset_t)) + ((entries % sizeof(bitset_t)) ? 1 : 0);
	bitset_t *toRet = malloc(sizeof(bitset_t)*indexCount);
	memset(toRet, 0, indexCount);
	return toRet;
}

int testBit(bitset_t *bitset, unsigned int bit)
{
	unsigned int index = bit/sizeof(bitset_t);
	return bitset[index] & (1 << (bit % sizeof(bitset_t)));
}

void setBit(bitset_t *bitset, unsigned int bit)
{
	unsigned int index = bit/sizeof(bitset_t);
	bitset[index] |= (1 << (bit % sizeof(bitset_t)));
}

void clearBit(bitset_t *bitset, unsigned int bit)
{
	unsigned int index = bit/sizeof(bitset_t);
	bitset[index] &= ~(1 << (bit % sizeof(bitset_t)));
}

unsigned int findFirstBit(bitset_t *bitset)
{
	unsigned int toRet= 0;
	while (bitset[toRet] == 0xFFFFFFFF) // find the first unfilled bitset
		toRet ++;
	toRet *= sizeof(bitset_t);

	while (testBit(bitset, toRet)) // find the first unset bit
		toRet++;
	return toRet;
}
