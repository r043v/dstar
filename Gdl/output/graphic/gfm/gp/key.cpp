
#ifndef _gdlkey_
#define _gdlkey_

#include "Gdl.h"

#ifndef GP32

u8 *keyArray = 0 ;
u8 *lastKey = 0 ;

void inikey(void)
{	if(!keyArray)
		{	keyArray = (u8*)malloc(keyArraySize*2);
			lastKey = keyArray+keyArraySize;
		}
	memset(keyArray,0,keyArraySize*2);
}

u32 keyUp(u32 key)
{	if(key>255) { memset(lastKey,0xff,256); return 0; }
	u32 up=0;
	up = (keyArray[key] && lastKey[key]==0);
	lastKey[key] = keyArray[key] ;
	return up;
}

u32 keyPush(u32 key)
{	if(key>255) { memset(lastKey,0xff,256); return 0; }
	return keyArray[key];
}

#else

u8  *kptr = (u8*)0x1560000d; // cross, a, b, l and r
u8 *skptr = (u8*)0x15600030; // start and select

/*	b4 10110100 select 0x80 128
	74 01110100 start  0x40 64
	34 00110100
*/

void inikey(void)
{	rPBCON=0x0;
}

u32 keyPush(u32 key)
{	if(key < 256)	return ((~*kptr)&key)==key;
	 else
	{	if(key == kstart || key == kselect)
			return (u32)~*skptr == key>>2;
		u16 k = ~(*kptr|(((*skptr)>>6)<<8));
		return (k&key)==key;
	}
}

u32 keyUp(u32 key)
{	static	u32 old = 0;
	if(key<256) // A, B, L, R and cross
		{	if((~*kptr)&key)
			{	if(old&key)		return 0;
				old |= key;		return 1;
			} 	old &= ~key;	return 0;
		}
	 else // start and select
		{	if(~*skptr & (key>>2))
			{	if(old&key)		return 0;
				old |= key;		return 1;
			}	old &= ~key;	return 0;
		}
}

#endif

// 06 13 94 02 90 rapten brother #1
//

#endif
