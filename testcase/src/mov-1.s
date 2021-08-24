
mov:     file format elf32-i386


Disassembly of section .text:

00060000 <start>:
   60000:	e9 00 00 00 00       	jmp    60005 <main>

00060005 <main>:
   60005:	b8 00 00 00 00       	mov    $0x0,%eax
   6000a:	bb 00 00 00 00       	mov    $0x0,%ebx
   6000f:	b9 00 00 00 00       	mov    $0x0,%ecx
   60014:	ba 00 00 00 00       	mov    $0x0,%edx
   60019:	b9 00 80 00 00       	mov    $0x8000,%ecx
   6001e:	66 bb 00 00          	mov    $0x0,%bx
   60022:	b7 00                	mov    $0x0,%bh
   60024:	c7 05 34 12 00 00 01 	movl   $0x1,0x1234
   6002b:	00 00 00 
   6002e:	66 c7 05 34 12 00 00 	movw   $0x1,0x1234
   60035:	01 00 
   60037:	c6 05 34 12 00 00 01 	movb   $0x1,0x1234
   6003e:	c7 01 01 00 00 00    	movl   $0x1,(%ecx)
   60044:	66 c7 01 01 00       	movw   $0x1,(%ecx)
   60049:	c6 01 01             	movb   $0x1,(%ecx)
   6004c:	c7 04 99 01 00 00 00 	movl   $0x1,(%ecx,%ebx,4)
   60053:	66 c7 04 99 01 00    	movw   $0x1,(%ecx,%ebx,4)
   60059:	c6 04 99 01          	movb   $0x1,(%ecx,%ebx,4)
   6005d:	c7 41 02 01 00 00 00 	movl   $0x1,0x2(%ecx)
   60064:	66 c7 41 02 01 00    	movw   $0x1,0x2(%ecx)
   6006a:	c6 41 02 01          	movb   $0x1,0x2(%ecx)
   6006e:	c7 41 fe 01 00 00 00 	movl   $0x1,-0x2(%ecx)
   60075:	66 c7 41 fe 01 00    	movw   $0x1,-0x2(%ecx)
   6007b:	c6 41 fe 01          	movb   $0x1,-0x2(%ecx)
   6007f:	c7 44 99 02 01 00 00 	movl   $0x1,0x2(%ecx,%ebx,4)
   60086:	00 
   60087:	66 c7 44 99 02 01 00 	movw   $0x1,0x2(%ecx,%ebx,4)
   6008e:	c6 44 99 02 01       	movb   $0x1,0x2(%ecx,%ebx,4)
   60093:	c7 44 99 fe 01 00 00 	movl   $0x1,-0x2(%ecx,%ebx,4)
   6009a:	00 
   6009b:	66 c7 44 99 fe 01 00 	movw   $0x1,-0x2(%ecx,%ebx,4)
   600a2:	c6 44 99 fe 01       	movb   $0x1,-0x2(%ecx,%ebx,4)
   600a7:	c7 81 00 20 00 00 01 	movl   $0x1,0x2000(%ecx)
   600ae:	00 00 00 
   600b1:	66 c7 81 00 20 00 00 	movw   $0x1,0x2000(%ecx)
   600b8:	01 00 
   600ba:	c6 81 00 20 00 00 01 	movb   $0x1,0x2000(%ecx)
   600c1:	c7 81 00 e0 ff ff 01 	movl   $0x1,-0x2000(%ecx)
   600c8:	00 00 00 
   600cb:	66 c7 81 00 e0 ff ff 	movw   $0x1,-0x2000(%ecx)
   600d2:	01 00 
   600d4:	c6 81 00 e0 ff ff 01 	movb   $0x1,-0x2000(%ecx)
   600db:	c7 84 99 00 20 00 00 	movl   $0x1,0x2000(%ecx,%ebx,4)
   600e2:	01 00 00 00 
   600e6:	66 c7 84 99 00 20 00 	movw   $0x1,0x2000(%ecx,%ebx,4)
   600ed:	00 01 00 
   600f0:	c6 84 99 00 20 00 00 	movb   $0x1,0x2000(%ecx,%ebx,4)
   600f7:	01 
   600f8:	c7 84 99 00 e0 ff ff 	movl   $0x1,-0x2000(%ecx,%ebx,4)
   600ff:	01 00 00 00 
   60103:	66 c7 84 99 00 e0 ff 	movw   $0x1,-0x2000(%ecx,%ebx,4)
   6010a:	ff 01 00 
   6010d:	c6 84 99 00 e0 ff ff 	movb   $0x1,-0x2000(%ecx,%ebx,4)
   60114:	01 
   60115:	89 c3                	mov    %eax,%ebx
   60117:	66 89 c3             	mov    %ax,%bx
   6011a:	88 e3                	mov    %ah,%bl
   6011c:	a3 34 12 00 00       	mov    %eax,0x1234
   60121:	66 a3 34 12 00 00    	mov    %ax,0x1234
   60127:	a2 34 12 00 00       	mov    %al,0x1234
   6012c:	88 25 34 12 00 00    	mov    %ah,0x1234
   60132:	89 03                	mov    %eax,(%ebx)
   60134:	89 04 99             	mov    %eax,(%ecx,%ebx,4)
   60137:	66 89 04 99          	mov    %ax,(%ecx,%ebx,4)
   6013b:	88 24 99             	mov    %ah,(%ecx,%ebx,4)
   6013e:	89 41 02             	mov    %eax,0x2(%ecx)
   60141:	66 89 41 02          	mov    %ax,0x2(%ecx)
   60145:	88 61 02             	mov    %ah,0x2(%ecx)
   60148:	89 44 99 02          	mov    %eax,0x2(%ecx,%ebx,4)
   6014c:	66 89 44 99 02       	mov    %ax,0x2(%ecx,%ebx,4)
   60151:	88 64 99 02          	mov    %ah,0x2(%ecx,%ebx,4)
   60155:	89 81 00 20 00 00    	mov    %eax,0x2000(%ecx)
   6015b:	66 89 81 00 20 00 00 	mov    %ax,0x2000(%ecx)
   60162:	88 a1 00 20 00 00    	mov    %ah,0x2000(%ecx)
   60168:	89 84 99 00 20 00 00 	mov    %eax,0x2000(%ecx,%ebx,4)
   6016f:	66 89 84 99 00 20 00 	mov    %ax,0x2000(%ecx,%ebx,4)
   60176:	00 
   60177:	88 a4 99 00 20 00 00 	mov    %ah,0x2000(%ecx,%ebx,4)
   6017e:	89 d3                	mov    %edx,%ebx
   60180:	66 89 d3             	mov    %dx,%bx
   60183:	88 f3                	mov    %dh,%bl
   60185:	89 15 34 12 00 00    	mov    %edx,0x1234
   6018b:	66 89 15 34 12 00 00 	mov    %dx,0x1234
   60192:	88 15 34 12 00 00    	mov    %dl,0x1234
   60198:	88 35 34 12 00 00    	mov    %dh,0x1234
   6019e:	89 13                	mov    %edx,(%ebx)
   601a0:	89 14 99             	mov    %edx,(%ecx,%ebx,4)
   601a3:	66 89 14 99          	mov    %dx,(%ecx,%ebx,4)
   601a7:	88 34 99             	mov    %dh,(%ecx,%ebx,4)
   601aa:	89 51 02             	mov    %edx,0x2(%ecx)
   601ad:	66 89 51 02          	mov    %dx,0x2(%ecx)
   601b1:	88 71 02             	mov    %dh,0x2(%ecx)
   601b4:	89 54 99 02          	mov    %edx,0x2(%ecx,%ebx,4)
   601b8:	66 89 54 99 02       	mov    %dx,0x2(%ecx,%ebx,4)
   601bd:	88 74 99 02          	mov    %dh,0x2(%ecx,%ebx,4)
   601c1:	89 91 00 20 00 00    	mov    %edx,0x2000(%ecx)
   601c7:	66 89 91 00 20 00 00 	mov    %dx,0x2000(%ecx)
   601ce:	88 b1 00 20 00 00    	mov    %dh,0x2000(%ecx)
   601d4:	89 94 99 00 20 00 00 	mov    %edx,0x2000(%ecx,%ebx,4)
   601db:	66 89 94 99 00 20 00 	mov    %dx,0x2000(%ecx,%ebx,4)
   601e2:	00 
   601e3:	88 b4 99 00 20 00 00 	mov    %dh,0x2000(%ecx,%ebx,4)
   601ea:	a1 34 12 00 00       	mov    0x1234,%eax
   601ef:	66 a1 34 12 00 00    	mov    0x1234,%ax
   601f5:	a0 34 12 00 00       	mov    0x1234,%al
   601fa:	8a 25 34 12 00 00    	mov    0x1234,%ah
   60200:	8b 03                	mov    (%ebx),%eax
   60202:	8b 04 99             	mov    (%ecx,%ebx,4),%eax
   60205:	66 8b 04 99          	mov    (%ecx,%ebx,4),%ax
   60209:	8a 24 99             	mov    (%ecx,%ebx,4),%ah
   6020c:	8b 41 02             	mov    0x2(%ecx),%eax
   6020f:	66 8b 41 02          	mov    0x2(%ecx),%ax
   60213:	8a 61 02             	mov    0x2(%ecx),%ah
   60216:	8b 44 99 02          	mov    0x2(%ecx,%ebx,4),%eax
   6021a:	66 8b 44 99 02       	mov    0x2(%ecx,%ebx,4),%ax
   6021f:	8a 64 99 02          	mov    0x2(%ecx,%ebx,4),%ah
   60223:	8b 81 00 20 00 00    	mov    0x2000(%ecx),%eax
   60229:	66 8b 81 00 20 00 00 	mov    0x2000(%ecx),%ax
   60230:	8a a1 00 20 00 00    	mov    0x2000(%ecx),%ah
   60236:	8b 84 99 00 20 00 00 	mov    0x2000(%ecx,%ebx,4),%eax
   6023d:	66 8b 84 99 00 20 00 	mov    0x2000(%ecx,%ebx,4),%ax
   60244:	00 
   60245:	8a a4 99 00 20 00 00 	mov    0x2000(%ecx,%ebx,4),%ah
   6024c:	8b 15 34 12 00 00    	mov    0x1234,%edx
   60252:	66 8b 15 34 12 00 00 	mov    0x1234,%dx
   60259:	8a 15 34 12 00 00    	mov    0x1234,%dl
   6025f:	8a 35 34 12 00 00    	mov    0x1234,%dh
   60265:	8b 13                	mov    (%ebx),%edx
   60267:	8b 14 99             	mov    (%ecx,%ebx,4),%edx
   6026a:	66 8b 14 99          	mov    (%ecx,%ebx,4),%dx
   6026e:	8a 34 99             	mov    (%ecx,%ebx,4),%dh
   60271:	8b 51 02             	mov    0x2(%ecx),%edx
   60274:	66 8b 51 02          	mov    0x2(%ecx),%dx
   60278:	8a 71 02             	mov    0x2(%ecx),%dh
   6027b:	8b 54 99 02          	mov    0x2(%ecx,%ebx,4),%edx
   6027f:	66 8b 54 99 02       	mov    0x2(%ecx,%ebx,4),%dx
   60284:	8a 74 99 02          	mov    0x2(%ecx,%ebx,4),%dh
   60288:	8b 91 00 20 00 00    	mov    0x2000(%ecx),%edx
   6028e:	66 8b 91 00 20 00 00 	mov    0x2000(%ecx),%dx
   60295:	8a b1 00 20 00 00    	mov    0x2000(%ecx),%dh
   6029b:	8b 94 99 00 20 00 00 	mov    0x2000(%ecx,%ebx,4),%edx
   602a2:	66 8b 94 99 00 20 00 	mov    0x2000(%ecx,%ebx,4),%dx
   602a9:	00 
   602aa:	8a b4 99 00 20 00 00 	mov    0x2000(%ecx,%ebx,4),%dh
   602b1:	b8 00 00 00 00       	mov    $0x0,%eax
   602b6:	82                   	.byte 0x82
