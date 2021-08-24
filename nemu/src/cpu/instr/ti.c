#include "cpu/instr.h"
make_instr_func(sti){
	//Set Interrupt-Enable Flag
	cpu.eflags.IF=1;
	return 1;
}

make_instr_func(cli){
	//Clear Interrupt-Enable Flag
	cpu.eflags.IF=0;
	return 1;
}
