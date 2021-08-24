#include "cpu/instr.h"
#include "stdlib.h"

static void instr_execute_2op() {
	operand_read(&opr_src);
	opr_dest.val = opr_src.val;
	operand_write(&opr_dest);
}

make_instr_impl_2op(mov, r, rm, b)
make_instr_impl_2op(mov, r, rm, v)
make_instr_impl_2op(mov, rm, r, b)
make_instr_impl_2op(mov, rm, r, v)
make_instr_impl_2op(mov, i, rm, b)
make_instr_impl_2op(mov, i, rm, v)
make_instr_impl_2op(mov, i, r, b)
make_instr_impl_2op(mov, i, r, v)
make_instr_impl_2op(mov, a, o, b)
make_instr_impl_2op(mov, a, o, v)
make_instr_impl_2op(mov, o, a, b)
make_instr_impl_2op(mov, o, a, v)
make_instr_func(mov_r2c_l){
	/*uint8_t regNum=paddr_read(eip+1,1);
	regNum=regNum&0x38;
	regNum=(regNum>>3);
	print_asm_2("cr2c", opr_dest.data_size == 8 ? "b" : (opr_dest.data_size == 16 ? "w" : "l"), 2, &opr_src, &opr_dest); 
	switch(regNum){
		case 0:cpu.cr0.val=cpu.eax;break;
		case 1:cpu.cr0.val=cpu.ecx;break;
		case 2:cpu.cr0.val=cpu.edx;break;
		case 3:cpu.cr0.val=cpu.ebx;break;
		case 4:cpu.cr0.val=cpu.esp;break;
		case 5:cpu.cr0.val=cpu.ebp;break;
		case 6:cpu.cr0.val=cpu.esi;break;
		case 7:cpu.cr0.val=cpu.edi;break;
	}
	return 2;*/
	static int num=0;num++;
	OPERAND op;
	op.data_size=32;
	int len=1;
	len+=modrm_rm(eip+1,&op);
	operand_read(&op);
	uint32_t mid=instr_fetch(eip+1,1);
	mid=(mid>>3)&0x7;
	//not only cr0 but also cr3..............
	//so switch this but not one switch and only change cr0
	if(mid==3)cpu.cr3.val=op.val;
	else if(mid==0){
		cpu.cr0.val=op.val;
		//printf("op.val:%x\n",op.val);
		//printf("cr0_pg:%d\tcr0_pe:%d\n",cpu.cr0.pg,cpu.cr0.pe);
	}
	else{
		printf("without r2c\n");
		assert(0);
	}
	print_asm_1("mov_r2c","",len,&op);
	if(num==2){
	printf("second\n");
	//exit(-1);
}
	return len;
}
make_instr_func(mov_c2r_l){
	OPERAND op;
	op.data_size=32;
	int len=1;
	len+=modrm_rm(eip+1,&op);
	uint32_t mid=instr_fetch(eip+1,1);
	mid=(mid>>3)&0x7;
	if(mid==3)op.val=cpu.cr3.val;
	else if(mid==0)op.val=cpu.cr0.val;
	else{
		printf("without c2r\n");
		assert(0);
	}
	operand_write(&op);
	print_asm_1("mov_c2r","",len,&op);
	return len;
	/*uint8_t regNum=paddr_read(eip+1,1);
	
	regNum=regNum&0x38;
	regNum=(regNum>>3);
	print_asm_2("c2cr", opr_dest.data_size == 8 ? "b" : (opr_dest.data_size == 16 ? "w" : "l"), 2, &opr_src, &opr_dest); 
	//printf("c2cr ");
	switch(regNum){
		case 0:cpu.eax=cpu.cr0.val;break;
		case 1:cpu.ecx=cpu.cr0.val;break;
		case 2:cpu.edx=cpu.cr0.val;break;
		case 3:cpu.ebx=cpu.cr0.val;break;
		case 4:cpu.esp=cpu.cr0.val;break;
		case 5:cpu.ebp=cpu.cr0.val;break;
		case 6:cpu.esi=cpu.cr0.val;break;
		case 7:cpu.edi=cpu.cr0.val;break;
	}
	return 2;	*/
}
make_instr_func(lgdt)
{
	int len=1;
	len+=modrm_rm(eip+1,&opr_src);
	//printf("addr=%x\t",opr_src.addr);
	//printf("val=%x\t",opr_src.val);
	opr_src.data_size=16;
	operand_read(&opr_src);
	//uint32_t val=paddr_read(eip+1,2);
	//printf("%x\t",val);
	//printf("%x\t",opr_src.val);
	cpu.gdtr.limit=opr_src.val;
	opr_src.addr=opr_src.addr+2;
	opr_src.data_size=32;
	operand_read(&opr_src);
	cpu.gdtr.base=opr_src.val;
	//printf("limit=%x\t",cpu.gdtr.limit);
	//printf("base=%x\t",cpu.gdtr.base);
	return len;
	//printf()

}
/*make_instr_func(lgdt){
	if(data_size==32){
		cpu.gdtr.base=paddr_read(eip+2,4);
		cpu.gdtr.limit=paddr_read(eip+6,2);
		return 6;
	}
	else{
		cpu.gdtr.base=paddr_read(eip+2,3);
		cpu.gdtr.limit=paddr_read(eip+5,2);
		return 6;
	}
}*/
make_instr_func(mov_r2sr_w){
	uint8_t modrm=paddr_read(eip+1,1);
	uint8_t reg=modrm&0x38;
	reg=reg>>3;
	uint8_t rm=modrm&0x7;
	cpu.segReg[reg].val=cpu.gpr[rm].val;
	load_sreg(reg);
	return 2;
}

/*
make_instr_func(mov_r2rm_b) {
	src.data_size = 8;
	dest.data_size = 8;

	len += modrm_r_rm(eip + 1, &src, &dest);
	
	OPERAND r, rm;
	r.data_size = 8;
	rm.data_size = 8;
	int len = 1;
	// read ModR/M for src and dest
	len += modrm_r_rm(eip + 1, &r, &rm);
	//operand_read(&r);
	//rm.val = r.val;
	//operand_write(&rm);
	execute();
	return len;
}*/



/*make_instr_func(mov_r2rm_v) {
	OPERAND r, rm;
	r.data_size = data_size;
	rm.data_size = data_size;
	int len = 1;
	// read ModR/M for src and dest
	len += modrm_r_rm(eip + 1, &r, &rm);
	//printf("mov_r2rm rm addr = 0x%08x\n", rm.addr);
	//operand_read(&r);
	//rm.val = r.val;
	//operand_write(&rm);
	execute(&r, &rm);
	return len;
}

make_instr_func(mov_rm2r_b) {
	OPERAND r, rm;
	r.data_size = 8;
	rm.data_size = 8;

	int len = 1;
	// read ModR/M for src and dest
	len += modrm_r_rm(eip + 1, &r, &rm);

	//operand_read(&rm);
	//r.val = rm.val;
	//operand_write(&r);
	execute(&rm, &r);
	return len;
}

make_instr_func(mov_rm2r_v) {
	OPERAND r, rm;
	r.data_size = data_size;
	rm.data_size = data_size;

	int len = 1;
	// read ModR/M for src and dest
	len += modrm_r_rm(eip + 1, &r, &rm);

	//operand_read(&rm);
	//r.val = rm.val;
	//operand_write(&r);
	execute(&rm, &r);
	return len;
}

make_instr_func(mov_i2rm_b) {
	OPERAND rm, imm;
	rm.data_size = 8;
	imm.data_size = 8;

	int len = 1;
	// read ModR/M for src and dest
	len += modrm_rm(eip + 1, &rm);

	imm.type = OPR_IMM;
	imm.addr = eip + len;
	// printf("addr imm %08x, len=%d\n", imm.addr, len);
	//operand_read(&imm);
	//rm.val = imm.val;
	//operand_write(&rm);
	execute(&imm, &rm);
	return len + 1; 
}

make_instr_func(mov_i2rm_v) {
	OPERAND rm, imm;
	rm.data_size = data_size;
	imm.data_size = data_size;

	int len = 1;
	// read ModR/M for src and dest
	len += modrm_rm(eip + 1, &rm);

	imm.type = OPR_IMM;
	imm.addr = eip + len;
	imm.data_size = data_size;
	// printf("addr imm %08x, len=%d\n", imm.addr, len);

	//operand_read(&imm);
	//rm.val = imm.val;
	//operand_write(&rm);
	execute(&imm, &rm);
	return len + data_size / 8;
}
make_instr_func(mov_i2r_b) {
	OPERAND r, imm;
	r.data_size = 8;
	r.type = OPR_REG;
	r.addr = opcode & 0x7;

	imm.type = OPR_IMM;
	imm.addr = eip + 1;
	imm.data_size = 8;

	//operand_read(&imm);
	//r.val = imm.val;
	//operand_write(&r);

	execute(&imm, &r);
	return 2;
}

make_instr_func(mov_i2r_v) {
	OPERAND r, imm;
	r.data_size = data_size;
	r.type = OPR_REG;
	r.addr = opcode & 0x7;

	imm.type = OPR_IMM;
	imm.addr = eip + 1;
	imm.data_size = data_size;

	//operand_read(&imm);
	//r.val = imm.val;
	//operand_write(&r);

	execute(&imm, &r);
	return 1 + data_size / 8;
}

make_instr_func(mov_off2a_b) {
	OPERAND r, m;
	r.data_size = 8;
	r.type = OPR_REG;
	r.addr = REG_AL;

	m.type = OPR_MEM;
	m.sreg = SREG_DS;
	m.addr = instr_fetch(eip + 1, 4);
	m.data_size = 8;

	operand_read(&m);
	r.val = m.val;
	operand_write(&r);
	return 5;
}


make_instr_func(mov_off2a_v) {
	OPERAND r, m;
	r.data_size = data_size;
	r.type = OPR_REG;
	r.addr = REG_AX;
	
	m.type = OPR_MEM;
	m.sreg = SREG_DS;
	m.addr = instr_fetch(eip + 1, 4);
	m.data_size = data_size;

	operand_read(&m);
	r.val = m.val;
	operand_write(&r);
	return 5;
}

make_instr_func(mov_a2off_b) {
	OPERAND r, m;
	r.data_size = 8;
	r.type = OPR_REG;
	r.addr = REG_AL;

	m.type = OPR_MEM;
	m.sreg = SREG_DS;
	m.addr = instr_fetch(eip + 1, 4);
	m.data_size = 8;

	operand_read(&r);
	m.val = r.val;
	operand_write(&m);
	return 5;
}

make_instr_func(mov_a2off_v) {
	OPERAND r, m;
	r.data_size = data_size;
	r.type = OPR_REG;
	r.addr = REG_AX;

	m.type = OPR_MEM;
	m.sreg = SREG_DS;
	m.addr = instr_fetch(eip + 1, 4);
	m.data_size = data_size;

	operand_read(&r);
	m.val = r.val;
	operand_write(&m);
	return 5;
}

*/
make_instr_func(mov_zrm82r_v) {
	int len = 1;
	OPERAND r, rm;
	r.data_size = data_size;
	rm.data_size = 8;
	len += modrm_r_rm(eip + 1, &r, &rm);
	
	operand_read(&rm);
	r.val = rm.val;
	operand_write(&r);

	print_asm_2("mov", "", len, &rm, &r);
	return len;
}

make_instr_func(mov_zrm162r_l) {
        int len = 1;
        OPERAND r, rm;
        r.data_size = 32;
        rm.data_size = 16;
        len += modrm_r_rm(eip + 1, &r, &rm);

        operand_read(&rm);
        r.val = rm.val;
        operand_write(&r);
	print_asm_2("mov", "", len, &rm, &r);
        return len;
}

make_instr_func(mov_srm82r_v) {
        int len = 1;
        OPERAND r, rm;
        r.data_size = data_size;
        rm.data_size = 8;
        len += modrm_r_rm(eip + 1, &r, &rm);
        
	operand_read(&rm);
        r.val = sign_ext(rm.val, 8);
        operand_write(&r);
	print_asm_2("mov", "", len, &rm, &r);
        return len;
}

make_instr_func(mov_srm162r_l) {
        int len = 1;
        OPERAND r, rm;
        r.data_size = 32;
        rm.data_size = 16;
        len += modrm_r_rm(eip + 1, &r, &rm);
        operand_read(&rm);
        r.val = sign_ext(rm.val, 16);
        operand_write(&r);

	print_asm_2("mov", "", len, &rm, &r);
        return len;
}
