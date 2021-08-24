#include "cpu/instr.h"
make_instr_func(call_i_v){
	opr_src.type=OPR_IMM;
	opr_src.sreg = SREG_CS;
	opr_src.data_size = data_size;
	opr_src.addr = eip + 1;
	operand_read(&opr_src);

	//下面的意思是：push 旧eip 
	cpu.esp-=data_size/8;
	uint32_t data=cpu.eip+1+data_size/8;
	vaddr_write(cpu.esp,SREG_SS,data_size/8,data);
	int offset=sign_ext(opr_src.val,data_size);
	print_asm_1("call", "", 1+data_size/8,&opr_src);
	cpu.eip+=offset;
	return 1+data_size/8;
}

make_instr_func(call_rm_v){
	int len=1;
	opr_src.data_size=data_size;
	len+=modrm_rm(eip+1,&opr_src);
	operand_read(&opr_src);
	cpu.esp-=data_size/8;
	uint32_t data=cpu.eip+len;
	vaddr_write(cpu.esp,SREG_SS,data_size/8,data);
	print_asm_1("call"," *",len,&opr_src);
	if(data_size==16)
		cpu.eip=opr_src.val&0xffff;
	else
	{
		int offset=sign_ext(opr_src.val,data_size);
		cpu.eip=offset;
		cpu.eip=opr_src.val;
	}
	return 0;
}




