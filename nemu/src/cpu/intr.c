#include "cpu/intr.h"
#include "cpu/instr.h"
#include "memory/memory.h"


void raise_intr(uint8_t intr_no) {
#ifdef IA32_INTR
	//printf("Please implement raise_intr()");
	//assert(0);
	//save old msg
	//assert(cpu.intr==1);
	//printf("intr_no=%d\n",intr_no);
	//static int num=0;printf("intr_num=%d\n",num++);
	//cpu.eflags.IF=0;
	//printf("in intr\n");
	cpu.esp-=4;vaddr_write(cpu.esp,SREG_SS,4,cpu.eflags.val);
	cpu.esp-=4;vaddr_write(cpu.esp,SREG_SS,4,cpu.cs.val);
	cpu.esp-=4;vaddr_write(cpu.esp,SREG_SS,4,cpu.eip);

	//read describe
	uint32_t base_addr=cpu.idtr.base;
	uint32_t intr_addr=base_addr+intr_no*8;
	GateDesc des;
	//use line addr!
	des.val[0]=laddr_read(intr_addr,4);
	des.val[1]=laddr_read(intr_addr+4,4);

	uint32_t offset_31_16=des.offset_31_16;
	uint32_t offset_15_0=des.offset_15_0;
	uint32_t offset=(offset_31_16<<16)+(offset_15_0&0x0000FFFF);

	cpu.cs.val=des.selector;
	cpu.eip=offset;
	//load_sreg(SREG_CS);
	if(des.type==0xE){
		cpu.eflags.IF=0;
	}
	//i8259_ack_intr();
	//printf("out intr\n");
	//cpu.eflags.IF=1;
#endif
}

void raise_sw_intr(uint8_t intr_no) {
	// return address is the next instruction
	cpu.eip += 2;
	raise_intr(intr_no);
}
