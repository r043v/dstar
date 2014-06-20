
/* Gdl² - dstar */

#include "../Gdl/Gdl.h" // the lib..

  // include gfx
#include "./gfx/greenfont.h"
#include "./gfx/tset.h"
#include "./gfx/star.h"
#include "./gfx/boom.h"
#include "./gfx/ball.h"
#include "./gfx/hp.h"
#include "./gfx/title.h"
#include "./gfx/refresh.h"
#include "./map.h"	// levels

#include "./sfx/cysa.xm.h" // song
//#include "./sfx/data.rar.h"

u32 *titleGfx;
u32 isSongMute=0;

// uncrunch data...
void uncrunchData(void)
{	// uncrunch gfx from 4b gfm to 32b gfm
	unCrunchGfm(greenfont,greenfontFrmNb);
	unCrunchGfm(tset,tsetFrmNb);
	unCrunchGfm(star,starFrmNb);
	unCrunchGfm(boom,boomFrmNb);
	unCrunchGfm(ball,ballFrmNb);
	unCrunchGfm(hp,hpFrmNb);
	unCrunchGfm(refresh,1);
	titleGfx = data2Gfm(title0);
}

clDeep *pink ;
void loadMap(int nb);
int *map, starNb ;
const char *info = "welcome into dstar :D ... use cross to move, ctrl to flip, fin to choose map, space to restart and esc to exit" ;

#define leftColor  0xff
#define rightColor 0
clDeep * wave = 0;
u32 fps = 0;

u32 hideScreen(void)
{	static u32 cpt=0;
	clDeep * scr = pixel;
	for(u32 y=0;y<HEIGHT;y+=2)
	{	clDeep * s = &scr[((WIDTH-1)-cpt)+WIDTH];
		memset(scr,leftColor,cpt*4);
		memset(s,rightColor,cpt*4);
		scr += WIDTH*2;
	};

	if(cpt > (WIDTH>>1))
	{	saveBlitLimit();
		setBlitLimit(WIDTH-cpt,0,cpt,HEIGHT-1);
		cdrawGfm(titleGfx);
		loadBlitLimit();
	}

	cpt += 320/fps;// 8;
	if(cpt >= WIDTH) { cpt=0; return 1; } return 0;
}

u32 showScreen(void)
{	static int cpt=WIDTH;
	clDeep * scr = pixel;
	for(u32 y=0;y<HEIGHT;y+=2)
	{	clDeep * s = &scr[((WIDTH-1)-cpt)+WIDTH];
		memset(scr,leftColor,cpt*4);
		memset(s,rightColor,cpt*4);
		scr += WIDTH*2;
	};

	if(cpt > (int)(WIDTH/2))
	{	saveBlitLimit();
		setBlitLimit(WIDTH-cpt,0,cpt,HEIGHT-1);
		cdrawGfm(titleGfx);
		loadBlitLimit();
	}

	cpt -= 320/fps;//6;
	if(cpt <= 0) { cpt=WIDTH; return 1; } return 0;
}

void chooseMap(int *nb=0)
{ int choose=0xffff, c,l,s ,limit=4, startx,starty,nbl, cantMove=0  ;
  static int *save = 0 ; int select=*nb ; char text[42] ;

  if(mapNb > 150) limit=15 ;
   else if(mapNb > 91) limit = 10 ;

  nbl = mapNb / limit ; if(mapNb%limit) nbl++ ;
  startx = 130 + ( ( 190 - (limit*12) )>>1 ) ;
  starty =((240 - (nbl*12))>>1) ;

  sprintf(text,"puzzle %i",select+1) ;

 while(choose == 0xffff)
 { c=0 ; l=starty ;
   memset(pixel,0,326*256*4);

   ligne(130,9,130,230,pink);
   ligne(132,230,132,9,pink);
   while(mapNb - c > 0)
    { if(mapNb - c > limit) // draw a full line
       { s=startx ;
         for(int t=c;t<limit+c;t++) { drawGfm(ball[t == select],s,l) ; s+=12 ; }
          l += 12 ; c+=limit ;
       } else {  // or an incomplete line
            s=startx ;
            while(mapNb - c > 0) { drawGfm(ball[c==select],s,l) ; c++ ; s+=12 ; }
       }
    };
      int tile,x,y ;
    for(c=0;c<20;c++) // draw map preview
     for(l=0;l<15;l++)
        { tile = (mapArray[select])[20*l+c] ; x = c<<2; y = l<<2;
          if(tile) { clDeep *t = &(pixel[(x+32)+(y+42)*336]);
                     int color = 0 ;
                     if(tile < 3) color = 0xff00ff ; // wall color
                      else if(tile == 3) color = 0xffffff; // star color
                            else if(tile < 6) color = 0xfafa22; // bloc and rock
                     if(color){ *t = color; *(t+336)=color ; *++t=color ; *(t+336)=color ; }
                   }
        };

// 336,256); 

	 if(cantMove) cantMove-- ;
        else      { int old = select ;
                    if(keyArray[kright])  { if(select < mapNb - 1) select++ ;            } else
                     if(keyArray[kleft])  { if(select) select-- ;                       } else
                      if(keyArray[kdown]) { if(select + limit < mapNb) select+=limit ; } else
                       if(keyArray[kup])  { if(select > limit - 1) select-=limit ;    }
                        cantMove = (select!=old)<<3 ;
                        if(cantMove) sprintf(text,"puzzle %i",select+1) ;
                  }
      if(keyArray[kenter]) choose=select ;
      else if(keyArray[kspace]) return;

      drawText(text,42,116) ;

        Gdl_flip();
 };  loadMap(select) ; *nb = select ;
}

struct anim * anm[2] ;
#define objNb 42*2
#define animAr anm
#define animNb 1
#define rotate  animAr[0]
#define explose animAr[1]

struct object
{ int enable ;
  int canStop, canCatch, canKill, x, y ;
  int canMove, isMove, speed, time, last ;
  struct anim ** anim ; clDeep *Gfm ;
};

struct object *rock=0, *bloc=0, **selected=&bloc ;
struct object obj[objNb] ;
struct anim *explosions, *expls ; int expl[42], explx[42], exply[42], explNb=0 ;

int lastx, lasty; // last current object position, for count move
u32 moveCount = 0;

void startMove(void)
{	lastx = (*selected)->x;
	lasty = (*selected)->y;
}

void endMove(void)
{	if( (lastx != (*selected)->x) || (lasty != (*selected)->y) ) moveCount++;
}

void addBoom(int x, int y)
{ int t=0; while(expl[t] && t<42) t++ ; // search for an empty
  if(t==42) return ; // 42 max!
  expl[t]=1 ; expls = &(explosions[t]) ; // enable boom :)
  resetAnim(&expls); // and reset anim
  explx[t]=x-24 ; exply[t]=y-24 ; explNb++ ;
}

void delBoom(struct anim **b)
{  struct anim *a = *b ;
   int p = a - explosions ;
   if(p>=0 && p<42) { expl[p]=0 ; explNb-- ; }
}

void delStar(int x, int y)
{ for(int t=0;t<42;t++)
  { if(obj[t].enable == 1) // 1-> star
     if(obj[t].x == x)
      if(obj[t].y == y)
       { obj[t].enable=0 ; starNb-- ; return ; }
  };
}

#define getStar if(*t == 3)\
                 { *t=0 ;\
                   l<<=4; c<<=4;\
                   addBoom(c,l);\
                   delStar(c,l);\
                 }

#define wallOrRock ((*t < 3)||(*selected == rock))

int rockAndBlocColide(void)
{  int rx,ry,bx,by ;
   rx = rock->x ; ry = rock->y ;
   bx = bloc->x ; by = bloc->y ;

   switch((*selected)->isMove)
    { case 0      : return 0 ;        break ;
      case kright : rx+=10 ; bx+=10 ; break ;
      case kdown    : ry+=10 ; by+=10 ; break ;
    };

   rx>>=4 ; ry>>=4 ; bx>>=4 ; by>>=4 ;
   return (rx==bx && ry==by) ;
}

/* - tileset
0 nothing
1 wall1
2 wall2
3 star
4 bloc
5 rock
*/

void loadMap(int nb)
{   int l,y=0,c=300 ;
    while(c--) map[c] = (mapArray[nb])[c]; // loadMap (no memcopy due to char -> int)

    // clear previous game
    memset(obj,0,objNb*sizeof(struct object)) ;
    memset(expl,0,42*4) ;      selected=&bloc ;
    starNb=explNb=moveCount=0 ;

    for(c=0;c<20;c++) // scanMap
     for(l=0;l<15;l++)
      switch(map[20*l+c])
      { case 0 : break ;
        case 3 : // star
         y=0 ; while(obj[y].enable) y++ ;
         obj[y].enable = 1 ; // 1-> star
         obj[y].x = c<<4 ;
         obj[y].y = l<<4 ;
         obj[y].anim = &rotate ;
         obj[y].canCatch = 1 ;
         obj[y].canStop = obj[y].canKill = 0 ;
         starNb++ ;
        break ;
        case 4 : // bloc
         y=0 ; while(obj[y].enable) y++ ;
         obj[y].enable = 2 ; // 2-> bloc
         obj[y].x = c<<4 ;
         obj[y].y = l<<4 ;
         obj[y].isMove = 0 ;
         obj[y].speed = 3 ;
         obj[y].time = 16 ;
         obj[y].Gfm = tset[4] ;
         map[20*l+c] = 0 ;
         *selected = bloc = &(obj[y]) ;
        break ;
        case 5 : // rock
         y=0 ; while(obj[y].enable) y++ ;
         obj[y].enable = 3 ; // 3-> rock
         obj[y].x = c<<4 ;
         obj[y].y = l<<4 ;
         obj[y].isMove = 0 ;
         obj[y].speed = 2 ;
         obj[y].time = 16 ;
         obj[y].Gfm = tset[5] ;
         map[20*l+c] = 0 ;
         rock = &(obj[y]) ;
        break ; default : break ;
      };  while(keyArray[kenter]) Gdl_updateMsg() ;
}

u32 rumble=0;

void showGame(void)
{		u32 tile,x,y,c,l,colide;
		static int infoPos=0, infox=320, infoTime=0;
		
		u32 xMore=8, yMore=0;

		if(rumble)
		{	xMore += (rand()%8)-4;
			yMore += (rand()%8)-4;
			rumble--;

		}

			for(l=0;l<16;l++)  drawGfm(tset[0],xMore-16,(l<<4)+yMore-16); // bg tile
			for(l=0;l<=16;l++) drawGfm(tset[0],WIDTH+xMore-16,(l<<4)+yMore-16); // bg tile
			for(l=1;l<=20;l++) drawGfm(tset[0],(l<<4)+xMore-16,yMore-16);
			for(l=0;l<=20;l++) drawGfm(tset[0],(l<<4)+xMore-16,HEIGHT+yMore-16);
		
			//setBlitLimit(xy2scr(16,16),xy2scr(WIDTH,HEIGHT),16,320+16);

		for(c=0;c<20;c++) // drawMap
			for(l=0;l<15;l++)
			{ tile = map[20*l+c] ; x = (c<<4)+xMore; y = (l<<4)+yMore ;
			  if(tile) drawGfm(tset[0],x,y); // bg tile
			  if(tile < 3) drawGfm(tset[tile],x,y);
			};

        l = starNb ; c=0 ; // drawStars
        while(l && c<(objNb/2))
        { if(obj[c].enable == 1) // 1-> star
           { drawAnim(obj[c].anim,obj[c].x + xMore,obj[c].y + yMore) ; --l ;
           } c++ ;
        };  Animate(&rotate) ; // animate star anim

        l=explNb ; c=0; // drawBoom
        while(l && c<42)
        { if(expl[c]) { expls = &(explosions[c]) ;
                        playAnim(&expls,explx[c]+xMore,exply[c]+yMore); --l ;
                      } c++ ;
        };

         if(bloc) drawGfm(tset[4],bloc->x + xMore,bloc->y + yMore) ; // draw bloc
         if(rock) drawGfm(tset[5],rock->x + xMore,rock->y + yMore) ; //  and rock
        drawGfm((*selected)->Gfm,20,HEIGHT-18) ; // draw curent obj

        { drawText(&(info[infoPos]),infox,HEIGHT-12) ; // draw info text
          if(--infox < 193) { infox=200 ; if(!info[++infoPos]){ infoPos=0 ; infox=320 ; } } // move text start (in screen and/or in text)
          drawGfm(tset[5],12*16,HEIGHT-16); // draw a tile, for hide text stop zone 12*16
        }

		if(curentMixBf) // show music
		{	int*color = (int*)curentMixBf,x,y=HEIGHT-8;
			u32 drawStart = 20;
			u32 drawSize  = 170;
			if(color)
			{	static u32 oldWidth = 0 ; static int wratio,hratio ;
				if(WIDTH!=oldWidth)	{	wratio = (curentMixSz<<15)/(WIDTH-drawSize);
										if(HEIGHT<255)	hratio = (127<<16)/((HEIGHT>>1) + 300);
										else			hratio = (((HEIGHT>>1)-100)<<16)/127;	
										oldWidth=WIDTH;
									}
					for(u32 n=0;n<WIDTH-drawSize;n++)
						{	x = (n*wratio)>>16 ;
							x = (color[x]>>23) ;
							x = (x*hratio)>>16 ;
							x = y+x ; if(x<0)x=0; else if(x>=(int)HEIGHT) x=HEIGHT-1;
							ligne(n+drawStart,y,n+drawStart,x,wave+32);
						};
			}
		}

		// show control button
		drawGfm(*refresh,2,HEIGHT-16); /* draw 'refresh word' gfx */
		drawGfm(hp[isSongMute],WIDTH-18,HEIGHT-16); /* draw song on/off gfx */

		prints(10,10,"move : %i",moveCount);

		// move or stop curent object..

		if((*selected)->isMove) // if current bloc move
        { colide = rockAndBlocColide() ;
          c = (*selected)->x ; l = (*selected)->y ; int *t ;
          switch((*selected)->isMove)
          { case kleft : // left
             c>>=4 ; l>>=4 ; t=&(map[20*l+c]) ;
             if(*t || colide)
             { if(colide || wallOrRock) { (*selected)->isMove = 0 ;
                            (*selected)->x = (c+1)<<4 ; endMove();
                          } else getStar
             } else { (*selected)->x -= (*selected)->speed ;
                    }
            break ;
            case kdown : // up
             l+=14 ; c>>=4 ; l>>=4 ; tile=l ; t=&(map[20*l+c]) ;
             if(*t || colide)
             { if(colide || wallOrRock) { (*selected)->isMove = 0 ;
                            (*selected)->y = (tile-1)<<4 ; endMove();
                          } else getStar
             } else { (*selected)->y += (*selected)->speed ;
                    }
            break ;
            case kright : // right
             c+=14 ; c>>=4 ; l>>=4 ; t=&(map[20*l+c]) ;
             if(*t || colide)
             { if(colide || wallOrRock) { (*selected)->isMove = 0 ;
                            (*selected)->x = (c-1)<<4 ; endMove();
                          } else getStar
             } else { (*selected)->x += (*selected)->speed ;
                    }
            break ;
            case kup : // down
             c>>=4 ; l>>=4 ; tile=l ; t=&(map[20*l+c]) ;
             if(*t || colide)
             { if(colide || wallOrRock) { (*selected)->isMove = 0 ;
                            (*selected)->y = (tile+1)<<4 ; endMove();
                          } else getStar
             } else { (*selected)->y -= (*selected)->speed ;
                    }
            break ;
          };
        }
}

int curMap;

// on mouse click event...
void onClick(int button, int value)
{  if(button<0 && !value) // left click end
   {	
		// clic on 'refresh'
		if(mousex < 18 && mousey >= HEIGHT-16)
		{	loadMap(curMap);
			rumble = 25;
			ptc_wizz(10);
			return;
		}

		// clic on the 'speaker' button
		if(mousex > WIDTH-18 && mousey >= HEIGHT-16)
		{	if(isSongMute)
			{	isSongMute=0;
				FMUSIC_setWantedVolume(32);
			} else	{ isSongMute=1;
					  FMUSIC_setWantedVolume(0);
					}

			return;
		}
   }
}


int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)

{
  /* open framebuffer */
	Gdl_init("[dstar] by ferof/dph",336,256);   // init the framebuffer
	Gdl_iniCallback( 0,&onClick,0,0,0,0,0,0);

  /* uncrunch sfx/song and gfx */
	uncrunchData();

  /* launch song playback */
	if(!Gdl_playSong("dstar.rar|song.xm"))
	 if(!Gdl_playSong("song.xm"))
	  Gdl_playSong(cysa,cysaSize);

  /* set default font */
	setGdlfont(greenfont);

  /* - - - - - - - - - - - - - - - - - - - */

	wave = (clDeep*)malloc(2048*4);
	{	for(u32 c=0;c<1024;c++)
		{	int red = 0x6b+c; if(red>0xff) red = 0xff;
			wave[c] = (red<<16)|(0x2b<<8)|0xc6 ;
		};
	}

	int c, infoPos=0, infox=320, infoTime=0;

	map = (int*)malloc(2048);//25*15*4) ;
    pink = (clDeep*)malloc(512*4);
    explosions = (struct anim *)malloc(42*sizeof(struct anim)) ;

    // init some thing
    for(c=0;c<256;c++) pink[255-c] = c|(c<<16) ; // create a pink graded line
    curMap = 0 ;//rand()%49 ; // choose a random map

     // create anims
    anm[0] = setAnim(star,20,42) ;
	anm[1] = setAnim(boom,16,16,1,delBoom) ;

    for(c=0;c<42;) memcpy(&(explosions[c++]),explose,sizeof(struct anim)) ;

	loadMap(curMap) ; // load first map

	do {  // main game loop       
		while(starNb) // main engine loop
		{	showGame(); // show game and move current block
			static u32 oldFps=0;
			fps = countFps();
			if(fps!=oldFps && fps)
			{	oldFps = fps;
				rock->speed = (fps>>5) + 2;
				bloc->speed = (fps>>4);
			}

			if(keyArray[kesc]) Gdl_exit(1);

			if((*selected)->isMove == 0) // if current bloc can move
			{	static int canFlip = !(keyArray[kctrl]) ;
				 if(keyArray[kright])  (*selected)->isMove = kright ;    else
				  if(keyArray[kleft])  (*selected)->isMove = kleft  ;   else
				   if(keyArray[kdown]) (*selected)->isMove = kdown  ;  else
					if(keyArray[kup])  (*selected)->isMove = kup    ; else
					 if(keyArray[kfin]) chooseMap(&curMap) ;         else
					  if(keyArray[kspace])
					  { loadMap(curMap);
						do { Gdl_updateMsg(); Sleep(1); } while(keyArray[kspace]);
					  }
				if((*selected)->isMove) startMove();
			 if(canFlip && keyArray[kctrl]) { canFlip=0 ; if(*selected == bloc) selected = &rock ; else selected = &bloc ; }
			  else canFlip = !(keyArray[kctrl]) ;
		   }


		   Gdl_flip(); // update window
		}; // engine loop end
	if(curMap++ == 48) curMap=0;
	while(!hideScreen()) {  Gdl_flip(); showGame(); } // hide game screen
	loadMap(curMap); // load next map
	while(explNb) showGame(); // wait for all boom to finish..
	while(!showScreen()) {  Gdl_flip(); showGame(); } // show new game screen
  } while(1);

	return 0;
}
