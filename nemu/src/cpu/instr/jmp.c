#include "cpu/instr.h"

make_instr_func(jmp_near) {
    OPERAND rel;
    rel.type = OPR_IMM;
	rel.sreg = SREG_CS;
    rel.data_size = data_size;
    rel.addr = eip + 1;

    operand_read(&rel);

	int offset = sign_ext(rel.val, data_size);
	print_asm_1("jmp", "",  1 + data_size / 8, &rel);

	cpu.eip += offset;

    return 1 + data_size / 8;
}

make_instr_func(jmp_near_b) {
    OPERAND rel;
    rel.type = OPR_IMM;
	rel.sreg = SREG_CS;
    rel.data_size = 8;
    rel.addr = eip + 1;

    operand_read(&rel);
	int offset = sign_ext(rel.val, 8);
	print_asm_1("jmp", "",  1 + data_size / 8, &rel);

	cpu.eip += offset;

    return 2;
}

make_instr_func(jmp_rm_v)
{
	int len=1;
	opr_src.data_size=data_size;
	len+=modrm_rm(eip+1,&opr_src);
	operand_read(&opr_src);

	int offset = sign_ext(opr_src.val, data_size);
	print_asm_1("jmp", "", len, &opr_src);

	cpu.eip = offset;
	return 0;
}

make_instr_func(jmp_prm_v){
	opr_src.data_size=32;
	modrm_rm(eip + 1, &opr_src);
	opr_dest.type = OPR_IMM;
	opr_dest.sreg = SREG_CS;
	opr_dest.data_size = data_size;
	opr_dest.addr = opr_src.val;

	operand_read(&opr_dest);
	int offset = sign_ext(opr_dest.val,data_size);
	print_asm_1("jmp","",7,&opr_dest);

	cpu.eip=offset;
	return 0;
}

make_instr_func(ljmp){
	uint32_t jmpAddr=paddr_read(eip+1,4);
	uint16_t segData=paddr_read(eip+5,2);
	assert((segData&0x08)==0x08);
	cpu.cs.val=segData;
	load_sreg((segData&0xF8)>>3);
	cpu.eip=jmpAddr;
	print_asm_1("ljmp","",7,&opr_dest);
	return 0;
}

