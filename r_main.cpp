#include "SDL.h"
#include "SDL_TTF.h"
#include <SDL_image.h>
#include <SDL_gfxPrimitives.h>

/*
C&C -clone by Juharts 2007



*/
SDL_Surface *naytto, *hiiri,*kuva[255][4],*tausta[15],*land[255],*talo[31],*panel; // Pinnat
SDL_Surface *kohde,*bg,*icon[51][1];
SDL_Event tapahtuma;  //Tapahtumat 
int pois = 0;
int hiiriX;
int hiiriY;
int napit;
int i=0;
int c=0;
int bc=0;
int ukot=5;

bool unitconst=true;

const int unitSize=32;
const int tankSize=141;
const int palikoita=49;
const int puut=14;
const int IconSize=52;
const int nurtsi=4999;

int ScrollSpeed=5;


struct soldier
{
	int x;
	int y;
	int hp;
	int frame;
	int orders;
	int dx;
	int dy;
	int TYPE;
	bool deploy;
}
;

struct building
{
	int x;
	int y;
	int hp;
	int orders;
	int size;
	int TYPE;
}
;
struct ground
{
	int x;
	int y;
}
;
struct accessory
{
	int x;
	int y;
}
;
struct ikoni
{
	int x;
	int y;
	int TYPE;
	int maxtime;
	int time;
}
;
struct ruoho
{
	int x;
	int y;
	
}
;

soldier Sotilaat[127];
building talot[100];
ground grass[puut];
accessory accessories[palikoita];
ikoni ICON[51];
ruoho nurmikko[nurtsi];

void LiikuKohteeseen(int dx,int dy,int x,int y,int i)
{
	if(x>dx)
	Sotilaat[i].x--;
	if(x<dx)
	Sotilaat[i].x++;
	if(y>dy)
	Sotilaat[i].y--;
	if(y<dy)
	Sotilaat[i].y++;

}

void ScrollMap()
{
	if(hiiriX==0)
	{
		for(int i=0;i<bc;i++)
		{
			talot[i].x=talot[i].x+ScrollSpeed;
		}
		for(i=0;i<palikoita;i++)
		{
			accessories[i].x=accessories[i].x+ScrollSpeed;
		}

		for(int j=0;j<ukot-1;j++)
		{
			Sotilaat[j].x=Sotilaat[j].x+ScrollSpeed;
			Sotilaat[j].dx=Sotilaat[j].dx+ScrollSpeed;
		}
		
		for(int v=0;v<puut;v++)
		{
			grass[v].x=grass[v].x+ScrollSpeed;
		}
		for(int o=0;o<nurtsi;o++)
		{
			nurmikko[o].x=nurmikko[o].x+ScrollSpeed;
		}
		
	}
	if(hiiriX>1022)
	{
		
		for(int i=0;i<bc;i++)
		{
			talot[i].x=talot[i].x-ScrollSpeed;
		}
        for(i=0;i<49;i++)
		{
			accessories[i].x=accessories[i].x-ScrollSpeed;
		}
		for(int j=0;j<ukot-1;j++)
		{
			Sotilaat[j].x=Sotilaat[j].x-ScrollSpeed;
			Sotilaat[j].dx=Sotilaat[j].dx-ScrollSpeed;
		}
		for(int v=0;v<puut;v++)
		{
			grass[v].x=grass[v].x-ScrollSpeed;
		}
		for(int o=0;o<nurtsi;o++)
		{
			nurmikko[o].x=nurmikko[o].x-ScrollSpeed;
		}
		
	}
	if(hiiriY==0)
	{
		for(int i=0;i<bc;i++)
		{
			talot[i].y=talot[i].y+ScrollSpeed;
		}
        for(i=0;i<49;i++)
		{
			accessories[i].y=accessories[i].y+ScrollSpeed;
		}
		for(int j=0;j<ukot-1;j++)
		{
			Sotilaat[j].y=Sotilaat[j].y+ScrollSpeed;
			Sotilaat[j].dy=Sotilaat[j].dy+ScrollSpeed;
		}
		for(int v=0;v<puut;v++)
		{
			grass[v].y=grass[v].y+ScrollSpeed;
		}
		for(int o=0;o<nurtsi;o++)
		{
			nurmikko[o].y=nurmikko[o].y+ScrollSpeed;
		}
	}
	if(hiiriY>766)
	{
		for(int i=0;i<bc;i++)
		{
			talot[i].y=talot[i].y-ScrollSpeed;
		}

        for(i=0;i<49;i++)
		{
			accessories[i].y=accessories[i].y-ScrollSpeed;
		}

		for(int j=0;j<ukot-1;j++)
		{
			Sotilaat[j].y=Sotilaat[j].y-ScrollSpeed;
			Sotilaat[j].dy=Sotilaat[j].dy-ScrollSpeed;
		}
		for(int v=0;v<puut;v++)
		{
			grass[v].y=grass[v].y-ScrollSpeed;
		}
		for(int o=0;o<nurtsi;o++)
		{
			nurmikko[o].y=nurmikko[o].y-ScrollSpeed;
		}
	}




}
void RakennuksenToiminta(int i)
{

if(napit && SDL_BUTTON(1) && hiiriX>talot[i].x && hiiriX<talot[i].x+tankSize && hiiriY>talot[i].y && hiiriY<talot[i].y+tankSize)
	   {
        if(unitconst==true)
		{
		talot[i].orders=1;
		
        
		 kuva[c][0]=SDL_LoadBMP("alfred.bmp");
	
	     kuva[c][1]=SDL_LoadBMP("alfredV.bmp");
	    //SDL_SetColorKey(kuva[0][0], SDL_SRCCOLORKEY, SDL_MapRGB(kuva[0][0]->format,0,0,0));

        Sotilaat[c].x=talot[i].x+(talot[i].x/2);
        Sotilaat[c].y=talot[i].y+(talot[i].y/2);
        Sotilaat[c].orders=0;
		Sotilaat[c].dx=0;
        Sotilaat[c].dx=0;
		c++;
		ukot++;
		unitconst=false;
		}
	   } 

 

}

void PiirraKuva(SDL_Surface *kuva, SDL_Surface *naytto, int x, int y)
{
  SDL_Rect alue; // mille alueellä näyttöä kuva piirretään
  alue.x = x; // koordinaatit
  alue.y = y;
  SDL_BlitSurface(kuva, NULL, naytto, &alue); // piirto
}

void PiirraKuvaEX(SDL_Surface *kuva, SDL_Surface *naytto, int kuvax, int kuvay, int leveys, int korkeus, int nayttox, int nayttoy)
{
    SDL_Rect kuvaalue; // alue, mikä kuvasta piirretään
    kuvaalue.x = kuvax;
    kuvaalue.y = kuvay;
    kuvaalue.h = korkeus;
    kuvaalue.w = leveys;

    SDL_Rect nayttoalue; // alue näytöllä, jolle kuva piirretään
    nayttoalue.x = nayttox;
    nayttoalue.y = nayttoy;

    SDL_BlitSurface(kuva, &kuvaalue, naytto, &nayttoalue);
}


int main( int argc, char* argv[] )
{
	bool construction=true;
  

  SDL_Init(SDL_INIT_VIDEO);  
    naytto = SDL_SetVideoMode(1024, 768, 32, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN);
    SDL_WM_SetCaption("Riskzation", NULL); 
    TTF_Init();
	 TTF_Font* font = TTF_OpenFont("armalite.ttf", 16);

   SDL_Color foregroundColor = { 0, 0, 255 };


   SDL_Surface* textSurface = TTF_RenderText_Solid(font, "Game Menu",
      foregroundColor);
 SDL_Rect textLocation = { 900, 10, 0, 0 };
   
  

	for(int l=0;l<puut;l++)//taustamaa,lagaa,keksi jotain
	{
		if(l%2==0)
			tausta[l]=IMG_Load("mud.jpg");
		else
     tausta[l]=IMG_Load("lolpuu.jpg");

     grass[l].x=rand()%1000-500;
	 grass[l].y=rand()%1000-500;
	}
    for(int s=0;s<50;s++)
	{
		land[s]=IMG_Load("kivi.jpg");
		accessories[s].x=s*75;
		accessories[s].y=rand()%1000-500;
       
	}
	 panel=SDL_LoadBMP("panel.bmp");//paneeli
	 kohde=IMG_Load("slash.jpg");
	 bg=IMG_Load("ruoho2f.jpg");
 for(int f=1;f<ukot;f++)//alkusoltut
 {
	 kuva[0][0]=SDL_LoadBMP("mcv.bmp");
     kuva[0][1]=SDL_LoadBMP("mcv.bmp");

	 kuva[f][0]=SDL_LoadBMP("alfred.bmp");
	
	 kuva[f][1]=SDL_LoadBMP("alfredV.bmp");

	Sotilaat[0].x=100;
	Sotilaat[0].y=100;
	Sotilaat[0].dx=100;
	Sotilaat[0].dy=100;
	Sotilaat[0].TYPE=1;
	Sotilaat[0].orders=0;
    Sotilaat[f].x=100+f*100;
    Sotilaat[f].y=100+f*100;
    Sotilaat[f].orders=0;
	Sotilaat[f].dx=100+f*100;
    Sotilaat[f].dy=100+f*100;
	c++;
 }
   talot[0].x=100;
   talot[0].y=100;
   talot[0].TYPE=1;
   talo[0]=SDL_LoadBMP("hq.bmp");
   
   bc++;
 for(int o=0;o<nurtsi;o++)
   {
	   nurmikko[o].x=rand()%4000-2000;
	   nurmikko[o].y=rand()%4000-2000;
   }

while(pois == 0) 
{ 
	
    if(i==ukot-1)
		i=0;

	 SDL_PollEvent(&tapahtuma); 
			
		napit=SDL_GetMouseState(&hiiriX, &hiiriY);
		 SDL_FillRect(naytto, NULL, SDL_MapRGB(naytto->format, 0, 100, 0));
	//	 PiirraKuva(bg,naytto,0,0);
	
	  if(napit && SDL_BUTTON(1) && Sotilaat[i].orders==1)
	   {
		Sotilaat[i].dx=hiiriX;
		Sotilaat[i].dy=hiiriY;
		
		PiirraKuva(kohde,naytto,hiiriX,hiiriY);
        

	   }
       if(napit && SDL_BUTTON(1) && hiiriX>Sotilaat[i].x && hiiriX<Sotilaat[i].x+unitSize && hiiriY>Sotilaat[i].y && hiiriY< Sotilaat[i].y+unitSize)
	   {
        

		Sotilaat[i].orders=1;
		 construction=true;
		 unitconst=true;
		 
        
	   } 
	   if(napit & SDL_BUTTON(3))
	   {
      
		Sotilaat[i].orders=0;
		      
	   } 
	   if(napit & SDL_BUTTON(2))
	   {
        if(construction==true)
		{
		talot[bc].x=hiiriX;
		talot[bc].y=hiiriY;
		talo[bc]=SDL_LoadBMP("tehas.bmp");
	
		bc++;
		construction=false;
		} 
	   } 
         for(int b=0;b<nurtsi;b++)
		 {
			if(b>(nurtsi/2))
				pixelRGBA(naytto,nurmikko[b].x,nurmikko[b].y,0,190,0,255);
			else
                pixelRGBA(naytto,nurmikko[b].x,nurmikko[b].y,0,255,0,255);
		 }

	         for(int v=0;v<puut;v++)
			 {
			  PiirraKuva(tausta[v],naytto,grass[v].x,grass[v].y); 
			 }
			  
			  for(int f=0;f<bc;f++)
			  {
			   PiirraKuva(talo[f],naytto,talot[f].x,talot[f].y);
			   SDL_SetColorKey(talo[f], SDL_SRCCOLORKEY, SDL_MapRGB(talo[f]->format,0,0,0));
			   if(talot[f].TYPE==0)
			   RakennuksenToiminta(f);
			  }
			   
			  for(int h=0;h<49;h++)
			  {
                PiirraKuva(land[h],naytto,accessories[h].x,accessories[h].y);
			  }

	   	 for(int a=0;a<ukot-1;a++)
		 {
			 
			   LiikuKohteeseen(Sotilaat[a].dx,Sotilaat[a].dy,Sotilaat[a].x,Sotilaat[a].y,a);
				
			   if(Sotilaat[a].orders==1)
			   {
                 PiirraKuva(kuva[a][1],naytto,Sotilaat[a].x,Sotilaat[a].y);
			     SDL_SetColorKey(kuva[a][1], SDL_SRCCOLORKEY, SDL_MapRGB(kuva[a][1]->format,0,0,0));
			   }
			   if(Sotilaat[a].orders==0)
			   {
				 PiirraKuva(kuva[a][0],naytto,Sotilaat[a].x,Sotilaat[a].y);
			     SDL_SetColorKey(kuva[a][0], SDL_SRCCOLORKEY, SDL_MapRGB(kuva[a][0]->format,0,0,0));
			   }

			  
		 }
		 ScrollMap();
		 PiirraKuva(panel,naytto,1024-180,0);
		 SDL_BlitSurface(textSurface, NULL, naytto, &textLocation);
				SDL_Flip(naytto);
          
				if ( tapahtuma.type == SDL_QUIT )  {  pois = 1;  }
				if ( tapahtuma.type == SDL_KEYDOWN )  {
					if ( tapahtuma.key.keysym.sym == SDLK_ESCAPE ) { pois = 1; }
				}
			 
  i++;
 
 }
 SDL_Quit();
 TTF_Quit();
  return 0;
}
