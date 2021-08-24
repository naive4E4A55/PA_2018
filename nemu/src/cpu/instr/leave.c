#include "cpu/instr.h"
make_instr_func(leave)
{
	cpu.esp=cpu.ebp;
	// mov ebp to esp

	OPERAND old_ebp;
	old_ebp.type=OPR_MEM;
	old_ebp.addr=cpu.esp;
	old_ebp.data_size=data_size;
	operand_read(&old_ebp);
	
	if(data_size==16){
		cpu.ebp=(cpu.ebp&0xffff0000)+(old_ebp.val&0x0000ffff);
	}
	else{
	cpu.ebp= old_ebp.val;
	}
	//cpu.ebp=old_ebp.val;
	cpu.esp+=data_size/8;
	print_asm_0("leave","",1);
	return 1;
	// pop ebp
}
