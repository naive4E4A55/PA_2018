#include "cpu/instr.h"
static void instr_execute_1op(){
	operand_read(&opr_src);
	cpu.idtr.limit=laddr_read(opr_src.addr,2);
	if(data_size==16){
		cpu.idtr.base=laddr_read(opr_src.addr+2,3);
	}
	else{
		cpu.idtr.base=laddr_read(opr_src.addr+2,4);
	}
}
make_instr_impl_1op(lidt,rm,v)
