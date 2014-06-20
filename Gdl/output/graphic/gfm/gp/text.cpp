#ifndef _gdlTxt_
#define _gdlTxt_

#include "Gdl.h"

char dbg[256];	// a buffer for the debug string
clDeep ** gdlfont = 0 ;

void drawText(const char *txt,int x, int y, int align, clDeep **font, int start, int max)
{ if(!txt)  return ;
  if(!font) font = gdlfont;
	const char *p = txt ;
	while(*p++ && txt-p<32); p-=2; // count string size, max is 32
	while(*p == 0x20) p--;	// remove space at end..
	p++; int sz=p-txt;
    #ifdef use16b
     int sx = (*font)[0];
    #else
     int sx = ((*font)[2])>>16;
    #endif
    int way=1;
  if(max) if(sz>max) sz=max ;
  if(align) { x-=sz*sx ; way=-1 ; } p=txt ;
  while(x<-sx && sz) { x+=sx ; p++ ; sz-- ; };
  while(sz--){ if(*p>=start && *p<123) drawGfm(font[(*p++) - start],x,y) ; else p++; x+=sx ;
               if(x > (int)WIDTH) return ;
             };
}

void drawText(const char *txt,int x, int y)
{	drawText(txt,x,y,0,gdlfont,' ',0);
}

void setGdlfont(clDeep ** font)
{	gdlfont = font ;
}

void setGdlfont(clDeep ** font, u32 frmNb)
{	unCrunchGfm(font,frmNb);
	gdlfont = font ;
}

clDeep ** getGdlfont(void)
{	return gdlfont ;
}

#include <stdarg.h>
/*
void prints(int x,int y,const char * format, ...) // a screen printf
{	if(!gdlfont) return ;
		va_list va; va_start(va,format); vsprintf(dbg,format,va); va_end(va);
	if(x<0 || y<0)
	{	const char *p = dbg ;
		while(*p++); p--;// count string size
		int size = p-dbg; if(!size) return ;
		int fsx,fsy; getGfmSize(&fsx,&fsy,*gdlfont);
		if(x<0) x = (WIDTH - (size*fsx))>>1;
		if(y<0) y = (HEIGHT - fsy)>>1;
	}
		drawText(dbg,x,y,0,gdlfont,' ',0);
}*/

#include "./gfx/gp_8x8font.h"
clDeep currentTextColor = 0xffff;
clDeep currentBgColor = pc2gpColor(0xc9f110);
clDeep consoleColors[10] = { 0x4232,0xffff,0xf52a,0,0,0,0,0,0,0 };

// very optimised and more powerfull mirko font system
void drawChar(u32 xx,u32 yy,u32 offset, clDeep color)
{	u32 x=8, y=8;
	clDeep * scr = xy2scr(xx,yy);
	clDeep * s;
	u8 * chr = (u8*)&font8x8[offset*8];
	u8 * px;
    do	{	y=8;
			s = scr;
			px = chr;
			do	{	if(!*px) *s = color;
					px += 1024;
					s--;
				} while(--y);
			scr += 240;
			chr++;
		} while(--x);
}

void drawString(u32 x,u32 y,char *string)
{    while(*string && x < 311)
      {	if(*string == '@') // color definition
		{	if(*++string == 0) return;
			if(*string >= '0' && *string <= '9') // text color
				currentTextColor = consoleColors[(*string)-'0'];
			else if(*string == '@') // bg color
					{	if(*++string == 0) return;
						if(*string >= '0' && *string <= '9')
						currentBgColor = consoleColors[(*string)-'0'];
					}
			
			if(*++string == 0) return;
		}
	    if (*string<=126 ) drawChar(x,y,*string,currentTextColor);
		x+=8; string++;
      };
}

void mkprints(u32 x, u32 y, const char * format, ...)
{		va_list va;
		va_start(va, format);
		vsprintf(dbg,format,va);
		va_end(va);
		drawString(x,y,dbg);
}

/*
void ldrawText(const char *txt,int x, int y, int align, int **font,int max=0)
{ const char *p = txt ; while(*p++); p-=2; while(*p == 0x20) p--; p++; int sz=p-txt, sx=((*font)[2])>>16, way=1 ;
  if(max) if(sz>max) sz=max ;
  if(align) { x-=sz*sx ; way=-1 ; } p=txt ;
  int c=0 ; while(x<-sx && sz) { x+=sx ; p++ ; sz-- ; };
  while(sz--){  int lt = *p ; if(!lt) return ;
				if(lt >= 'A' && lt <= 'Z') { lt-='A'; lt+='a'; } // down to a-z if need
				if(lt != ' ' && ((lt >= 'a' && lt <= 'z')||(lt >= '0' && lt <= '9')||lt=='\''||lt=='.'||lt=='-') )
					{			if(lt>='a')		drawGfm(font[lt-'a'],x,y);
						else	if(lt == '\'')	drawGfm(font[26+10],x,y);
						else	if(lt == '.')	drawGfm(font[26+11],x,y);
						else	if(lt == '-')	drawGfm(font[26+12],x,y);
						else					drawGfm(font[lt-'0'+26],x,y);
					}
				x+=sx ; p++;
                if(x > 320) return ;
             };
}*/

void drawInt(int n, int x, int y, const char *method, int align, clDeep **font, int start)
{ char t[16] ; sprintf(t,method,n); drawText(t,x,y,align,font,start);
}

#endif
