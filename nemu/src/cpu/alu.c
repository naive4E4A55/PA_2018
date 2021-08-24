#include "cpu/cpu.h"
#include <stddef.h>
int test_bit(int dest,int src)
{
	dest<<=(32-src);
	if((int)dest<0)
		return 1;
	else return 0;
}
int set_PF(uint32_t j)
{
	j<<=24;
	int i=1;
	for(;;)
	{
		if((int)j<0)
			i++;
		else if(j==0)
			break;
		j<<=1;
	}
	return (i%2);
}
uint32_t alu_add(uint32_t src, uint32_t dest) {
	//printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	//assert(0);
	uint32_t adc;
	adc=src+dest;
	if((unsigned)adc<(unsigned)src||(unsigned)adc<(unsigned)dest)
		cpu.eflags.CF=1;
	else cpu.eflags.CF=0;
	if(adc==0)
		cpu.eflags.ZF=1;
	else cpu.eflags.ZF=0;
	if((int)adc>0&&(int)src<0&&(int)(dest)<0)
		cpu.eflags.OF=1;
	else if((int)adc<0&&(int)src>0&&(int)dest>0)
		cpu.eflags.OF=1;
	else cpu.eflags.OF=0;
	if((int)adc<0)
		cpu.eflags.SF=1;
	else cpu.eflags.SF=0;
	int i=1;
	uint32_t j=adc;
	j<<=24;
	for(;;)
	{
		if((int)j<0)
			i++;
		else if(j==0)
			break;
		j<<=1;
	}
	cpu.eflags.PF=(i%2);
	return adc;
}

uint32_t alu_adc(uint32_t src, uint32_t dest) {
	//printf("\e[0;31mPlease adc implement me at alu.c\e[0m\n");
	//assert(0);
	int adc=src+dest+cpu.eflags.CF;//can be proved 
	int src_bit=test_bit(src,32);
	int dest_bit=test_bit(dest,32);
	int adc_bit=test_bit(adc,32);
	if(src_bit==dest_bit&&src_bit!=adc_bit)//set OF
		cpu.eflags.OF=1;
	else cpu.eflags.OF=0;  
	if((src==0xffffffff||dest==0xffffffff)&&cpu.eflags.CF==1) //set CF
		cpu.eflags.CF=1;
	else if((unsigned)adc<(unsigned)src||(unsigned)adc<(unsigned)dest)
		cpu.eflags.CF=1;
	else cpu.eflags.CF=0;
	if((int)adc<0)		//set SF
		cpu.eflags.SF=1;
	else cpu.eflags.SF=0;
	//if(adc==0)		//set ZF
	//	cpu.eflags.ZF=1;
	//else cpu.eflags.ZF=0;
	cpu.eflags.ZF=!(adc&&1);
	int i=set_PF((uint32_t)adc);
	cpu.eflags.PF=i;
	return adc;
}


uint32_t alu_sub(uint32_t src, uint32_t dest) {
	//printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	//assert(0);
	//dest-src;
	//OF CF PF SF ZF
	uint32_t oSrc=~src;
	uint32_t cout=0;
	if(src==0)
		cout=1;
	uint32_t res1=oSrc+dest;
	if((test_bit(oSrc,32)==test_bit(dest,32))&&(test_bit(oSrc,32)!=test_bit(res1+1,32)))//set OF
		cpu.eflags.OF=1;
	else cpu.eflags.OF=0;
	oSrc++;
	uint32_t res=res1+1;
	if((uint32_t)res<(uint32_t)oSrc||(uint32_t)res<(uint32_t)dest) //set CF
		cout++;
	cpu.eflags.CF=(uint32_t)!(cout&&1);
	uint32_t PF=set_PF(res);//set PF
	cpu.eflags.PF=PF;
	if((int)res<0)
		cpu.eflags.SF=1;
	else cpu.eflags.SF=0;
	cpu.eflags.ZF=(uint32_t)!(res&&1);
	return res;
}

uint32_t alu_sbb(uint32_t src, uint32_t dest) {
	//printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	//assert(0);
	uint32_t cSrc=src+cpu.eflags.CF;
	uint32_t ocSrc=~cSrc;
	uint32_t cout=0;
	if(src==0xFFFFFFFF&&cpu.eflags.CF==1)
		cout=0;
	else if(cSrc==0)
		cout=1;
	uint32_t res1=ocSrc+dest;
	if(test_bit(dest,32)==test_bit(res1,32)&&test_bit(dest,32)!=test_bit(res1,32))//set OF
		cpu.eflags.OF=1;
	else cpu.eflags.OF=0;
	uint32_t res=dest-src-cpu.eflags.CF;					      //set CF
	ocSrc++;
	if((uint32_t)res<(uint32_t)ocSrc||(uint32_t)res<(uint32_t)dest)
		cout++;
	cpu.eflags.CF=(uint32_t)!(cout&&1);
	uint32_t PF=set_PF(res);
	cpu.eflags.PF=PF;
	if((int)res<0)
		cpu.eflags.SF=1;
	else cpu.eflags.SF=0;
	cpu.eflags.ZF=(uint32_t)!(res&&1);
	return res;
}


uint64_t alu_mul(uint32_t src, uint32_t dest, size_t data_size) {
	//printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	//assert(0);
	//cpu.eflags.OF=cpu.eflags.CF=cpu.eflags.ZF=cpu.eflags.SF=cpu.eflags.PF=0;
	/*uint32_t nSrc,nDest;
	nSrc=(((uint32_t)(src<<(32-(int)data_size)))>>(32-(int)data_size));
	nDest=(((uint32_t)(dest<<(32-(int)data_size)))>>(32-(int)data_size));
	uint64_t res=(uint64_t)nSrc*nDest;
	uint32_t hRax=(uint64_t)res>>32;
	if(hRax!=0)
		cpu.eflags.OF=cpu.eflags.CF=1;
	else cpu.eflags.OF=cpu.eflags.CF=0;
	if(res==0)
		cpu.eflags.ZF=1;
	else cpu.eflags.ZF=0;
	uint32_t lRax=(uint32_t)((res<<32)>>32);
	uint32_t PF=set_PF(lRax);
	cpu.eflags.PF=PF;
	uint32_t sign=res&0x8000000000000000;
	if(sign==0x8000000000000000)
		cpu.eflags.SF=1;
	else cpu.eflags.SF=0;
	return res;*/
//	uint32_t nSrc,nDest;
	uint64_t res;
	if(data_size==32)
	{
		res=(uint64_t)src*dest;
		uint32_t hRax=(res>>32);
		if(hRax!=0)
			cpu.eflags.OF=cpu.eflags.CF=1;
		else cpu.eflags.OF=cpu.eflags.CF=0;
		if(res==0)
			cpu.eflags.ZF=1;
		else cpu.eflags.ZF=0;
		uint32_t lRax=(uint32_t)((res<<32)>>32);
		cpu.eflags.PF=set_PF(lRax);
		if((int)hRax<0)
			cpu.eflags.SF=1;
		else cpu.eflags.SF=0;
		return res;
	}
	else if(data_size==16)
	{
		uint32_t lSrc,lDest;
		lSrc=(uint32_t)((uint32_t)(src<<16)>>16);
		lDest=(uint32_t)((uint32_t)(dest<<16)>>16);
		res=(uint64_t)lSrc*lDest;
		uint32_t lRax=lSrc*lDest;
		uint32_t nlRax=((uint32_t)(lRax<<16)>>16);
		if(lRax==nlRax)
			cpu.eflags.CF=cpu.eflags.OF=0;
		else cpu.eflags.CF=cpu.eflags.OF=1;
		if(res==0)
			cpu.eflags.ZF=1;
		else cpu.eflags.ZF=0;
		cpu.eflags.PF=set_PF(lRax);
		cpu.eflags.SF=test_bit(lRax,32);
		return (uint64_t)lRax;
	}
	else
	{
		uint32_t bSrc,bDest;
		bSrc=(uint32_t)((uint32_t)(src<<24)>>24);
		bDest=(uint32_t)((uint32_t)(dest<<24)>>24);
		res=(uint64_t)bSrc*bDest;
		uint32_t lRax=bSrc*bDest;
		uint32_t nlRax=(lRax>>8);
		if(nlRax==0)
			cpu.eflags.CF=cpu.eflags.OF=0;
		else cpu.eflags.CF=cpu.eflags.OF=1;
		if(res==0)
			cpu.eflags.ZF=1;
		else cpu.eflags.ZF=0;
		cpu.eflags.PF=set_PF(lRax);
		cpu.eflags.SF=test_bit(lRax,16);
		return res;
	}
	return 0;
}

int64_t alu_imul(int32_t src, int32_t dest, size_t data_size) {
	//printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	//assert(0);
	int64_t res=(int64_t)src*dest;
	return res;
}

uint32_t alu_div(uint64_t src, uint64_t dest, size_t data_size) {
	//printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	//assert(0);
	uint32_t res=dest/src;
	return res;
}

int32_t alu_idiv(int64_t src, int64_t dest, size_t data_size) {
	//printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	//assert(0);
	uint64_t res=dest/src;
	return (uint32_t)res;
}

uint32_t alu_mod(uint64_t src, uint64_t dest) {
	//printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	//assert(0);
	uint64_t res=dest%src;
	return (uint32_t)res;
}

int32_t alu_imod(int64_t src, int64_t dest) {
	//printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	//assert(0);
	//uint32_t res=dest%src;
	return dest%src;
}

uint32_t alu_and(uint32_t src, uint32_t dest) {
	//printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	//assert(0);
	cpu.eflags.OF=cpu.eflags.CF=0;
	uint32_t res=src&dest;
	if(res==0)
		cpu.eflags.ZF=1;
	else cpu.eflags.ZF=0;
	if((int)res<0)
		cpu.eflags.SF=1;
	else cpu.eflags.SF=0;
	uint32_t PF=set_PF(res);
	cpu.eflags.PF=PF;
	return res;
}

uint32_t alu_xor(uint32_t src, uint32_t dest) {
	//printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	//assert(0);
	cpu.eflags.CF=cpu.eflags.OF=0;
	uint32_t res=src^dest;
	if(res==0)
		cpu.eflags.ZF=1;
	else cpu.eflags.ZF=0;
	if((int)res<0)
		cpu.eflags.SF=1;
	else cpu.eflags.SF=0;
	uint32_t PF=set_PF(res);
	cpu.eflags.PF=PF;
	return res;
}

uint32_t alu_or(uint32_t src, uint32_t dest) {
	//printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	//assert(0);
	cpu.eflags.CF=cpu.eflags.OF=0;
	uint32_t res=src|dest;
	if(res==0)
		cpu.eflags.ZF=1;
	else cpu.eflags.ZF=0;
	if((int)res<0)
		cpu.eflags.SF=1;
	else cpu.eflags.SF=0;
	uint32_t PF=set_PF(res);
	cpu.eflags.PF=PF;
	return res;
}

uint32_t alu_shl(uint32_t src, uint32_t dest, size_t data_size) {
	//printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	//assert(0);
	uint32_t lDest=((uint32_t)dest<<(32-(int)data_size))>>(32-(int)data_size);
	if(src!=0)
	{
		lDest<<=(int)(src-1);
		if(test_bit((int)lDest,(int)data_size)==1)
			cpu.eflags.CF=1;
		else cpu.eflags.CF=0;
		lDest<<=1;
	}
	lDest=((uint32_t)lDest<<(32-(int)data_size))>>(32-(int)data_size);
	if(lDest==0)
		cpu.eflags.ZF=1;
	else cpu.eflags.ZF=0;
	if((test_bit((int)lDest,(int)data_size)==1))
		cpu.eflags.SF=1;
	else cpu.eflags.SF=0;
	uint32_t hDest;
	if(data_size!=32)
		hDest=(((uint32_t)dest>>((int)data_size))<<(int)data_size);
	else hDest=0;
	uint32_t res=hDest+lDest;
	uint32_t PF=set_PF(res);
	cpu.eflags.PF=PF;
	return res;
}

uint32_t alu_shr(uint32_t src, uint32_t dest, size_t data_size) {
	//printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	//assert(0);
	uint32_t lDest=((uint32_t)dest<<(32-(int)data_size))>>(32-(int)data_size);
	if(src!=0)
	{
		lDest>>=(int)(src-1);
		if(test_bit((int)lDest,1)==1)
			cpu.eflags.CF=1;
		else cpu.eflags.CF=0;
		lDest>>=1;
	}
	if(lDest==0)
		cpu.eflags.ZF=1;
	else cpu.eflags.ZF=0;
	if((test_bit((int)lDest,(int)data_size)==1))
		cpu.eflags.SF=1;
	else cpu.eflags.SF=0;
	uint32_t hDest;
	if(data_size!=32)
		hDest=(((uint32_t)dest>>((int)data_size))<<(int)data_size);
	else hDest=0;
	uint32_t res=hDest+lDest;
	uint32_t PF=set_PF(res);
	cpu.eflags.PF=PF;
	return res;

}

uint32_t alu_sar(uint32_t src, uint32_t dest, size_t data_size) {
	//printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	//assert(0);
	int lDest=((int)(dest<<(32-(int)data_size))>>(32-(int)data_size));
	if(src!=0)
	{
		lDest>>=(int)(src-1);
		if(test_bit((int)lDest,1)==1)
			cpu.eflags.CF=1;
		else cpu.eflags.CF=0;
		lDest>>=1;
		
	}
	if(test_bit((int)lDest,(int)data_size)==1)
		cpu.eflags.SF=1;
	else cpu.eflags.SF=0;
	if(lDest==0)
		cpu.eflags.ZF=1;
	else cpu.eflags.ZF=0;
	uint32_t nlDest=(uint32_t)((uint32_t)((uint32_t)lDest<<(32-(int)data_size))>>(32-(int)data_size));
       	uint32_t hDest=0;
	if(data_size!=32)
		hDest=((uint32_t)((uint32_t)dest>>((int)data_size))<<(int)data_size);
	uint32_t res=hDest+nlDest;
	uint32_t PF=set_PF(res);
	cpu.eflags.PF=PF;
	return res;
}

uint32_t alu_sal(uint32_t src, uint32_t dest, size_t data_size) {
	//printf("\e[0;31mPlease implement me at alu.c\e[0m\n");
	//assert(0);
	//set ZF CF SF PF
	//cpu.eflags.PF=PF;
	//return res;
	uint32_t lDest=((uint32_t)dest<<(32-(int)data_size))>>(32-(int)data_size);
	if(src!=0)
	{
		lDest<<=(int)(src-1);
		if(test_bit((int)lDest,(int)data_size)==1)
			cpu.eflags.CF=1;
		else cpu.eflags.CF=0;
		lDest<<=1;
	}
	lDest=((uint32_t)lDest<<(32-(int)data_size))>>(32-(int)data_size);
	if(lDest==0)
		cpu.eflags.ZF=1;
	else cpu.eflags.ZF=0;
	if((test_bit((int)lDest,(int)data_size)==1))
		cpu.eflags.SF=1;
	else cpu.eflags.SF=0;
	uint32_t hDest;
	if(data_size!=32)
		hDest=(((uint32_t)dest>>((int)data_size))<<(int)data_size);
	else hDest=0;
	uint32_t res=hDest+lDest;
	uint32_t PF=set_PF(res);
	cpu.eflags.PF=PF;
	return res;

}
