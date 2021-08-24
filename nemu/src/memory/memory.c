#include "nemu.h"
#include "cpu/cpu.h"
#include "memory/memory.h"
#include "device/mm_io.h"
#include <memory.h>
#include <stdio.h>
#include "memory/cache.h"


uint8_t hw_mem[MEM_SIZE_B];

uint32_t hw_mem_read(paddr_t paddr, size_t len) {
	uint32_t ret = 0;
	memcpy(&ret, hw_mem + paddr, len);
	return ret;
}

void hw_mem_write(paddr_t paddr, size_t len, uint32_t data) {
	memcpy(hw_mem + paddr, &data, len);
}

uint32_t paddr_read(paddr_t paddr, size_t len) {
	uint32_t ret = 0;
#ifdef HAS_DEVICE_VGA
	if(is_mmio(paddr)!=-1)
		ret=mmio_read(paddr,len,is_mmio(paddr));//read mmio,is vmem
	else
		ret=hw_mem_read(paddr,len);
#else
	#ifdef CACHE_ENABLED
		ret=cache_read(paddr,len);
	#else
		ret = hw_mem_read(paddr, len);
	#endif
#endif
	return ret;
}

void paddr_write(paddr_t paddr, size_t len, uint32_t data) {
#ifdef HAS_DEVICE_VGA
	if(is_mmio(paddr)!=-1)
		mmio_write(paddr,len,data,is_mmio(paddr));//write mmio is vmem
	else
		hw_mem_write(paddr,len,data);
#else
	#ifdef CACHE_ENABLED
		cache_write(paddr,len,data);
	#else
		hw_mem_write(paddr, len, data);
	#endif
#endif
}


uint32_t laddr_read(laddr_t laddr, size_t len) {
	assert(len==1||len==2||len==4);
	//have no bug!!!
#ifdef IA32_PAGE
	//printf("read laddr%x\n",laddr);
	//printf("pg==%d\tpe==%d\n",cpu.cr0.pg,cpu.cr0.pe);
	if(cpu.cr0.pg==1&&cpu.cr0.pe==1){
		//if IA32_PAGE&&pg==1,translate(laddr)->paddr
		//printf("read laddr%x\n",laddr);
		uint32_t res=0;
		if(len==4){
			uint32_t res0=(laddr_read(laddr,1)&0x000000FF);
			uint32_t res1=(laddr_read(laddr+1,1)&0x000000FF);
			uint32_t res2=(laddr_read(laddr+2,1)&0x000000FF);
			uint32_t res3=(laddr_read(laddr+3,1)&0x000000FF);
			res=res0+(res1<<8)+(res2<<16)+(res3<<24);
			//printf("len==4,%x\n",res);
			return res;
		}
		else if(len==2){
			res=0;
			uint32_t res0=(laddr_read(laddr,1)&0x000000FF);
			uint32_t res1=(laddr_read(laddr+1,1)&0x000000FF);
			res=res0+(res1<<8);
			return res;
		}
		else if(len==1){
			paddr_t paddr=laddr;
			paddr=page_translate(laddr);
			//printf("%x\n",paddr);
			//printf("len==1:%x\n",paddr_read(paddr,1));
			return paddr_read(paddr,1);
		}
	}
	else return paddr_read(laddr,len);
#endif
	return paddr_read(laddr, len);
}

void laddr_write(laddr_t laddr, size_t len, uint32_t data) {
	//paddr_t paddr=laddr;
#ifdef IA32_PAGE
		//same with last
	//printf("write laddr%x\n",laddr);
	if(cpu.cr0.pg==1&&cpu.cr0.pe==1){
		if(len==4){
			//printf("write_len==4:%x\n",data);
			uint32_t data0=(data&0x000000FF);
			uint32_t data1=(data&0x0000FF00);data1=(data1>>8);
			uint32_t data2=(data&0x00FF0000);data2=(data2>>16);
			uint32_t data3=(data&0xFF000000);data3=(data3>>24);
			laddr_write(laddr,1,data0);
			laddr_write(laddr+1,1,data1);
			laddr_write(laddr+2,1,data2);
			laddr_write(laddr+3,1,data3);
			//paddr_t paddr0=page_translate(laddr);
			//paddr_t paddr1=page_translate(laddr+1);
			//paddr_t paddr2=page_translate(laddr+2);
			//paddr_t paddr3=page_translate(laddr+3);
			//paddr_write(paddr0,1,data0);
			//paddr_write(paddr1,1,data1);
			//paddr_write(paddr2,1,data2);
			//paddr_write(paddr3,1,data3);
		}
		else if(len==2){
			uint32_t data0=(data&0x000000FF);
			uint32_t data1=(data&0x0000FF00);data1=(data1>>8);
			laddr_write(laddr,1,data0);
			laddr_write(laddr+1,1,data1);
		}
		else if(len==1){
			//printf("write_len==1:%x\n",data);
			paddr_t hwaddr=page_translate(laddr);
			paddr_write(hwaddr,len,data);
		}
	}
	else paddr_write(laddr,len,data);
#else
	//this is a wrong that I don't write #else but #endif..............................
	paddr_write(laddr, len, data);
#endif
}


uint32_t vaddr_read(vaddr_t vaddr, uint8_t sreg, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
#ifndef IA32_SEG 
	return laddr_read(vaddr, len); 
#else 
	uint32_t laddr = vaddr; 
	if(cpu.cr0.pe==1) { 
		laddr = segment_translate(vaddr, sreg); 
	} 
	//printf("varrd_read-> vaddr:%x\nladdr_read->laddr:%x\n",vaddr,laddr);
	return laddr_read(laddr, len); 
#endif
}

void vaddr_write(vaddr_t vaddr, uint8_t sreg, size_t len, uint32_t data) {
	assert(len == 1 || len == 2 || len == 4);
#ifndef IA32_SEG 
	laddr_write(vaddr, len, data);
#else
	if(cpu.cr0.pe==1){
		//protect 
		//load and change
		vaddr=segment_translate(vaddr,sreg);
	}
	laddr_write(vaddr, len, data);
#endif
}

void init_mem() {
	// clear the memory on initiation
	memset(hw_mem, 0, MEM_SIZE_B);
#ifdef CACHE_ENABLED
	init_cache();
#endif

#ifdef TLB_ENABLED
	make_all_tlb();
	init_all_tlb();
#endif
}

uint32_t instr_fetch(vaddr_t vaddr, size_t len) {
	assert(len == 1 || len == 2 || len == 4);
	return vaddr_read(vaddr, SREG_CS, len);
}

uint8_t * get_mem_addr() {
	return hw_mem;
}
