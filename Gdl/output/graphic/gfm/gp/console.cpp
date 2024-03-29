
#include "Gdl.h"
#include <stdarg.h>

#define lineSpace 9
extern clDeep currentBgColor;
extern clDeep currentTextColor;

void alphaZone(u32 x, u32 y, u32 sx, u32 sy)
{	clDeep * screen = xy2scr(x,(y+sy));
	//currentBgColor = 0;
	static clDeep lastBgColor = 0;
	static clDeep * bgColorAlpha=0;
	if((currentBgColor != lastBgColor) || !bgColorAlpha)
	{	if(!bgColorAlpha) bgColorAlpha = (clDeep*)malloc(65536*2);
		
		lastBgColor = currentBgColor;
		u32 r,g,b,br,bg,bb,n=0;
		u32 alpha = 64;
		
		br = (currentBgColor>>11)&0x1f;
		bg = (currentBgColor>> 6)&0x1f;
		bb = (currentBgColor>> 1)&0x1f;

//		shell.print("-new bgcolor-\n0x%x\n%i.%i.%i",currentBgColor,br,bg,bb);
		u32 tk = GetTickCount();
		while(n<65536)
		{	r = ((n>>11)&0x1f);
			g = ((n>> 6)&0x1f);
			b = ((n>> 1)&0x1f);//*alpha)>>7))>>1;

			r = (((r<<4)*alpha)>>7)>>4;
			g = (((g<<4)*alpha)>>7)>>4;
			b = (((b<<4)*alpha)>>7)>>4;

			r += br; r>>=1;
			g += bg; g>>=1;
			b += bb; b>>=1;
			
			bgColorAlpha[n++] = (r<<11)|(g<<6)|(b<<1)|0;
		};
		tk = GetTickCount()-tk;
		shell.print("\n%i tick..\n",tk);
	}

	clDeep * s;
	
	while(sx--)
	{	
		s = screen;
		screen += 240;
		u32 n = sy>>5;
		u32 m = sy - (n<<5);
		while(n--)
		{	*s = bgColorAlpha[*s];s++;
				*s = bgColorAlpha[*s];s++;
				*s = bgColorAlpha[*s];s++;
				*s = bgColorAlpha[*s];s++;
			*s = bgColorAlpha[*s];s++;
				*s = bgColorAlpha[*s];s++;
				*s = bgColorAlpha[*s];s++;
				*s = bgColorAlpha[*s];s++;
			*s = bgColorAlpha[*s];s++;
				*s = bgColorAlpha[*s];s++;
				*s = bgColorAlpha[*s];s++;
				*s = bgColorAlpha[*s];s++;
			*s = bgColorAlpha[*s];s++;
				*s = bgColorAlpha[*s];s++;
				*s = bgColorAlpha[*s];s++;
				*s = bgColorAlpha[*s];s++;
			*s = bgColorAlpha[*s];s++;
				*s = bgColorAlpha[*s];s++;
				*s = bgColorAlpha[*s];s++;
				*s = bgColorAlpha[*s];s++;
			*s = bgColorAlpha[*s];s++;
				*s = bgColorAlpha[*s];s++;
				*s = bgColorAlpha[*s];s++;
				*s = bgColorAlpha[*s];s++;
			*s = bgColorAlpha[*s];s++;
				*s = bgColorAlpha[*s];s++;
				*s = bgColorAlpha[*s];s++;
				*s = bgColorAlpha[*s];s++;
			*s = bgColorAlpha[*s];s++;
				*s = bgColorAlpha[*s];s++;
				*s = bgColorAlpha[*s];s++;
				*s = bgColorAlpha[*s];s++;
		};
		if(m >= 16)
		{	*s = bgColorAlpha[*s];s++;
				*s = bgColorAlpha[*s];s++;
				*s = bgColorAlpha[*s];s++;
				*s = bgColorAlpha[*s];s++;
			*s = bgColorAlpha[*s];s++;
				*s = bgColorAlpha[*s];s++;
				*s = bgColorAlpha[*s];s++;
				*s = bgColorAlpha[*s];s++;
			*s = bgColorAlpha[*s];s++;
				*s = bgColorAlpha[*s];s++;
				*s = bgColorAlpha[*s];s++;
				*s = bgColorAlpha[*s];s++;
			*s = bgColorAlpha[*s];s++;
				*s = bgColorAlpha[*s];s++;
				*s = bgColorAlpha[*s];s++;
				*s = bgColorAlpha[*s];s++;
			m -= 16;
		}
		while(m--)
		{	*s = bgColorAlpha[*s]; s++; };
	};
}

//currentBgColor rgb[3];


inline void drawAlphapixel(u32 x, u32 y, u32 alpha, clDeep color)  // alpha: 0..128
{	clDeep * screen = xy2scr(x,y);
	register u32 r,g,b;
    r = ((*screen)>>11)&0x1f;
	g = ((*screen)>> 6)&0x1f;
	b = ((*screen)>> 1)&0x1f;
	r *= alpha; r>>=7;
	g *= alpha; g>>=7;
	b *= alpha; b>>=7;
	
	r += (color>>19)&0x1f;
    g += (color>> 11)&0x1f;
    b += (color>>3)&0x1f;
	
	r>>=1;
	g>>=1;
	b>>=1;
	
	*screen = (r<<11)|(g<<6)|(b<<1)|0;  
}

void console::set(int px,int py,u32 sx,u32 sy)
{	this->sx = sx; this->sy = sy;
	sxpx = sx*8; sypx = sy*9;
	
	if(px<0) px=(320-sxpx)>>1; // if pos is not valid, center the output
	if(py<0) py=(240-sypx)>>1;

	this->px = px;
	this->py = py;

	bufferSize = bufferFree = (sx+16)*sy*128; // alloc memory for 128 text pages and a 4ko temp
	    buffer	= (char*)malloc(bufferSize + 4096);
		temp	=   buffer + bufferSize;
	memset(buffer,0,bufferSize + 4096);
	x=y=bufferUsed=scroll=0; showCursor=1;
	currentChar = currentLine = buffer;
	textcolor = 0, linefill=0; newline=1;
	//Gdl_showMsg("set %i.%i %i.%i %i",px,py,sx,sy,bufferSize);
}

void console::draw(void)
{	u32 cpty=0;	char * bf = buffer+(sx+16)*scroll;
	u32 bpy = py;
	clDeep clr = currentTextColor;
	static clDeep color = currentTextColor;
	currentTextColor = color;
	alphaZone(px,py-4,sxpx,sypx+4);
	
	//mkprints(10,30,"scroll %i linefill %i",scroll,linefill);
	
	while((cpty < sy) && (cpty <= linefill))
	{	if(*bf) drawString(px,bpy,bf);
	    // else blit_string(px,bpy,"-- empty --");
		bf += sx+16; bpy += lineSpace;
		cpty++;
	};
	
	color = currentTextColor;
	currentTextColor = clr;
}

void console::jumpLine(void)
{	*currentChar = 0;
	//currentLine[sx]=0;
	currentLine += sx+16;
	currentChar  = currentLine;
	y++; x=0;
	if(newline)
			{	linefill++;
				if(linefill <= sy) scroll=0;
				 else scroll = (linefill-sy);
			}
	newline=1;
}



void console::print(const char * format, ...) // import text size can up to 4ko
{	va_list va;
	va_start(va, format);
	vsprintf(temp,format,va);
	va_end(va);
	//Gdl_showMsg("%i %s",strlen(temp),temp);
	char * c = temp;
	while(*c)
	{	if(*c == '@')
		{	if(c[1] == '@') *currentChar++ = *c++;
			*currentChar++ = *c++;
			*currentChar++ = *c++;
		}
		if(*c == '\n') jumpLine();
		  else
		{	if(newline)
			{	newline=0; linefill++;
				if(linefill <= sy) scroll=0;
				 else scroll = (linefill-sy);
			}
			*currentChar++ = *c;
			if(++x >= sx && (c[1]!='\n' && c[1])) jumpLine();
		}
		c++;
	};
	*currentChar=0;
}
