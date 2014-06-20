
#include "gdl.h"

#ifdef GP32
	
 /*** CPU SPEED ***/
	
	u32 CLKDIV=0x25003,MCLK=33750000,CLKMODE=0,HCLK=MCLK,PCLK=MCLK;
	
	u32 gp_getPCLK(void) { return PCLK; }
	u32 gp_getHCLK(void) { return HCLK; }	
	
	extern void inikey(void);
			
	void gpSetCpuSpeed(u32 frequency)
	{   switch(frequency)
		{	case 166: { CLKDIV=0x4B011; MCLK=166000000; CLKMODE=3; break;}
			case 164: { CLKDIV=0x4a011; MCLK=164000000; CLKMODE=3; break;}
			case 160: { CLKDIV=0x48011; MCLK=160000000; CLKMODE=3; break;}
			case 156: { CLKDIV=0x2c001; MCLK=156000000; CLKMODE=3; break;}
			case 144: { CLKDIV=0x28001; MCLK=144000000; CLKMODE=3; break;}
			case 133: { CLKDIV=0x3a011; MCLK=132000000; CLKMODE=2; break;}
			case 100: { CLKDIV=0x2b011; MCLK=102000000; CLKMODE=0; break;}
			case  66: { CLKDIV=0x25002; MCLK= 67500000; CLKMODE=0; break;}
			case  50: { CLKDIV=0x2a012; MCLK= 50000000; CLKMODE=0; break;}
			case  40: { CLKDIV=0x48013; MCLK= 40000000; CLKMODE=0; break;}
			case  33: { CLKDIV=0x25003; MCLK= 33750000; CLKMODE=0; break;}
			case  22: { CLKDIV=0x33023; MCLK= 22125000; CLKMODE=0; break;}
		};
		
	   switch(CLKMODE)
		{	case 0 : HCLK=MCLK;	PCLK=MCLK;		break;
			case 1 : HCLK=MCLK;	PCLK=MCLK>>1;	break;
			case 2 : HCLK=MCLK>>1;	PCLK=MCLK>>1;	break;
			case 3 : HCLK=MCLK>>1;	PCLK=MCLK>>2;	break;
		};
		
		gp_setCpu(MCLK,CLKDIV,CLKMODE);
		inikey();
		currentFrequency = frequency;
	}
 /*** RESET ***/
 
	void gpReset(void)
	{  gpSetCpuSpeed(66);
	   asm volatile("swi #4\n");
	}

 /*** REAL TIME CLOCK ***/

	u32 rGLOBALCOUNTER;
	
	static void RTCInt(void) __attribute__ ((interrupt ("IRQ")));
	static void RTCInt() { rGLOBALCOUNTER++; }
	
	u32 gp_getRTC(void) { return rGLOBALCOUNTER; }
	
	void gp_initRTC()
	{	static u8 init=0;
		if(init) return;
		rCLKCON |= 0x800;
		rTICINT = 0x81;
		rGLOBALCOUNTER = 0;
		gp_disableIRQ();
		gp_installSWIIRQ(8,(void*)RTCInt);
		gp_enableIRQ();
		init=1;
	}
	
	void gp_clearRTC() {
	   rGLOBALCOUNTER=0;
	}

#endif

