#include "cpu/instr.h"
static void instr_execute_1op()
{
	operand_read(&opr_src);
	cpu.esp-=data_size/8;
	vaddr_write(cpu.esp,SREG_SS,data_size/8,opr_src.val);
}


make_instr_impl_1op(push,r,v)
make_instr_impl_1op(push,i,b)
make_instr_impl_1op(push,i,v)
make_instr_impl_1op(push,rm,v)
make_instr_func(push_a_v)
{

	int len=1;
	uint32_t old_esp=cpu.esp;
	//opr_src.data_size=opr_dest.data_size=32;
	//opr_src.type=OPR_REG;
	for(int i=0;i<8;i++)
	{
		if(i==4){
			//use esp old
			cpu.esp-=4;
			vaddr_write(cpu.esp,SREG_SS,4,old_esp);
		}
		else{
			cpu.esp-=4;
			vaddr_write(cpu.esp,SREG_SS,4,cpu.gpr[i].val);
		}
	}
	print_asm_1("push_a_v",opr_dest.data_size==8 ? "b":(opr_dest.data_size==16?"w":"l"),len,&opr_src);
	return len;
}
