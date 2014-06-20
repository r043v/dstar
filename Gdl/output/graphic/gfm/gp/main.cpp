
#include "gdl.h"

#include "./gfx/star.h"
#include "./gfx/tile10.h"
#include "./gfx/tile54.h"
#include "./gfx/zeldaTiles.h"
#include "./gfx/zeldaTiles.map.h"
//#include "./gfx/PRZYSTAN.map.h"
//#include "./gfx/PRZYSTAN_Tiles.h"
#include "./gfx/shock.mod.h"

void drawOutZone(outzone*out)
{	/*gp_drawLine16(out->x,out->y,out->x+out->width,out->y,0,pixel);
	gp_drawLine16(out->x,out->y,out->x,out->y+out->height,0,pixel);
	gp_drawLine16(out->x+out->width,out->y,out->x+out->width,out->y+out->height,0,pixel);
	gp_drawLine16(out->x,out->y+out->height,out->x+out->width,out->y+out->height,0,pixel);
*/}

u32 freq=1, freqTable[] = { 22,33,40,50,66,80,133 };

extern void screenTest(void);

extern void drawString(u32 x,u32 y,char *string);

extern u32 gp_resetScreen(void);

extern "C" {	void gp_startSoundmixer(int finetuning);
				void gp_startModfile(unsigned char *mod);
			}

int main()
{	
	
	gp_startSoundmixer(0);
	gp_startModfile(shock);

	while(1);
	Gdl_initGp32(freqTable[freq],85);
	unCrunchGfm(zeldaTiles,zeldaTilesFrmNb);
	unCrunchGfm(tile10,tile10FrmNb);
	unCrunchGfm(tile54,tile54FrmNb);
	unCrunchGfm(star,starFrmNb);

	outzone * out = createOutzone(116,10,200,210);
	outzone * out2= createOutzone(10,10,104,210);

	map myMap, myMap2;	

	myMap.set((u16*)zeldaTilesMap,zeldaTiles,zeldaTilesFrmNb,16,16,80,60,0,0,out,0);
	myMap2.set((u16*)zeldaTilesMap,zeldaTiles,zeldaTilesFrmNb,16,16,80,60,0,0,out2,0);
	myMap2.setScroll(433,296);

	anim * mystar =  setAnim(star,starFrmNb,80);
	anim * t10 = setAnim(tile10,tile10FrmNb,150);
	anim * t54 = setAnim(tile54,tile54FrmNb,320);
	
	myMap.setAnimatedTile(10,t10);
	myMap.setAnimatedTile(54,t54);
	myMap2.setAnimatedTile(10,t10);
	myMap2.setAnimatedTile(54,t54);
	
	u32 xxx=110,yyy=110;
	u32 fps,oldfps=0xffff,old_tick=0;
	char debug[1024];
	
	setBlitLimit(out);
	screenTest();


	 while (1)
		 {	fps = countFps();
			if(fps && (fps != oldfps || tick - old_tick > 1000) )
			{	sprintf(debug,"%i/%ifps . %iMhz . %i",fps,currentFps,freqTable[freq],tick>>10);
				oldfps = fps;
				old_tick = tick;
			}
			
			myMap2.draw90();
			myMap.draw90();
			drawOutZone(out);
			drawOutZone(out2);
			
			static u32 hway=2, wway=8;
			u32 rtn = myMap.scroll(hway|wway,1);
			if(rtn)
			{	if(rtn&1) hway=2;
				if(rtn&2) hway=1;
				if(rtn&4) wway=8;
				if(rtn&8) wway=4;
			}

			static u32 zhway=2, zwway=8;
			rtn = myMap2.scroll(zhway|zwway,1);
			if(rtn)
			{	if(rtn&1) zhway=2;
				if(rtn&2) zhway=1;
				if(rtn&4) zwway=8;
				if(rtn&8) zwway=4;
			}

			playAnim(&mystar,xxx,yyy);
			drawString(120,12,debug);
				
			Gdl_flip();

			if(keyPush(kstart|kselect)) gpReset();
			if(keyUp(kselect)) drawGdlShell ^= 1;

			if(!keyPush(kl))
			{	if(keyPush(kup))		myMap.scroll(1,1);
				if(keyPush(kdown))		myMap.scroll(2,1);
				if(keyPush(kleft))		myMap.scroll(4,1);
				if(keyPush(kright))	myMap.scroll(8,1);
			}	else
				{	if(keyPush(kup))		yyy--;
					if(keyPush(kdown))		yyy++;
					if(keyPush(kleft))		xxx--;
					if(keyPush(kright))	xxx++;
				}
			
			if(keyUp(ka))
			{	if(freqTable[freq] < 133) freq++; else freq = 0;
				gpSetCpuSpeed(freqTable[freq]);
				currentFps = gp_resetScreen();
				shell.print("\n@2* @1%iMhz@0.@1%iHz",currentFrequency,currentFps);
				screenTest();
			}
			
			for(u32 n=1;n<=512;n<<=1) if(keyUp(n)) shell.print("\nbutton %i",n);
		};
}
