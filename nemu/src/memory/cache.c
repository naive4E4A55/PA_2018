#include "memory/cache.h"
#include "nemu.h"
#include "cpu/cpu.h"
#include "memory/memory.h"
#include "device/mm_io.h"
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
struct CacheLine Cache[128][8];
extern uint8_t hw_mem[MEM_SIZE_B];
extern uint32_t hw_mem_read(paddr_t paddr,size_t len);
extern void hw_mem_write(paddr_t paddr,size_t len,uint32_t data);
void init_cache(){
	//fresh Cache
	for(int i=0;i<128;i++){
		for(int j=0;j<8;j++){
			Cache[i][j].valid_bit=0;
		}
	}
}


uint32_t cache_read(paddr_t paddr, size_t len){
	uint32_t tlb0=(paddr&0xFFFFE000)>>13;
	uint32_t group0=(paddr&0x00001FC0)>>6;
	uint32_t tail0=paddr&0x0000003F;
	if(len==1){
		bool hit=0;
		int i=0;
		for(;i<8;i++){
			//I am a ZZZZZZZZZZ
			if(Cache[group0][i].valid_bit==1&&Cache[group0][i].tlb==tlb0){
				hit=1;
				break;
			}
		}
		if(hit==1){
			//uint8_t data_8=(data&0x000000FF);
			uint32_t myRes=0;
			myRes=Cache[group0][i].block[tail0];
			//printf("read:0x%x\n",myRes);
			return myRes;
		}
		else{
			int i=0;
			for(;i<8;i++){
				if(Cache[group0][i].valid_bit==0){
					break;
				}
			}
			if(i!=8){
				//read and not write through
				memcpy((uint8_t*)Cache[group0][i].block,(uint8_t*)(hw_mem+(paddr&0xFFFFFFC0)),64);
				Cache[group0][i].tlb=tlb0;
				Cache[group0][i].valid_bit=1;
				uint32_t myRes=0;
				myRes=Cache[group0][i].block[tail0];
				//printf("read:0x%x\n",myRes);
				return myRes;
			}
			else{
				//write through and read
				//write through
				i=rand()%8;
				uint32_t write_addr=(Cache[group0][i].tlb<<13)+(group0<<6);
				memcpy((uint8_t*)(write_addr+hw_mem),(uint8_t*)Cache[group0][i].block,64);
				//read
				memcpy((uint8_t*)Cache[group0][i].block,(uint8_t*)(hw_mem+(paddr&0xFFFFFFC0)),64);
				Cache[group0][i].tlb=tlb0;
				Cache[group0][i].valid_bit=1;
				uint32_t myRes=0;
				myRes=Cache[group0][i].block[tail0];
				//printf("read:0x%x\n",myRes);
				return myRes;
			}
		}
	}
	else if(len==2){
		uint32_t dataH=0;
		dataH=cache_read(paddr+1,1);
		dataH=dataH<<8;
		uint32_t dataL=0;
		dataL=cache_read(paddr,1);
		uint32_t myRes=0;
		myRes=dataH+dataL;
		//printf("read:0x%x\n",myRes);
		return myRes;
	}
	else if(len==4){
		uint32_t data3=0;
		data3=cache_read(paddr+3,1);
		data3=data3<<24;
		uint32_t data2=0;
		data2=cache_read(paddr+2,1);
		data2=data2<<16;
		uint32_t data1=0;
		data1=cache_read(paddr+1,1);
		data1=data1<<8;
		uint32_t data0=0;
		data0=cache_read(paddr,1);		
		uint32_t myRes=data3+data2+data1+data0;
		//printf("read:0x%x\n",myRes);
		return myRes;
	}
	else{
		assert(0);
	}
}


void cache_write(paddr_t paddr, size_t len, uint32_t data){
	uint32_t tlb0=(paddr&0xFFFFE000)>>13;
	uint32_t group0=(paddr&0x00001FC0)>>6;
	uint32_t tail0=paddr&0x0000003F;
	//printf("write:0x%x\n",data);
	if(len==1){
		bool hit=0;
		int i=0;
		for(;i<8;i++){
			if(Cache[group0][i].valid_bit==1&&Cache[group0][i].tlb==tlb0){
				hit=1;
				break;
			}
		}
		if(hit==1){
			uint8_t data_8=(data&0x000000FF);
			Cache[group0][i].block[tail0]=data_8;
			//printf("need_write:0x%x\t",data_8);
			//printf("write:0x%x\n",Cache[group0][i].block[tail0]);
			return ;
		}
		else{
			int i=0;
			for(;i<8;i++){
				if(Cache[group0][i].valid_bit==0){
					break;
				}
			}
			if(i!=8){
				//read and not write through
				memcpy((uint8_t*)Cache[group0][i].block,(uint8_t*)(hw_mem+(paddr&0xFFFFFFC0)),64);
				Cache[group0][i].tlb=tlb0;
				Cache[group0][i].valid_bit=1;
				uint8_t data_8=(data&0x000000FF);
				//printf("need_write:0x%x\t",data_8);
				Cache[group0][i].block[tail0]=data_8;
				//printf("write:0x%x\n",Cache[group0][i].block[tail0]);
				return;
			}
			else{
				//write through and read
				//write through
				i=rand()%8;
				uint32_t write_addr=(Cache[group0][i].tlb<<13)+(group0<<6);
				memcpy((uint8_t*)(write_addr+hw_mem),(uint8_t*)Cache[group0][i].block,64);
				//read
				memcpy((uint8_t*)Cache[group0][i].block,(uint8_t*)(hw_mem+(paddr&0xFFFFFFC0)),64);
				Cache[group0][i].tlb=tlb0;
				Cache[group0][i].valid_bit=1;
				uint8_t data_8=(data&0x000000FF);
				//printf("need_write:0x%x\t",data_8);
				Cache[group0][i].block[tail0]=data_8;
				//printf("write:0x%x\n",Cache[group0][i].block[tail0]);
				return;
			}
		}
	}
	else if(len==2){
		uint32_t dataH=data&0x0000FF00;
		dataH=dataH>>8;
		uint32_t dataL=data&0x000000FF;
		cache_write(paddr,1,dataH);
		cache_write(paddr+1,1,dataL);
		return ;
	}
	else if(len==4){
		uint32_t data3=data&0xFF000000;
		data3=data3>>24;
		uint32_t data2=data&0x00FF0000;
		data2=data2>>16;
		uint32_t data1=data&0x0000FF00;
		data1=data1>>8;
		uint32_t data0=data&0x000000FF;
		//printf("len4 write:0x%x\n",data);
		//printf("len0 write:0x%x\n",data0);
		//printf("len1 write:0x%x\n",data1);
		//printf("len2 write:0x%x\n",data2);
		//printf("len3 write:0x%x\n",data3);
		cache_write(paddr,1,data0);
		cache_write(paddr+1,1,data1);
		cache_write(paddr+2,1,data2);
		cache_write(paddr+3,1,data3);
		//uint32_t write_res=cache_read(paddr,len);
		return ;
	}
}




/*uint32_t cache_read(paddr_t paddr, size_t len, CacheLine * cache){
	uint16_t mark0=((paddr>>16)&&0x0000FFFF);
	uint16_t mark3=(((paddr+len-1)>>16)&&0x0000FFFF);
	//if paddr~paddr+len-1 at the same CacheLine
	//else read other

	//paddr_head
	uint32_t group0=paddr&0x0000FE00;
	uint32_t groupMark0=parrd&0x000001C00;
	uint32_t paddrPail0=parrd&0x0000003F;
	//paddr_pail
	uint32_t group3=paddr&0x0000FE00;
	uint32_t groupMark3=parrd&0x000001FC0;
	uint32_t parrdPail3=parrd&0x0000003F;
	if(group0==group3&&group_mark0==group_mark3){
		//group0==group3&&group_mark0==group_mark3 -> mark0==mark3
		//at the same CacheLine
		//search all cache[group0][0]~cache[group0][7]
		int i=0;
		int exist=0;
		for(;i<8;i++){
			if(cache[group0][i].valid_bit==1&&cache[group0][i].mark==mark&&cache[group0][i].groupMark==groupMark0){
				exist=1;
				break;			
			}
		}
		if(exist==1){
			uint32_t my_res=0;
			if(len==1)
				uint8_t* pmy_res=cache[group0][i].block[parrdPail0];
			if(len==2)
				uint16_t* pmy_res=cache[group0][i].block[parrdPail0];
			if(len==4)
				uint32_t* pmy_res=cache[group0][i].block[parrdPail0];
			my_res=*pmy_res;
			return my_res;
		}
		else{
			//read a cacheLine
			int i=0;
			for(;i<8;i++)
				if(cache[group0][i].valid_bit==0){
					break;
				}
			if(i==8)
				i==rand()%8;
			//write through i
			if(i!=8){
				uint32_t write_mem=(cache[group0][i].mark<<16)+(group0<<9)+(cache[group0][i].groupMark<<6);
			}
		}
	}
}*/
