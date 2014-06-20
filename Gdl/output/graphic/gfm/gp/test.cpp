
#include "gdl.h"

extern clDeep ** star;
#define starFrmNb 20

u32 doBlitSpeedTest(void)
{	int*pos = (int*)malloc(10240);
	u32 totaltick=0, tickNbr, nb, c, n;
	
	for(c=0;c<4;c++)
	{	for(n=0;n<128;n++)
		{	pos[n]=		(rand()%380)-30;
			pos[n+128]=	(rand()%300)-30;
			pos[n+256]=	(rand()%starFrmNb);
		};
		nb=64;
		tickNbr = GetTickCount();
		while(nb--)
		{	drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
			drawGfm(star[pos[nb+256]],pos[nb],pos[nb+128]);
		};
	
		tickNbr = GetTickCount()-tickNbr;
		totaltick += tickNbr;
	};
	totaltick >>= 2;
	free(pos);
	//sprintf(blitspeed,"draw %i star in %i ticks",64*96,tickNbr);
	//blitspeedsz = strlen(blitspeed);
	return totaltick;
}

	void screenTest(void)
	{	saveBlitLimit();
		fullBlitLimit();
		clrScr(0);
		mkprints(84,100,".. please wait ..");
		mkprints(70,120,"test blit & lcd speed");
		mkprints(102,130," . %i mhz .",currentFrequency);
		Gdl_flip();
		clrScr(0);
		mkprints(84,100,".. please wait ..");
		mkprints(70,120,"test blit & lcd speed");
		mkprints(102,130," . %i mhz .",currentFrequency);
		Gdl_flip();

		u32 time = GetTickCount();
		u32 nb=64;
		
		while(nb--)
			{ while ((rLCDCON1 >> 18) !=   1) asm volatile("nop\n""nop\n""nop\n");
			  while ((rLCDCON1 >> 18) != 319) asm volatile("nop\n""nop\n""nop\n");
			  while ((rLCDCON1 >> 18) !=   1) asm volatile("nop\n""nop\n""nop\n");
			  while ((rLCDCON1 >> 18) != 319) asm volatile("nop\n""nop\n""nop\n");
			};
			
		tick = GetTickCount();
		time = tick - time;

		u32 frmDelay = time>>=7;
		shell.print("\n frmDellay %i\nfps %i",frmDelay,1000/frmDelay);
		Gdl_flip(); Gdl_flip();
		u32 tme = doBlitSpeedTest();

		u32 maxBlitPerFrm = (96*64*frmDelay)/tme;
		shell.print("\n maxBlit %i",maxBlitPerFrm);
		//Gdl_showMsg("%iMhz, %ifps (%ims), maxBlt %i",currentFrequency,1000/frmDelay,frmDelay,maxBlitPerFrm);
		clrScr(0);
		mkprints(10,230,"%iMhz, %ifps (%ims), maxBlt %i",currentFrequency,1000/frmDelay,frmDelay,maxBlitPerFrm);
		 Gdl_flip(); clrScr(0);
		mkprints(10,230,"%iMhz, %ifps (%ims), maxBlt %i",currentFrequency,1000/frmDelay,frmDelay,maxBlitPerFrm);
		 Gdl_flip();
		//gp_drawString(10,230,blitspeedsz,blitspeed,color,pixel);
		loadBlitLimit();
	}
