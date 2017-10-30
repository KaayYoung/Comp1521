// ADT for Bit-strings
// COMP1521 17s2 Week02 Lab Exercise
// Written by John Shepherd, July 2017
// Modified by ...

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "Bits.h"

// assumes that an unsigned int is 32 bits
#define BITS_PER_WORD 32

// A bit-string is an array of unsigned ints (each a 32-bit Word)
// The number of bits (hence Words) is determined at creation time
// Words are indexed from right-to-left
// words[0] contains the most significant bits
// words[nwords-1] contains the least significant bits
// Within each Word, bits are indexed right-to-left
// Bit position 0 in the Word is the least significant bit
// Bit position 31 in the Word is the most significant bit

typedef unsigned int Word;

struct BitsRep {
   int nwords;   // # of Words
   Word *words;  // array of Words
};

// make a new empty Bits with space for at least nbits
// rounds up to nearest multiple of BITS_PER_WORD
Bits makeBits(int nbits)
{
   Bits new;
   new = malloc(sizeof(struct BitsRep));
   assert(new != NULL);
   int  nwords;
   if (nbits%BITS_PER_WORD == 0)
      nwords = nbits/BITS_PER_WORD;
   else
      nwords = 1+nbits/BITS_PER_WORD;
   new->nwords = nwords;
   // calloc sets to all 0's
   new->words = calloc(nwords, sizeof(Word));
   assert(new->words != NULL);
   return new;
}

// release space used by Bits
void  freeBits(Bits b)
{
   assert(b != NULL && b->words != NULL);
   free(b->words);
   free(b);
}

// form bit-wise AND of two Bits a,b
// store result in res Bits
void andBits(Bits a, Bits b, Bits res)
{	
	int i;
	for (i = 0; i < b->nwords; i++) {
    	res->words[i] = a->words[i] & b->words[i];
    }	
	res->nwords = b->nwords;
}

// form bit-wise OR of two Bits a,b
// store result in res Bits
void orBits(Bits a, Bits b, Bits res)
{
	int i;
	for (i = 0; i < b->nwords; i++) {
    	res->words[i] = a->words[i] | b->words[i];
    }	
	res->nwords = b->nwords;

}

// form bit-wise negation of Bits a,b
// store result in res Bits
void invertBits(Bits a, Bits res)
{
	int i;
	for (i = 0; i < a->nwords; i++) {
    	res->words[i] = ~ a->words[i];
    }	
	res->nwords = a->nwords;
}

// left shift Bits
void leftShiftBits(Bits b, int shift, Bits res)
{
	/*int i, j;
	char binary[b->nwords * 32 + 1];
	for (i = 0; i < b->nwords; i++) {
		//printf("words[0]: %u\n", b->words[i]);
		j = 0;	
		while (j < 32) {
			if (b->words[i] & ((Word) 1 << (31 - j))) {
				binary[j + i * 32] = '1';
			} else {
				binary[j + i * 32] = '0';
			}
			j++;
		}
	}
	binary[b->nwords * 32] = '\0';
	for (j = 0; j < b->nwords * 32 - shift; j++) {
			binary[j] = binary[j + shift]; 
				//printf("binary: %c\n", binary[j + i * 32]);
	}
	for (j = b->nwords * 32 - shift; j < b->nwords * 32; j++) {
			binary[j] = '0';
	} 
	res->nwords = b->nwords;
	setBitsFromString(res, binary);*/
	int i;
	res->nwords = b->nwords;
	for (i = 0; i < b->nwords; i++) {
		res->words[i] = b->words[i] << shift;
	}
}

// right shift Bits
void rightShiftBits(Bits b, int shift, Bits res)
{
   	/*int i, j;
	char binary[b->nwords * 32 + 1];
	for (i = 0; i < b->nwords; i++) {
		//printf("words[0]: %u\n", b->words[i]);
		j = 0;	
		while (j < 32) {
			//Word mask = (unsigned) 1 << (31 - j);
			//printf("b->words: %d  mask: %d\n", b->words[i], mask);
			
			if (b->words[i] & ((Word) 1 << (31 - j))) {
				binary[j + i * 32] = '1';
			} else {
				binary[j + i * 32] = '0';
			}
			j++;
		}
	}
	binary[b->nwords * 32] = '\0';
	//printf("binary: %s\n", binary);
	for (j = b->nwords * 32 - 1; j >= shift; j--) {
				binary[j] = binary[j - shift]; 
				//printf("j: %d, binary: %c\n", j, binary[j]);
	}
	for (j = 0; j < shift; j++) {
				binary[j] = '0';
	}
		//printf("binary: %s\n", binary); 
	res->nwords = b->nwords;
	setBitsFromString(res, binary);*/
	int i;
	res->nwords = b->nwords;
	for (i = 0; i < b->nwords; i++) {
		res->words[i] = b->words[i] >> shift;
	}
}

// copy value from one Bits object to another
void setBitsFromBits(Bits from, Bits to)
{	
	int i;
	to->nwords = from->nwords;
  	for (i = 0; i < from->nwords; i++) {
  		//printf("from:%d, to:%d", from->words[i], to->words[i]);
  		to->words[i] = from->words[i];

  	}
}

// assign a bit-string (sequence of 0's and 1's) to Bits
// if the bit-string is longer than the size of Bits, truncate higher-order bits
void setBitsFromString(Bits b, char *bitseq)
{	
	int i, j;
	char *ptr = bitseq;
	int len = strlen(ptr);
	unsigned int result[10] = {0};

	if (len < b->nwords * 32) {
		for (i = b->nwords * 32 - 1; i >= b->nwords * 32 - len; i--){
			ptr[i] = ptr[i - b->nwords * 32 + len]; 
		}
		for (i = 0; i < b->nwords * 32 - len; i++) {
			ptr[i] = '0';
		}
		ptr[b->nwords * 32] = '\0';
	} else {
		int diff = len - b->nwords * 32;
		for (i = 0; i < b->nwords * 32; i++) ptr[i] = ptr[diff + i];
	}

	for (i = 0; i < b->nwords; i++) {
		j = 31;
		while (j >= 0) {
			if (*ptr == '1') {
				result[i] = result[i] | ((Word) 1 << j);
			}
			ptr++;
			j--;
		}
		b->words[i] = result[i];
	}
}

// display a Bits value as sequence of 0's and 1's
void showBits(Bits b)
{	
	int i;
	for (i = 0; i < b->nwords; i++) {
		
		char binary[BITS_PER_WORD];
		int j;
		for (j = 0; j < BITS_PER_WORD; j++) {

			Word mask = (unsigned) 1 << (31 - j);
			if (b->words[i] & mask) {
				binary[j] = '1';
			} else {
				binary[j] = '0';
			}
			printf("%c", binary[j]);
		}
	}
}
