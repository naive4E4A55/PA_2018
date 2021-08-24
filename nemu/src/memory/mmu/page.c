#include "cpu/cpu.h"
#include "memory/memory.h"

// translate from linear address to physical address
paddr_t page_translate(laddr_t laddr) {
//printf("translate\n");
#ifndef TLB_ENABLED
	//printf("\nPlease implement page_translate()\n");
	//assert(0);
	//have TLB
	uint32_t pageDirectory=cpu.cr3.page_directory_base;
	pageDirectory=(pageDirectory<<12);
	uint32_t offset=0,page=0,dir=0;
	offset=laddr&0x00000FFF;
	page=laddr&0x003FF000;page=(page>>12);
	dir=laddr&0xFFC00000;dir=(dir>>12);
	PDE pageTable1;//PDE is Partial Differential Equations?
	pageTable1.val=paddr_read(pageDirectory+dir*4,4);//get pageTable base addr
	assert(pageTable1.present==1);

	PTE pageTable2;
	pageTable2.val=paddr_read((pageTable1.page_frame<<12)+page*4,4);
	//There is a problem of wasting space. The secondary page table can completely not retain the dir data. It is guessed that one is for alignment and the other is for compatibility.
	assert(pageTable2.present==1);
	uint32_t paddr=(pageTable2.page_frame<<12)+offset;
	//printf("laddr:%x\tpaddr:%x\n",laddr,paddr);
	return paddr;
#else	
	return tlb_read(laddr) | (laddr & PAGE_MASK);;
#endif
}
