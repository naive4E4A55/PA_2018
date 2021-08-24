#include "cpu/instr.h"
#include "cpu/intr.h"
#include "stdlib.h"
make_instr_func(Int){
	//exit(-1);
	//assert(0);
	print_asm_0("Int","",2);
	uint8_t num=instr_fetch(cpu.eip+1,1);
	cpu.eip+=2;//before raise,eip+=2
	raise_intr(num);

	return 0;
	
	/*uint8_t num=instr_fetch(cpu.eip+1,1);
	raise_intr(num);
	print_asm_0("Int","",2);
	return 2;*/
	
}

