#include "cpu/instr.h"
#include "device/port_io.h"
//#define IO_PORT_SPACE 65536
//extern static uint8_t io_port[IO_PORT_SPACE];


//countn't use edx?
make_instr_func(out_a2d_b){
	//user DX as prot
	//memcpy(&(cpu.edx._16), &cpu.eax._8[0], 1);
	//wrong
	//must use func to do
	pio_write(cpu.gpr[2]._16,1,cpu.gpr[0]._8[0]);
	return 1;
}

make_instr_func(out_a2d_l){
	pio_write(cpu.gpr[2]._16,4,cpu.eax);
	return 1;
}

make_instr_func(in_d2a_b)
{
	cpu.gpr[0]._8[0]=pio_read(cpu.gpr[2]._16,1);
	return 1;
}
make_instr_func(in_d2a_l)
{
	cpu.eax=pio_read(cpu.gpr[2]._16,4);
	return 1;
}
