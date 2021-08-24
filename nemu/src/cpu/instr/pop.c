#include "cpu/instr.h"
static void instr_execute_1op() {
	/*OPERAND pop_data;
	pop_data.type=OPR_MEM;
	pop_data.addr=cpu.esp;
	pop_data.sreg=SREG_SS;
	pop_data.data_size=data_size;
	operand_read(&pop_data);*/
	opr_src.val=vaddr_read(cpu.esp,SREG_SS,data_size/8);
	operand_write(&opr_src);
	cpu.esp=cpu.esp+data_size/8;
}

make_instr_impl_1op(pop,r,v)
make_instr_impl_1op(pop,rm,v)

make_instr_func(pop_a_v)
{


	int len=1;
	opr_src.data_size=opr_dest.data_size=data_size;
	opr_src.type=OPR_REG;
	for(int i=7;i>=0;i--)																						//wrong!!!
	{
		if(i==4){
			cpu.esp+=4;
			continue;
		}
		
		cpu.gpr[i].val=vaddr_read(cpu.esp,2,4);
		cpu.esp+=4;
		//opr_src.addr=i;
		//instr_execute_1op();
	}
	print_asm_1("pop_a_v",opr_dest.data_size==8 ? "b":(opr_dest.data_size==16?"w":"l"),len,&opr_src);
	return len;
}
