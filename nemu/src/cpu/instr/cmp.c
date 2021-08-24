#include "cpu/instr.h"
static void instr_execute_2op() {
	operand_read(&opr_src);
	operand_read(&opr_dest);
	opr_src.val=sign_ext(opr_src.val,opr_src.data_size);
	opr_dest.val=sign_ext(opr_dest.val,opr_dest.data_size);
	//printf("src:%d\t",opr_src.val);
	//printf("dest:%d\n",opr_dest.val);
	//printf("OF=%d\n",cpu.eflags.OF);
	//printf("CF=%d\n",cpu.eflags.CF);
	alu_sub(opr_src.val,opr_dest.val);
}


make_instr_impl_2op(cmp,i,rm,bv)
make_instr_impl_2op(cmp,r,rm,b)
make_instr_impl_2op(cmp,r,rm,v)
make_instr_impl_2op(cmp,rm,r,b)
make_instr_impl_2op(cmp,rm,r,v)
make_instr_impl_2op(cmp,i,a,b)
make_instr_impl_2op(cmp,i,a,v)
make_instr_impl_2op(cmp,i,rm,b)
make_instr_impl_2op(cmp,i,rm,v)

