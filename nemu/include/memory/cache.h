#ifndef CACHE_H
#define CACHE_H
#include "nemu.h"
//#include "memory/mmu/segment.h"
//#include "memory/mmu/page.h"
//#include "memory/mmu/tlb.h"
struct CacheLine{
	uint8_t valid_bit;
	uint32_t tlb;
	uint8_t block[64];
};

void init_cache();//fresh Cache
uint32_t cache_read(paddr_t paddr, size_t len); 
void cache_write(paddr_t paddr, size_t len, uint32_t data);
#endif
