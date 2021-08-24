#include "cpu/instr.h"
static void instr_execute_1op()
{
	operand_read(&opr_src);
	uint32_t i;
	i=sign_ext(opr_src.val,opr_src.data_size);
	opr_src.val=cpu.eax;
	cpu.eax=i;
	operand_write(&opr_src);	
}

make_instr_impl_1op(xchg,r,v)
