#include "cpu/cpu.h"
#include "memory/memory.h"
#include "stdlib.h"

// return the linear address from the virtual address and segment selector
uint32_t segment_translate(uint32_t offset, uint8_t sreg) {
	/* TODO: perform segment translation from virtual address to linear address
	 * by reading the invisible part of the segment register 'sreg'
	 */
	sreg=sreg&0x7;
	cpu.segReg[sreg].base=0;

	assert(cpu.segReg[sreg].base==0);
	//if(sreg>6){
	//	printf("%d\n",sreg);exit(-1);
	//}
	//printf("sreg:%x  ",sreg);
	//printf("%x,%x\n",cpu.segReg[sreg].base+offset,offset);
	//assert(sreg<6);
	return cpu.segReg[sreg].base+offset;
}

// load the invisible part of a segment register
void load_sreg(uint8_t sreg) {
	/* TODO: load the invisibile part of the segment register 'sreg' by reading the GDT.
	 * The visible part of 'sreg' should be assigned by mov or ljmp already.
	 */
	assert(sreg<6);
	uint32_t sregIndex=cpu.segReg[sreg].index;
	uint16_t gdtrLimit=cpu.gdtr.limit;
	assert(gdtrLimit>=((sregIndex<<3)));
	uint32_t sreAddr=cpu.gdtr.base+(sregIndex<<3);
	SegDesc dest;
	dest.val[0]=paddr_read(sreAddr,4);
	dest.val[1]=paddr_read(sreAddr+4,4);
	uint32_t sregBase_15_0=dest.base_15_0;
	uint32_t sregBase_23_16=dest.base_23_16;
	uint32_t sregBase_31_24=dest.base_31_24;
	uint32_t base=sregBase_15_0+(sregBase_23_16<<16)+(sregBase_31_24<<24);
	assert(base==0);
	uint32_t sregLimit_15_0=dest.limit_15_0;
	uint32_t sregLimit_19_16=dest.limit_19_16;
	uint32_t limit=(sregLimit_15_0+(sregLimit_19_16<<16))&0x000FFFFF;
	assert(limit==0x000FFFFF);
	assert(dest.granularity==1);
	assert(dest.present==1);

	cpu.segReg[sreg].limit=gdtrLimit;
	cpu.segReg[sreg].base=base;
	cpu.segReg[sreg].type=dest.type;
	cpu.segReg[sreg].privilege_level=dest.privilege_level;
	cpu.segReg[sreg].soft_use=dest.soft_use;
}
