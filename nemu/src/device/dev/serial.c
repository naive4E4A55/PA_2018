#include "nemu.h"
#include "device/serial.h"

//#define make_pio_handler(name) void name(uint16_t port, size_t len, bool is_write)
make_pio_handler(handler_serial) {
	if(is_write) {
		assert(len == 1);
#ifdef HAS_DEVICE_SERIAL
		if(port == SERIAL_PORT) { // offset == 0
			char c = (char)read_io_port(port, 1);
			putc(c, stdout);//put out char
			//printf("this is handler_serial\n");
			fflush(stdout);
		}
#endif
	}
}

void init_serial() {
	// serial port always free
	write_io_port(SERIAL_PORT + 5, 1, 0x20);
}
