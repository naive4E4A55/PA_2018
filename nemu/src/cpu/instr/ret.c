#include "cpu/instr.h"
make_instr_func(ret){
	print_asm_0("ret","",1);
	OPERAND old_eip;
	old_eip.type=OPR_MEM;
	old_eip.sreg=SREG_CS;
	old_eip.addr=cpu.esp;
	old_eip.data_size=data_size;
	operand_read(&old_eip);
	cpu.eip=old_eip.val;
	if(data_size==16){
		cpu.eip=cpu.eip&0x0000ffff;
	}
	cpu.esp+=data_size/8;
	return 0;
}



make_instr_func(ret_i_w){
	opr_src.type=OPR_IMM;
	opr_src.sreg=SREG_CS;
	opr_src.addr=eip+1;
	opr_src.data_size=16;//data_size must 16
	operand_read(&opr_src);
	opr_dest.type=OPR_MEM;
	opr_dest.addr=cpu.esp;
	opr_dest.data_size=data_size;//data_size is globe data_size
	operand_read(&opr_dest);
	cpu.eip=opr_dest.val;
	if(data_size==16){
		cpu.eip=cpu.eip&0x0000ffff;
		cpu.esp+=2;
	}
	else{
		cpu.esp+=4;
	}
	cpu.esp+=opr_src.val;
	print_asm_0("retw","",3);
	return 0;
}

make_instr_func(iret){
	//user vaddr_read,set the SREG_SS
	cpu.eip=vaddr_read(cpu.esp,SREG_SS,4);
	cpu.esp+=4;
	cpu.cs.val=vaddr_read(cpu.esp,SREG_SS,4);
	cpu.esp+=4;
	cpu.eflags.val=vaddr_read(cpu.esp,SREG_SS,4);
	cpu.esp+=4;
	return 0;
}
