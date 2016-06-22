/*

C&C - clone primitve drawing
(c) Juharts 2007

*/
#include <SDL.h>
#include <SDL_gfxPrimitives.h>



void GenerateGrass(SDL_Surface *dst,int x[2499],int y[2499])
{


	for(int i=0;i<2500;i++)
	{
		
		pixelRGBA(dst,x[i],y[i],0,255,0,255);

	}
        

}