#include "common.h"
#include "memory.h"
#include "string.h"

#include <elf.h>
#include <stdlib.h>
#include <stdio.h>

#ifdef HAS_DEVICE_IDE
#define ELF_OFFSET_IN_DISK 0
#endif

#define STACK_SIZE (1 << 20)

void ide_read(uint8_t *, uint32_t, uint32_t);
void create_video_mapping();
uint32_t get_ucr3();

uint32_t loader() {	
	Elf32_Ehdr *elf;
	Elf32_Phdr *ph, *eph;

#ifdef HAS_DEVICE_IDE
	//Log("1\n");
	uint8_t buf[4096];
	ide_read(buf, ELF_OFFSET_IN_DISK, 4096);
	elf = (void*)buf;
	Log("ELF loading from hard disk.");
#else
	elf = (void *)0x0;
	Log("ELF loading from ram disk.");
#endif


	/* Load each program segment */
	ph = (void *)elf + elf->e_phoff;
	eph = ph + elf->e_phnum;	//end_ph
	for(; ph < eph; ph ++) {
		if(ph->p_type == PT_LOAD) {

#ifndef IA32_PAGE
		//pa 2.2
		//panic("Please implement the loader");
		//
		/* TODO: copy the segment from the ELF file to its proper memory area */
		/* TODO: zeror the memory area [vaddr + file_sz, vaddr + mem_sz) */
		memcpy((void*)ph->p_vaddr,(uint8_t*)elf+ph->p_offset,ph->p_filesz);
		memset((void*)(ph->p_vaddr+ph->p_filesz),0,ph->p_memsz-ph->p_filesz);
		//int pzero[100000];//int* pzero=(int*)malloc(4*(ph->p_memsz-ph->p_filesz));//pzero+=1;//pzero-=1;
		//free(pzero);//for(int i=;i<ph->p_memsz-ph->p_filesz;i+=1)//pzero[i]=pzero[i];
		//Log("%d")//memcpy((void*)(ph->p_vaddr+ph->p_filesz),(void*)pzero,ph->p_memsz-ph->p_filesz);
		//memcpy((void*)pzero,(void*)ph->p_vaddr+ph->p_filesz,ph->p_memsz-ph->p_filesz);
#endif

#ifdef IA32_PAGE
		
	#ifdef HAS_DEVICE_IDE
		uint32_t addr=ph->p_vaddr;
		uint32_t paddr=mm_malloc(addr,ph->p_memsz);
		assert(ph->p_filesz<=4096*32);
		uint8_t buf2[4096*32];
		ide_read(buf2,ELF_OFFSET_IN_DISK+ph->p_offset,ph->p_filesz);
		memcpy((void*)(paddr),(void*)(buf2),ph->p_filesz);
		//Log("ph->p_vaddr:%x\npaddr:%x\n",ph->p_vaddr,paddr);
	#else
		//pa 3.3
		uint32_t paddr=mm_malloc(ph->p_vaddr,ph->p_memsz);//mm_malloc 
		//the same with pa2.2
		memcpy((void*)paddr,(uint8_t*)elf+ph->p_offset,ph->p_filesz);
		memset((void*)(paddr+ph->p_filesz),0,ph->p_memsz-ph->p_filesz);
		//Log("ph->p_vaddr:%x\npaddr:%x\n",ph->p_vaddr,paddr);
	#endif
#endif

#ifdef IA32_PAGE
			/* Record the program break for future use */
			extern uint32_t brk;
			uint32_t new_brk = ph->p_vaddr + ph->p_memsz - 1;
			if(brk < new_brk) { brk = new_brk; }
#endif
		}
	}
	volatile uint32_t entry = elf->e_entry;

#ifdef IA32_PAGE
	mm_malloc(KOFFSET - STACK_SIZE, STACK_SIZE);
#ifdef HAS_DEVICE_VGA
	create_video_mapping();
#endif
	write_cr3(get_ucr3());
#endif
	return entry;
}
